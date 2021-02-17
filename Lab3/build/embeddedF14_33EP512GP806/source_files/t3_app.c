#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"

ESOS_USER_TASK(rpg) {
    ESOS_TASK_BEGIN();

    static BOOL b_rpg_previous;
    while (TRUE) {
        if (esos_uiF14_isRPGTurning() && esos_uiF14_isRPGTurning() != b_rpg_previous) {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("TURNING");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }

        b_rpg_previous = esos_uiF14_isRPGTurning();

        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. NOT YET IMPLEMENTED

}

