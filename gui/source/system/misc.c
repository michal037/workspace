/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "misc.h"
#include "common.h"
#include "engine.h"

public void analyze_arguments(int *argc, char *(*argv[]))
{
    opterr = 0; /* Do not print errors to stderr */
    int option, errorCode = 0, index;
    char buffer[5];


    /* Parse the arguments */
    while((option = getopt(*argc, *argv, ":h")) != -1)
        switch(option)
        {
            case 'h': printf("argument -h\n"); break;


                /* Error handling */
            case ':':
                sprintf(buffer, "%c", (char)optopt);
                print_logs(3, "The option '-", buffer, "' requires an argument!");
                errorCode = 1;
                break;

            case '?': default:
                if(isprint(optopt))
                {
                    sprintf(buffer, "%c", (char)optopt);
                    print_logs(3, "An unknown option '-", buffer, "'");
                }
                else {
                    sprintf(buffer, "%#02x", (char)optopt);
                    print_logs(3, "An unknown option character '", buffer, "'");
                }
        }

    /* Print the unknown arguments */
    for(index = optind; index < *argc ;index++) print_logs(3, "An unknown argument: '", (*argv)[index], "'");

    if(errorCode) exit(EXIT_FAILURE);
} /* analyze_arguments */

public void init_allegro5_addons(void)
{
    /* Initialize image add-on */
    if(!al_init_image_addon())
    {
        print_logs(1, "Program can not init Allegro 5 image add-on!");
        exit(EXIT_FAILURE);
    }

    /* Initialize native dialogs add-on */
    if(!al_init_native_dialog_addon())
    {
        print_logs(1, "Program can not init Allegro 5 native dialogs add-on!");
        exit(EXIT_FAILURE);
    }

    /* Install keyboard and mouse drivers, register event sources */
    if(!al_install_keyboard())
    {
        print_logs(1, "Program can not install keyboard!");
        exit(EXIT_FAILURE);
    }
    al_register_event_source(event_queue_main, al_get_keyboard_event_source());
    if(!al_install_mouse())
    {
        print_logs(1, "Program can not install mouse!");
        exit(EXIT_FAILURE);
    }
    al_register_event_source(event_queue_main, al_get_mouse_event_source());

    /* Initialize primitives add-on */
    if(!al_init_primitives_addon())
    {
        print_logs(1, "Program can not init primitives addon!");
        exit(EXIT_FAILURE);
    }

    /* Initialize font and TTF add-on */
    if(!al_init_font_addon())
    {
        print_logs(1, "Program can not init font addon!");
        exit(EXIT_FAILURE);
    }
    if(!al_init_ttf_addon())
    {
        print_logs(1, "Program can not init TTF addon!");
        exit(EXIT_FAILURE);
    }
} /* init_allegro5_addons */

public void uninit_allegro5_addons(void)
{
    /* Uninitialzie add-ons */
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_shutdown_native_dialog_addon();
} /* uninit_allegro5_addons */

public uint16 crc16ansi(uint16 value)
{
    /* Do not change poly! Then there may be a bug. */
    // uint32 poly = 0x18005; /* (1<<16) | (1<<15) | (1<<2) | (1<<0); CRC-16 ANSI */
    uint32 data = 0;
    uint8 dataN = 31;

    data = (((uint32)value ) << 16);

    while(dataN - 16 > 0)
    {
        while(((1 << dataN) & data) == 0 && dataN != 0) dataN--;
        data = data ^ (0x18005 << (dataN - 16));
    }

    return (uint16)data;
} /* crc16ansi */
