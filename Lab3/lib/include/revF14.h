#pragma once

#include "pic24_all.h"

// pin names used from https://courses.ece.msstate.edu/ece4723/fall17/lab/schematic_revF14.pdf
// based on example files given in pic24lib_all folder

#define CONFIG_LED1() CONFIG_RF4_AS_DIG_OUTPUT()
#define LED1  (_LATF4) //green led

#define CONFIG_LED2() CONFIG_RB14_AS_DIG_OUTPUT()
#define LED2  (_LATB14) //yellow led

#define CONFIG_LED3() CONFIG_RB15_AS_DIG_OUTPUT()
#define LED3  (_LATB15) // red led


void CONFIG_SW1() 
{
	CONFIG_RB13_AS_DIG_INPUT();
	ENABLE_RB13_PULLUP();
	DELAY_US(1);
}

void CONFIG_SW2() 
{
	CONFIG_RB12_AS_DIG_INPUT();
	ENABLE_RB12_PULLUP();
	DELAY_US(1);
}

void CONFIG_SW3()  
{
	CONFIG_RC15_AS_DIG_INPUT();
	ENABLE_RC15_PULLUP();
	DELAY_US(1);
}

void CONFIG_RGB()
{
    CONFIG_RB8_AS_DIG_INPUT();
    CONFIG_RB9_AS_DIG_INPUT();
    ENABLE_RB8_PULLUP();
    ENABLE_RB9_PULLUP();
    DELAY_US(1);
}

#define RPGA (_RB8)
#define RPGB (_RB9)

#define SW1_PRESSED (_RB13 == 0)
#define SW1_RELEASED (_RB13 == 1)

#define SW2_PRESSED (_RB12 == 0)
#define SW2_RELEASED (_RB12 == 1)

#define SW3_PRESSED (_RC15 == 0)
#define SW3_RELEASED (_RC15 == 1)
