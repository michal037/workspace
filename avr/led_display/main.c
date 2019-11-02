#include <avr/io.h>
#include <avr/interrupt.h>
#include "display_led/dled.h"

int main(void)
{	
	display_led_init();
	
	DLED_N1 = 15;
	DLED_N2 = 10;
	DLED_N3 = 13;
	DLED_N4 = 14;
	
	sei();
	
    while(1) 
    {
		
	}
} /* main */
