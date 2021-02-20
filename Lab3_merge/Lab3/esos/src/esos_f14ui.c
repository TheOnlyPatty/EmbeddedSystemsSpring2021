/*******************************************************************
 *
 * C code framework for ESOS user-interface (UI) service
 *
 *    requires the EMBEDDED SYSTEMS target rev. F14
 *
 * ****************************************************************/

#include "esos_f14ui.h"
#include "revF14.h"
#include "esos.h"
#include "esos_pic24.h"

//from Alex's:
//#include "esos_f14ui.h"
//#include <esos.h>
//#include "esos_pic24.h"
//#include <revF14.h>
#include <stdio.h>

    // PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.i16_RPGCounter = newValue;
    return;
}
inline void _esos_uiF14_setLastRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.i16_lastRPGCounter = newValue;
    return;
}

    // PUBLIC SWITCH FUNCTIONS

//SW1
inline BOOL esos_uiF14_getSW1Pressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW1Pressed;
    _st_esos_uiF14Data.b_SW1Pressed = FALSE;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW1Released (void) {
    BOOL temp = !_st_esos_uiF14Data.b_SW1Pressed;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW1DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW1DoublePressed;
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    return (temp==TRUE);
}
//SW2
inline BOOL esos_uiF14_getSW2Pressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW2Pressed;
    _st_esos_uiF14Data.b_SW2Pressed = FALSE;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW2Released (void) {
    BOOL temp = !_st_esos_uiF14Data.b_SW2Pressed;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW2DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW2DoublePressed;
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    return (temp==TRUE);
}
//SW3
inline BOOL esos_uiF14_getSW3Pressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW3Pressed;
    _st_esos_uiF14Data.b_SW3Pressed = FALSE;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW3Released (void) {
    BOOL temp = !_st_esos_uiF14Data.b_SW3Pressed;
    return (temp==TRUE);
}
inline BOOL esos_uiF14_getSW3DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW3DoublePressed;
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
    return (temp==TRUE);
}


    // PUBLIC LED FUNCTIONS

//LED1
inline BOOL esos_uiF14_isLED1On (void) {
    return (_st_esos_uiF14Data.b_LED1On==TRUE);
}
inline BOOL esos_uiF14_isLED1Off (void) {
    return (_st_esos_uiF14Data.b_LED1On==FALSE);
}
inline void esos_uiF14_turnLED1On (void) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED1On = TRUE;
    return;
}
inline void esos_uiF14_turnLED1Off (void) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED1On = FALSE;
    return;
}
inline void esos_uiF14_toggleLED1 (void) {
    _st_esos_uiF14Data.b_LED1On ^= 1;
    LED1 = !LED1;
    return;
}
inline void esos_uiF14_flashLED1( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = u16_period;
    return;
}
//LED2
inline BOOL esos_uiF14_isLED2On (void) {
    return (_st_esos_uiF14Data.b_LED2On==TRUE);
}
inline BOOL esos_uiF14_isLED2Off (void) {
    return (_st_esos_uiF14Data.b_LED2On==FALSE);
}
inline void esos_uiF14_turnLED2On (void) {
    _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED2On = TRUE;
    return;
}
inline void esos_uiF14_turnLED2Off (void) {
    _st_esos_uiF14Data.u16_LED2FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED2On = FALSE;
    return;
}
inline void esos_uiF14_toggleLED2 (void) {
    _st_esos_uiF14Data.b_LED2On ^= 1;
    LED2 = !LED2;
    return;
}
inline void esos_uiF14_flashLED2( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED2FlashPeriod = u16_period;
    return;
}
//LED3
inline BOOL esos_uiF14_isLED3On (void) {
    return (_st_esos_uiF14Data.b_LED3On==TRUE);
}
inline BOOL esos_uiF14_isLED3Off (void) {
    return (_st_esos_uiF14Data.b_LED3On==FALSE);
}
inline void esos_uiF14_turnLED3On (void) {
    _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED3On = TRUE;
    return;
}
inline void esos_uiF14_turnLED3Off (void) {
    _st_esos_uiF14Data.u16_LED3FlashPeriod = 0;
    _st_esos_uiF14Data.b_LED3On = FALSE;
    return;
}
inline void esos_uiF14_toggleLED3 (void) {
    _st_esos_uiF14Data.b_LED3On ^= 1;
    LED3 = !LED3;
    return;
}
inline void esos_uiF14_flashLED3( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED3FlashPeriod = u16_period;
    return;
}

    // PUBLIC RPG FUNCTIONS

