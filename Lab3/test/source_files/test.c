#include "esos.h"
#include "esos_pic24.h"
#include "revF14.h"
#include "pic24_ports.h"
#include "esos_irq.h"
#include "esos_pic24_rs232.h" // Pretty sure rs232 is a random communication protocol
#include "pic24_timer.h"

#define __ESOS_UIF14_UI_PERIOD_MS 10


typedef struct {
    BOOL b_SW1Pressed;
    BOOL b_SW1DoublePressed;
    BOOL b_SW2Pressed;
    BOOL b_SW2DoublePressed;    
    BOOL b_SW3Pressed;
    BOOL b_SW3DoublePressed;    
    
    BOOL b_RPGAHigh;
    BOOL b_RPGALast;
    BOOL b_RPGBHigh;
    BOOL b_RPGBLast;
    BOOL b_RPGMoving;
    BOOL b_RPGMoving_slow;
    BOOL b_RPGMoving_med;
    BOOL b_RPGMoving_fast;
    BOOL b_RPGTurning_CW;
    BOOL b_RPGTurning_CCW;

    uint16_t u16_noVelocity;
    uint16_t u16_medVelocity;
    uint16_t u16_fastVelocity;
    
    BOOL b_LED1On;
    uint16_t u16_LED1FlashPeriod;    
    BOOL b_LED2On;
    uint16_t u16_LED2FlashPeriod;        
    BOOL b_LED3On;
    uint16_t u16_LED3FlashPeriod;        
    
    uint16_t i16_RPGCounter;
    uint16_t i16_lastRPGCounter;
    uint16_t u16_RPGPeriod_ms;
    uint16_t u16_RPGLastPeriod_ms;
} _st_esos_uiF14Data_t;

_st_esos_uiF14Data_t _st_esos_uiF14Data;

void defaults( void ) {
  _st_esos_uiF14Data.b_SW1Pressed = FALSE;
  _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
  _st_esos_uiF14Data.b_SW2Pressed = FALSE;
  _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
  _st_esos_uiF14Data.b_SW3Pressed = FALSE;
  _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;

  _st_esos_uiF14Data.b_RPGAHigh = FALSE;
  _st_esos_uiF14Data.b_RPGALast = FALSE;
  _st_esos_uiF14Data.b_RPGBHigh = FALSE;
  _st_esos_uiF14Data.b_RPGBLast = FALSE;
  _st_esos_uiF14Data.b_RPGMoving = FALSE;
  _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
  _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
  _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
  _st_esos_uiF14Data.b_RPGTurning_CW = FALSE;
  _st_esos_uiF14Data.b_RPGTurning_CCW = FALSE;

  _st_esos_uiF14Data.u16_noVelocity = 400; 
  _st_esos_uiF14Data.u16_medVelocity = 150;
  _st_esos_uiF14Data.u16_fastVelocity = 15;

  _st_esos_uiF14Data.b_LED1On = FALSE;
  _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
  _st_esos_uiF14Data.b_LED2On = FALSE;
  _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
  _st_esos_uiF14Data.b_LED3On = FALSE;
  _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;

  _st_esos_uiF14Data.i16_RPGCounter = 0;
  _st_esos_uiF14Data.i16_lastRPGCounter = 0;
  _st_esos_uiF14Data.u16_RPGPeriod_ms = 0;
  _st_esos_uiF14Data.u16_RPGLastPeriod_ms = 0;

  return;
}

