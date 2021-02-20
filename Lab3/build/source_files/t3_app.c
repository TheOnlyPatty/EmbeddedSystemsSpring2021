#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "t3_interface.h"

//strings for printing state changes

static char str_RPG_CW_FAST[] = "RPG turning CW fast\n";
static char str_RPG_CW_MED[] = "RPG turning CW medium\n";
static char str_RPG_CW_SLOW[] = "RPG turning CW slow\n";
static char str_RPG_CCW_FAST[] = "RPG turning CCW fast\n";
static char str_RPG_CCW_MED[] = "RPG turning CCW medium\n";
static char str_RPG_CCW_SLOW[] = "RPG turning CCW slow\n";
static char str_RPG_NO_MOVEMENT[] = "RPG not Turning\n";
static char str_SW1_P[] = "SW1 Pressed\n";
static char str_SW1_DP[] = "SW1 Double Pressed\n";
static char str_SW2_P[] = "SW2 Pressed\n";
static char str_SW2_DP[] = "SW1 Double Pressed\n";
static char str_SW3_P[] = "SW3 Pressed\n";
static char str_SW3_DP[] = "SW3 Double Pressed\n";


ESOS_USER_TASK(rpg) {
    ESOS_TASK_BEGIN();
	
	BOOL IF_CW_FAST = FALSE;
	BOOL IF_CCW_FAST = FALSE;
	BOOL IF_CW_MED = FALSE;
	BOOL IF_CCW_MED = FALSE;
	BOOL IF_CW_SLOW = FALSE;
	BOOL IF_CCW_SLOW = FALSE;
	BOOL IF_NO_MOVE = FALSE;

    while(TRUE) {
		
		
		
        if (esos_uiF14_isRPGTurningFast() == TRUE) {
			
            esos_uiF14_flashLED2(100);
			
			if (esos_uiF14_isRPGTurningCW() && !IF_CW_FAST) {
				
				IF_CW_FAST = TRUE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_FAST);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
			else if (esos_uiF14_isRPGTurningCCW() && !IF_CCW_FAST){
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = TRUE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_FAST);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
			
        }
        else if (esos_uiF14_isRPGTurningMedium() == TRUE) {
			
            esos_uiF14_flashLED2(500);
			
			if (esos_uiF14_isRPGTurningCW() && !IF_CW_MED) {
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = TRUE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_MED);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
			else if (esos_uiF14_isRPGTurningCCW() && !IF_CCW_MED){
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = TRUE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_MED);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
        }
        else if (esos_uiF14_isRPGTurningSlow() == TRUE) {
            esos_uiF14_turnLED2On();
			
			if (esos_uiF14_isRPGTurningCW() && !IF_CW_SLOW) {
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = TRUE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_SLOW);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
			else if (esos_uiF14_isRPGTurningCCW() && !IF_CCW_SLOW){
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = TRUE;
				IF_NO_MOVE = FALSE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_SLOW);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			}
			
        }
        else if (esos_uiF14_isRPGTurning() == FALSE) {
            esos_uiF14_turnLED2Off();
			
			if(!IF_NO_MOVE){
				
				IF_CW_FAST = FALSE;
				IF_CCW_FAST = FALSE;
				IF_CW_MED = FALSE;
				IF_CCW_MED = FALSE;
				IF_CW_SLOW = FALSE;
				IF_CCW_SLOW = FALSE;
				IF_NO_MOVE = TRUE;
				
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_NO_MOVEMENT);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				
			}
			
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
