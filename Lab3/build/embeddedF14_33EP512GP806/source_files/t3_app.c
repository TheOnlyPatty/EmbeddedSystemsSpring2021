#include "esos_f14ui.h"
#include "esos.h"
#include "esos_pic24.h"

//ESOS_USER_TASK(rpg) {
//    // Do stuff with rotary pulse generator.
//}

void user_init(void) {
    config_esos_uiF14();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. NOT YET IMPLEMENTED
}

