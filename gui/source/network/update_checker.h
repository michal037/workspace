/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_NETWORK_UPDATE_CHECKER_H
#define SRC_NETWORK_UPDATE_CHECKER_H

#include "../types.h"
#include "../macros.h"

/*
 * Check for updates.
 *
 * Function accept, numbers, dots, string length from 2 to 24.
 *
 * Return:
 *   0 - Update check failure or no update
 *   1 - Update available
 *
 *   OUT_version - If update available, return pointer to allocated string with update version,
 *                 else return NULL.
 *
 * Example:
 *   char *a;
 *   uint8 x = check_update(& a);
 */
public uint8 check_update(char **OUT_version);

#endif /* SRC_NETWORK_UPDATE_CHECKER_H */
