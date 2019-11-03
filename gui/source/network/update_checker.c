/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "update_checker.h"
#include "../system/common.h"
#include "../about.h"

typedef struct
{
    char *memory;
    size_t size;
} MemStruct;

private size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

public uint8 check_update(char **OUT_version)
{
    CURL *curl_handle;
    CURLcode curl_result;
    MemStruct chunk;
    uint8 result = 0;
    char *memtest_ptr = NULL;

    /* Allocate 1byte of memory for later realloc operation; Data size = 0 */
    chunk.memory = (char *) malloc(1 * sizeof(char));
    chunk.size = 0;

    /* Init the curl session */
    curl_handle = curl_easy_init();

    /* Specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, ABOUT_UPDATE_CHECK_URL);

    /* Use only SSL connection */
    curl_easy_setopt(curl_handle, CURLOPT_USE_SSL, CURLUSESSL_NONE);

    /* Register write callback */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    /* Select memory chunk for write data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    /* Provide fake user-agent */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Linux; rv:53.0) Gecko/20100101 Firefox/53.0");

    /* Execute */
    curl_result = curl_easy_perform(curl_handle);

    /* If update check failure */
    if(curl_result != CURLE_OK)
    {
        /* Send 0 and free allocated memory block */
        *OUT_version = NULL;
        result = 0;
        free(chunk.memory);

        /* Print error */
        print_logs(2, "Update Checker: ", curl_easy_strerror(curl_result));

        /* Cleanup curl handle */
        curl_easy_cleanup(curl_handle);

        /* Return update status */
        return result;
    }

    /* Update_string received; Check for update */
    if(chunk.size < 2  ||  chunk.size > 24) /* 16 + 8 for future */
    {
        /* Input too long or too short, probably bad */
        result = 0;
    } else {
        /* Remove last LF char (from GitHub) */
        chunk.memory[chunk.size - 1] = '\0';

        memtest_ptr = chunk.memory;
        result = 1;

        /* Check for incorrect char in string */
        while(*memtest_ptr != '\0')
        {
            /* Accepts only numbers and dots */
            if(*memtest_ptr < 46  ||  *memtest_ptr == 47  ||  *memtest_ptr > 57)
            {
                result = 0;
                break;
            }
            memtest_ptr++;
        }

        /* if(result == 1) Compare with current version */
        if(result)
        {
            result = (uint8) (strncmp(chunk.memory, ABOUT_APP_VERSION, chunk.size) ? 1 : 0);
        }
    }

    /* If update available */
    if(result)
    {
        /* Output receive data */
        *OUT_version = chunk.memory;
    } else { /* Update no available */
        *OUT_version = NULL;

        /* Free allocated memory block */
        free(chunk.memory);
    }

    /* Cleanup curl handle */
    curl_easy_cleanup(curl_handle);

    /* Return update status */
    return result;
} /* m3_check_update */

private size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemStruct *mem = (MemStruct *)userp;

    /* Allocate memory for data */
    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL)
    {
        /* Out of memory! */
        print_logs(1, "Update Checker: WriteMemoryCallback realloc return NULL!");
        return 0;
    }

    /* Copy contents to memory block */
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;

    /* Set 0 at the end of memory block */
    mem->memory[mem->size] = 0;

    return realsize;
} /* M3WriteMemoryCallback */
