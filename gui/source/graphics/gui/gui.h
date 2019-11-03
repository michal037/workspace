/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_GRAPHICS_GUI_GUI_H
#define SRC_GRAPHICS_GUI_GUI_H

#include "../../types.h"
#include "../../macros.h"

typedef enum _mouse_event_type {MOUSE_AXES, MOUSE_BUTTON_DOWN, MOUSE_BUTTON_UP} MOUSE_EV_TYPE;
typedef enum _key_event_type {KEY_DOWN, KEY_UP, KEY_CHAR} KEY_EV_TYPE;

/* Initialize GUI */
public void gui_init(void);

/* Uninitialize GUI */
public void gui_exit(void);

/* GUI tick */
public void gui_tick(ALLEGRO_EVENT *ev, uint8 *ev_main_occurred);

#endif /* SRC_GRAPHICS_GUI_GUI_H */
