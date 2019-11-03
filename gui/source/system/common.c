/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>
#include <sys/stat.h>

#include "common.h"

public void print_logs(int arguments_amount, ...)
{
    time_t time_seconds_global;
    struct tm *time_now_is;
    char time_buffer[18];
    FILE *file_logs = NULL;
    va_list var_arguments_list;
    char *argument_next = NULL;


    /* Prepare time string, '11-AAA-1111 11-11' */
    time(&time_seconds_global);
    time_now_is = localtime(&time_seconds_global);
    setlocale( LC_ALL, "English" );
    strftime(time_buffer, sizeof(time_buffer), "%d-%b-%Y %H:%M", time_now_is);

    /* Open logs file */
    file_logs = fopen(PRINT_LOGS_FILE ".log", "ab");
    if(!file_logs)
    {
        fprintf(stderr, "print_logs can not open %s.log file!\n", PRINT_LOGS_FILE);
        return;
    }

    /* Write date */
    fprintf(file_logs, "[%s] ", time_buffer);
    fprintf(stderr, "[%s] ", time_buffer);

    /* Write logs from arguments to file */
    va_start(var_arguments_list, arguments_amount);
    do
    {
        argument_next = va_arg(var_arguments_list, char*);
        fprintf(file_logs, "%s", argument_next);
        fprintf(stderr, "%s", argument_next);
        arguments_amount--;
    } while(arguments_amount != 0);
    va_end(var_arguments_list);

    /* Write new line at the end of file */
    fprintf(file_logs, "\r\n");
    fprintf(stderr, "\r\n");

    /* Close logs file*/
    if(fclose(file_logs) == EOF)
    {
        fprintf(stderr, "print_logs can not close %s.log file!\n", PRINT_LOGS_FILE);
        return;
    }
} /* print_logs */

public uint8 check_file(char* name)
{
    struct stat buf;

    return (uint8) !stat(name, &buf);
} /* check_file */

public void __safeFree(void **pp)
{
    if(pp != NULL && *pp != NULL)
    {
        free(*pp);
        *pp = NULL;
    }
} /* __safeFree */

public void *safe_Malloc(size_t size)
{
    void *mem = malloc(size);

    if(mem == NULL)
    {
        print_logs(1, "Out of RAM memory!");
        exit(EXIT_FAILURE);
    }

    return mem;
} /* safe_Malloc */
