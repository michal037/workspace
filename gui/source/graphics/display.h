/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_GRAPHICS_DISPLAY_H
#define SRC_GRAPHICS_DISPLAY_H

#include <allegro5/allegro.h>
#include "../types.h"
#include "../macros.h"

/* Main display size */
#define DISPLAY_MAIN_WIDTH 700
#define DISPLAY_MAIN_HEIGHT 450
/* Main display title */
#define DISPLAY_MAIN_TITLE "GUI Engine"


/* Main display pointer */
extern ALLEGRO_DISPLAY *display_main;

/* User select start main display position */
typedef struct
{
    int32 x;
    int32 y;
    int32 adapter;
} DISPLAY_START_POS;
extern DISPLAY_START_POS *display_main_start_pos;

/* Main display FPS */
extern uint8 display_FPS;

/* Skip welcome screen, default 0 */
extern uint8 skip_welcome_screen;

/* Create and start main display */
public void create_main_display(void);

/* Destroy main display */
public void destroy_main_display(void);

#endif /* SRC_GRAPHICS_DISPLAY_H */
