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

// Used for determining which way the RPG is rotating and at what velocity
#define velocity(v) (v < 0 ? -v : v)

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
    return
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
    return
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
    return
}

/****** RED, GREEN, and YELLOW functions need to be created *******/

// PUBLIC RPG FUNCTIONS

inline uint16_t esos_uiF14_getRpgValue_u16 ( void ) {
    return _st_esos_uiF14Data.u16_RPGCounter;
}

inline BOOL esos_uiF14_isRpgTurning ( void ) {
    return (esos_uiF14_getRpgVelocity_i16() != 0);
}

inline BOOL esos_uiF14_isRpgTurningSlow( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return /* Check the velocity vs the velocity required to be slow */
}

inline BOOL esos_uiF14_isRpgTurningMedium( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return /* Check the velocity vs the velocity required to be medium */
}

inline BOOL esos_uiF14_isRpgTurningFast( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return /* Check the velocity vs the velocity required to be fast */
}

inline BOOL esos_uiF14_isRpgTurningCW( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return (v > 0 && esos_uiF14_isRPGTurning()); 
}

inline BOOL esos_uiF14_isRpgTurningCCW( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return (v < 0 && esos_uiF14_isRPGTurning());
}

int16_t esos_uiF14_getRpgVelocity_i16( void ) {
  return _st_esos_uiF14Data.i16_RPGVelocity;
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

// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14() {
    __esos_unsafe_PutString(HELLO_MSG);
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    CONFIG_RGB();
    
    esos_RegisterTimer(__esos_uiF14_task,10); //in ESOS, 1 tick/ms, so run this task every 10ms
    esos_RegisterTask(update_LED1);
    esos_RegisterTask(update_LED2);
    esos_RegisterTask(update_LED3);
}

void config_interrupts() {
    IFS0bits.IC1IF = 0; //Clear the IC1 interrupt status flag
    IEC0bits.IC1IE = 1; //Enable IC1 interrupts
    IPC0bits.IC1IP = 1; //Set module interrupt priority as 1
    
    _IC1R = SW1; //Set IC1 input as SW1
//    IC1CON1
    
}
    

ESOS_USER_TIMER(_esos_uiF14_task) { //UI Task called my timer every 10ms
    if(SW1_PRESSED) { // Switch states do not need to be reset. This is done when the state is read
        _st_esos_uiF14Data.b_SW1Pressed = TRUE;
//        T2
    }
    else {
        _st_esos_uiF14Data.b_SW1Released = TRUE;
    }
}


ESOS_USER_TASK(update_LED1) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        UPDATE_LED(1);
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED2) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        UPDATE_LED(2);
    ESOS_TASK_END();
}
ESOS_USER_TASK(update_LED3) {
    //define any local vars here
    ESOS_TASK_BEGIN();
        UPDATE_LED(3);
    ESOS_TASK_END();
}
