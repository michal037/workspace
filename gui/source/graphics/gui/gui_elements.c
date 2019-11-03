/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "gui_elements.h"
#include "../display.h"
#include "../../system/onewaylist.h"
#include "gui.h"
#include "misc.h"

public void gui_initialize_element(void *element, ENUM_GUI_ELEMENT_TYPE element_type)
{
    /* Convert pointer */
    UNION_GUI_ELEMENT_POINTER_CONVERSION union_gui_el_ptr_conv;
    union_gui_el_ptr_conv.unknown = element;

    /* Choose element and set defaults */
    switch(element_type)
    {
        /* Element is button */
        case ENUM_GUI_ELEMENT_TYPE_BUTTON:
        {
            GUI_Button *button = union_gui_el_ptr_conv.button;
            /* Type */
            button->element_type = ENUM_GUI_ELEMENT_TYPE_BUTTON;
            /* Position */
            button->pos.x = button->pos.y = 0;
            /* Dimensions */
            button->dim.width = button->dim.height = 1;
            button->border_width = 0;
            /* Mouse states */
            button->mstate = ENUM_GUI_ELEMENT_STATE_MOUSE_NORMAL;
            button->mstate_normal.color = button->mstate_normal.border_color = al_map_rgb(0,0,0);
            button->mstate_hover = NULL;
            button->mstate_click = NULL;
            button->mstate_dclick = NULL;
            button->mstate_last.state = button->mstate; /* State: normal */
            button->mstate_last.Timer1 = 0; /* Default timer is stopped */
            /* Mouse callbacks */
            button->callbacks.hover = button->callbacks.click = button->callbacks.dclick = NULL;
            /* Button title */
            button->element_title = NULL;
        }break;
        default: break;
    }

} /* gui_initialize_element */

public void gui_draw_element(void *element)
{
    /* Convert pointer */
    UNION_GUI_ELEMENT_POINTER_CONVERSION union_gui_el_ptr_conv;
    union_gui_el_ptr_conv.unknown = element;

    /* Get main display */
    al_set_target_bitmap(al_get_backbuffer(display_main));

    /* Draw button */
    if(union_gui_el_ptr_conv.button->element_type == ENUM_GUI_ELEMENT_TYPE_BUTTON)
    {
        GUI_Button *button = union_gui_el_ptr_conv.button;

        switch((button->mstate_last.Timer1>0)? button->mstate_last.state : button->mstate)
        {
            case ENUM_GUI_ELEMENT_STATE_MOUSE_NORMAL:
            {
                al_draw_filled_rectangle(button->pos.x, button->pos.y, button->pos.x + button->dim.width,
                                         button->pos.y + button->dim.height, button->mstate_normal.color);
                /* Border */
                if(button->border_width > 0)
                { al_draw_rectangle(button->pos.x + 0.5, button->pos.y + 0.5, button->pos.x + button->dim.width,
                                             button->pos.y + button->dim.height, button->mstate_normal.border_color,
                                             button->border_width);
                }
            }break;

            case ENUM_GUI_ELEMENT_STATE_MOUSE_HOVER:
            {
                /* Skip if pointer is NULL */
                if(button->mstate_hover == NULL) break;
                al_draw_filled_rectangle(button->pos.x, button->pos.y, button->pos.x + button->dim.width,
                                         button->pos.y + button->dim.height, button->mstate_hover->color);
                /* Border */
                if(button->border_width > 0)
                { al_draw_rectangle(button->pos.x + 0.5, button->pos.y + 0.5, button->pos.x + button->dim.width,
                                      button->pos.y + button->dim.height, button->mstate_hover->border_color,
                                      button->border_width);
                }
            }break;

            case ENUM_GUI_ELEMENT_STATE_MOUSE_CLICK:
            {
                /* Skip if pointer is NULL */
                if(button->mstate_click == NULL) break;

                al_draw_filled_rectangle(button->pos.x, button->pos.y, button->pos.x + button->dim.width,
                                         button->pos.y + button->dim.height, button->mstate_click->color);
                /* Border */
                if(button->border_width > 0)
                { al_draw_rectangle(button->pos.x + 0.5, button->pos.y + 0.5, button->pos.x + button->dim.width,
                                      button->pos.y + button->dim.height, button->mstate_click->border_color,
                                      button->border_width);
                }
            }break;

            case ENUM_GUI_ELEMENT_STATE_MOUSE_DCLICK:
            {
                /* Skip if pointer is NULL */
                if(button->mstate_dclick == NULL) break;

                al_draw_filled_rectangle(button->pos.x, button->pos.y, button->pos.x + button->dim.width,
                                         button->pos.y + button->dim.height, button->mstate_dclick->color);
                /* Border */
                if(button->border_width > 0)
                { al_draw_rectangle(button->pos.x + 0.5, button->pos.y + 0.5, button->pos.x + button->dim.width,
                                      button->pos.y + button->dim.height, button->mstate_dclick->border_color,
                                      button->border_width);
                }
            }break;

            default: break;
        }
    }
} /* gui_draw_element */

