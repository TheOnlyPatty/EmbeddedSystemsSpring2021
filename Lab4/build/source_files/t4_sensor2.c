#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
//#include "t3_interface.h"
#include "esos_sensor.h"
#include "revF14.h"
#include <stdio.h>

//NOT FINISHED

static esos_sensor_process_t process_mode;

//Child task to print menu and set processing mode for main user tasks 
ESOS_CHILD_TASK(mode_selection) {
    static uint8_t mode;
    static uint8_t sample_size;

    ESOS_TASK_BEGIN();
	
	
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();     
    ESOS_TASK_WAIT_ON_SEND_STRING("Mode Selection: \n");
    ESOS_TASK_WAIT_ON_SEND_STRING("1. one-shot\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("2. average\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("3. minimum\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("4. maximum\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("5. median\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("**********************\n");
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM(); 
    ESOS_TASK_WAIT_ON_GET_UINT8(mode); 
    ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
	//sample size shouldn't matter for one-shot, right? 
    ESOS_TASK_WAIT_ON_SEND_STRING("Sample Size Selection (doesn't matter for one-shot): \n");
    ESOS_TASK_WAIT_ON_SEND_STRING("1. two");
    ESOS_TASK_WAIT_ON_SEND_STRING("2. four\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("3. eight\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("4. sixteen\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("5. thirty-two\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("6. sixty-four\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("**********************\n");
    ESOS_TASK_WAIT_ON_SEND_STRING("> ");
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

    ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
    ESOS_TASK_WAIT_ON_GET_UINT8(sample_size);
    ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();

	//sets processing_mode based on input
	//one-shot
    if(mode == '1'){process_mode = ESOS_SENSOR_ONE_SHOT;}
	//avg
	else if(mode == '2' && sample_size == '1'){process_mode = ESOS_SENSOR_AVG2;}
	else if(mode == '2' && sample_size == '2'){process_mode = ESOS_SENSOR_AVG4;}
	else if(mode == '2' && sample_size == '3'){process_mode = ESOS_SENSOR_AVG8;}
	else if(mode == '2' && sample_size == '4'){process_mode = ESOS_SENSOR_AVG16;}
	else if(mode == '2' && sample_size == '5'){process_mode = ESOS_SENSOR_AVG32;}
	else if(mode == '2' && sample_size == '6'){process_mode = ESOS_SENSOR_AVG64;}
	//min
	else if(mode == '3' && sample_size == '1'){process_mode = ESOS_SENSOR_MIN2;}
	else if(mode == '3' && sample_size == '2'){process_mode = ESOS_SENSOR_MIN4;}
	else if(mode == '3' && sample_size == '3'){process_mode = ESOS_SENSOR_MIN8;}
	else if(mode == '3' && sample_size == '4'){process_mode = ESOS_SENSOR_MIN16;}
	else if(mode == '3' && sample_size == '5'){process_mode = ESOS_SENSOR_MIN32;}
	else if(mode == '3' && sample_size == '6'){process_mode = ESOS_SENSOR_MIN64;}
	//max
	else if(mode == '4' && sample_size == '1'){process_mode = ESOS_SENSOR_MAX2;}
	else if(mode == '4' && sample_size == '2'){process_mode = ESOS_SENSOR_MAX4;}
	else if(mode == '4' && sample_size == '3'){process_mode = ESOS_SENSOR_MAX8;}
	else if(mode == '4' && sample_size == '4'){process_mode = ESOS_SENSOR_MAX16;}
	else if(mode == '4' && sample_size == '5'){process_mode = ESOS_SENSOR_MAX32;}
	else if(mode == '4' && sample_size == '6'){process_mode = ESOS_SENSOR_MAX64;}
	//median
	else if(mode == '5' && sample_size == '1'){process_mode = ESOS_SENSOR_MEDIAN2;}
	else if(mode == '5' && sample_size == '2'){process_mode = ESOS_SENSOR_MEDIAN4;}
	else if(mode == '5' && sample_size == '3'){process_mode = ESOS_SENSOR_MEDIAN8;}
	else if(mode == '5' && sample_size == '4'){process_mode = ESOS_SENSOR_MEDIAN16;}
	else if(mode == '5' && sample_size == '5'){process_mode = ESOS_SENSOR_MEDIAN32;}
	else if(mode == '5' && sample_size == '6'){process_mode = ESOS_SENSOR_MEDIAN64;}
	
	//invalid selection was entered, what should we default process_mode to in this case? 
	else {process_mode = ESOS_SENSOR_ONE_SHOT;}

    ESOS_TASK_END();
}

ESOS_USER_TASK(sensor) {
	//child task memory allocation
    static ESOS_TASK_HANDLE child; 
    ESOS_TASK_BEGIN();
	while(TRUE){
		
		
		//TODO: implement SW1 and SW2 presses, and the sensor stuff
		
		
		//if switch 3 is pressed, run mode_selection child tasks which sets process_mode
		if (esos_uiF14_isSW3Pressed()){ 
			ESOS_ALLOCATE_CHILD_TASK(child);
			ESOS_TASK_SPAWN_AND_WAIT(child, mode_selection);
		}

    }

      
    ESOS_TASK_END();
}

void user_init(void){
    config_esos_uiF14();
	esos_uiF14_flashLED3(250);
    esos_RegisterTask(sensor);
}