/*
* oled_spi.c
*
* Created: 19.08.2017 23:25:13
*  Author: Frode Hansen
*/

#include "oled_spi.h"

static void oled_write_spi(uint8_t dat);
static void oled_cmd(uint8_t cmd);
static void oled_data(uint8_t cmd);
static void oled_reset(void);

static const char OLED_INIT[] PROGMEM = {
	0xa8, 0x3f,		   // set MUX ratio
	0xd3, 0x00,		   // set display offset
	0x40,			   // set display start line
	0xda,			   // set COM pins hardware configuration
	0x12,			   // reset value is 0x12
	0x81, 0xff,		   // set contrast (2-byte)
	0xa4,			   // disable entire display on
	0xa6,			   // set normal display
	0xd5, 0x80,		   // set osc frequency
	0x8d, 0x14,		   // enable charge pump
	0xaf,			   // set display on
	0x21, 0x00, 0x7f,  // set column start and end address
	0x22, 0x00, 0x07   // set row start and end address
};

static void oled_write_spi(uint8_t dat)
{
	// Shift out bits MSB.
	for (int i = 8; i--;) {
		PORT_SCL &= ~(1 << SCL);

		if (dat >> 7) {
			PORT_SDA |= (1 << SDA);
		}
		else {
			PORT_SDA &= ~(1 << SDA);
		}
		PORT_SCL |= (1 << SCL);

		dat <<= 1;
	}
}

static void oled_cmd(uint8_t cmd)
{
	PORT_DC &= ~(1 << DC);

	oled_write_spi(cmd);
}

static void oled_data(uint8_t cmd)
{
	PORT_DC |= (1 << DC);

	oled_write_spi(cmd);
}

static void oled_reset(void)
{
	PORT_RST &= ~(1 << RST);

	// From SSD1306 datasheet. Delay > 3us
	// i > 4 or else replaced by 4x nop.
	// 5 cycles pr. loop. 16MHz->312,5ns
	// 16MHz, i = 10, 3.1ms.
	for (int i = 1; i < 20; i++) {
		asm volatile("nop\t\n"
					 :);
	}

	PORT_RST |= (1 << RST);
}

void oled_putc(uint8_t character)
{
	for (int i = 0; i < FONT_WIDTH; i++) {
		oled_data(pgm_read_byte(&(ASCII[character - ' '][i])));
	}

	oled_data(0x00);  // Add space to next character;
}

void oled_setpos(uint8_t pos, uint8_t line)
{
	pos = pos * 6;

	oled_cmd(0x20);						   // set page addressing mode
	oled_cmd(0x02);						   //
	oled_cmd(0xb0 | line);				   // set page start address to page 0
	oled_cmd(pos & 0x0F);				   // set lower column start address
	oled_cmd(0x10 + ((pos & 0xF0) >> 4));  // set upper column start address
}

void oled_putc_pos(uint8_t character, uint8_t pos, uint8_t line)
{
	oled_setpos(pos, line);

	oled_putc(character);
}

void oled_init(void)
{
	// Set output pins
	DDR(PORT_DC) |= (1 << DC);
	DDR(PORT_SDA) |= (1 << SDA);
	DDR(PORT_SCL) |= (1 << SCL);
	DDR(PORT_RST) |= (1 << RST);

	oled_reset();

	for (int i = 0; i < sizeof(OLED_INIT); i++) {
		oled_cmd(pgm_read_byte(&(OLED_INIT[i])));
	}
}

void oled_puts(char *characters)
{
	if (!characters)
		return;

	while (*characters) {
		oled_putc(*characters++);
	}
}

void oled_puts_P(const char *characters)
{
	char c;

	if (!characters)
		return;

	while ((c = pgm_read_byte(characters++))) {
		oled_putc(c);
	}
}

void oled_puts_pos(char *characters, uint8_t pos, uint8_t line)
{
	oled_setpos(pos, line);

	if (!characters)
		return;

	while (*characters) {
		oled_putc(*characters++);
	}
}

void oled_puts_pos_P(const char *characters, uint8_t pos, uint8_t line)
{
	oled_setpos(pos, line);

	char c;

	if (!characters)
		return;

	while ((c = pgm_read_byte(characters++))) {
		oled_putc(c);
	}
}

void oled_flip(uint8_t rotate)
{
	if (rotate) {
		oled_cmd(0xa1);  // set segment re-map (horizontal flip) - reset value is 0xa0 (or 0xa1)
		oled_cmd(0xc8);  // set COM output scan direction (vertical flip) - reset value is 0xc0 (or 0xc8)
	}
	else {
		oled_cmd(0xa0);  // set segment re-map (horizontal flip) - reset value is 0xa0 (or 0xa1)
		oled_cmd(0xc0);  // set COM output scan direction (vertical flip) - reset value is 0xc0 (or 0xc8)
	}
}

void oled_contrast(uint8_t contrast)
{
	oled_cmd(0x81);
	oled_cmd(contrast);
}

void oled_clear(void)
{
	oled_cmd(0x20);  // set horizontal addressing mode for screen clear
	oled_cmd(0x01);

	for (int i = 0; i < 1024; i++) {
		oled_data(0x00);  // clear oled screen
	}

	oled_setpos(0, 0);
}
