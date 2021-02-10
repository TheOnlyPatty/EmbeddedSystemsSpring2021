/*******************************************************************
 * 
 * C code framework for ESOS user-interface (UI) service
 * 
 *    requires the EMBEDDED SYSTEMS target rev. F14
 * 
 * ****************************************************************/

//# include esos_f14ui.h; //original line here. Seemed wrong?
#include "esos_f14ui.h"
#include "revF14.h"
#include "esos.h"
#include "esos_pic24.h"

// PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_RPGCounter = newValue;
    return;
}

inline void _esos_uiF14_setLastRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_lastRPGCounter = newValue;
    return;
}

// PUBLIC SWITCH FUNCTIONS

//SW1
inline BOOL esos_uiF14_getSW1Pressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW1Pressed;
    _st_esos_uiF14Data.b_SW1Pressed = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW1Released (void) {
    bool temp = _st_esos_uiF14Data.b_SW1Released;
    _st_esos_uiF14Data.b_SW1Released = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW1DoublePressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW1DoublePressed;
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    return (temp==TRUE);
}
//SW2
inline BOOL esos_uiF14_getSW2Pressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW2Pressed;
    _st_esos_uiF14Data.b_SW2Pressed = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW2Released (void) {
    bool temp = _st_esos_uiF14Data.b_SW2Released;
    _st_esos_uiF14Data.b_SW2Released = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW2DoublePressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW2DoublePressed;
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    return (temp==TRUE);
}
//SW3
inline BOOL esos_uiF14_getSW3Pressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW3Pressed;
    _st_esos_uiF14Data.b_SW3Pressed = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW3Released (void) {
    bool temp = _st_esos_uiF14Data.b_SW3Released;
    _st_esos_uiF14Data.b_SW3Released = FALSE;
    return (temp==TRUE);
}

inline BOOL esos_uiF14_getSW3DoublePressed (void) {
    bool temp = _st_esos_uiF14Data.b_SW3DoublePressed;
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
    return (temp==TRUE);
}


// PUBLIC LED FUNCTIONS

inline BOOL esos_uiF14_isLED1On (void) {
    return (_st_esos_uiF14Data.b_LED1On==TRUE);
}

inline BOOL esos_uiF14_isLED1Off (void) {
    return (_st_esos_uiF14Data.b_LED1On==FALSE);
}

inline void esos_uiF14_turnLED1On (void) {
    LED1 = TRUE; //added
    _st_esos_uiF14Data.b_LED1On = TRUE;
    return;
}

inline void esos_uiF14_turnLED1Off (void) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = 0; //added
    LED1 = FALSE; //added
    _st_esos_uiF14Data.b_LED1On = FALSE;
    return;
}

inline void esos_uiF14_toggleLED1 (void) {
    _st_esos_uiF14Data.b_LED1On ^= 1;
    LED1 = !LED1;
    return;
}

inline void esos_uiF14_flashLED1( uint16_t u16_period) { //TODO: Finish this
    _st_esos_uiF14Data.u16_LED1FlashPeriod = u16_period; //Maybe add the flash cycle in an additional ESOS task along with 
    return
}

/****** LED2 and LED3 will need similar.  ********/
/****** RED, GREEN, and YELLOW functions need to be created *******/

// PUBLIC RPG FUNCTIONS

inline uint16_t esos_uiF14_getRpgValue_u16 ( void ) {
    return _st_esos_uiF14Data.u16_RPGCounter;
}

inline BOOL esos_uiF14_isRpgTurning ( void ) {
    return (esos_uiF14_getRpgVelocity_i16() != 0);
}

inline BOOL esos_uiF14_isRpgTurningSlow( void ) {
  // not yet implemented
}

inline BOOL esos_uiF14_isRpgTurningMedium( void ) {
  // not yet implemented
}

inline BOOL esos_uiF14_isRpgTurningFast( void ) {
  // not yet implemented
}

inline BOOL esos_uiF14_isRpgTurningCW( void ) {
  // not yet implemented
}

inline BOOL esos_uiF14_isRpgTurningCCW( void ) {
  // not yet implemented
}

int16_t esos_uiF14_getRpgVelocity_i16( void ) {
  // not yet implemented
}

// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14() {
  // setup your UI implementation
    __esos_unsafe_PutString(HELLO_MSG);
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    CONFIG_RGB();
    
    esos_RegisterTimer(__esos_uiF14_task,10); //in ESOS, 1 tick/ms, so run this task every 10ms
}
    
ESOS_USER_TIMER(_esos_uiF14_task) { //UI Task called my timer every 10ms
    if(SW1_PRESSED) { // Switch states do not need to be reset. This is done when the state is read
        if (_st_esos_uiF14Data.b_SW1Pressed == TRUE) { //switch was aleady pressed the 10ms ago
            
        }
        _st_esos_uiF14Data.b_SW1Pressed = TRUE;
    }
    else {
        _st_esos_uiF14Data.b_SW1Released = TRUE;
    }
}


// UIF14 task to manage user-interface
//ESOS_USER_TASK( __esos_uiF14_task ){ //Commented out, because I think we need to use a user timer instead of user task for this function to make sure it runs every 10ms as required
//
//    ESOS_TASK_BEGIN();
//    while(TRUE) {
//        // do your UI stuff here
//        ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD ); //What is this?
//    }
//    ESOS_TASK_END();
//}
