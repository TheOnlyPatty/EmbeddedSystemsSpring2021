/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */

#include "esos_pic24_lcd.h"


void __esos_lcd44780_pic24_config ( void ) //TODO: not finished
{
    // Set up the hardware aspects of the pic24 interface of the LCD module service
    //    direction, thresholds, etc beyond what is already done in esos_lcd44780_config()
    
    LCD44780_CONFIG_BASIC();
}

void __esos_lcd44780_pic24_setDataPins( uint8_t u8_data) { //write u8_data to data pins
    __esos_lcd44780_pic24_configDataPinsAsOutput();
    //TODO: may need to send a command or assert a bit here to write
    LCD_DB0 = u8_data && 0b00000001;
    LCD_DB1 = u8_data && 0b00000010;
    LCD_DB2 = u8_data && 0b00000100;
    LCD_DB3 = u8_data && 0b00001000;
    LCD_DB4 = u8_data && 0b00010000;
    LCD_DB5 = u8_data && 0b00100000;
    LCD_DB6 = u8_data && 0b01000000;
    LCD_DB7 = u8_data && 0b10000000;
    return;
}

uint8_t __esos_lcd44780_pic24_getDataPins( void ) { //read u8_data to data pins
    __esos_lcd44780_pic24_configDataPinsAsInput();
    //TODO: may need to send a command or assert a bit here to read
    uint8_t u8_read_buffer = (
        LCD_DB0 << 0 |
        LCD_DB1 << 1 |
        LCD_DB2 << 2 |
        LCD_DB3 << 3 |
        LCD_DB4 << 4 |
        LCD_DB5 << 5 |
        LCD_DB6 << 6 |
        LCD_DB7 << 7 );
    return u8_read_buffer;
}

void __esos_lcd44780_pic24_configDataPinsAsInput( void ) { //Configure data pins as inputs and clear esos user flag
    if(esos_IsUserFlagSet(ESOS_LCD_IN_OUTPUT_MODE)) {
        LCD44780_CONFIG_INPUT();
        esos_ClearUserFlag(ESOS_LCD_IN_OUTPUT_MODE);
    }
}

void __esos_lcd44780_pic24_configDataPinsAsOutput( void ) { //Configure data pins as outputs and set esos user flag
    if(!esos_IsUserFlagSet(ESOS_LCD_IN_OUTPUT_MODE)) {
        LCD44780_CONFIG_OUTPUT();
        esos_SetUserFlag(ESOS_LCD_IN_OUTPUT_MODE);
    }
}