inline uint16_t esos_uiF14_getRpgValue_u16 ( void ) {
    return _st_esos_uiF14Data.i16_RPGCounter;
}
inline BOOL esos_uiF14_isRpgTurning ( void ) {
    return _st_esos_uiF14Data.b_RPGMoving;
}
inline BOOL esos_uiF14_isRpgTurningSlow( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_slow;
}
inline BOOL esos_uiF14_isRpgTurningMedium( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_med;
}
inline BOOL esos_uiF14_isRpgTurningFast( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_fast;
}
inline BOOL esos_uiF14_isRpgTurningCW( void ) {
    return _st_esos_uiF14Data.b_RPGTurning_CW;
}
inline BOOL esos_uiF14_isRpgTurningCCW( void ) {
    return _st_esos_uiF14Data.b_RPGTurning_CCW;
}
inline uint16_t esos_uiF14_getRpgPeriod_u16( void ) {
    return _st_esos_uiF14Data.u16_RPGPeriod_ms;
}
inline void esos_uiF14_setRPG_noVelocity( uint16_t noVelocity ) {
    _st_esos_uiF14Data.u16_noVelocity = noVelocity;
    return;
}
inline void esos_uiF14_setRPG_medVelocity( uint16_t medVelocity ) {
    _st_esos_uiF14Data.u16_noVelocity = medVelocity;
    return;
}
inline void esos_uiF14_setRPG_fastVelocity( uint16_t fastVelocity ) {
    _st_esos_uiF14Data.u16_fastVelocity = fastVelocity;
    return;
}


void init_defaults( void ) { // Set default values
    _st_esos_uiF14Data.b_SW1Pressed = FALSE;
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    _st_esos_uiF14Data.b_SW2Pressed = FALSE;
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    _st_esos_uiF14Data.b_SW3Pressed = FALSE;
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;

    //_st_esos_uiF14Data.b_RPGAHigh = FALSE;
    _st_esos_uiF14Data.b_RPGALast = FALSE;
    //_st_esos_uiF14Data.b_RPGBHigh = FALSE;
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

ESOS_USER_TASK( __esos_uiF14_task ) {
    // Helper variables only needed in this scope
    ESOS_TASK_BEGIN();
    while(TRUE) {
        // do your UI stuff here

        LED1 = _st_esos_uiF14Data.b_LED1On;
        LED2 = _st_esos_uiF14Data.b_LED2On;
        LED3 = _st_esos_uiF14Data.b_LED3On;


        /* BEGIN SWITCH STUFF IF THAT'S HOW YOU WANNA DO IT */



        /* BEGIN RPG STUFF */


        // Check if RPGA has changed
            if (RPGA != _st_esos_uiF14Data.b_RPGALast) {
                // RPG is moving
                _st_esos_uiF14Data.b_RPGMoving = TRUE;
                // Set RPGALast to whatever RPGA is right now
                _st_esos_uiF14Data.b_RPGALast = RPGA;

                // Calculate time since last change in RPG. Used to calculate velocity
                _st_esos_uiF14Data.u16_RPGPeriod_ms = (esos_GetSystemTick()) - (_st_esos_uiF14Data.u16_RPGLastPeriod_ms);
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
                else if (_st_esos_uiF14Data.u16_RPGPeriod_ms <=       _st_esos_uiF14Data.u16_medVelocity &&     _st_esos_uiF14Data.u16_RPGPeriod_ms > _st_esos_uiF14Data.u16_fastVelocity) {
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
                //
                // THIS NEEDS TESTING
                //
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
        ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD_MS ); // Wait 10 ms and run again
    }
    ESOS_TASK_END();
}



ESOS_USER_TASK(update_LED1) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        if(_st_esos_uiF14Data.u16_LED1FlashPeriod != 0) {
            LED1 = !LED1;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED1FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED1On == TRUE) {
                LED1 = TRUE;
            }
            else {
                LED1 = FALSE;
            }
        }
        if(_st_esos_uiF14Data.u16_LED1FlashPeriod != 0) {
            LED1 = !LED1;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED1FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED1On == TRUE) {
                LED1 = TRUE;
            }
            else {
                LED1 = FALSE;
            }
        }
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED2) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        if(_st_esos_uiF14Data.u16_LED2FlashPeriod != 0) {
            LED2 = !LED2;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED2FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED2On == TRUE) {
                LED2 = TRUE;
            }
            else {
                LED2 = FALSE;
            }
        }       if(_st_esos_uiF14Data.u16_LED2FlashPeriod != 0) {
            LED2 = !LED2;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED2FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED2On == TRUE) {
                LED2 = TRUE;
            }
            else {
                LED2 = FALSE;
            }
        }
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED3) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        if(_st_esos_uiF14Data.u16_LED3FlashPeriod != 0) {
            LED3 = !LED3;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED3FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED3On == TRUE) {
                LED3 = TRUE;
            }
            else {
                LED3 = FALSE;
            }
        }       if(_st_esos_uiF14Data.u16_LED3FlashPeriod != 0) {
            LED3 = !LED3;
            ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED3FlashPeriod / 2);
        }
        else {
            if(_st_esos_uiF14Data.b_LED3On == TRUE) {
                LED3 = TRUE;
            }
            else {
                LED3 = FALSE;
            }
        }
    ESOS_TASK_END();
}

// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14() {
    __esos_unsafe_PutString(HELLO_MSG);
    init_defaults();
    
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    CONFIG_RPG();
    
    esos_RegisterTask(__esos_uiF14_task);
    
    esos_RegisterTask(update_LED1);
    esos_RegisterTask(update_LED2);
    esos_RegisterTask(update_LED3);
    return;
}
