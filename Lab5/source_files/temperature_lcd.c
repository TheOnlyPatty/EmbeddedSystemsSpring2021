#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "esos_sensor.h"
#include "revF14.h"
#include <stdio.h>

//static char str_INSTRUCTIONS1[] = "Press SW1 to sample the temperature once.\nPress SW2 to begin sampling the temperature once per second.\nPress SW3 for further options.\n\n";
//static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 or SW3 to quit sampling.\n";
static char str_POT_READING[] = "Pot Reading: ";
static char str_TEMP_READING[] = "Temp Reading: ";
static char str_CELSIUS[] = " Celsius\n";
static char str_EQUALS[] = " = ";

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
                if (MENU_STATE == CONTINUOUS_POT)
                    MENU_STATE = CONTINUOUS_TEMP;
                else 
                    MENU_STATE = CONTINUOUS_POT;
            }
        }
            
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

static uint16_t u16_data;
//static uint8_t u8_input = 0x00;

ESOS_USER_TASK(SerialOutput) {
    static uint32_t u32_temp_temp;
    static uint32_t u32_temp_int;
    static uint32_t u32_temp_dec;
    static char str_temp_temp[12];
    ESOS_TASK_BEGIN();
    while (1) {
        if(MENU_STATE == CONTINUOUS_POT) {
            /*
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS2);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            */
            ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL, ESOS_SENSOR_VREF_3V3);
            while(MENU_STATE == CONTINUOUS_POT) {
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, processing_mode, ESOS_SENSOR_FORMAT_BITS);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(str_POT_READING);
                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
                ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_TICKS(1000);
            }
            ESOS_SENSOR_CLOSE();
		}
        else if(MENU_STATE == CONTINUOUS_TEMP) {
            /*
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS2);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            */
            ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
            while(MENU_STATE == CONTINUOUS_TEMP) {
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_VOLTAGE);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();

                // Convert from voltage in mV to temperature in Celsius
                u32_temp_temp = (uint32_t)u16_data * 1000; // no decimals
                u32_temp_temp = (u32_temp_temp - 424000) / 625; // see datasheet page 1 "Typical Application" for formula
                u32_temp_int = u32_temp_temp / 100; // integer only
                u32_temp_dec = u32_temp_temp - (u32_temp_int * 100); // decimal only

                ESOS_TASK_WAIT_ON_SEND_STRING(str_TEMP_READING);
                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
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
                ESOS_TASK_WAIT_TICKS(1000);
            }
            ESOS_SENSOR_CLOSE();
            //MENU_STATE = INSTRUCT;
        }
        


        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
//    config_ui_menu();
    esos_uiF14_flashLED3(1000); //1000 ms flash on LED3. (Heartbeat)
    MENU_STATE = CONTINUOUS_POT;
    esos_RegisterTask(SerialOutput);
    esos_RegisterTask(StateChange);

}
