#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include <stdio.h>

static char str_INSTRUCTIONS1[] = "Press SW1 to sample the potentiometer once.\nPress SW2 to begin sampling the potentiometer once per second.\n";
static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 to quit sampling.\n"

static uint16_t u16_data;


ESOS_USER_TASK(SerialOutput) {
    static uint16_t state = 0;
    static uint16_t previous_state = 0;
    ESOS_TASK_BEGIN();
    while(1) {
        ESOS_TASK_WAIT_ON_AVAILABLE_SENSOR(POT_CHANNEL,ESOS_SENSOR_VREF_3V3);
        ESOS_TASK_WAIT_SENSOR_READ(u16_data,
        ESOS_SENSOR_CLOSE();
        
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
//    config_ui_menu();
    esos_uiF14_flashLED3(500); //500 ms flash on LED3. (Heartbeat)
    esos_RegisterTask(SerialOutput);

}
