
#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include "esos_sensor.h"
#include "revF14.h"
#include <stdio.h>

static char str_INSTRUCTIONS1[] = "Press SW1 to sample the potentiometer once.\nPress SW2 to begin sampling the potentiometer once per second.\nPress SW3 for further options.\n\n";
static char str_INSTRUCTIONS2[] = "Press SW1, SW2, or SW3 to quit sampling.\n";
static char str_ONE_SHOT_POT_PRE1[] = "Previous potentiometer reading: ";
static char str_ONE_SHOT_POT_PRE2[] = "Current potentiometer reading or calculation: ";

static esos_sensor_process_t processing_mode;

static enum STATE {
    INSTRUCT,
    WAIT,
    ONCE,
    CONTINUOUS,
    MENU,
} MENU_STATE;

ESOS_USER_TASK(StateChange) {
    static BOOL SW1_STATE, SW2_STATE, SW3_STATE = FALSE;
    ESOS_TASK_BEGIN();
    while (1) {
        if (SW1_STATE != esos_uiF14_isSW1Pressed()) { //Require a release before changing state again
            SW1_STATE = esos_uiF14_isSW1Pressed();
            if (SW1_STATE) {
                if (MENU_STATE == CONTINUOUS) 
                    MENU_STATE = INSTRUCT;
				
                else {
                    processing_mode = ESOS_SENSOR_ONE_SHOT;
                    MENU_STATE = ONCE;
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
                    MENU_STATE = MENU;
				
            }
        }
            
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

static uint16_t u16_data;


ESOS_USER_TASK(SerialOutput) {
    
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
        else if(MENU_STATE == ONCE) {
            uint8_t temp = 0;
            while (temp < 2){
                ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL, ESOS_SENSOR_VREF_3V3);
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, processing_mode, ESOS_SENSOR_FORMAT_BITS);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                if (temp == 0){
                    ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE1);
                    ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
                    ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                }
                else if (temp == 1){
                    ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE2);
                    ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
                    ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                }

                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                ESOS_SENSOR_CLOSE();
                temp++;
            }
            MENU_STATE = INSTRUCT;
        }
        else if(MENU_STATE == CONTINUOUS) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS2);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL, ESOS_SENSOR_VREF_3V3);
            while(MENU_STATE == CONTINUOUS) {
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, processing_mode, ESOS_SENSOR_FORMAT_BITS);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE2);
                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
                ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_TICKS(1000);
            }
            ESOS_SENSOR_CLOSE();
		}
		else if(MENU_STATE == MENU) {
            static uint8_t mode;
            static uint8_t sample_size;

			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();     
			ESOS_TASK_WAIT_ON_SEND_STRING("Mode Selection: \n");
			ESOS_TASK_WAIT_ON_SEND_STRING("1. one-shot\n");
			ESOS_TASK_WAIT_ON_SEND_STRING("2. average\n");
			ESOS_TASK_WAIT_ON_SEND_STRING("3. minimum\n");
			ESOS_TASK_WAIT_ON_SEND_STRING("4. maximum\n");
			ESOS_TASK_WAIT_ON_SEND_STRING("5. median\n");
			ESOS_TASK_WAIT_ON_SEND_STRING("**********************\n");
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM(); 
            ESOS_TASK_WAIT_ON_GET_UINT8(mode); 
            ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

            //one-shot
            if(mode == '1'){processing_mode = ESOS_SENSOR_ONE_SHOT; MENU_STATE = ONCE;}
            else {
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                //sample size shouldn't matter for one-shot, right? 
                //ESOS_TASK_WAIT_ON_SEND_STRING("Sample Size Selection (doesn't matter for one-shot): \n");
                ESOS_TASK_WAIT_ON_SEND_STRING("1. two\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("2. four\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("3. eight\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("4. sixteen\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("5. thirty-two\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("6. sixty-four\n");
                ESOS_TASK_WAIT_ON_SEND_STRING("**********************\n");
                //ESOS_TASK_WAIT_ON_SEND_STRING("> ");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
                ESOS_TASK_WAIT_ON_GET_UINT8(sample_size);
                ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

                //sets processing_mode based on input
                
                //avg
                if(mode == '2' && sample_size == '1'){processing_mode = ESOS_SENSOR_AVG2;}
                else if(mode == '2' && sample_size == '2'){processing_mode = ESOS_SENSOR_AVG4;}
                else if(mode == '2' && sample_size == '3'){processing_mode = ESOS_SENSOR_AVG8;}
                else if(mode == '2' && sample_size == '4'){processing_mode = ESOS_SENSOR_AVG16;}
                else if(mode == '2' && sample_size == '5'){processing_mode = ESOS_SENSOR_AVG32;}
                else if(mode == '2' && sample_size == '6'){processing_mode = ESOS_SENSOR_AVG64;}
                //min
                else if(mode == '3' && sample_size == '1'){processing_mode = ESOS_SENSOR_MIN2;}
                else if(mode == '3' && sample_size == '2'){processing_mode = ESOS_SENSOR_MIN4;}
                else if(mode == '3' && sample_size == '3'){processing_mode = ESOS_SENSOR_MIN8;}
                else if(mode == '3' && sample_size == '4'){processing_mode = ESOS_SENSOR_MIN16;}
                else if(mode == '3' && sample_size == '5'){processing_mode = ESOS_SENSOR_MIN32;}
                else if(mode == '3' && sample_size == '6'){processing_mode = ESOS_SENSOR_MIN64;}
                //max
                else if(mode == '4' && sample_size == '1'){processing_mode = ESOS_SENSOR_MAX2;}
                else if(mode == '4' && sample_size == '2'){processing_mode = ESOS_SENSOR_MAX4;}
                else if(mode == '4' && sample_size == '3'){processing_mode = ESOS_SENSOR_MAX8;}
                else if(mode == '4' && sample_size == '4'){processing_mode = ESOS_SENSOR_MAX16;}
                else if(mode == '4' && sample_size == '5'){processing_mode = ESOS_SENSOR_MAX32;}
                else if(mode == '4' && sample_size == '6'){processing_mode = ESOS_SENSOR_MAX64;}
                //median
                else if(mode == '5' && sample_size == '1'){processing_mode = ESOS_SENSOR_MEDIAN2;}
                else if(mode == '5' && sample_size == '2'){processing_mode = ESOS_SENSOR_MEDIAN4;}
                else if(mode == '5' && sample_size == '3'){processing_mode = ESOS_SENSOR_MEDIAN8;}
                else if(mode == '5' && sample_size == '4'){processing_mode = ESOS_SENSOR_MEDIAN16;}
                else if(mode == '5' && sample_size == '5'){processing_mode = ESOS_SENSOR_MEDIAN32;}
                else if(mode == '5' && sample_size == '6'){processing_mode = ESOS_SENSOR_MEDIAN64;}
                
                //invalid selection was entered, what should we default processing_mode to in this case? 
                else {processing_mode = ESOS_SENSOR_ONE_SHOT;}
                MENU_STATE = ONCE;
            }
		}
		ESOS_TASK_YIELD();
	}
	ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();

    esos_uiF14_flashLED3(250); //250 ms flash on LED3. (Heartbeat)
    MENU_STATE = INSTRUCT;
    esos_RegisterTask(StateChange);
    esos_RegisterTask(SerialOutput);


}