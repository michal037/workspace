/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_COMMON_H
#define SRC_SYSTEM_COMMON_H

#include "../types.h"
#include "../macros.h"

/* Logs file name without extensions */
#define PRINT_LOGS_FILE "gui_engine"

/*
 * Write logs to file
 *
 * Variables are only char*
 *
 * Example:
 *   print_logs(2, "M", "3");
 */
public void print_logs(int arguments_amount, ...);

/*
 * Check file, if exist return 1 else 0
 */
public uint8 check_file(char* name);

/*
 * Safe Free
 * Use with macro:
 *   #define safeFree(p) __safeFree((void**)&(p))
 */
#define safeFree(p) __safeFree((void**)&(p))
public void __safeFree(void **pp);

/*
 * Safe Malloc()
 *
 * Parameters:
 *   INPUT: size - size of memory to allocate
 *
 * Result:
 *   Pointer to memory. If cause error, close program.
 *
 */
public void *safe_Malloc(size_t size);

#endif /* SRC_SYSTEM_COMMON_H */
