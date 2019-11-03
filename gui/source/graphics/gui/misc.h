/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_GRAPHICS_GUI_MISC_H
#define SRC_GRAPHICS_GUI_MISC_H

#include "../../types.h"
#include "../../macros.h"
#include "gui_elements.h"

public uint8 is_collision(int32 mouseX, int32 mouseY, int32 boxX, int32 boxY, int32 boxWidth, int32 boxHeight);

public void inject_event_display_close(void);

#endif /* SRC_GRAPHICS_GUI_MISC_H */
