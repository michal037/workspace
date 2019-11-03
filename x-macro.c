#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STRUCT_FIELDS \
    X(uint8_t, data1, show_uint8)  \
    X(char *,  name,  show_string) \
    X(char,    v,     show_char)   \
    X(float,   price, show_float)

typedef struct
{
#define X(type, name, func_ptr) type name;
    STRUCT_FIELDS
#undef X
} Data_t;

static void show_uint8(void * value)
{
    uint8_t data = *((uint8_t *)value);
    printf("%d", data);
} /* show_uint8 */

static void show_string(void * value)
{
    char * str = *((char * *)value);
    printf("%s", str);
} /* show_string */

static void show_char(void * value)
{
    char data = *((char *)value);
    putchar(data);
} /* show_char */

static void show_float(void * value)
{
    float data = *((float *)value);
    printf("%f", data);
} /* show_float */

static void (*functions[])(void *) =
{
#define X(type, name, func_ptr) func_ptr,
    STRUCT_FIELDS
#undef X
};

static Data_t data = 
{ 
        .data1 = 124,
        .name = "poi",
        .v = 'q',
        .price = 126.5
};

static int struct_offsets[] = {
#define X(type, name, func_ptr) (int)((char *)(&data.name) - (char *)&data),
    STRUCT_FIELDS
#undef X
};

int main(int argc, char *argv[])
{
    size_t index;
    size_t offsets_last = sizeof(functions) / sizeof(void (*)(void *)) - 1;
    printf("Set index [0, %d]: ", offsets_last);
    scanf("%ul", &index);
    if(index < 0 || index > offsets_last)
    {
        fprintf(stderr, "Index error\n");
        exit(EXIT_FAILURE);
    }

    char * data_ptr = &((char *)&data)[struct_offsets[index]];
    functions[index]((void *)data_ptr);
    putchar('\n');

    return EXIT_SUCCESS;
} /* main */
