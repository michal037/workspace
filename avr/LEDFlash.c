/*
 * main.c
 *
 *  Plik Utworzono: 22-06-2014
 *  Autor: Michał Kozakiewicz
 *  Opis: Program po przycisnięciu klawisza K1 wykonuje 10 błysków LED co 500ms.
 */

#include <avr/io.h> // Wczytanie pliku <avr/io.h>.
#include <util/delay.h> // Wczytanie pliku <until/delay.h>.


// *************   Definicje dla preprocesora
// Dioda LED.
#define LED_PIN (1<<PC7) 			// Definicja pinu do którego podłączona jest dioda.
#define LED_TOG PORTC ^= LED_PIN	// Makrodefinicja – zmiana stanu diody.

// klawisz K1.
#define KEY_PIN (1<<PC6)
#define KEY_DOWN !(PINC & KEY_PIN)

uint8_t klawisz_wcisniety(void);	// Deklaracja funkcji klawisz_wcisniety().


int main(void){ // Początek głównego programu.

	// ****** inicjalizacja *********
	DDRC |= LED_PIN;		// Kierunek pinu PC7 – wyjściowy.
	PORTC |= LED_PIN;		// Wyłączenie diody LED.
	DDRC &= ~KEY_PIN;		// Kierunek pinu PC6 - wejściowy.
	PORTC |= KEY_PIN;		// Podciągnięcie pinu do VCC.

    int i, x, c; // Deklaracja zmiennych.
    	x = 0; // Nadanie wartośći zmiennej x.
    	i = 0; // Nadanie wartośći zmiennej i.
        c = 0; // Nadanie wartośći zmiennej c.
    while(1){ // Pętla nieskończona.

        if (x==0){  // Warunek mówiący jeśli x==0 wtedy oczekuje na wcisnięcie klawisza, jeżeli wcisnięto = prawdzie, przechodzi dalej, jeżeli nie wcisnięto, program oczekuje.
        		if( klawisz_wcisniety()){ // Jeżeli Klawisz został wcisnięty, x+1 wtedy if staje się fałszem i przechodzi do else.
        			x=x+1; // Dodanie do x, 1.
        		}
        }else if (c!=10){ // Jeżeli c różne od 10 wtedy prawda, jeżeli c nie jest różne od 10 wtedy fałszl. Jeżeli prawda, przechodzi do wykonania pętli for.
                for(i=0;i<10 && x==1; i=i+1);// Jeżeli x==1 gdzie wcisnięcie klawisza ustawia x+1 wtedy funkcja AND potwierdza prawdę i zlicza 10 mrygnięć, następuje fałsz i przechodzi do następnego else.
   			    LED_TOG;		// Zmienia stan diody na przeciwny.
   		    	_delay_ms(500);	// Pauza 500ms.
                c= c+1; // Dodaje do c, 1. Tak 10 razy aż pierwszy else stanie się prawdą.
        }else if(c==10){   //Realizuje wtedy gdy pierwszy else jest fałszywy. Jeżeli c==10 wtedy następuje zerowanie wartosci.
                i= i-10;   // Odejmuje od i, 10.
                c= c-10; // Odejmuje od c, 10.
                x= x-1; // Zeruje deklaracje x (Wcisnięcie klawisza).
        }; // Koniec instrukcji warunkowej If.
    }; // Koniec pętli while.
return 0; // Kończący return.
};// Koniec głównego programu.

// Definicja funkcji klawisz_wcisniety().
uint8_t klawisz_wcisniety(void){
	if( KEY_DOWN ){					// Czy klawisz wciśnięty ? Jeżeli prawda wykonuje.
		_delay_ms(80);				// Eliminacja czasu drgań styków.
		if( KEY_DOWN ) return 1;   	// Jeśli wciśnięty?  zakończ funkcję - rezultat = 1 .
	}

	return 0;	// Jeśli nie wciśnięty klawisz, zakończ funkcję, rezultat = 0 .
}
