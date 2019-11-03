/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_GRAPHICS_GUI_LAYOUTS_MAIN_GUI_LAYOUTS_MAIN_H
#define SRC_GRAPHICS_GUI_LAYOUTS_MAIN_GUI_LAYOUTS_MAIN_H

#include "../../../../system/onewaylist.h"
#include "../../gui_elements.h"

/* Layout elements list */
extern OWL_List GUI_Layout_Main;

/* Create Main GUI Layout */
public void gui_create_layout_main(void);

/* Destroy Main GUI Layout */
public void gui_destroy_layout_main(void);

#endif /* SRC_GRAPHICS_GUI_LAYOUTS_MAIN_GUI_LAYOUTS_MAIN_H */
