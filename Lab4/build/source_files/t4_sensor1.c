#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include "esos_sensor.h"
#include "revF14.h"
#include <stdio.h>

static char str_INSTRUCTIONS1[] = "Press SW1 to sample the potentiometer once.\nPress SW2 to begin sampling the potentiometer once per second.\n";
static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 to quit sampling.\n";

static char str_ONE_SHOT_POT_PRE1[] = "Previous potentiometer reading: ";
static char str_ONE_SHOT_POT_PRE2[] = "Current potentiometer reading: ";


static enum STATE {
    INSTRUCT,
    WAIT,
    ONE_SHOT,
    CONTINUOUS,
} MENU_STATE;

ESOS_USER_TASK(StateChange) {
    static BOOL SW1_STATE, SW2_STATE;
    ESOS_TASK_BEGIN();
    while (1) {
        if (SW1_STATE != esos_uiF14_isSW1Pressed()) { //Require a release before changing state again
            SW1_STATE = esos_uiF14_isSW1Pressed();
            if (SW1_STATE) {
                if (MENU_STATE == CONTINUOUS) MENU_STATE = INSTRUCT;
                else MENU_STATE = ONE_SHOT;
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
        else if(MENU_STATE == ONE_SHOT) {

            uint8_t temp = 0;
            while (temp < 2){
                ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL, ESOS_SENSOR_VREF_3V3);
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_BITS);
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
                ESOS_TASK_WAIT_SENSOR_READ(u16_data, ESOS_SENSOR_ONE_SHOT, ESOS_SENSOR_FORMAT_BITS);
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();

                ESOS_TASK_WAIT_ON_SEND_STRING(str_ONE_SHOT_POT_PRE1);

                ESOS_TASK_WAIT_ON_SEND_UINT16_AS_HEX_STRING(u16_data);
                ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_TICKS(1000);
            }
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
