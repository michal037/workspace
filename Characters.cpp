/*
 * print all characters
 * 25.09.2019, Michal Kozakiewicz, michal037
 */

#include <stdio.h>

int main() {
	/* print lowercase letters */
	for(unsigned char i = 'a'; i <= 'z'; i++) {
		printf("%c", i);
	}
	printf("\n");

	/* print uppercase letters */
	for(unsigned char i = 'A'; i <= 'Z'; i++) {
		printf("%c", i);
	}
	printf("\n");

	/* print digits */
	for(unsigned char i = '0'; i <= '9'; i++) {
		printf("%c", i);
	}
	printf("\n");

	/* print symbols */
	for(unsigned char i = 33; i <= 126; i++) {
		if((i >= '0') && (i <= '9')) continue; // skip digits
		if((i >= 'a') && (i <= 'z')) continue; // skip lowercase letters
		if((i >= 'A') && (i <= 'Z')) continue; // skip uppercase letters
		printf("%c", i);
	}
}
