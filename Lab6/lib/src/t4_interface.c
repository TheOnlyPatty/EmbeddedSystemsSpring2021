#include "esos_f14ui.h"
#include "esos.h"
#include "esos_pic24.h"

//_st_esos_uiF14Data_t _st_esos_uiF14Data;

enum STATE {
	INSTRUCT,
    ONE_SHOT,
	CONTINUOUS,
};

static char str_INSTRUCTIONS1[] = "Press SW1 to sample the potentiometer once.\nPress SW2 to begin sampling the potentiometer once per second.\n";
static char str_INSTRUCTIONS2[] = "Press SW1 or SW2 to quit sampling.\n"


ESOS_USER_TASK(interface)
{
	static enum STATE MENU_STATE = BASE; //set default state
	ESOS_TASK_BEGIN();
	while (1) {
		if (MENU_STATE == INSTRUCT) {
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_INSTRUCTIONS1);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Set next state based on selection
            if(esos_uiF14_isSW1Pressed()) {
                MENU_STATE = ONE_SHOT;
            }
            else if(esos_uiF14_isSW2Pressed) {
                MENU_STATE = CONTINUOUS;
            }
		}
			
		//ONE_SHOT
		else if (MENU_STATE == ONE_SHOT) {
			
			static uint16_t u16_sw1_period_val = 500; // This variable has to be hardcoded unfortunately
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW1_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)u16_sw1_period_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();


			// Set next state based on selection
			switch (u8_input) {
			case '1':
				esos_uiF14_setSW1DoublePressedPeriod((u16_sw1_period_val += u16_sw1_period_val/10));
				break;
			case '2':
				esos_uiF14_setSW1DoublePressedPeriod((u16_sw1_period_val -= u16_sw1_period_val/11));
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}

		}
		
		//SW2
		else if (MENU_STATE == S_SW2) {
			
			static uint16_t u16_sw2_period_val = 500;
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW2_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)u16_sw2_period_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
			case '1':
				esos_uiF14_setSW2DoublePressedPeriod(u16_sw2_period_val += u16_sw2_period_val/10);
				break;
			case '2':
				esos_uiF14_setSW2DoublePressedPeriod(u16_sw2_period_val -= u16_sw2_period_val/11);
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}
		}
		
		// Print separator
		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
		ESOS_TASK_WAIT_ON_SEND_STRING(str_SEP);
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
	}

	ESOS_TASK_END();
}

void config_ui_menu()
{
	esos_RegisterTask(interface);
}


