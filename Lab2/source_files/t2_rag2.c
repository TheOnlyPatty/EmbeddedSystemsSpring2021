#include "revF14.h"
#include "esos.h"
#include "esos_pic24.h"

//Define LED colors
#define RED_LED LED3
#define AMBER_LED LED2
#define GREEN_LED LED1

//Define states
#define RED 0
#define AMBER 1
#define GREEN 2

#define EAST_WEST 0
#define NORTH_SOUTH 1

uint8_t state[2]; // Array to store the states of both traffic signals


ESOS_USER_TASK(state_machine) {
    ESOS_TASK_BEGIN();
    while(TRUE) {
        state[NORTH_SOUTH] = RED;
        state[EAST_WEST] = GREEN;
        
        if(SW1_PRESSED) ESOS_TASK_WAIT_TICKS(30000) // Wait for 30s
        else ESOS_TASK_WAIT_TICKS(10000) // Wait for 10s
        
        state[EAST_WEST] = AMBER;
        
        ESOS_TASK_WAIT_TICKS(3000) // Wait for 3s
        
        if(SW1_PRESSED) {
            state[EAST_WEST] = RED;
            ESOS_TASK_WAIT_TICKS(1000) // Wait for 1s
        }
        
        state[NORTH_SOUTH] = GREEN;
        state[EAST_WEST] = RED;
        
        if(SW1_PRESSED) ESOS_TASK_WAIT_TICKS(30000) // Wait for 30s
        else ESOS_TASK_WAIT_TICKS(10000) // Wait for 10s
        
        state[NORTH_SOUTH] = AMBER;
        ESOS_TASK_WAIT_TICKS(3000) // Wait for 3s
        
        if(SW1_PRESSED) {
            state[NORTH_SOUTH] = RED;
            ESOS_TASK_WAIT_TICKS(1000) // Wait for 1s
        }
    }
    ESOS_TASK_END();
}

ESOS_USER_TASK(display_switcher) {
    ESOS_TASK_BEGIN();
    uint8_t curr_state;
    while(TRUE) {
        if(SW3_PRESSED) curr_state = EAST_WEST; // Define which traffic signal is displayed
        else curr_state = NORTH_SOUTH;
        
        if(state[curr_state] == RED) { // Turn on red LED and turn off others
            RED_LED = 0;
            AMBER_LED = 0;
            GREEN_LED = 0;
        }
        else if(state[curr_state] == AMBER) { // Turn on amber LED and turn off others
            RED_LED = 1;
            AMBER_LED = 1;
            GREEN_LED = 0;
        }
        else if(state[curr_state] == GREEN) { // Turn on green LED and turn off others
            RED_LED = 1;
            AMBER_LED = 0;
            GREEN_LED = 1;
        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}


void user_init()
{
    __esos_unsafe_PutString( HELLO_MSG );
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW3();
    
    esos_RegisterTask(state_machine);
    esos_RegisterTask(display_switcher);
}
