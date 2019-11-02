/*
 * LED Display Library
 */ 

#ifndef _DISPLAY_LED_H_
#define _DISPLAY_LED_H_

/** CONFIGURATION **/
/* Cathodes */
#define _DLED_DATA_DDR  DDRC
#define _DLED_DATA_PORT PORTC

/* Anodes */
#define _DLED_DISPNUM_DDR  DDRA
#define _DLED_DISPNUM_PORT PORTA
#define _DLED_DISPNUM_1 (1<<PA0)
#define _DLED_DISPNUM_2 (1<<PA1)
#define _DLED_DISPNUM_3 (1<<PA2)
#define _DLED_DISPNUM_4 (1<<PA3)
/** END OF CONFIGURATION **/

extern volatile uint8_t DLED_N1;
extern volatile uint8_t DLED_N2;
extern volatile uint8_t DLED_N3;
extern volatile uint8_t DLED_N4;

void display_led_init(void);

#endif /* _DISPLAY_LED_H_ */
