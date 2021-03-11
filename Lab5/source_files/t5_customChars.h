#ifndef ESOS_LCD44780_CUSTOMCHARS
#define ESOS_LCD44780_CUSTOMCHARS

#include "esos_lcd44780.h"


static uint8_t char_BAR1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F };
static uint8_t char_BAR2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F };
static uint8_t char_BAR3[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F };
static uint8_t char_BAR4[8] = { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F };
static uint8_t char_BAR5[8] = { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
static uint8_t char_BAR6[8] = { 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
static uint8_t char_BAR7[8] = { 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
static uint8_t char_BAR8[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

enum custom_chars_bar {
    BAR1,
    BAR2,
    BAR3,
    BAR4,
    BAR5,
    BAR6,
    BAR7,
    BAR8,
};

/*
000 00000     0x00
000 00000     0x00
000 00000     0x00
000 11111     0x1F
000 00000     0x00
000 00000     0x00
000 00000     0x00
000 00000     0x00
*/
//These are still kind of chars, but the esos_lcd44780_setCustomChar() function in esos_lcd44780.c (line 312 expects a uint8_t)
//static uint8_t pot_slider_line[8] = 0x0000001F00000000;
static uint8_t pot_slider_line[8] = { 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00};

/*
000 00001     0x01
000 00001     0x01
000 00001     0x01
000 11111     0x1F
000 00001     0x01
000 00001     0x01
000 00001     0x01
000 00000     0x00
*/
//static uint8_t pot_slider_pos5[8] = 0x0101011F01010100;
static uint8_t pot_slider_pos5[8] = { 0x01, 0x01, 0x01, 0x1F, 0x01, 0x01, 0x01, 0x00};

/*
000 00010     0x02
000 00010     0x02
000 00010     0x02
000 11111     0x1F
000 00010     0x02
000 00010     0x02
000 00010     0x02
000 00000     0x00
*/
//static uint8_t pot_slider_pos4[8] = 0x0202021F02020200;
static uint8_t pot_slider_pos4[8] = { 0x02, 0x02, 0x02, 0x1F, 0x02, 0x02, 0x02, 0x00};

/*
000 00100     0x04
000 00100     0x04
000 00100     0x04
000 11111     0x1F
000 00100     0x04
000 00100     0x04
000 00100     0x04
000 00000     0x00
*/
//static uint8_t pot_slider_pos3[8] = 0x0404041F04040400;
static uint8_t pot_slider_pos3[8] = { 0x04, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x04, 0x00};

/*
000 01000     0x08
000 01000     0x08
000 01000     0x08
000 11111     0x1F
000 01000     0x08
000 01000     0x08
000 01000     0x08
000 00000     0x00
*/
//static uint8_t pot_slider_pos2[8] = 0x0808081F08080800;
static uint8_t pot_slider_pos2[8] = { 0x08, 0x08, 0x08, 0x1F, 0x08, 0x08, 0x08, 0x00};

/*
000 10000     0x10
000 10000     0x10
000 10000     0x10
000 11111     0x1F
000 10000     0x10
000 10000     0x10
000 10000     0x10
000 00000     0x00
*/
//static uint8_t pot_slider_pos1[8] = 0x1010101F10101000;
static uint8_t pot_slider_pos1[8] = { 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x10, 0x00};
enum custom_chars_slider {
    SLIDER_LINE,
    SLIDER_POS1,
    SLIDER_POS2,
    SLIDER_POS3,
    SLIDER_POS4,
    SLIDER_POS5,
};

void esos_lcd44780_bar_init() {
    esos_lcd44780_setCustomChar(BAR1, char_BAR1);
    esos_lcd44780_setCustomChar(BAR2, char_BAR2);
    esos_lcd44780_setCustomChar(BAR3, char_BAR3);
    esos_lcd44780_setCustomChar(BAR4, char_BAR4);
    esos_lcd44780_setCustomChar(BAR5, char_BAR5);
    esos_lcd44780_setCustomChar(BAR6, char_BAR6);
    esos_lcd44780_setCustomChar(BAR7, char_BAR7);
    esos_lcd44780_setCustomChar(BAR8, char_BAR8);
}
void esos_lcd44780_slider_init() {
    esos_lcd44780_setCustomChar(SLIDER_LINE, pot_slider_line);
    esos_lcd44780_setCustomChar(SLIDER_POS1, pot_slider_pos1);
    esos_lcd44780_setCustomChar(SLIDER_POS2, pot_slider_pos2);
    esos_lcd44780_setCustomChar(SLIDER_POS3, pot_slider_pos3);
    esos_lcd44780_setCustomChar(SLIDER_POS4, pot_slider_pos4);
    esos_lcd44780_setCustomChar(SLIDER_POS5, pot_slider_pos5);
}

#endif