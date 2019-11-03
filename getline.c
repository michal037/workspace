//
// Created by Michal on 20-02-2017.
//

#include <stdio.h>
#include <stdlib.h>

char *getLine(void)
{
    const size_t sizeIncrement = 10;
    char *buffer = malloc(sizeIncrement);
    char *currentPosition = buffer;
    size_t maximumLenght = sizeIncrement;
    size_t length = 0;
    int character;

    if(currentPosition == NULL) return NULL;

    printf("\n>");

    while(1)
    {
        character = fgetc(stdin);
        if(character == '\n') break;

        if(++length >= maximumLenght)
        {
            char *newBuffer = realloc(buffer, maximumLenght += sizeIncrement);

            if(newBuffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            currentPosition = newBuffer + (currentPosition - buffer);
            buffer = newBuffer;
        }
        *currentPosition++ = character;
    }
    *currentPosition = '\0';
    return buffer;
}

int main(int argc, char *argv[])
{
    char *aa = getLine();

    printf("wynik: %c\n", aa);

    return 0;
}
