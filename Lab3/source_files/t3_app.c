#include "esosf14ui.h"

ESOS_USER_TASK(rpg) {
    // Do stuff with rotary pulse generator.
}

void user_init(void) {
    config_esos_uiF14();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. NOT YET IMPLEMENTED
    
    esos_RegisterTimer(__esos_uiF14_task,10); //
    esos_RegisterTask(rpg);
}

ESOS_USER_TIMER(__esos_uiF14_task) { //UI Task called my timer every 10ms
    
}
