/*******************************************************************
 *
 * C code framework for ESOS user-interface (UI) service
 *
 *    requires the EMBEDDED SYSTEMS target rev. F14
 *
 * ****************************************************************/

#include "esos.h"
#include "esos_pic24.h"
#include "esos_f14ui.h"
#include "revF14.h"
#include <stdio.h>

_st_esos_uiF14Data_t _st_esos_uiF14Data;

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
inline BOOL esos_uiF14_isSW1Pressed (void) {
    return _st_esos_uiF14Data.b_SW1Pressed;
}
inline BOOL esos_uiF14_isSW1Released (void) {
    return (!_st_esos_uiF14Data.b_SW1Pressed);
}
inline BOOL esos_uiF14_isSW1DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW1DoublePressed;
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    return temp;
}
inline void esos_uiF14_setSW1DoublePressedPeriod (uint16_t period) {
    _st_esos_uiF14Data.u16_SW1DoublePressedPeriod = period;
    return;
}
inline uint16_t esos_uiF14_getSW1DoublePressedPeriod (void) {
    return _st_esos_uiF14Data.u16_SW1DoublePressedPeriod;
}

//SW2
inline BOOL esos_uiF14_isSW2Pressed (void) {
    return _st_esos_uiF14Data.b_SW2Pressed;
}
inline BOOL esos_uiF14_isSW2Released (void) {
    return (!_st_esos_uiF14Data.b_SW2Pressed);
}
inline BOOL esos_uiF14_isSW2DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW2DoublePressed;
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    return temp;
}
inline void esos_uiF14_setSW2DoublePressedPeriod (uint16_t period) {
    _st_esos_uiF14Data.u16_SW2DoublePressedPeriod = period;
    return;
}
inline uint16_t esos_uiF14_getSW2DoublePressedPeriod (void) {
    return _st_esos_uiF14Data.u16_SW2DoublePressedPeriod;
}
//SW3
inline BOOL esos_uiF14_isSW3Pressed (void) {
    return _st_esos_uiF14Data.b_SW3Pressed;
}
inline BOOL esos_uiF14_isSW3Released (void) {
    return (!_st_esos_uiF14Data.b_SW3Pressed);
}
inline BOOL esos_uiF14_isSW3DoublePressed (void) {
    BOOL temp = _st_esos_uiF14Data.b_SW3DoublePressed;
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
    return temp;
}
inline void esos_uiF14_setSW3DoublePressedPeriod (uint16_t period) {
    _st_esos_uiF14Data.u16_SW3DoublePressedPeriod = period;
    return;
}
inline uint16_t esos_uiF14_getSW3DoublePressedPeriod (void) {
    return _st_esos_uiF14Data.u16_SW3DoublePressedPeriod;
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

inline int16_t esos_uiF14_getRPGValue_i16 ( void ) {
    return _st_esos_uiF14Data.i16_RPGCounter;
}
inline BOOL esos_uiF14_isRPGTurning ( void ) {
    return _st_esos_uiF14Data.b_RPGMoving;
}
inline BOOL esos_uiF14_isRPGTurningSlow( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_slow;
}
inline BOOL esos_uiF14_isRPGTurningMedium( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_med;
}
inline BOOL esos_uiF14_isRPGTurningFast( void ) {
    return _st_esos_uiF14Data.b_RPGMoving_fast;
}
inline BOOL esos_uiF14_isRPGTurningCW( void ) {
    return _st_esos_uiF14Data.b_RPGTurning_CW;
}
inline BOOL esos_uiF14_isRPGTurningCCW( void ) {
    return _st_esos_uiF14Data.b_RPGTurning_CCW;
}
inline uint16_t esos_uiF14_getRPGPeriod_u16( void ) {
    return _st_esos_uiF14Data.u16_RPGPeriod_ms;
}
inline void esos_uiF14_setRPG_noVelocity( uint16_t noVelocity ) {
    _st_esos_uiF14Data.u16_noVelocity = noVelocity;
    return;
}
inline uint16_t esos_uiF14_getRPGSlowThreshold(void) {
    return _st_esos_uiF14Data.u16_noVelocity;
}
inline void esos_uiF14_setRPG_medVelocity( uint16_t medVelocity ) {
    _st_esos_uiF14Data.u16_medVelocity = medVelocity;
    return;
}
inline uint16_t esos_uiF14_getRPGMediumThreshold(void) {
    return _st_esos_uiF14Data.u16_medVelocity;
}
inline void esos_uiF14_setRPG_fastVelocity( uint16_t fastVelocity ) {
    _st_esos_uiF14Data.u16_fastVelocity = fastVelocity;
    return;
}
inline uint16_t esos_uiF14_getRPGFastThreshold(void) {
    return _st_esos_uiF14Data.u16_fastVelocity;
}

inline int16_t esos_uiF14_getRPGCounter_i16(void) {
    return _st_esos_uiF14Data.i16_RPGCounter;
}

inline void esos_uiF14_setRPGCounter_i16(int16_t new_counter) {
    _st_esos_uiF14Data.i16_RPGCounter = new_counter;
}

inline int16_t esos_uiF14_getRPGVelocity_i16(void) {
    return _st_esos_uiF14Data.i16_RPGVelocity;
}

inline void esos_uiF14_resetRPG(void) {
    _st_esos_uiF14Data.i16_RPGCounter = 0;
    _st_esos_uiF14Data.i16_RPGVelocity = 0;
}

void init_defaults( void ) { // Set default values
    _st_esos_uiF14Data.b_SW1Pressed = FALSE;
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    _st_esos_uiF14Data.u16_SW1DoublePressedPeriod = 500;
    _st_esos_uiF14Data.b_SW2Pressed = FALSE;
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    _st_esos_uiF14Data.u16_SW2DoublePressedPeriod = 500;
    _st_esos_uiF14Data.b_SW3Pressed = FALSE;
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
    _st_esos_uiF14Data.u16_SW3DoublePressedPeriod = 500;

    _st_esos_uiF14Data.b_RPGALast = FALSE;
    _st_esos_uiF14Data.b_RPGBLast = FALSE;
    _st_esos_uiF14Data.b_RPGMoving = FALSE;
    _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
    _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
    _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
    _st_esos_uiF14Data.b_RPGTurning_CW = FALSE;
    _st_esos_uiF14Data.b_RPGTurning_CCW = FALSE;
    _st_esos_uiF14Data.i16_RPGVelocity = 0;

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

static volatile int32_t i32_average_velocity = 0;

ESOS_USER_TASK( __esos_uiF14_task ) {

    uint16_t time_since_change = 0;

    ESOS_TASK_BEGIN();
    while(TRUE) {

        /* BEGIN RPG STUFF */
        time_since_change = (esos_GetSystemTick()) - (_st_esos_uiF14Data.u16_RPGLastPeriod_ms);
        // Check if RPGA has changed
        if (RPGA != _st_esos_uiF14Data.b_RPGALast) {
            // RPG is moving
            _st_esos_uiF14Data.b_RPGMoving = TRUE;
            // Set RPGALast to whatever RPGA is right now
            _st_esos_uiF14Data.b_RPGALast = RPGA;

            // Calculate time since last change in RPG. Used to calculate velocity
            _st_esos_uiF14Data.u16_RPGPeriod_ms = (esos_GetSystemTick()) - (_st_esos_uiF14Data.u16_RPGLastPeriod_ms);

            // New method for getting last period
            _st_esos_uiF14Data.u16_RPGLastPeriod_ms = esos_GetSystemTick();

            i32_average_velocity = (3 * _st_esos_uiF14Data.u16_RPGPeriod_ms / 8) + (5 * i32_average_velocity / 8); // Moving exponential average
            _st_esos_uiF14Data.i16_RPGVelocity = i32_average_velocity;

            // Figure out what speed the RPG is moving (slow, medium, fast)
            //Slow
            if (_st_esos_uiF14Data.u16_RPGPeriod_ms >= _st_esos_uiF14Data.u16_medVelocity) {
                _st_esos_uiF14Data.b_RPGMoving_slow = TRUE;
                _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
            }

            // Medium
            else if ((_st_esos_uiF14Data.u16_RPGPeriod_ms <= _st_esos_uiF14Data.u16_medVelocity) && (_st_esos_uiF14Data.u16_RPGPeriod_ms > _st_esos_uiF14Data.u16_fastVelocity)) {
                _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_med = TRUE;
                _st_esos_uiF14Data.b_RPGMoving_fast = FALSE;
            }
            // Fast
            else {
                _st_esos_uiF14Data.b_RPGMoving_slow = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_med = FALSE;
                _st_esos_uiF14Data.b_RPGMoving_fast = TRUE;
            }

            // Figure out which direction the RPG is moving (clockwise or counter-clockwise)
            // Clockwise
            if ((RPGA == 1 && RPGB == 0) || (RPGA == 0 && RPGB == 1) ) {
                _st_esos_uiF14Data.b_RPGTurning_CW = TRUE;
                _st_esos_uiF14Data.b_RPGTurning_CCW = FALSE;
                _st_esos_uiF14Data.i16_RPGCounter += 1;
            }
            // Counter-clockwise
            else {
                _st_esos_uiF14Data.b_RPGTurning_CW = FALSE;
                _st_esos_uiF14Data.b_RPGTurning_CCW = TRUE;
                _st_esos_uiF14Data.i16_RPGCounter -= 1;
            }
                            
        }
        // If the RPG is not moving, set all of the movement related variables to false
        else if (time_since_change > _st_esos_uiF14Data.u16_noVelocity) {
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

/* BEGIN LED STUFF */

ESOS_USER_TASK(update_LED1) {
    ESOS_TASK_BEGIN();
    while(1) {
        if(_st_esos_uiF14Data.u16_LED1FlashPeriod != 0) _st_esos_uiF14Data.b_LED1On ^= 1;
        if(_st_esos_uiF14Data.b_LED1On == TRUE) LED1_ON();
        else LED1_OFF();
        if(_st_esos_uiF14Data.u16_LED1FlashPeriod != 0) ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED1FlashPeriod / 2);
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED2) {
    ESOS_TASK_BEGIN();
    while(1) {
        if(_st_esos_uiF14Data.u16_LED2FlashPeriod != 0) _st_esos_uiF14Data.b_LED2On ^= 1;
        if(_st_esos_uiF14Data.b_LED2On == TRUE) LED2_ON();
        else LED2_OFF();
        if(_st_esos_uiF14Data.u16_LED2FlashPeriod != 0) ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED2FlashPeriod / 2);
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED3) {
    ESOS_TASK_BEGIN();
    while(1) {
        if(_st_esos_uiF14Data.u16_LED3FlashPeriod != 0) _st_esos_uiF14Data.b_LED3On ^= 1;
        if(_st_esos_uiF14Data.b_LED3On == TRUE) LED3_ON();
        else LED3_OFF();
        if(_st_esos_uiF14Data.u16_LED3FlashPeriod != 0) ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED3FlashPeriod / 2);
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

/* BEGIN SWITCH INTERRUPT STUFF */

ESOS_USER_TIMER(SW_Update)
{
    //Check switches every 60ms and use their value at that moment as a debounced switch value
    SW1_DEBOUNCED = SW1_PRESSED;
    SW2_DEBOUNCED = SW2_PRESSED;
    SW3_DEBOUNCED = SW3_PRESSED;
    
    _st_esos_uiF14Data.b_SW1Pressed = SW1_DEBOUNCED;
    _st_esos_uiF14Data.b_SW2Pressed = SW2_DEBOUNCED;
    _st_esos_uiF14Data.b_SW3Pressed = SW3_DEBOUNCED;
    
//    if(_st_esos_uiF14Data.b_SW1Pressed) esos_uiF14_turnLED1On();
//    else esos_uiF14_turnLED1Off();
//    if(_st_esos_uiF14Data.b_SW2Pressed) esos_uiF14_turnLED2On();
//    else esos_uiF14_turnLED2Off();
//    if(_st_esos_uiF14Data.b_SW3Pressed) esos_uiF14_turnLED3On();
//    else esos_uiF14_turnLED3Off();

    //Reset IC Buffers if only a single press occurred
    if (SW1_IC_BUFFER / CYCLES_PER_MS >= _st_esos_uiF14Data.u16_SW1DoublePressedPeriod) SW_IC_BUFFER_RESET(11,12);
    if (SW2_IC_BUFFER / CYCLES_PER_MS >= _st_esos_uiF14Data.u16_SW2DoublePressedPeriod) SW_IC_BUFFER_RESET(13,14);
    if (SW3_IC_BUFFER / CYCLES_PER_MS >= _st_esos_uiF14Data.u16_SW3DoublePressedPeriod) SW_IC_BUFFER_RESET(15,16);
}

ESOS_USER_INTERRUPT(ESOS_IRQ_PIC24_IC11) //Interrupt for SW1 press
{
    BOOL debounce = !SW1_DEBOUNCED;
    if (debounce) {
        //_st_esos_uiF14Data.b_SW1Pressed = 1;
        _st_esos_uiF14Data.b_SW1DoublePressed = 0;
        if (IC11CON2bits.ICTRIG == 0) {
            if(SW1_IC_BUFFER / CYCLES_PER_MS < _st_esos_uiF14Data.u16_SW1DoublePressedPeriod) {
                _st_esos_uiF14Data.b_SW1DoublePressed = 1;
//                esos_uiF14_turnLED1On();
            }
        }
        else {
            SW_IC_BUFFER_RESET(11,12);
            IC11CON2bits.ICTRIG = IC12CON2bits.ICTRIG = 0; //resume IC
        }
    }
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(ESOS_IRQ_PIC24_IC11);
}
ESOS_USER_INTERRUPT(ESOS_IRQ_PIC24_IC13) //Interrupt for SW2 press
{
    BOOL debounce = !SW2_DEBOUNCED;
    if (debounce) {
//        _st_esos_uiF14Data.b_SW2Pressed = 1;
        _st_esos_uiF14Data.b_SW2DoublePressed = 0;
        if (IC13CON2bits.ICTRIG == 0) {
            if(SW2_IC_BUFFER / CYCLES_PER_MS < _st_esos_uiF14Data.u16_SW2DoublePressedPeriod) {
                _st_esos_uiF14Data.b_SW2DoublePressed = 1;
//                esos_uiF14_turnLED2On();
            }
        }
        else {
            SW_IC_BUFFER_RESET(13,14);
            IC13CON2bits.ICTRIG = IC14CON2bits.ICTRIG = 0; //resume IC
        }
    }
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(ESOS_IRQ_PIC24_IC13);
}
ESOS_USER_INTERRUPT(ESOS_IRQ_PIC24_IC15) //Interrupt for SW3 press
{
    BOOL debounce = !SW3_DEBOUNCED;
    if (debounce) {
//        _st_esos_uiF14Data.b_SW3Pressed = 1;
        _st_esos_uiF14Data.b_SW3DoublePressed = 0;
        if (IC15CON2bits.ICTRIG == 0) {
            if(SW3_IC_BUFFER / CYCLES_PER_MS < _st_esos_uiF14Data.u16_SW3DoublePressedPeriod) {
                _st_esos_uiF14Data.b_SW3DoublePressed = 1;
//                esos_uiF14_turnLED3On();
            }
        }
        else {
            SW_IC_BUFFER_RESET(15,16);
            IC15CON2bits.ICTRIG = IC16CON2bits.ICTRIG = 0; //resume IC
        }
    }
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(ESOS_IRQ_PIC24_IC15);
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
    CONFIG_SW1_DEBOUNCE_AND_IC();
    CONFIG_SW2_DEBOUNCE_AND_IC();
    CONFIG_SW3_DEBOUNCE_AND_IC();
    CONFIG_RPG();
    CONFIG_POT();
    CONFIG_THERM();
    
    esos_RegisterTask(__esos_uiF14_task);
    
    esos_RegisterTimer(SW_Update, 60);

    // These tasks did not function properly for me. Moved the code into the __esos_uiF14_task
    esos_RegisterTask(update_LED1);
    esos_RegisterTask(update_LED2);
    esos_RegisterTask(update_LED3);
    return;
}
