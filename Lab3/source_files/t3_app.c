#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "t3_interface.h"

ESOS_USER_TASK(rpg) {
    ESOS_TASK_BEGIN();
    while(TRUE) {
        if (esos_uiF14_isRPGTurningFast() == TRUE) {
            esos_uiF14_flashLED2(100);
        }
        else if (esos_uiF14_isRPGTurningMedium() == TRUE) {
            esos_uiF14_flashLED2(500);
        }
        else if (esos_uiF14_isRPGTurningSlow() == TRUE) {
            esos_uiF14_turnLED2On();
        }
        else if (esos_uiF14_isRPGTurning() == FALSE) {
            esos_uiF14_turnLED2Off();
        }

        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

ESOS_USER_TASK(LED) {
    ESOS_TASK_BEGIN();
    while (TRUE) {
        if ((esos_uiF14_isSW1DoublePressed() == TRUE) || (esos_uiF14_isSW2DoublePressed() == TRUE)) {
            esos_uiF14_turnLED1Off();
            ESOS_TASK_WAIT_TICKS(300);
            esos_uiF14_turnLED1On();
            ESOS_TASK_WAIT_TICKS(200);
            esos_uiF14_turnLED1Off();
            ESOS_TASK_WAIT_TICKS(200);
            esos_uiF14_turnLED1On();
            ESOS_TASK_WAIT_TICKS(200);
            esos_uiF14_turnLED1Off();
            ESOS_TASK_WAIT_TICKS(200);
            esos_uiF14_turnLED1On();
            ESOS_TASK_WAIT_TICKS(200);
            esos_uiF14_turnLED1Off();
        }
        else if ((esos_uiF14_isSW1Pressed() == TRUE) || (esos_uiF14_isSW2Pressed() == TRUE)) {
            esos_uiF14_turnLED1On();
        }
        else if ((esos_uiF14_isSW1Released() == TRUE) && (esos_uiF14_isSW2Released() == TRUE)) {
            esos_uiF14_turnLED1Off();
        }
        
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
    config_ui_menu();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. (Heartbeat)

    esos_RegisterTask(rpg);
    esos_RegisterTask(LED);
}
