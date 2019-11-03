#include <stdio.h>

/** Method with arguments **/
#define obj(object, method, ...) ((object).method(&(object), __VA_ARGS__))

/** Method with arguments but without 'this' object **/
#define obje(object, method, ...) ((object).method(__VA_ARGS__))

/** Method without arguments **/
#define objc(object, method) ((object).method(&(object)))

/** Variable **/
#define objv(object, variable) ((object).variable)

/* Class */
typedef struct class
{
    int a;
    int (*methodName)(struct class *this, int b, int c);
} className;

/* Method */
int code(className *this, int b, int c)
{
    return this->a*b+c;
} /* code */

/* Constructor */
className constructor(int a)
{
    className result = {a, code};
    return result;
}

int main(int argc, char *argv[])
{
    className objName = constructor(10);
    int result = obj(objName, methodName, 1, 9);

    printf("%d\n", result);

    return 0;
} /* main */
