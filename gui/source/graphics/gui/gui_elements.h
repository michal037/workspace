/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_GRAPHICS_GUI_GUI_ELEMENTS_H
#define SRC_GRAPHICS_GUI_GUI_ELEMENTS_H

#include <allegro5/allegro.h>
#include "../../types.h"
#include "../../macros.h"
#include "../../system/onewaylist.h"
#include "gui.h"


/*
 * ENUM GUI Element Types
 */
typedef enum _ENUM_GUI_ELEMENT_TYPE
{
    ENUM_GUI_ELEMENT_TYPE_BUTTON
} ENUM_GUI_ELEMENT_TYPE;


/*
 * ENUM GUI Item Mouse States
 */
typedef enum _ENUM_GUI_ELEMENT_STATE_MOUSE
{
    ENUM_GUI_ELEMENT_STATE_MOUSE_NORMAL,
    ENUM_GUI_ELEMENT_STATE_MOUSE_HOVER,
    ENUM_GUI_ELEMENT_STATE_MOUSE_CLICK,
    ENUM_GUI_ELEMENT_STATE_MOUSE_DCLICK
} ENUM_GUI_ELEMENT_STATE_MOUSE;


/*
 * STRUCT GUI Elements Mouse States
 */
typedef struct _GUI_ELEMENT_STATE_MOUSE_NORMAL
{
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR border_color;
} GUI_ELEMENT_STATE_MOUSE_NORMAL;
typedef struct _GUI_ELEMENT_STATE_MOUSE_HOVER
{
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR border_color;
} GUI_ELEMENT_STATE_MOUSE_HOVER;
typedef struct _GUI_ELEMENT_STATE_MOUSE_CLICK
{
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR border_color;
} GUI_ELEMENT_STATE_MOUSE_CLICK;
typedef struct _GUI_ELEMENT_STATE_MOUSE_DCLICK
{
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR border_color;
} GUI_ELEMENT_STATE_MOUSE_DCLICK;
typedef struct _GUI_ELEMENT_STATE_MOUSE_LAST
{
    ENUM_GUI_ELEMENT_STATE_MOUSE state;
    uint16 Timer1;
} GUI_ELEMENT_STATE_MOUSE_LAST;

/*
 * GUI Elements Mouse callbacks
 */
typedef struct _GUI_ELEMENT_MOUSE_CALLBACKS
{
    void (*hover)(void);
    void (*click)(void);
    void (*dclick)(void);
} GUI_ELEMENT_MOUSE_CALLBACKS;


/*
 * GUI Elements Position and Dimensions
 */
typedef struct _GUI_ELEMENT_POSITION
{
    int32 x;
    int32 y;
} GUI_ELEMENT_POSITION;
typedef struct _GUI_ELEMENT_DIMENSIONS
{
    int32 width;
    int32 height;
} GUI_ELEMENT_DIMENSIONS;

/*
 * GUI Items
 */
typedef struct _GUI_Button
{
    ENUM_GUI_ELEMENT_TYPE element_type; /* Must be first in every elements */

    GUI_ELEMENT_POSITION pos;
    GUI_ELEMENT_DIMENSIONS dim;
    int32 border_width;

    ENUM_GUI_ELEMENT_STATE_MOUSE    mstate;
    GUI_ELEMENT_STATE_MOUSE_NORMAL  mstate_normal;
    GUI_ELEMENT_STATE_MOUSE_HOVER  *mstate_hover;
    GUI_ELEMENT_STATE_MOUSE_CLICK  *mstate_click;
    GUI_ELEMENT_STATE_MOUSE_DCLICK *mstate_dclick;
    GUI_ELEMENT_STATE_MOUSE_LAST    mstate_last;

    GUI_ELEMENT_MOUSE_CALLBACKS callbacks;

    char *element_title;
} GUI_Button;

/* Pointer conversion Union for GUI Elements */
typedef union _UNION_GUI_ELEMENT_POINTER_CONVERSION
{
    GUI_Button *button;
    void *unknown;
} UNION_GUI_ELEMENT_POINTER_CONVERSION;


/* Itinialize GUI Element */
public void gui_initialize_element(void *element, ENUM_GUI_ELEMENT_TYPE element_type);

/* Draw GUI Element */
public void gui_draw_element(void *element);

/* Respond to mouse collisions with GUI elements */
public void gui_mouse_on_element_collisions(OWL_List *list, ALLEGRO_EVENT *mouse_ev, MOUSE_EV_TYPE mouse_ev_type, uint8 mouse_click_count);

/* GUI timer for graphic details */
public void gui_element_state_mouse_last_tick(void *element);

#endif /* SRC_GRAPHICS_GUI_GUI_ELEMENTS_H */
