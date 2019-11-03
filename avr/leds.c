#include <stdio.h>

#define printPORT(x) printf("[ %s ]\n", binToStr(x))
char* binToStr(const unsigned char value)
{
    static char str[9];

    for(unsigned char i=0; i<=7; i++)
    {
        str[i] = (char) ((value & (128 >> i)) ? '1' : '0');
    }
    str[8] = '\0';

    return str;
}

int main(void)
{
    unsigned char PORTC = 255;
    unsigned char k1 = 1; /* Wymagane 1 na poczatku programu */

    for(int i=0; i<=32; i++) // lub while(1)
    {
        printPORT(PORTC); // Do podgladu portu, bo nie kompilowane na avr
        // _delay_ms(200);

        if(PORTC && k1)
        {
            PORTC <<= 1;
        } else if((PORTC == 0) && k1)
        {
            PORTC = 128;
            k1--; // lub k1=0;
        } else
        {
            PORTC = PORTC | (PORTC >> 1);
            if(PORTC == 255) k1++; // lub k1=1;
        }
    }

    return 0;
}
