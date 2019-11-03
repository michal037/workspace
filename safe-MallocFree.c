#include <stdio.h>
#include <stdlib.h>

/*
 * safeMalloc()
 *
 * Allocate memory.
 *
 * Parameters:
 *   INPUT: size - Size of memory to allocate.
 *
 * Result:
 *   Pointer to memory. If cause error, close program.
 *
 */
void *safeMalloc(size_t size)
{
    void *mem = malloc(size);

    if(mem == NULL)
    {
        fprintf(stderr, "Out of RAM memory\n");
        exit(1);
    }

    return mem;
} /* safeMalloc */

#define safeFree(p) __safeFree((void**)&(p))

/*
 * __safeFree()
 *
 * Free memory.
 *
 * Parameters:
 *   OUTPUT: ptr - Address of [pointer to memory] to clear.
 *
 * Use with macro:
 *   #define safeFree(p) __safeFree((void**)&(p))
 *
 */
void __safeFree(void **ptr)
{
    if(ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
} /* __safeFree */

int main(int argc, char *argv[])
{
    int *pi = (int*) safeMalloc(1 * sizeof(int));
    *pi = 5;

    printf("Before: %p\n", pi);
    safeFree(pi);

    printf("After: %p\n", pi);
    safeFree(pi);

    return 0;
} /* main */
