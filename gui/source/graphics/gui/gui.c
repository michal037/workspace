/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "gui.h"
#include "gui_elements.h"
#include "gui_colors.h"
#include "../../system/engine.h"
#include "../../system/common.h"
#include "../display.h"
#include "misc.h"
#include "../../system/onewaylist.h"
#include "gui_elements.h"
#include "layouts/main/gui_layouts_main.h"


/* Private functions */
private void gui_redraw(void);
private void gui_event_mouse(ALLEGRO_EVENT *ev, MOUSE_EV_TYPE ev_type);
private void gui_event_keyboard(ALLEGRO_EVENT *ev);

/*
 * GUI event queue for timer.
 * Needed for adjusting gui elements.
 * To relieve the main queue.
 */
ALLEGRO_EVENT_QUEUE *event_queue_gui;
ALLEGRO_TIMEOUT event_queue_gui_timeout;
ALLEGRO_EVENT ev_gui;
ALLEGRO_TIMER *guims_tick;

/* GUI state */
struct _gui_state
{
    uint8 redraw_flag;
    uint8 display_sw_InOut;
    uint8 mouse_click_count;
} static guiState = {
        0,
        1,
        0
};

/* Double click variables */
uint8 mouse_doubleclick_timer = 0;
ALLEGRO_MOUSE_EVENT EV_MOUSE_BUTTON_DOWN;

public void gui_tick(ALLEGRO_EVENT *ev, uint8 *ev_main_occurred)
{
    /* Read GUI tick event */
    if(al_wait_for_event_until(event_queue_gui, &ev_gui, &event_queue_gui_timeout))
    {
        switch(ev_gui.type)
        {
            /* TIMER - 10ms resolution */
            case ALLEGRO_EVENT_TIMER:
                /* Mouse double-click checker; MOUSE_BUTTON_DOWN */
                if(mouse_doubleclick_timer) mouse_doubleclick_timer++;
                if(mouse_doubleclick_timer == 46  ||  guiState.mouse_click_count>=2)
                { /* (46-1)*10ms = 450ms */
                    gui_event_mouse(ev, MOUSE_BUTTON_DOWN);

                    /* Reset variables */
                    mouse_doubleclick_timer = 0;
                    guiState.mouse_click_count = 0;
                }

                /* GUI timer for graphic details */
                OWL_DoOnList(&GUI_Layout_Main, gui_element_state_mouse_last_tick);
                break;

            /* The event has not been handled */
            default: break;
        }
    }

    /* Read main event if event occured */
    if(*ev_main_occurred) switch(ev->type)
        {
            /* TIMER */
            case ALLEGRO_EVENT_TIMER:
                guiState.redraw_flag = 1;
                break;

                /* DISPLAY */
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                guiState.display_sw_InOut = 1;
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                guiState.display_sw_InOut = 0;
                break;

                /* MOUSE */
            case ALLEGRO_EVENT_MOUSE_AXES:
                gui_event_mouse(ev, MOUSE_AXES);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                /* Add 1 to mouse counter; Start timer */
                guiState.mouse_click_count++;
                mouse_doubleclick_timer = 1;
                /* Copy event data */
                EV_MOUSE_BUTTON_DOWN.x = ev->mouse.x;
                EV_MOUSE_BUTTON_DOWN.y = ev->mouse.y;
                EV_MOUSE_BUTTON_DOWN.z = ev->mouse.z;
                EV_MOUSE_BUTTON_DOWN.button = ev->mouse.button;
                EV_MOUSE_BUTTON_DOWN.pressure = ev->mouse.pressure;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                gui_event_mouse(ev, MOUSE_BUTTON_UP);
                break;

                /* KEYBOARD */
            case ALLEGRO_EVENT_KEY_DOWN:
                gui_event_keyboard(ev);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                gui_event_keyboard(ev);
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                gui_event_keyboard(ev);
                break;

            /* The event has not been handled */
            default: break;
        }

    /* Redraw */
    if(guiState.redraw_flag && al_is_event_queue_empty(event_queue_main)) gui_redraw();
} /* gui_tick */

