/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_CONFIG_H
#define SRC_SYSTEM_CONFIG_H

#include "../types.h"
#include "../macros.h"

#define GLOBAL_CONFIG_NAME "global.cfg"

/*
 * Read application configuration file.
 * If configuration file do not exists, create it with defaults.
 */
public void application_config(void);

#endif /* SRC_SYSTEM_CONFIG_H */
