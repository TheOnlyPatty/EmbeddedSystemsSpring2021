// prevents errors if header is included multiple times and begins "definition"
// of the REVF14_H token
#ifndef REVF14_H
#define REVF14_H
#define NUM_UART_MODS 1
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

inline void CONFIG_SW1()
{
	CONFIG_RB13_AS_DIG_INPUT();
	ENABLE_RB13_PULLUP();
	DELAY_US(1);
}
inline void CONFIG_SW2()
{
	CONFIG_RB12_AS_DIG_INPUT();
	ENABLE_RB12_PULLUP();
	DELAY_US(1);
}
inline void CONFIG_SW3()
{
	CONFIG_RC15_AS_DIG_INPUT();
	ENABLE_RC15_PULLUP();
	DELAY_US(1);
}

#define RPGA (_RB8)
#define RPGB (_RB9)

inline void CONFIG_RPG()  {
    CONFIG_RB8_AS_DIG_INPUT();
    CONFIG_RB9_AS_DIG_INPUT();
    ENABLE_RB8_PULLUP();
    ENABLE_RB9_PULLUP();
    DELAY_US(1);
}

#define POT (RB2_AN)
#define CONFIG_POT() CONFIG_RB2_AS_ANALOG()

#define THERM (RB3_AN)
#define CONFIG_THERM() CONFIG_RB3_AS_ANALOG()

inline void CONFIG_ADC() {
    AD1CON1bits.ADON    = 0b0;    //Turn ADC off
    AD1CON1bits.ADSIDL  = 0b0;    //Continue module operation in Idle mode
    AD1CON1bits.FORM    = 0b0;    //Integer 16-bit (DOUT = 0000 0000 0000 0000 0000 00dd dddd dddd)
    AD1CON1bits.SSRC    = 0b111;  //Internal counter ends sampling and starts conversion (auto convert)
    AD1CON1bits.CLRASAM = 0b111;  //Normal operation, buffer contents will be overwritten by the next conversion sequence
    AD1CON1bits.ASAM    = 0b0;    //Sampling begins when SAMP bit is set (change this to auto-sample)
    AD1CON1bits.SAMP    = 0b0;    //The ADC sample/hold amplifier is holding
    AD1CON1bits.DONE    = 0b0;    //Analog-to-digital conversion is not done or has not started
//    AD1CON1bits.ADDMABM = 0b1;  //DMA Buffers written in order of conversion
//    AD1CON1bits.AD12B = 0b1;    //Enable 12 bit mode
//    AD1CON1bits.SSRCG = 0b0;    //Sample clock source group
    
    AD1CON2bits.VCFG    = 0b001;  //Set ADC VR+ to VREF+ pin and VR- to AVSS pin
    AD1CON2bits.OFFCAL  = 0b0;    //Disable Offset Calibration mode
    AD1CON2bits.CSCNA   = 0b0;    //Do not scan inputs
    AD1CON2bits.SMPI    = 0b0000; //Interrupts at the completion of conversion for each sample/convert sequence
    AD1CON2bits.BUFM    = 0b0;    //Buffer configured as one 16-word buffer ADC1BUF(15...0.)
    AD1CON2bits.ALTS    = 0b0;    //Always use MUX A input multiplexer settings
//    AD1CON2bits.CHPS    = 0b00; //Channel select bits
    
    AD1CON3bits.ADRC    = 0b1;    //ADC internal RC clock
    AD1CON3bits.SAMC    = 0b11111;//Auto-sample Time bits: 31 TAD */
//    AD1CON4bits.ADDMAEN = 0b0;
    AD1CON1bits.ADON = 1;
    }


#endif // closes the #ifndef block