private void gui_redraw(void)
{
    /* Clear redraw flag */
    guiState.redraw_flag = 0;

    /* Clear display */
    al_set_target_bitmap(al_get_backbuffer(display_main));
    al_clear_to_color(color_white);

    /* Head */
    al_draw_filled_rectangle(0, 0, DISPLAY_MAIN_WIDTH, 27, color_gray);
    if(guiState.display_sw_InOut)
    {
        al_draw_line(0, 28, DISPLAY_MAIN_WIDTH, 28, color_orange, 1);
    } else {
        al_draw_line(0, 28, DISPLAY_MAIN_WIDTH, 28, color_gray_2, 1);
    }

    /* Draw GUI Elements */
    OWL_DoOnList(&GUI_Layout_Main, gui_draw_element);

    al_flip_display();
} /* gui_redraw */

private void gui_event_mouse(ALLEGRO_EVENT *ev, MOUSE_EV_TYPE ev_type)
{
    ALLEGRO_MOUSE_EVENT tmp_ev_data;

    /* Paste event data */
    if(ev_type == MOUSE_BUTTON_DOWN)
    {   /* For later ease. To use only data from an event.
         * Prepare copy because event is shared in union */
        tmp_ev_data.x = ev->mouse.x;
        tmp_ev_data.y = ev->mouse.y;
        tmp_ev_data.z = ev->mouse.z;
        tmp_ev_data.button = ev->mouse.button;
        tmp_ev_data.pressure = ev->mouse.pressure;
        ev->mouse.x = EV_MOUSE_BUTTON_DOWN.x;
        ev->mouse.y = EV_MOUSE_BUTTON_DOWN.y;
        ev->mouse.z = EV_MOUSE_BUTTON_DOWN.z;
        ev->mouse.button = EV_MOUSE_BUTTON_DOWN.button;
        ev->mouse.pressure = EV_MOUSE_BUTTON_DOWN.pressure;
    }

    /* Respond to mouse collisions with GUI elements */
    gui_mouse_on_element_collisions(&GUI_Layout_Main, ev, ev_type, guiState.mouse_click_count);

    /* Paste event data */
    if(ev_type == MOUSE_BUTTON_DOWN)
    {
        ev->mouse.x = tmp_ev_data.x;
        ev->mouse.y = tmp_ev_data.y;
        ev->mouse.z = tmp_ev_data.z;
        ev->mouse.button = tmp_ev_data.button;
        ev->mouse.pressure = tmp_ev_data.pressure;
    }
} /* gui_event_mouse */

private void gui_event_keyboard(ALLEGRO_EVENT *ev)
{
    KEY_EV_TYPE event_type;

    switch(ev->type)
    {
        case ALLEGRO_EVENT_KEY_DOWN:
            event_type = KEY_DOWN;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            event_type = KEY_UP;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            event_type = KEY_CHAR;
            break;
    }
} /* gui_event_keyboard */

public void gui_init(void)
{
    /* Set colors */
    color_white = al_map_rgb(255, 255, 255);
    color_gray = al_map_rgb(36, 41, 46);
    color_gray_2 = al_map_rgb(20, 23, 26);
    color_black = al_map_rgb(0, 0, 0);
    color_blue = al_map_rgb(14, 107, 208);
    color_orange = al_map_rgb(255, 120, 0);

    /* Create GUI event queue.
     * Needed to GUI timer for adjusting gui elements.
     * To relieve the main queue from events.
     */
    event_queue_gui = al_create_event_queue();
    if(!event_queue_gui)
    {
        print_logs(1, "Failed to create GUI event queue!");
        exit(EXIT_FAILURE);
    }
    al_init_timeout(&event_queue_gui_timeout, 0.001); /* 1ms timeout */

    /* Create timer for adjusting gui elements */
    guims_tick = al_create_timer(0.01); /* 10ms resolution */
    if(!guims_tick)
    {
        print_logs(1, "Failed to create guims_tick timer!");
        exit(EXIT_FAILURE);
    }
    al_register_event_source(event_queue_gui, al_get_timer_event_source(guims_tick));
    /* Start GUI timer */
    al_start_timer(guims_tick);

    /* Create Layouts */
    gui_create_layout_main();
} /* gui_init */

public void gui_exit(void)
{
    /* Destroy Layouts */
    gui_destroy_layout_main();

    /* Destroy guims_tick timer */
    al_destroy_timer(guims_tick);

    /* Destroy GUI event queue */
    al_destroy_event_queue(event_queue_gui);
} /* gui_exit */
