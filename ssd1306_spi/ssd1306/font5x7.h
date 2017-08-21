/*
 * font5x7.h
 *
 * Created: 19.08.2017 23:23:09
 *  Author: Frode Hansen
 */

#ifndef FONT5X7_H_
#define FONT5X7_H_

#define FONT_CHARS 96
#define FONT_WIDTH 5

#include <avr/pgmspace.h>

const unsigned char ASCII[FONT_CHARS][FONT_WIDTH];

#endif /* FONT5X7_H_ */