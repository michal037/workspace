/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 *
 * From: 03-May-2017y.
 * Standard C11
 */

#include "detect_os.h"
#ifdef OS_WINDOWS
#include <windows.h>
#endif

#include "macros.h"
#include "types.h"
#include "system/engine.h"

public int32 main(int32 argc, char *argv[])
{
    int32 result = 0;

    /* Hide console window */
    #ifdef OS_WINDOWS
        if(argc < 2) ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_HIDE);
    #endif

    /* Start engine */
    result = m3_engine_loop(&argc, &argv);

    /* Show console window */
    #ifdef OS_WINDOWS
        if(argc < 2)
        {
            ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_SHOWNA);
            FreeConsole();
        }
    #endif

    return result;
}
