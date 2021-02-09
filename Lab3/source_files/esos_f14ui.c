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
    return (_st_esos_uiF14Data.b_SW1Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW1Released (void) {
    return (_st_esos_uiF14Data.b_SW1Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW1DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW1DoublePressed==TRUE);
}
//SW2
inline BOOL esos_uiF14_getSW2Pressed (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW2Released (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW2DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW2DoublePressed==TRUE);
}
//SW3
inline BOOL esos_uiF14_getSW3Pressed (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW3Released (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW3DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW3DoublePressed==TRUE);
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
    __esos_unsafe_PutString( HELLO_MSG );
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    
//    esos_RegisterTask( __uiF14_task ); // Original line here. Wrong, right?
    esos_RegisterTask( __esos_uiF14_task )
}


// UIF14 task to manage user-interface
ESOS_USER_TASK( __esos_uiF14_task ){
  
    ESOS_TASK_BEGIN();
    while(TRUE) {
        // do your UI stuff here
        ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD ); //What is this?
    }
    ESOS_TASK_END();
}
