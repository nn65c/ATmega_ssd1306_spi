/*
 * main.c
 *
 * Created: 19.08.2017 23:19:19
 * Author : Frode Hansen
 */

#include "ssd1306/oled_spi.h"

#include <stdbool.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

int main(void)
{
	oled_init();

	oled_clear();

	oled_flip(true);

	oled_contrast(200);

	oled_puts_pos_P(PSTR("012345678901234567890"), 0, 0);

	for (int i = 1; i < 8; i++) {
		oled_putc_pos('0' + i, 0, i);
	}

	oled_puts_pos_P(PSTR("PGM txt with pos"), 2, 2);
	oled_setpos(2, 3);
	oled_puts_P(PSTR("PRM txt after pos"));

	oled_puts_pos("RAM txt with pos", 2, 5);
	oled_setpos(2, 6);
	oled_puts("RAM text after pos");

	while (1) {
	}
}