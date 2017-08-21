/*
 * oled_spi.h
 *
 * Created: 19.08.2017 23:23:42
 *  Author: Frode Hansen
 */

#ifndef OLED_SPI_H_
#define OLED_SPI_H_

#include "oled_config.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

// Set character position (pos) and line.
// Top left is 0,0
void oled_setpos(uint8_t pos, uint8_t line);

// Print character at current position and line.
void oled_putc(uint8_t character);

// Print character position (pos) on line.
// Top left is 0,0
void oled_putc_pos(uint8_t character, uint8_t pos, uint8_t line);

// Print string starting at character position (pos) on line.
// Top left is 0,0
// No position check. Characters will wrap to start of same line.
void oled_puts_pos(char *characters, uint8_t pos, uint8_t line);

// Print from program memory starting at character position (pos) on line.
// Top left is 0,0
// No position check. Characters will wrap to start of same line.
// Use PSTR("string")
void oled_puts_pos_P(const char *characters, uint8_t pos, uint8_t line);

// Print string at current position and line.
// No position check. Characters will wrap to start of same line.
void oled_puts(char *characters);

// Print from program memory at current position and line.
// No position check. Characters will wrap to start of same line.
// Use PSTR("string")
void oled_puts_P(const char *characters);

// Flip OLED screen horizontally
void oled_flip(uint8_t rotate);

// Clear OLED screen
void oled_clear(void);

// Initialize OLED
void oled_init(void);

// Set OLED contrast (0-255)
void oled_contrast(uint8_t contrast);

#endif /* OLED_SPI_H_ */