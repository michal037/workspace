#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN (1<<PC7)
#define LED_ON PORTC &= ~LED_PIN
#define LED_OFF PORTC |= LED_PIN
#define LED_TOG PORTC ^= LED_PIN

#define KEY1_PIN (1<<PC6)
#define KEY2_PIN (1<<PC5)
#define KEY3_PIN (1<<PC4)

uint8_t klawisz_wcisniety(uint8_t klawisz);

int main(void)
{
	/* LED to VCC, is OFF */
	DDRC |= LED_PIN;
	PORTC |= LED_PIN;
	
	/* KEY to VCC, is OFF */
	DDRC &= ~(KEY1_PIN | KEY2_PIN | KEY3_PIN);
	PORTC |= KEY1_PIN | KEY2_PIN | KEY3_PIN;
	
    while(1) 
    {
		if(klawisz_wcisniety(KEY1_PIN)) LED_ON;
		if(klawisz_wcisniety(KEY2_PIN)) LED_OFF;
		if(klawisz_wcisniety(KEY3_PIN)) LED_TOG;
		_delay_ms(200);
    }
}

uint8_t klawisz_wcisniety(uint8_t klawisz)
{
	if(!(PINC & klawisz))
	{
		_delay_ms(80);
		if(!(PINC & klawisz)) return 1;
	}
	
	return 0;
}
