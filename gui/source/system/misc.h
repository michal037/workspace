/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_MISC_H
#define SRC_SYSTEM_MISC_H

#include "../types.h"
#include "../macros.h"

/* Analyze arguments */
public void analyze_arguments(int *argc, char *(*argv[]));

/* Initialize Allegro 5 add-ons */
public void init_allegro5_addons(void);

/* Uninitialise Allegro 5 add-ons */
public void uninit_allegro5_addons(void);

/* Calculate CRC16 from input */
public uint16 crc16ansi(uint16 value);

#endif /* SRC_SYSTEM_MISC_H */
