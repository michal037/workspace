/*
 * LED Display Library
 *
 * ATmega32A, 16 000 000 Hz, Timer0
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "dled.h"

/* Outputs */
volatile uint8_t DLED_N1;
volatile uint8_t DLED_N2;
volatile uint8_t DLED_N3;
volatile uint8_t DLED_N4;

/* Segments */
#define SEG_A  (1<<0)
#define SEG_B  (1<<1)
#define SEG_C  (1<<2)
#define SEG_D  (1<<3)
#define SEG_E  (1<<4)
#define SEG_F  (1<<5)
#define SEG_G  (1<<6)
#define SEG_DP (1<<7)

/* Array of characters */
const uint8_t dledTab[18] PROGMEM =
{
	~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F), /* 0: 0 */
	~(SEG_B|SEG_C), /* 1: 1 */
	~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G), /* 2: 2 */
	~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G), /* 3: 3 */
	~(SEG_B|SEG_C|SEG_F|SEG_G), /* 4: 4 */
	~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G), /* 5: 5 */
	~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G), /* 6: 6 */
	~(SEG_A|SEG_B|SEG_C|SEG_F), /* 7: 7 */
	~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G), /* 8: 8 */
	~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G), /* 9: 9 */
	~(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G), /* 10: A */
	~(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G), /* 11: b */
	~(SEG_A|SEG_D|SEG_E|SEG_F), /* 12: C */
	~(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G), /* 13: d */
	~(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G), /* 14: E */
	~(SEG_A|SEG_E|SEG_F|SEG_G), /* 15: F */
	~(SEG_G), /* 16: - */
	~(0) /* 17: Empty */
};

/* Initialization */
void display_led_init(void)
{
	/* All data pins as output and disable */
	_DLED_DATA_DDR = 0xFF;
	_DLED_DATA_PORT = 0xFF;
	
	/* Pins as output and disable */
	_DLED_DISPNUM_DDR  |= _DLED_DISPNUM_1 | _DLED_DISPNUM_2 | _DLED_DISPNUM_3 | _DLED_DISPNUM_4;
	_DLED_DISPNUM_PORT |= _DLED_DISPNUM_1 | _DLED_DISPNUM_2 | _DLED_DISPNUM_3 | _DLED_DISPNUM_4;
	
	TCCR0 |= (1<<WGM01); /* CTC Mode */
	TCCR0 |= (1<<CS02) | (1<<CS00); /* Prescaler: 1024 */
	OCR0 = 77; /* Compare with (77+1) */
	TIMSK |= (1<<OCIE0); /* Permission to interrupt: Compare Match */
} /* display_led_init */

/* Interrupt */
ISR(TIMER0_COMP_vect)
{
	static uint8_t num = 1;
	
	_DLED_DISPNUM_PORT = (_DLED_DISPNUM_PORT & 0xF0) | (~num & 0x0F);
	
	if(num == 1)      _DLED_DATA_PORT = pgm_read_byte(&dledTab[DLED_N1]);
	else if(num == 2) _DLED_DATA_PORT = pgm_read_byte(&dledTab[DLED_N2]);
	else if(num == 4) _DLED_DATA_PORT = pgm_read_byte(&dledTab[DLED_N3]);
	else if(num == 8) _DLED_DATA_PORT = pgm_read_byte(&dledTab[DLED_N4]);
	
	num <<= 1;
	if(num > 8) num = 1;
} /* ISR: TIMER0_COMP_vect */
