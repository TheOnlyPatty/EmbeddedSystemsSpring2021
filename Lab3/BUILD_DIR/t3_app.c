#include "esos.h"
#include "esos_pic24.h"
#include "pic24_util.h"
#include "pic24_serial.h"
#include "esos_pic24_rs232.h"
#include <p33EP512GP806.h>
#include <stdio.h>
#include <stdlib.h>
#include "esos_comm.h"
#include <string.h>

#include "esos_f14ui.h"


ESOS_USER_TASK(heartbeat) {
    ESOS_TASK_BEGIN();
    
    while (1) {
        esos_uiF14_turnLED1On();
        ESOS_TASK_WAIT_TICKS(50);
        esos_uiF14_turnLED1Off();
        ESOS_TASK_WAIT_TICKS(450);
    }

    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();
    esos_RegisterTask(heartbeat);
}

