#include <esos.h>
#include "esos_pic24.h"
#include "esos_pic24_rs232.h"
#include <p33EP512GP806.h>
#include <stdio.h>
#include <stdlib.h>
#include "pic24_util.h"
#include "pic24_serial.h"
#include "esos_comm.h"
#include <string.h>

#include "esos_f14ui.h"


char buffer[8];

 
ESOS_USER_TASK(demoLEDsAndSwitches) {
    ESOS_TASK_BEGIN();
	  while(1){
	    esos_uiF14_flashLED3(500);           //heartbeat always blinking
		// RPG controls LED2
		if (esos_uiF14_isRPGTurning()){
			esos_uiF14_turnLED2Off();
		}
		if (esos_uiF14_isRPGTurningSlow()){
			esos_uiF14_turnLED2On();
		}
		if (esos_uiF14_isRPGTurningMedium()){
			esos_uiF14_flashLED2(500);
		}
		if (esos_uiF14_isRPGTurningFast()){
			esos_uiF14_flashLED2(100);
		}
		//switch on RPG (SW3) controls whether SW1 or SW2 controls LED1
		if (esos_uiF14_isSW3Released()){      
			if (esos_uiF14_isSW1Pressed()){
				esos_uiF14_turnLED1On();
			} else if (esos_uiF14_isSW1Released()){
				esos_uiF14_turnLED1Off();
			}
			if (esos_uiF14_isSW1DoublePressed()){
				int k;
				for (k = 0; k<3; k++){
					esos_uiF14_turnLED1On();
					ESOS_TASK_WAIT_TICKS(150);
					esos_uiF14_turnLED1Off();
					ESOS_TASK_WAIT_TICKS(150);
				}
			}
		}else if(esos_uiF14_isSW3Pressed()){
			if (esos_uiF14_isSW2Pressed()){
				esos_uiF14_turnLED1On();
			} else if (esos_uiF14_isSW2Released()){
				esos_uiF14_turnLED1Off();
			}
			if (esos_uiF14_isSW2DoublePressed()){
				int m;
				for (m = 0; m<3; m++){
					esos_uiF14_turnLED1On();
					ESOS_TASK_WAIT_TICKS(150);
					esos_uiF14_turnLED1Off();
					ESOS_TASK_WAIT_TICKS(150);
				}
			}
		}
	  }
	ESOS_TASK_END();
}	


