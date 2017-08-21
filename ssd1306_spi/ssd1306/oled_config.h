/*
* oled_config.h
*
* Created: 19.08.2017 23:23:31
*  Author: Frode Hansen
*
* Pin config for SSD1306 0,96" 128x64 SPI
*
* GND VCC SCLK SDIN RST DC
*
*/

#ifndef OLED_CONFIG_H_
#define OLED_CONFIG_H_

#include "font5x7.h"

#define PIN(x) (*(&x - 2))  // Address Of Data Direction Register Of Port x
#define DDR(x) (*(&x - 1))  // Address Of Input Register Of Port x
#define PORT(x) (x)

#define PORT_SCL PORTB  // SPI Clock
#define SCL 4

#define PORT_SDA PORTB  // SPI Data
#define SDA 5

#define PORT_RST PORTB  // SSD1306 Reset
#define RST 6

#define PORT_DC PORTB  // SSD1306 Data/Command
#define DC 7

#endif /* OLED_CONFIG_H_ */