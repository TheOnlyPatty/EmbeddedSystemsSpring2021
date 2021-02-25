#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include "esos_sensor.h"
#include "revF14.h"
#include <stdio.h>

static char str_INSTRUCTIONS1[] = "Press SW1 to sample the temperature once.\nPress SW2 to begin sampling the temperature once per second.\nPress SW3 for further options.\n\n";
static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 to quit sampling.\n";
static char str_ONE_SHOT_POT_PRE[] = "Temperature reading: ";
static char str_OPTIONS1[] = "Use the numbers on your keyboard to select an option.\n1. one-shot\n2. average\n3. minimum\n4. maximum\n5. median\n\n";
static char str_OPTIONS2[] = "1. two\n2. four\n3. eight\n4. sixteen\n5. thirty-two\n6. sixty-four\n\n";
static char str_AVG[] = "Average: ";
static char str_MIN[] = "Minimum: ";
static char str_MAX[] = "Maximum: ";
static char str_MEDIAN[] = "Median: ";
static char str_CELSIUS[] = " Celsius\n";
static char str_EQUALS[] = " = ";

static uint8_t u8_option1 = 0;
static uint8_t u8_option2 = 0;

static esos_sensor_process_t processing_mode;

// LM60 Datasheet
// https://courses.ece.msstate.edu/ece4723/datasheets/LM60.pdf

static enum STATE {
    INSTRUCT,
    WAIT,
    ONE_SHOT,
    CONTINUOUS,
    OPTIONS,
    OPTIONS2,
    OPTIONS_MODE,
    EXECUTE,
} MENU_STATE;