ESOS_USER_TASK(task1) {
    ESOS_TASK_BEGIN();
    while(1) {

        // Check if RPGA has changed
        if (RPGA != _st_esos_uiF14Data.b_RPGALast) {
            // RPG is moving
            _st_esos_uiF14Data.b_RPGMoving = TRUE;
            // Set RPGALast to whatever RPGA is right now
            _st_esos_uiF14Data.b_RPGALast = RPGA;


            // THIS NEEDS FIXING
            // Calculate time since last change in RPG. Used to calculate velocity
            _st_esos_uiF14Data.u16_RPGPeriod_ms = (esos_GetSystemTick() - _st_esos_uiF14Data.u16_RPGLastPeriod_ms);

            // For testing
            printf("Period: %u\n", _st_esos_uiF14Data.u16_RPGPeriod_ms);
            printf("Period Last: %u\n", _st_esos_uiF14Data.u16_RPGLastPeriod_ms);
            printf("Time: %lu\n\n", esos_GetSystemTick());

            // Change last period to current period
            //_st_esos_uiF14Data.u16_RPGLastPeriod_ms = _st_esos_uiF14Data.u16_RPGPeriod_ms;

            // New method for getting last period
            _st_esos_uiF14Data.u16_RPGLastPeriod_ms = esos_GetSystemTick();

            // Figure out what speed the RPG is moving (slow, medium, fast)
            //Fast
            if (_st_esos_uiF14Data.u16_RPGPeriod_ms >= _st_esos_uiF14Data.u16_medVelocity) {
                _st_esos_uiF14Data.b_RPGMoving_slow = TRUE;
                _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
            }

            // Medium
            else if (_st_esos_uiF14Data.u16_RPGPeriod_ms <= _st_esos_uiF14Data.u16_medVelocity && _st_esos_uiF14Data.u16_RPGPeriod_ms > _st_esos_uiF14Data.u16_fastVelocity) {
                _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_med = TRUE;
                _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
            }
            // Slow
            else {
                _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_fast = TRUE;
            }

            // Figure out which direction the RPG is moving (clockwise or counter-clockwise)
            // Counter-clockwise
            if ((RPGA == 1 && RPGB == 0) || (RPGA == 0 && RPGB == 1) ) {
                _st_esos_uiF14Data.b_RPGTurning_CW = TRUE;
                _st_esos_uiF14Data.b_RPGTurning_CCW = FALSE;
                _st_esos_uiF14Data.i16_RPGCounter += 1;
            }
            // Clockwise
            else {
                _st_esos_uiF14Data.b_RPGTurning_CW = FALSE;
                _st_esos_uiF14Data.b_RPGTurning_CCW = TRUE;
                _st_esos_uiF14Data.i16_RPGCounter -= 1;
            }
                            
        }
        // If the RPG is not moving, set all of the movement related variables to false
        else {
        _st_esos_uiF14Data.b_RPGMoving = FALSE;
        _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
        _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
        _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
        _st_esos_uiF14Data.b_RPGTurning_CW = FALSE;
        _st_esos_uiF14Data.b_RPGTurning_CCW = FALSE;
        }

        ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD_MS );
    
    }
    ESOS_TASK_END();
}

ESOS_USER_TASK(task2) {
    ESOS_TASK_BEGIN();
    while (1) {
        /* // Test movement detection
        if (_st_esos_uiF14Data.b_RPGMoving == TRUE) {
            LED2_ON();
            ESOS_TASK_WAIT_TICKS(1000);
            LED2_OFF();
        }
        */

        /* // Test clockwise vs. counter-clockwise
        if (_st_esos_uiF14Data.b_RPGTurning_CW) {
            LED3_ON();
            ESOS_TASK_WAIT_TICKS(1000);
            LED3_OFF();
        }
        
        if (_st_esos_uiF14Data.b_RPGTurning_CCW) {
            LED1_ON();
            ESOS_TASK_WAIT_TICKS(1000);
            LED1_OFF();
        }
        */

        // Test rotational velocity
        if (_st_esos_uiF14Data.b_RPGMoving_fast == TRUE) {
            LED3_ON();
            ESOS_TASK_WAIT_TICKS(100);
            LED3_OFF();
        }
        if (_st_esos_uiF14Data.b_RPGMoving_med == TRUE) {
            LED2_ON();
            ESOS_TASK_WAIT_TICKS(100);
            LED2_OFF();
        }
        if (_st_esos_uiF14Data.b_RPGMoving_slow == TRUE) {
            LED1_ON();
            ESOS_TASK_WAIT_TICKS(100);
            LED1_OFF();
        }
        

        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

void init_config() {
    __esos_unsafe_PutString(HELLO_MSG);
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
    CONFIG_RPG();
}

void user_init(void) {
    init_config();
    defaults();
    esos_RegisterTask(task1);
    esos_RegisterTask(task2);
}
