#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "esos_sensor.h"
#include "esos_pic24_sensor.h"

ESOS_USER_TASK(task) {
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}

void user_init(void) {
    config_esos_uiF14();

    esos_uiF14_flashLED3(250);

    esos_RegisterTask(task); // Maybe come up with a better name later
}