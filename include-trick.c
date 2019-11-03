#include <stdio.h>

int main(int argc, char *argv[])
{
    char *vara[] = {
        #include "test.txt"
    };
    printf("%s %s %s\n", vara[1], vara[2], vara[3]);

    return 0;
}

// test.txt file:
// "The quick", "brown fox", "jumps over", "the lazy dog."
