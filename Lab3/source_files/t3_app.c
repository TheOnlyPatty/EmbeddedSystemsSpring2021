#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "t3_interface.h"
#include <stdio.h>

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
static char str_SW2_DP[] = "SW2 Double Pressed\n";
static char str_SW3_P[] = "SW3 Pressed\n";
//static char str_SW3_DP[] = "SW3 Double Pressed\n";



ESOS_USER_TASK(rpg) {
    ESOS_TASK_BEGIN();

	// States to prevent spamming the same messages over and over again
	static uint16_t state = 0;
	static uint16_t previous_state = 0;

	// Special states relating to no RPG movement
	static uint16_t special_state = 0;
	static uint16_t previous_special_state = 0;

    while(TRUE) {
		
        if (esos_uiF14_isRPGTurningFast() == TRUE) {
			
            esos_uiF14_flashLED2(100);
			
			if (esos_uiF14_isRPGTurningCW() == TRUE) {
				state = 1;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_FAST);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			else if (esos_uiF14_isRPGTurningCCW() == TRUE){
				state = 2;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_FAST);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			special_state = 0;
        }
        else if (esos_uiF14_isRPGTurningMedium() == TRUE) {
			
            esos_uiF14_flashLED2(500);
			
			if (esos_uiF14_isRPGTurningCW() == TRUE) {				
				state = 3;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_MED);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			else if (esos_uiF14_isRPGTurningCCW() == TRUE){
				state = 4;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_MED);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			special_state = 0;
        }
        else if (esos_uiF14_isRPGTurningSlow() == TRUE) {
            esos_uiF14_turnLED2On();
			
			if (esos_uiF14_isRPGTurningCW() == TRUE) {
				state = 5;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CW_SLOW);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			else if (esos_uiF14_isRPGTurningCCW() == TRUE){
				state = 6;
				if (state != previous_state) {
					ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_CCW_SLOW);
					ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
					ESOS_TASK_WAIT_TICKS(20);
					previous_state = state;
				}
			}
			special_state = 0;
        }
        else if (esos_uiF14_isRPGTurning() == FALSE) {
            esos_uiF14_turnLED2Off();
			special_state = 1;
			if (special_state != previous_special_state) {
				ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_ON_SEND_STRING(str_RPG_NO_MOVEMENT);
				ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
				ESOS_TASK_WAIT_TICKS(20);
			}
			
        }

		previous_special_state = special_state;

        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

ESOS_USER_TASK(LED) {
    ESOS_TASK_BEGIN();
    while (TRUE) {
        if (esos_uiF14_isSW1DoublePressed() == TRUE) {
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW1_DP);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			if (esos_uiF14_isSW3Pressed() == FALSE) {
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
        }
		// Made another separate statement instead of including in the previous if as and or 
		// due to the serial communication
		if (esos_uiF14_isSW2DoublePressed() == TRUE) {
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW2_DP);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			if (esos_uiF14_isSW3Pressed() == TRUE) {
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
        }

		// LED control (SW3 stuff)
        if ((esos_uiF14_isSW1Pressed() == TRUE) && (esos_uiF14_isSW3Pressed() == FALSE)) {
            esos_uiF14_turnLED1On();
        }
		else if ((esos_uiF14_isSW2Pressed() == TRUE) && (esos_uiF14_isSW3Pressed() == TRUE)) {
			esos_uiF14_turnLED1On();
		}
        else if ((esos_uiF14_isSW1Released() == TRUE) && (esos_uiF14_isSW2Released() == TRUE)) {
            esos_uiF14_turnLED1Off();
        }

		// Switch serial output
		if (esos_uiF14_isSW1Pressed() == TRUE) {
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW1_P);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_TICKS(350);
		}
		if (esos_uiF14_isSW2Pressed() == TRUE) {
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW2_P);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_TICKS(350);
		}
		if (esos_uiF14_isSW3Pressed() == TRUE) {
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW3_P);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_TICKS(350);
		}
        
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

/*
// For testing the interface's ability to raise and lower times
ESOS_USER_TASK(test) {
	ESOS_TASK_BEGIN();
	while(TRUE) {
		printf("\n\nSW1: %u\n", esos_uiF14_getSW1DoublePressedPeriod());
		printf("\nSW2: %u\n", esos_uiF14_getSW2DoublePressedPeriod());
		printf("\nSW3: %u\n", esos_uiF14_getSW3DoublePressedPeriod());
		printf("\nRPG SLOW: %u\n", esos_uiF14_getRPGSlowThreshold());
		printf("\nRPG MEDIUM: %u\n", esos_uiF14_getRPGMediumThreshold());
		printf("\nRPG FAST:%u\n\n", esos_uiF14_getRPGFastThreshold());
		ESOS_TASK_WAIT_TICKS(1000);
	}
	
	ESOS_TASK_END();
}
*/

void user_init(void) {
    config_esos_uiF14();
    config_ui_menu();

    esos_uiF14_flashLED3(500); //500 ms flash on LED3. (Heartbeat)

    esos_RegisterTask(rpg);
    esos_RegisterTask(LED);
	//esos_RegisterTask(test);

}
