/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

#define STANDARD_FILE_OUT "headerFile"
#define BUFFER_SIZE 20

int main(int argc, char *argv[])
{
    struct stat fileIN_stat;
    FILE *fileIN = NULL, *fileOUT = NULL;
    uint8 buffer[BUFFER_SIZE], n;
    uint32 fileIN_size;

    /* Print help if arguments are not specified */
    if(argc == 1)
    {
        printf("Help bin2header - github.com/michal037\n"
               "  bin2header fileIN [fileOUT]\n"
        );
        exit(EXIT_SUCCESS);
    }

    /* Check file */
    if(stat(argv[1], &fileIN_stat))
    {
        fprintf(stderr, "File %s do not exists!\n", argv[1]);
        exit(EXIT_FAILURE);
    } else {
        fileIN_size =  (uint32) ceil(fileIN_stat.st_size / (float)BUFFER_SIZE);
    }

    /* Open files */
    fileIN = fopen(argv[1], "rb");
    if(!fileIN)
    {
        fprintf(stderr, "Failed to open fileIN!\n");
        exit(EXIT_FAILURE);
    }
    fileOUT = fopen(argv[2], "wb");
    if(!fileOUT)
    {
        fprintf(stderr, "Failed to create fileOUT!\n"
                "Attempting to create the file with the standard name.\n");
        fileOUT = fopen(STANDARD_FILE_OUT ".h", "wb");
        if(!fileOUT)
        {
            fprintf(stderr, "Failed to create fileOUT!\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Binary to Header */
    fprintf(fileOUT, "#ifndef fileName_H\n#define fileName_H\n\n#define fileName {");
    while((n = (uint8) fread(buffer, 1, BUFFER_SIZE, fileIN)) > 0)
    {
        fileIN_size--;

        fprintf(fileOUT, "\\\n");

        for(uint8 b=n; n > 0 ; n--)
        {
            fprintf(fileOUT, "%hhu%s", buffer[b-n], (fileIN_size?",":((n==1)?"":",")));
        }
    }
    fprintf(fileOUT, "}\n\n#endif\n");

    /* Close the file */
    if(fclose(fileIN) == EOF)
    {
        fprintf(stderr, "Unable to close fileIN!\n");
        exit(EXIT_FAILURE);
    }
    if(fclose(fileOUT) == EOF)
    {
        fprintf(stderr, "Unable to close fileOUT!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
} /* main */
