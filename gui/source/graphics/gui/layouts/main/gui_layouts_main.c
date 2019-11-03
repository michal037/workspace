/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "gui_layouts_main.h"
#include "../../../display.h"
#include "../../gui_colors.h"
#include "../../../../system/common.h"
#include "../../misc.h"


/* Layout element list to draw */
OWL_List GUI_Layout_Main;

/* GUI Elements */
GUI_Button button_exit;
GUI_Button button_test1;

void tekst(void){printf("ok");}

public void gui_create_layout_main(void)
{
    /* Initialize list */
    OWL_InitializeList(&GUI_Layout_Main);

    /* Exit button */
    gui_initialize_element(&button_exit, ENUM_GUI_ELEMENT_TYPE_BUTTON); /* Initialize button */
    /* Prepare button */
    button_exit.pos.x = DISPLAY_MAIN_WIDTH - 45;
    button_exit.pos.y = 0;
    button_exit.dim.width = 45;
    button_exit.dim.height = 27;
    button_exit.mstate_normal.color = al_map_rgb(36, 41, 46);
    button_exit.mstate_normal.border_color = al_map_rgb(36, 41, 46);
    button_exit.mstate_hover = safe_Malloc(sizeof(GUI_ELEMENT_STATE_MOUSE_HOVER));
    button_exit.mstate_hover->color = al_map_rgb(228, 0, 41);
    button_exit.mstate_hover->border_color = al_map_rgb(228, 0, 41);
    button_exit.mstate_click = safe_Malloc(sizeof(GUI_ELEMENT_STATE_MOUSE_CLICK));
    button_exit.mstate_click->color = al_map_rgb(187, 0, 35);
    button_exit.mstate_click->border_color = al_map_rgb(187, 0, 35);
    button_exit.callbacks.click = inject_event_display_close;
    OWL_AddTail(&GUI_Layout_Main, &button_exit); /* Add to GUI list */



    gui_initialize_element(&button_test1, ENUM_GUI_ELEMENT_TYPE_BUTTON);
    button_test1.pos.x = 100;
    button_test1.pos.y = 100;
    button_test1.dim.width = 200;
    button_test1.dim.height = 50;
    button_test1.border_width = 1;
    button_test1.mstate_normal.color = al_map_rgb(200, 200, 200);
    button_test1.mstate_normal.border_color = color_black;
    button_test1.mstate_hover = safe_Malloc(sizeof(GUI_ELEMENT_STATE_MOUSE_HOVER));
    button_test1.mstate_hover->color = al_map_rgb(180, 180, 180);
    button_test1.mstate_hover->border_color = color_black;
    button_test1.mstate_click = safe_Malloc(sizeof(GUI_ELEMENT_STATE_MOUSE_CLICK));
    button_test1.mstate_click->color = al_map_rgb(140, 140, 140);
    button_test1.mstate_click->border_color = color_black;
    button_test1.callbacks.click = tekst;
    OWL_AddTail(&GUI_Layout_Main, &button_test1);
} /* gui_create_layout_main */

public void gui_destroy_layout_main(void)
{
    OWL_Node *tempNode = NULL;
    UNION_GUI_ELEMENT_POINTER_CONVERSION union_gui_el_ptr_conv; /* Pointer Conversion Union */

    while(GUI_Layout_Main.head != NULL) /* While list isn't empty */
    {
        tempNode = GUI_Layout_Main.head; /* Get Node */
        GUI_Layout_Main.head = GUI_Layout_Main.head->next; /* List head -> write next */
        union_gui_el_ptr_conv.unknown = tempNode->data; /* Convert pointer */

        /* If current element is button */
        if(union_gui_el_ptr_conv.button->element_type == ENUM_GUI_ELEMENT_TYPE_BUTTON)
        {
            GUI_Button *button = union_gui_el_ptr_conv.button;

            /* Free dynamic allocated memory in button */
            safeFree(button->mstate_hover);
            safeFree(button->mstate_click);
            safeFree(button->mstate_dclick);
            safeFree(button->element_title);
        }

        safeFree(tempNode); /* Free node */
    }

    /* Clear List's pointers */
    GUI_Layout_Main.head = NULL;
    GUI_Layout_Main.tail = NULL;
    GUI_Layout_Main.current = NULL;
} /* gui_destroy_layout_main */
