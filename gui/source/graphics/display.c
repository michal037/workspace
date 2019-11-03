/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_memfile.h>
#include "../detect_os.h"
#ifdef OS_WINDOWS
#include <allegro5/allegro_direct3d.h>
#endif

#include "display.h"
#include "../system/common.h"
#include "../system/engine.h"
#include "../files/icon.h"

/* Main display pointer */
ALLEGRO_DISPLAY *display_main;
DISPLAY_START_POS *display_main_start_pos;
uint8 skip_welcome_screen;
/* Main display FPS */
uint8 display_FPS;

/* Setup icon in main display */
private void setup_main_display_icon(void);
/* Print welcome screen */
private void welcome_screen(void);

public void create_main_display(void)
{
    uint32 display_flags;

    /* New display flags */
    display_flags = ALLEGRO_WINDOWED | ALLEGRO_NOFRAME;// | ALLEGRO_RESIZABLE;
    /* For Windows use Direct3D */
    if(OS_WINDOWS) display_flags |= ALLEGRO_DIRECT3D;

    /* Set display flags */
    al_set_new_display_flags(display_flags);

    /* If the app will run in the windowed mode, set new display position */
    if(display_flags & ALLEGRO_WINDOWED)
    {
        int32 width = 0, height = 0;
        ALLEGRO_MONITOR_INFO info;

        switch(display_main_start_pos->adapter)
        {
            case -2: /* User manual (x,y) */
                al_set_new_window_position(display_main_start_pos->x, display_main_start_pos->y);
                break;

            case -1: /* Automatic by Allegro 5 */
                al_set_new_display_adapter(ALLEGRO_DEFAULT_DISPLAY_ADAPTER);
                break;

            default: /* User manual, with automatic center alignment display */
                al_set_new_display_adapter(display_main_start_pos->adapter);
        }

        /* Automatic alignment display */
        if(display_main_start_pos->adapter >= 0)
        {
            /* Get monitor info */
            if(! al_get_monitor_info(display_main_start_pos->adapter, &info))
            {
                print_logs(1, "The user has set the wrong video adapter in the configuration file!");
                exit(EXIT_FAILURE);
            }

            /* Calculate where to set new display */
            width = (info.x2 - info.x1 - DISPLAY_MAIN_WIDTH) / 2 + info.x1;
            height = (info.y2 - info.y1 - DISPLAY_MAIN_HEIGHT) / 2 + info.y1;

            /* Set new display position */
            al_set_new_window_position(width, height);
        }
    }
    safeFree(display_main_start_pos);


    display_main = al_create_display(DISPLAY_MAIN_WIDTH, DISPLAY_MAIN_HEIGHT);
    if(!display_main)
    {
        print_logs(1, "Failed while creating main display!");
        exit(EXIT_FAILURE);
    }

    /* Setup display title */
    al_set_window_title(display_main, DISPLAY_MAIN_TITLE);

    /* Register event sources */
    al_register_event_source(event_queue_main, al_get_display_event_source(display_main));

    /* Setup display icon */
    setup_main_display_icon();

    /* Print welcome screen */
    welcome_screen();
} /* create_main_display */

public void destroy_main_display(void)
{
    /* Destroy main display */
    al_destroy_display(display_main);

    /* Clean pointer */
    display_main = NULL;
} /* destroy_main_display */

private void setup_main_display_icon(void)
{
    ALLEGRO_FILE *icon_memfile = NULL;
    ALLEGRO_BITMAP *icon_bitmap = NULL;
    uint8 icon_file_raw[] = APP_ICON_PNG;

    /* Create memfile for icon */
    icon_memfile = al_open_memfile(icon_file_raw, sizeof(icon_file_raw), "r");
    if(!icon_memfile)
    {
        print_logs(1, "Program can not create memfile for main display icon!");
        return;
    }

    /* Create icon bitmap */
    icon_bitmap = al_load_bitmap_f(icon_memfile, ".png");
    if(!icon_bitmap)
    {
        print_logs(1, "Program can not create bitmap for main display icon!");
        return;
    }

    /* Close memfile, set icon for main display, destroy bitmap */
    al_fclose(icon_memfile);
    al_set_display_icon(display_main, icon_bitmap);
    al_destroy_bitmap(icon_bitmap);
} /* setup_main_display_icon */

private void welcome_screen(void)
{
    if(skip_welcome_screen) return;

    al_set_target_bitmap(al_get_backbuffer(display_main));
    al_clear_to_color(al_map_rgb(80, 80, 80));
    al_flip_display();
} /* welcome_screen */