/*ESOS_USER_TASK(drawDisplay) {
    ESOS_TASK_BEGIN();
		//initDataXfer(); 
		//format for below... var name from enum above, actual var name, T/F changeable, label
		//SPECIFY_VAR(u16_DOUBLE_PRESS_UPPER_MS_NDX, _st_esos_uiF14Data.u16_doublePressUpperMs, TRUE, "%u", "Upper double press time limit");
		//SPECIFY_VAR(u16_RPG_SLOW_MS_NDX, _st_esos_uiF14Data.u16_RPGNotMovingToSlowPeriodMs, TRUE, "%u", "Time in ms between RPG clicks -not moving to slow");
		//SPECIFY_VAR(u16_RPG_MEDIUM_MS_NDX, _st_esos_uiF14Data.u16_RPGSlowToMediumPeriodMs, TRUE, "%u", "Time in ms between RPG clicks -slow to medium");
		//SPECIFY_VAR(u16_RPG_FAST_MS_NDX, _st_esos_uiF14Data.u16_RPGMediumToFastPeriodMs, TRUE, "%u", "Time in ms between RPG clicks -medium to fast");
		//SPECIFY_VAR(u16_RPG_PERIOD_NDX, _st_esos_uiF14Data.u16_RPGPeriodMs, FALSE, "%u", "Time between clicks in ms");
		//SPECIFY_VAR(U16_RPG_VALUE_NDX, _st_esos_uiF14Data.i16_RPGCounter, FALSE, "%u", "Current RPG Counter");
		while(1){

			memset(&buffer, 0, sizeof(buffer));	// clear out the input buffer

			if (esos_uiF14_isSW1Pressed()){ESOS_TASK_WAIT_ON_SEND_STRING("\nSw1 is Pushed  ");}
			if (esos_uiF14_isSW1Released()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw1 is Released");}
			if (esos_uiF14_isSW1DoublePressed()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw1 is Double Pressed\n");
				ESOS_TASK_WAIT_TICKS(300);
			} else {ESOS_TASK_WAIT_ON_SEND_STRING("Sw1 is NOT Double Pressed\n");}
			if (esos_uiF14_isSW2Pressed()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw2 is Pushed  ");}
			if (esos_uiF14_isSW2Released()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw2 is Released");}
			if (esos_uiF14_isSW2DoublePressed()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw2 is Double Pressed\n");
				ESOS_TASK_WAIT_TICKS(300);
			} else {ESOS_TASK_WAIT_ON_SEND_STRING("Sw2 is NOT Double Pressed\n");}
			if (esos_uiF14_isSW3Pressed()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw3 is Pushed  ");}
			if (esos_uiF14_isSW3Released()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw3 is Released");}
			if (esos_uiF14_isSW3DoublePressed()){ESOS_TASK_WAIT_ON_SEND_STRING("Sw3 is Double Pressed\n\n");
				ESOS_TASK_WAIT_TICKS(300);
			} else {ESOS_TASK_WAIT_ON_SEND_STRING("Sw3 is NOT Double Pressed\n\n");}

			if (esos_uiF14_isRPGTurning()) {
				ESOS_TASK_WAIT_ON_SEND_STRING("RPG is Turning ");
				if (esos_uiF14_isRPGTurningCW()) { 
					ESOS_TASK_WAIT_ON_SEND_STRING("CW ");
				} else {
					ESOS_TASK_WAIT_ON_SEND_STRING("CCW");
				}
				if (esos_uiF14_isRPGTurningSlow()) {
					ESOS_TASK_WAIT_ON_SEND_STRING(" Slowly\n");
				} else if (esos_uiF14_isRPGTurningMedium()) {
					ESOS_TASK_WAIT_ON_SEND_STRING(" Mediumly\n");
				} else { 
					ESOS_TASK_WAIT_ON_SEND_STRING(" Fastly\n");
				}
			} else {
				ESOS_TASK_WAIT_ON_SEND_STRING("RPG is Not Turning");
			}
			ESOS_TASK_WAIT_TICKS(50);
			ESOS_TASK_WAIT_ON_SEND_STRING("\n\n\n\n\n\n\n\n"); //these newlines clear the screen and allow overwrite
			//!!!		THE FOLLOWING SHOULD BE TREATED AS PSEUDOCODE UNTIL WE CAN PUT THIS ON A BOARD			!!!
			ESOS_TASK_WAIT_ON_SEND_STRING(	"+-------Configuration-------+\n\
											 | 1). Double Press Speed    |\n\
											 | 2). RPG Speeds			 |\n\
											 |               			 |\n\
											 +---------------------------+\n\
											 \n\
											 > "
			);

			ESOS_TASK_WAIT_ON_GET_STRING(&buffer);
			

			// hoo baby this is a nasty switch case
			// BUFFER WILL PROBABLY NEED SOME PROCESSING HERE
			switch(buffer[0]) {
			
				case "1":
					ESOS_TASK_WAIT_ON_SEND_STRING("Enter threshold for double press detection (in ms)\n\
											 > "
					);
					memset(&buffer, 0, sizeof(buffer));
					ESOS_TASK_WAIT_ON_GET_STRING(&buffer);
					// SET THRESHOLD (needs setter function)

				case "2":
					ESOS_TASK_WAIT_ON_SEND_STRING(	"+----RPG Speed Thresholds---+\n\
													 | 1). Slow                  |\n\
													 | 2). Medium    			 |\n\
													 | 3). Fast        			 |\n\
													 +---------------------------+\n\
													\n\
													> "
					);
					memset(&buffer, 0, sizeof(buffer));
					ESOS_TASK_WAIT_ON_GET_STRING(&buffer);

					// oh hell yeah nested switch case
					switch(buffer[0]) {
						case "1":
							ESOS_TASK_WAIT_ON_SEND_STRING("Enter threshold for turning the RPG slowly\n\
													> "
							);
							memset(&buffer, 0, sizeof(buffer));
							ESOS_TASK_WAIT_ON_GET_STRING(&buffer);
							// SET THRESHOLD (needs setter function)
						case "2":
							ESOS_TASK_WAIT_ON_SEND_STRING("Enter threshold for turning the RPG ...mediumly\n\
													> "
							);
							memset(&buffer, 0, sizeof(buffer));
							ESOS_TASK_WAIT_ON_GET_STRING(&buffer);
							// SET THRESHOLD (needs setter function)
						case "3":
						ESOS_TASK_WAIT_ON_SEND_STRING("Enter threshold for turning the RPG ...fastly\n\
													> "
							);
							memset(&buffer, 0, sizeof(buffer));
							ESOS_TASK_WAIT_ON_GET_STRING(&buffer);
							// SET THRESHOLD (needs setter function)
					}
			}
		}
	ESOS_TASK_END();
}*/

void user_init(void){
	esos_RegisterTask(demoLEDsAndSwitches);
	//esos_RegisterTask(drawDisplay);
}
