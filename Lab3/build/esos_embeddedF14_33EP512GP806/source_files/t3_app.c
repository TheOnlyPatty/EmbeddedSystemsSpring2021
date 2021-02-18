#include "esosf14ui.h"

void user_init(void) {
    config_esos_uiF14();
    
    esos_RegisterTimer(__esos_uiF14_task,10); //
}

ESOS_USER_TIMER(__esos_uiF14_task) { //UI Task called my timer every 10ms
    
}
