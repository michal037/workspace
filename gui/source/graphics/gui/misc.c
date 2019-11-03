/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <allegro5/allegro.h>

#include "misc.h"
#include "../display.h"
#include "../../system/engine.h"

public uint8 is_collision(int32 mouseX, int32 mouseY, int32 boxX, int32 boxY, int32 boxWidth, int32 boxHeight)
{
    /* Check collision */
    if(mouseX >= boxX && mouseX <= boxX + boxWidth &&
       mouseY >= boxY && mouseY <= boxY + boxHeight)
        return 1; /* Collision detected */
    else
        return 0; /* Collision undetected */
} /* is_collision */

public void inject_event_display_close(void)
{
    ALLEGRO_EVENT fake_event;

    /* Prepare event */
    fake_event.any.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
    fake_event.display.source = display_main;

    /* Inject event */
    al_emit_user_event(&m3_event_src, &fake_event, NULL);
} /* inject_event_display_close */
