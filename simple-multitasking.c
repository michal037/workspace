#include <stdio.h>
#include <time.h>

unsigned short int Timer1, Timer2, Timer3;

void delay_ms(int ms)
{
    clock_t end = clock() + ms * CLOCKS_PER_SEC / 1000.0;
    while(clock() < end) continue;
} /* delay_ms */

void timer_tick(unsigned short int ms)
{
    while(ms--)
    {
        delay_ms(1);

        if(Timer1) --Timer1;
        if(Timer2) --Timer2;
        if(Timer3) --Timer3;
    }
} /* timer_tick */

int main(int argc, char *argv[])
{
    while(1)
    {
        if(!Timer1)
        {
            printf("A");
            Timer1 = 200;
        }
        if(!Timer2)
        {
            printf("B");
            Timer2 = 999;
        }
        if(!Timer3)
        {
            printf("C\n");
            Timer3 = 2000;
        }
        timer_tick(1);
    }
} /* main */
