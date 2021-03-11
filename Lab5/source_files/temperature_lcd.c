#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "esos_sensor.h"
#include "esos_pic24_sensor.h"
#include "esos_lcd44780.h"
#include "revF14.h"
#include "t5_customChars.h"
#include <stdio.h>

#define REFRESH_RATE 150 // Prevents crashes of BullyCPP. Adjust for taste.

//static char str_INSTRUCTIONS1[] = "Press SW1 to sample the temperature once.\nPress SW2 to begin sampling the temperature once per second.\nPress SW3 for further options.\n\n";
//static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 or SW3 to quit sampling.\n";
static char str_POT_READING[] = "Pot Reading: ";
static char str_TEMP_READING[] = "Temp Reading: ";
static char str_CELSIUS[] = " Celsius\n";
static char str_EQUALS[] = " = ";
static uint16_t refresh_timer;

//static uint8_t u8_option1 = 0;
//static uint8_t u8_option2 = 0;

static esos_sensor_process_t processing_mode;

// LM60 Datasheet
// https://courses.ece.msstate.edu/ece4723/datasheets/LM60.pdf

static enum STATE {
    CONTINUOUS_POT,
    CONTINUOUS_TEMP,
} MENU_STATE;

ESOS_USER_TASK(StateChange) {
    // SW3_STATE controls whether pot is used or temp
    static BOOL SW3_STATE;
    ESOS_TASK_BEGIN();
    while (1) {
        if (SW3_STATE != esos_uiF14_isSW3Pressed()) {
            SW3_STATE = esos_uiF14_isSW3Pressed();
            if (SW3_STATE) {
                if (MENU_STATE == CONTINUOUS_POT) {
                    MENU_STATE = CONTINUOUS_TEMP;
                    esos_lcd44780_clearScreen();
                }
                else {
                    MENU_STATE = CONTINUOUS_POT;
                    esos_lcd44780_clearScreen();
                }
            }
        }
            
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

static uint16_t pu16_data; // Receives data from sensors (using pointers)
//static uint8_t u8_input = 0x00;

ESOS_USER_TASK(SerialOutput) {
    // Variables for temperature calculation
    static uint32_t u32_temp_temp;
    static uint32_t u32_temp_int;
    static uint32_t u32_temp_dec;
    static char str_temp_temp[12];

    ESOS_TASK_BEGIN();
    while (1) {
        if (refresh_timer >= REFRESH_RATE) {
            refresh_timer = 0; // Reset timer whenever timer exceeds refresh rate
            if(MENU_STATE == CONTINUOUS_POT) {
                esos_lcd44780_slider_init();
                ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL, ESOS_SENSOR_VREF_3V3);
                //while(MENU_STATE == CONTINUOUS_POT) {
                ESOS_TASK_WAIT_SENSOR_READ(pu16_data, processing_mode, ESOS_SENSOR_FORMAT_BITS);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(str_POT_READING);
                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(pu16_data);
                ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                //ESOS_TASK_WAIT_TICKS(1000);
                //}
                ESOS_SENSOR_CLOSE();

                esos_lcd44780_writeString(0, 0, "pot 0x");

                static uint8_t au8_slider[8];
                static char pot_value[3];
                static uint8_t i;
                for (i = 0; i < 8; i++) {
                    au8_slider[i] = SLIDER_LINE;
                }

                i = pu16_data >> 9;

                au8_slider[i] = (((pu16_data & 0x1FF) / 0x067) + 1);
                uint32_to_str(pu16_data >> 4, pot_value, 3);

                /*
                printf("\n\n");
                static int j = 0;
                for (j = 0; j < 3; j++) {
                    printf("%u", au8_slider[j]);
                }
                printf("\n\n");
                */

                esos_lcd44780_writeString(0, 6, pot_value);
                esos_lcd44780_writeBuffer(1, 0, au8_slider, 8);
            }
            else if(MENU_STATE == CONTINUOUS_TEMP) {
                ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
                //while(MENU_STATE == CONTINUOUS_TEMP) {
                ESOS_TASK_WAIT_SENSOR_READ(pu16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_VOLTAGE);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();

                // Convert from voltage in mV to temperature in Celsius
                u32_temp_temp = (uint32_t)pu16_data * 1000; // no decimals
                u32_temp_temp = (u32_temp_temp - 424000) / 625; // see datasheet page 1 "Typical Application" for formula
                u32_temp_int = u32_temp_temp / 100; // integer only
                u32_temp_dec = u32_temp_temp - (u32_temp_int * 100); // decimal only

                ESOS_TASK_WAIT_ON_SEND_STRING(str_TEMP_READING);
                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(pu16_data);
                ESOS_TASK_WAIT_ON_SEND_STRING(str_EQUALS);
                uint32_to_str(u32_temp_int, str_temp_temp, 12);
                ESOS_TASK_WAIT_ON_SEND_STRING(str_temp_temp);
                    ESOS_TASK_WAIT_ON_SEND_UINT8('.');
                    if (u32_temp_dec >= 0 && u32_temp_dec <= 9) {
                        ESOS_TASK_WAIT_ON_SEND_UINT8('0');
                    }
                    uint32_to_str(u32_temp_dec, str_temp_temp, 12);
                    ESOS_TASK_WAIT_ON_SEND_STRING(str_temp_temp);
                    ESOS_TASK_WAIT_ON_SEND_STRING(str_CELSIUS);
                    
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                //ESOS_TASK_WAIT_TICKS(1000);

            }
            ESOS_SENSOR_CLOSE();
                //MENU_STATE = INSTRUCT;
            //}

        }

        else {
            refresh_timer += 10;
            ESOS_TASK_WAIT_TICKS(10);
            //continue;
        }
        
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
    esos_lcd44780_init();
    esos_lcd44780_configDisplay();
//    config_ui_menu();
    esos_uiF14_flashLED3(1000); //1000 ms flash on LED3. (Heartbeat)
    MENU_STATE = CONTINUOUS_POT;
    esos_RegisterTask(SerialOutput);
    esos_RegisterTask(StateChange);

}
