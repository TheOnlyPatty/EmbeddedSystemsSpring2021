// prevents errors if header is included multiple times and begins "definition"
// of the REVF14_H token
#ifndef REVF14_H
#define REVF14_H
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

#define SW1 (!_RB13)
#define SW2 (!_RB12)
#define SW3 (!_RC15)

#define SW1_PRESSED (_RB13 == 0)
#define SW1_RELEASED (_RB13 == 1)
#define SW2_PRESSED (_RB12 == 0)
#define SW2_RELEASED (_RB12 == 1)
#define SW3_PRESSED (_RC15 == 0)
#define SW3_RELEASED (_RC15 == 1)

#define CONFIG_SW1() \
	CONFIG_RB13_AS_DIG_INPUT(); \
	ENABLE_RB13_PULLUP(); \
	DELAY_US(1)

#define CONFIG_SW2() \
	CONFIG_RB12_AS_DIG_INPUT(); \
	ENABLE_RB12_PULLUP(); \
	DELAY_US(1)

#define CONFIG_SW3() \
	CONFIG_RC15_AS_DIG_INPUT(); \
	ENABLE_RC15_PULLUP(); \
	DELAY_US(1)

#define RPGA (_RB8)
#define RPGB (_RB9)

#define CONFIG_RPG() \
    CONFIG_RB8_AS_DIG_INPUT(); \
    CONFIG_RB9_AS_DIG_INPUT(); \
    ENABLE_RB8_PULLUP(); \
    ENABLE_RB9_PULLUP(); \
    DELAY_US(1)

#define POT (RB2_AN)
#define POT_CHANNEL ESOS_SENSOR_CH02
#define CONFIG_POT() CONFIG_RB2_AS_ANALOG()

#define THERM (RB3_AN)
#define THERM_CHANNEL ESOS_SENSOR_CH03
#define CONFIG_THERM() CONFIG_RB3_AS_ANALOG()

#define LCD_E (_LATD10)
#define LCD_RW (_LATD11)
#define LCD_RS (_LATC12)
#define LCD_DB0 (_LATE0)
#define LCD_DB1 (_LATE1)
#define LCD_DB2 (_LATE2)
#define LCD_DB3 (_LATE3)
#define LCD_DB4 (_LATE4)
#define LCD_DB5 (_LATE5)
#define LCD_DB6 (_LATE6)
#define LCD_DB7 (_LATE7)

#define ESOS_LCD_IN_OUTPUT_MODE ESOS_USER_FLAG_8

#define LCD44780_CONFIG_BASIC() \
    CONFIG_RD10_AS_DIG_OUTPUT(); /*Enable*/ \
    CONFIG_RD11_AS_DIG_OUTPUT(); /*Read/Write*/ \
    CONFIG_RC12_AS_DIG_OUTPUT() /*Register Select*/

#define LCD44780_CONFIG_OUTPUT() \
    CONFIG_RE0_AS_DIG_OUTPUT(); /*DB0 (output)*/ \
    DISABLE_RE0_PULLUP(); \
    CONFIG_RE1_AS_DIG_OUTPUT(); /*DB1 (output)*/ \
    DISABLE_RE1_PULLUP(); \
    CONFIG_RE2_AS_DIG_OUTPUT(); /*DB2 (output)*/ \
    DISABLE_RE2_PULLUP(); \
    CONFIG_RE3_AS_DIG_OUTPUT(); /*DB3 (output)*/ \
    DISABLE_RE3_PULLUP(); \
    CONFIG_RE4_AS_DIG_OUTPUT(); /*DB4 (output)*/ \
    DISABLE_RE4_PULLUP(); \
    CONFIG_RE5_AS_DIG_OUTPUT(); /*DB5 (output)*/ \
    DISABLE_RE5_PULLUP(); \
    CONFIG_RE6_AS_DIG_OUTPUT(); /*DB6 (output)*/ \
    DISABLE_RE6_PULLUP(); \
    CONFIG_RE7_AS_DIG_OUTPUT(); /*DB7 (output)*/ \
    DISABLE_RE7_PULLUP(); \
    DELAY_US(1)

#define LCD44780_CONFIG_INPUT() \
    CONFIG_RE0_AS_DIG_INPUT(); /*DB0 (input)*/ \
    ENABLE_RE0_PULLUP(); \
    CONFIG_RE1_AS_DIG_INPUT(); /*DB1 (input)*/ \
    ENABLE_RE1_PULLUP(); \
    CONFIG_RE2_AS_DIG_INPUT(); /*DB2 (input)*/ \
    ENABLE_RE2_PULLUP(); \
    CONFIG_RE3_AS_DIG_INPUT(); /*DB3 (input)*/ \
    ENABLE_RE3_PULLUP(); \
    CONFIG_RE4_AS_DIG_INPUT(); /*DB4 (input)*/ \
    ENABLE_RE4_PULLUP(); \
    CONFIG_RE5_AS_DIG_INPUT(); /*DB5 (input)*/ \
    ENABLE_RE5_PULLUP(); \
    CONFIG_RE6_AS_DIG_INPUT(); /*DB6 (input)*/ \
    ENABLE_RE6_PULLUP(); \
    CONFIG_RE7_AS_DIG_INPUT(); /*DB7 (input)*/ \
    ENABLE_RE7_PULLUP(); \
    DELAY_US(1)

#endif // closes the #ifndef block