public void gui_mouse_on_element_collisions(OWL_List *list, ALLEGRO_EVENT *mouse_ev, MOUSE_EV_TYPE mouse_ev_type, uint8 mouse_click_count)
{
    /* Convert pointer */
    UNION_GUI_ELEMENT_POINTER_CONVERSION union_gui_el_ptr_conv;

    OWL_Node *currentNode = list->head;

    /* Check all GUI elements */
    while(currentNode != NULL)
    {
        union_gui_el_ptr_conv.unknown = currentNode->data;

        /* if current element from list is button */
        if(union_gui_el_ptr_conv.button->element_type == ENUM_GUI_ELEMENT_TYPE_BUTTON)
        {
            GUI_Button *button = union_gui_el_ptr_conv.button;

            /* Check collision, else set Mouse State as Normal */
            if(is_collision(mouse_ev->mouse.x, mouse_ev->mouse.y, button->pos.x,
                            button->pos.y, button->dim.width, button->dim.height))
            {
                switch(mouse_ev_type)
                {
                    case MOUSE_AXES:
                        button->mstate = ENUM_GUI_ELEMENT_STATE_MOUSE_HOVER;
                        if(button->callbacks.hover != NULL) button->callbacks.hover();
                        break;

                    case MOUSE_BUTTON_DOWN: // TODO dodać timer żeby event był widzialny przez pareset ms a nie od razu znikał
                        if(button->callbacks.dclick != NULL  &&  mouse_click_count == 2)
                        {
                            button->mstate = ENUM_GUI_ELEMENT_STATE_MOUSE_DCLICK;
                            button->mstate_last.state = button->mstate;
                            button->mstate_last.Timer1 = 15; /* (15*10 = 150ms) */
                            button->callbacks.dclick();
                        } else if(button->callbacks.click != NULL  &&  mouse_click_count >= 1){
                            button->mstate = ENUM_GUI_ELEMENT_STATE_MOUSE_CLICK;
                            button->mstate_last.state = button->mstate;
                            button->mstate_last.Timer1 = 15; /* (15*10 = 150ms) */
                            button->callbacks.click();
                        }
                        break;

                    case MOUSE_BUTTON_UP: break;
                    default: break;
                }
            } else {
                button->mstate = ENUM_GUI_ELEMENT_STATE_MOUSE_NORMAL;
            }
        }

        /* Go to next element */
        currentNode = currentNode->next;
    }
} /* gui_mouse_on_element_collisions */

public void gui_element_state_mouse_last_tick(void *element)
{
    /* Convert pointer */
    UNION_GUI_ELEMENT_POINTER_CONVERSION union_gui_el_ptr_conv;

    union_gui_el_ptr_conv.unknown = element;

    /* If element is button */
    if(union_gui_el_ptr_conv.button->element_type == ENUM_GUI_ELEMENT_TYPE_BUTTON)
    {
        GUI_Button *button = union_gui_el_ptr_conv.button;

        /* Decrease timer */
        if(button->mstate_last.Timer1) button->mstate_last.Timer1--;
    }
} /* gui_element_state_mouse_last_tick */
