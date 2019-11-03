/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "autoit3/autoit3.h"
#include "engine.h"
#include "../graphics/display.h"
#include "common.h"
#include "misc.h"
#include "config.h"
#include "../about.h"
#include "../graphics/gui/gui.h"

ALLEGRO_EVENT_QUEUE *event_queue_main;
ALLEGRO_EVENT_SOURCE m3_event_src;
ALLEGRO_TIMER *timer_FPS;
uint8 skip_confirm_exit;

private void m3_engine_init(int *argc, char *(*argv[]));
private void m3_engine_exit(void);

public int32 m3_engine_loop(int *argc, char *(*argv[]))
{
    ALLEGRO_EVENT ev;
    uint8 main_loop_done = 0;
    uint8 ev_main_occurred;

    /* Initialize engine */
    m3_engine_init(argc, argv);

    /* Main loop */
    while(!main_loop_done)
    {
        /* Must be event_timed, for CPU time optimization. 1ms */
        ev_main_occurred = (uint8) al_wait_for_event_timed(event_queue_main, &ev, 0.001);

        if((ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) && ev_main_occurred)
        {
            if(!skip_confirm_exit)
            {
                main_loop_done = (uint8) al_show_native_message_box(display_main,
                                 "Confirm Exit", "Are you sure you want to exit?", NULL, NULL,
                                 ALLEGRO_MESSAGEBOX_QUESTION | ALLEGRO_MESSAGEBOX_OK_CANCEL);
            } else main_loop_done = 1;
        }

        gui_tick(&ev, &ev_main_occurred);
    }

    /* Cleanup and exit */
    m3_engine_exit();
    return EXIT_SUCCESS;
}

private void m3_engine_init(int *argc, char *(*argv[]))
{
    //    char *new_update_version_strptr = NULL;

    /* Prepare the random number generator */
    srand((uint32) time(NULL));

    /* Analyze program arguments */
    analyze_arguments(argc, argv);

//    /* Initialize CURL library */
//    curl_global_init(CURL_GLOBAL_ALL);

    /* Initialize AutoIt3 library */
    AU3_Init();

    /* Setup application name for Allegro 5 */
    al_set_app_name(ABOUT_APP_NAME);
    /* Setup organization name for Allegro 5 */
    al_set_org_name(ABOUT_ORG_NAME);

    /* Initialize Allegro 5 library */
    if(!al_init())
    {
        print_logs(1, "Failed to initialize Allegro 5 library!");
        exit(EXIT_FAILURE);
    }

    /* Create main event queue */
    event_queue_main = al_create_event_queue();
    if(!event_queue_main)
    {
        print_logs(1, "Failed to create main event queue!");
        exit(EXIT_FAILURE);
    }

    /* Initialise and register user event source */
    al_init_user_event_source(&m3_event_src);
    al_register_event_source(event_queue_main, &m3_event_src);

    /* Initialize Allegro 5 add-ons */
    init_allegro5_addons();

    /* Read and analyze application config */
    application_config();

    /* Create timer for FPS */
    timer_FPS = al_create_timer(1.0 / display_FPS);
    if(!timer_FPS)
    {
        print_logs(1, "Failed to create main display FPS timer!");
        exit(EXIT_FAILURE);
    }
    al_register_event_source(event_queue_main, al_get_timer_event_source(timer_FPS));

    /* Setup and create main display, print welcome screen */
    create_main_display();

//    /* Check for updates */
//    if(m3_check_update(& new_update_version_strptr))
//    {
//        /* Print info to console */
//        printf("Available update: %s -> %s!\n", M3_APPLICATION_VERSION, new_update_version_strptr);
//
//        /* Free memory chunk */
//        m3_safeFree(new_update_version_strptr);
//    }

    /* Start main display FPS timer */
    al_start_timer(timer_FPS);

    /* Initialize GUI */
    gui_init();
}

private void m3_engine_exit(void)
{
    /* Uninitialize GUI */
    gui_exit();

    /* Destroy main display */
    destroy_main_display();

    /* Destroy timer_FPS */
    al_destroy_timer(timer_FPS);

    /* Uninitialise Allegro 5 add-ons */
    uninit_allegro5_addons();

    /* Unregister and Uninitialise user event source */
    al_unregister_event_source(event_queue_main, &m3_event_src);
    al_destroy_user_event_source(&m3_event_src);

    /* Destroy main event queue */
    al_destroy_event_queue(event_queue_main);

    /* Uninitialize AutoIt3 library */
    AU3_Exit();

    /* CURL library end, cleanup */
    // curl_global_cleanup();
}
