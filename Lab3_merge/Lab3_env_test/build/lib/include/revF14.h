// prevents errors if header is included multiple times and begins "definition"
// of the REVF14_H token
#ifndef REVF14_H
#define REVF14_H

#ifndef __dsPIC33EP512GP806__
#define __dsPIC33EP512GP806__
#endif

//#define NUM_UART_MODS 1
#include "pic24_all.h"



// The following definitions are more or less directly from the code examples
// supplied in Microprocessors
// https://www.google.com/url?q=http%3A%2F%2Fcourses.ece.msstate.edu%2Fece3724%2Fmain_pic24%2Flabs%2Ffiles%2Fpic24_code_examples.zip&sa=D&sntz=1&usg=AFQjCNGoPEjqijnThxBXTiBlNnussuN9Yw
// The difference being the pins they are connected to (RF4 instead of RB14, etc)
// Specific files used: ledflash_timer.c, ledsw1_cn.c
//


// LED1 - Green LED (Top, connected to RF4)
#define CONFIG_LED1() CONFIG_RF4_AS_DIG_OUTPUT()
#define LED1  (_LATF4)
#define LED1_ON() (LED1 = 1)
#define LED1_OFF() (LED1 = 0)

// LED2 - Yellow LED (Middle, connected to RB14)
#define CONFIG_LED2() CONFIG_RB14_AS_DIG_OUTPUT()
#define LED2  (_LATB14)
#define LED2_ON() (LED2 = 1)
#define LED2_OFF() (LED2 = 0)

// LED3 - Red LED (Bottom, connected to RB15)
#define CONFIG_LED3() CONFIG_RB15_AS_DIG_OUTPUT()
#define LED3  (_LATB15)
#define LED3_ON() (LED3 = 0)
#define LED3_OFF() (LED3 = 1)

#define SW1 (_RB13)
#define SW2 (_RB12)
#define SW3 (_RC15)



#define CONFIG_SW1()                                                                                               \
{                                                                                                                  \
    CONFIG_RB13_AS_DIG_INPUT();                                                                                    \
    ENABLE_RB13_PULLUP();                                                                                          \
    DELAY_US(1);                                                                                                   \
}

#define CONFIG_SW2()                                                                                               \
{                                                                                                                  \
    CONFIG_RB12_AS_DIG_INPUT();                                                                                    \
    ENABLE_RB12_PULLUP();                                                                                          \
    DELAY_US(1);                                                                                                   \
}

#define CONFIG_SW3()                                                                                               \
{                                                                                                                  \
    CONFIG_RC15_AS_DIG_INPUT();                                                                                    \
    ENABLE_RC15_PULLUP();                                                                                          \
    DELAY_US(1);                                                                                                   \
}

#define CONFIG_RPG()                                                                                               \
{                                                                                                                  \
  CONFIG_RB8_AS_DIG_INPUT();                                                                                       \
  CONFIG_RB9_AS_DIG_INPUT();                                                                                       \
  ENABLE_RB8_PULLUP();                                                                                             \
  ENABLE_RB9_PULLUP();                                                                                             \
  DELAY_US(1);                                                                                                     \
}

#define RPGA (_RB8)
#define RPGB (_RB9)

#define SW1_PRESSED (_RB13 == 0)
#define SW1_RELEASED (_RB13 == 1)

#define SW2_PRESSED (_RB12 == 0)
#define SW2_RELEASED (_RB12 == 1)

#define SW3_PRESSED (_RC15 == 0)
#define SW3_RELEASED (_RC15 == 1)

#endif // closes the #ifndef block
