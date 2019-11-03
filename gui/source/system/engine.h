/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_ENGINE_H
#define SRC_SYSTEM_ENGINE_H

#include <allegro5/allegro.h>
#include "../types.h"
#include "../macros.h"

/* Main event queue pointer */
extern ALLEGRO_EVENT_QUEUE *event_queue_main;

/* User event source */
extern ALLEGRO_EVENT_SOURCE m3_event_src;

/* Confirmation of program closure, default 0 */
extern uint8 skip_confirm_exit;

/* Initialize, loop, exit; GUI Engine */
public int32 m3_engine_loop(int *argc, char *(*argv[]));

#endif /* SRC_SYSTEM_ENGINE_H */