ESOS_USER_TASK(StateChange) {
    static BOOL SW1_STATE, SW2_STATE, SW3_STATE;
    ESOS_TASK_BEGIN();
    while (1) {
        if (SW1_STATE != esos_uiF14_isSW1Pressed()) { //Require a release before changing state again
            SW1_STATE = esos_uiF14_isSW1Pressed();
            if (SW1_STATE) {
                if (MENU_STATE == CONTINUOUS) 
                    MENU_STATE = INSTRUCT;
                else {
                    processing_mode = ESOS_SENSOR_ONE_SHOT;
                    MENU_STATE = EXECUTE;
                }
            }
        }
        if (SW2_STATE != esos_uiF14_isSW2Pressed()) { //Require a release before changing state again
            SW2_STATE = esos_uiF14_isSW2Pressed();
            if (SW2_STATE) {
                if (MENU_STATE == CONTINUOUS)
                    MENU_STATE = INSTRUCT;
                else
                    MENU_STATE = CONTINUOUS;
            }
        }
        if (SW3_STATE != esos_uiF14_isSW3Pressed()) {
            SW3_STATE = esos_uiF14_isSW3Pressed();
            if (SW3_STATE) {
                if (MENU_STATE == CONTINUOUS)
                    MENU_STATE = INSTRUCT;
                else
                    MENU_STATE = OPTIONS;
            }
        }
            
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

static uint16_t u16_data;
static uint8_t u8_input = 0x00;

ESOS_USER_TASK(SerialOutput) {
    static uint32_t u32_temp_temp;
    static uint32_t u32_temp_int;
    static uint32_t u32_temp_dec;
    static char str_temp_temp[12];
    ESOS_TASK_BEGIN();
    while (1) {
        if(MENU_STATE == INSTRUCT) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS1);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            MENU_STATE = WAIT;
        }
        else if(MENU_STATE == WAIT) {
            
        }
        else if(MENU_STATE == CONTINUOUS) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS2);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
            while(MENU_STATE == CONTINUOUS) {
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_VOLTAGE);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();

                // Convert from voltage in mV to temperature in Celsius
                u32_temp_temp = (uint32_t)u16_data * 1000; // no decimals
                u32_temp_temp = (u32_temp_temp - 424000) / 625; // see datasheet page 1 "Typical Application" for formula
                u32_temp_int = u32_temp_temp / 100; // integer only
                u32_temp_dec = u32_temp_temp - (u32_temp_int * 100); // decimal only

                ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE);
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
            MENU_STATE = INSTRUCT;
        }
        else if(MENU_STATE == OPTIONS) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_OPTIONS1);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

            u8_option1 = u8_input;

            if (u8_option1 == '1'){
                processing_mode = ESOS_SENSOR_ONE_SHOT;
				MENU_STATE = EXECUTE;
            }
            else
                MENU_STATE = OPTIONS2;

        }
        else if(MENU_STATE == OPTIONS2) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_OPTIONS2);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

            u8_option2 = u8_input;

            MENU_STATE = OPTIONS_MODE;
        }
        // Sets the processing mode depending on the user input
        else if(MENU_STATE == OPTIONS_MODE) {
            switch (u8_option1) {
				
            // This case should never happen
			case '1':
                processing_mode = ESOS_SENSOR_ONE_SHOT;
				MENU_STATE = EXECUTE;
				break;
				
			case '2':
				switch (u8_option2) {
                    case '1':
                        processing_mode = ESOS_SENSOR_AVG2;
                        break;
                    case '2':
                        processing_mode = ESOS_SENSOR_AVG4;
                        break;
                    case '3':
                        processing_mode = ESOS_SENSOR_AVG8;
                        break;
                    case '4':
                        processing_mode = ESOS_SENSOR_AVG16;
                        break;
                    case '5':
                        processing_mode = ESOS_SENSOR_AVG32;
                        break;
                    case '6':
                        processing_mode = ESOS_SENSOR_AVG64;
                        break;
                }   
				break;
				
			case '3':
				switch (u8_option2) {
                    case '1':
                        processing_mode = ESOS_SENSOR_MIN2;
                        break;
                    case '2':
                        processing_mode = ESOS_SENSOR_MIN4;
                        break;
                    case '3':
                        processing_mode = ESOS_SENSOR_MIN8;
                        break;
                    case '4':
                        processing_mode = ESOS_SENSOR_MIN16;
                        break;
                    case '5':
                        processing_mode = ESOS_SENSOR_MIN32;
                        break;
                    case '6':
                        processing_mode = ESOS_SENSOR_MIN64;
                        break;
                }   
				break;
				
			case '4':
				switch (u8_option2) {
                    case '1':
                        processing_mode = ESOS_SENSOR_MAX2;
                        break;
                    case '2':
                        processing_mode = ESOS_SENSOR_MAX4;
                        break;
                    case '3':
                        processing_mode = ESOS_SENSOR_MAX8;
                        break;
                    case '4':
                        processing_mode = ESOS_SENSOR_MAX16;
                        break;
                    case '5':
                        processing_mode = ESOS_SENSOR_MAX32;
                        break;
                    case '6':
                        processing_mode = ESOS_SENSOR_MAX64;
                        break;
                }   
				break;
				
			case '5':
				switch (u8_option2) {
                    case '1':
                        processing_mode = ESOS_SENSOR_MEDIAN2;
                        break;
                    case '2':
                        processing_mode = ESOS_SENSOR_MEDIAN4;
                        break;
                    case '3':
                        processing_mode = ESOS_SENSOR_MEDIAN8;
                        break;
                    case '4':
                        processing_mode = ESOS_SENSOR_MEDIAN16;
                        break;
                    case '5':
                        processing_mode = ESOS_SENSOR_MEDIAN32;
                        break;
                    case '6':
                        processing_mode = ESOS_SENSOR_MEDIAN64;
                        break;
                }   
				break;
			
			default:
				MENU_STATE = WAIT;
				break;
			}
            MENU_STATE = EXECUTE;
        }
        else if(MENU_STATE == EXECUTE) {
            ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(THERM_CHANNEL, ESOS_SENSOR_VREF_3V0);
            ESOS_TASK_WAIT_SENSOR_READ(u16_data, processing_mode, ESOS_SENSOR_FORMAT_VOLTAGE);
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            // Convert from voltage in mV to temperature in Celsius
            u32_temp_temp = (uint32_t)u16_data * 1000; // no decimals
            u32_temp_temp = (u32_temp_temp - 424000) / 625; // see datasheet page 1 "Typical Application" for formula
            u32_temp_int = u32_temp_temp / 100; // integer only
            u32_temp_dec = u32_temp_temp - (u32_temp_int * 100); // decimal only

            ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE);
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
            ESOS_SENSOR_CLOSE();
            MENU_STATE = INSTRUCT;
        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
//    config_ui_menu();
    esos_uiF14_flashLED3(250); //250 ms flash on LED3. (Heartbeat)
    MENU_STATE = INSTRUCT;
    esos_RegisterTask(SerialOutput);
    esos_RegisterTask(StateChange);

}
