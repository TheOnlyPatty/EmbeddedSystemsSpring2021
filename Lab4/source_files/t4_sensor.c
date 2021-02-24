#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include <stdio.h>


void user_init(void) {
    config_esos_uiF14();
//    config_ui_menu();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. (Heartbeat)

}
