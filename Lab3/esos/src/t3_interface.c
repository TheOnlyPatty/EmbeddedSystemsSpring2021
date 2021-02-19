#include "esos_f14ui.h"
#include "esos.h"
#include "esos_pic24.h"

//NOT FINISHED

//TODO: just need to replace the getters/setters in this file with what we end up going with in our esos_f14ui files



enum STATE {
	BASE,
	CURR,
	SW1,
	SW2,
	SW3,
	SLOW,
	MED,
	FAST
};

static char str_SW1_DIS[] = "SW1 DP current value: ";
static char str_SW2_DIS[] = "SW2 DP current value: ";
static char str_SW3_DIS[] = "SW3 DP current value: ";
static char str_SLOW_DIS[] = "RPG slow current value: ";
static char str_MED_DIS[] = "RPG med current value: ";
static char str_FAST_DIS[] = "RPG fast current value: ";


static char str_SW1[] = "1: Change SW1 DP Period\n";
static char str_SW2[] = "2: Change SW2 DP Period\n";
static char str_SW3[] = "3: Change SW3 DP Period\n";


static char str_SLOW[] = "4: Change RPG Slow velocity\n";
static char str_MED[] = "5: Change RPG Medium velocity\n";
static char str_FAST[] = "6: Change RPG Fast velocity\n";

static char str_CHANGE[] = "press 1/2 to increase/decrease this value by ~10%, press 3 to go back to main menu\n";

static char str_SEP[] = "*****************************\n\n";


ESOS_USER_TASK(interface)
{
	// State and input variables
	static uint8_t u8_input = 0x00;
	static enum STATE MENU_STATE = BASE;

	ESOS_TASK_BEGIN();

	while (TRUE) {
		if (MENU_STATE == BASE) {
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW1);
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW2);
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW3);
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SLOW);
			ESOS_TASK_WAIT_ON_SEND_STRING(str_MED);
			ESOS_TASK_WAIT_ON_SEND_STRING(str_FAST);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
				
			case '1':
				MENU_STATE = SW1;
				break;
				
			case '2':
				MENU_STATE = SW2;
				break;
				
			case '3':
				MENU_STATE = SW3;
				break;
				
			case '4':
				MENU_STATE = SLOW;
				break;
				
			case '5':
				MENU_STATE = MED;
				break;
				
			case '6':
				MENU_STATE = FAST;
				break;
				
			default:
				MENU_STATE = BASE;
				break;
			}
		}
			
		//SW1
		else if (MENU_STATE == SW1) {
			
			
			uint16_t u16_sw1_period_val;
			u16_sw1_period_val = esos_uiF14_getSW1DoublePressedPeriod();
			
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
			case "1":
				esos_uiF14_setSW1DoublePressedPeriod(u16_sw1_period_val + u16_sw1_period_val/10);
				break;
			case "2":
				esos_uiF14_setSW1DoublePressedPeriod(u16_sw1_period_val - u16_sw1_period_val/11);
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
		else if (MENU_STATE == SW2) {
			
			uint16_t u16_sw2_period_val;
			u16_sw2_period_val = esos_uiF14_getSW2DoublePressedPeriod();
			
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
			case "1":
				esos_uiF14_setSW2DoublePressedPeriod(u16_sw2_period_val + u16_sw2_period_val/10);
				break;
			case "2":
				esos_uiF14_setSW1DoublePressedPeriod(u16_sw2_period_val - u16_sw2_period_val/11);
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}
		}
		
		//SW3
		else if (MENU_STATE == SW3) {
			
			uint16_t u16_sw3_period_val;
			u16_sw3_period_val = esos_uiF14_getSW3DoublePressedPeriod();
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SW3_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)u16_sw3_period_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
			case "1":
				esos_uiF14_setSW3DoublePressedPeriod(u16_sw3_period_val + u16_sw3_period_val/10);
				break;
			case "2":
				esos_uiF14_setSW3DoublePressedPeriod(u16_sw3_period_val - u16_sw3_period_val/11);
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}
		}
		
		//RPG SLOW
		else if (MENU_STATE == SLOW) {
			
			uint16_t i16_rpg_slow_val;
			i16_rpg_slow_val = esos_uiF14_getRPGSlowThreshold();
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_SLOW_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)i16_rpg_slow_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
			case "1":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_slow_val + i16_rpg_slow_val/10);
				break;
			case "2":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_slow_val - i16_rpg_slow_val/11);
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}
		}
		
		//RPG MED
		else if (MENU_STATE == MED) {
			
			uint16_t i16_rpg_med_val;
			i16_rpg_slow_val = esos_uiF14_getRPGMediumThreshold();
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_MED_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)i16_rpg_med_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
			case "1":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_med_val + i16_rpg_med_val/10);
				break;
			case "2":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_med_val - i16_rpg_med_val/11);
				break;
			case '3':
				MENU_STATE = BASE;
				break;
			default:
				MENU_STATE = BASE;
				break;
			}
		}
		
		//RPG FAST
		else if (MENU_STATE == FAST) {
			
			uint16_t i16_rpg_fast_val;
			i16_rpg_fast_val = esos_uiF14_getRPGFastThreshold();
			
			// Print menu options
			ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_FAST_DIS);
			ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING((uint32_t)i16_rpg_fast_val);
			ESOS_TASK_WAIT_ON_SEND_UINT8('\n');
			
			ESOS_TASK_WAIT_ON_SEND_STRING(str_CHANGE);
			ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

			// Wait for selection
			ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
			ESOS_TASK_WAIT_ON_GET_UINT8(u8_input);
			ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

			// Set next state based on selection
			switch (u8_input) {
			case "1":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_fast_val + i16_rpg_fast_val/10);
				break;
			case "2":
				esos_uiF14_setSW1DoublePressedPeriod(i16_rpg_fast_val - i16_rpg_fast_val/11);
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


