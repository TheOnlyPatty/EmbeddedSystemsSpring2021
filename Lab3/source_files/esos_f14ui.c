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
#include <stdbool.h>

// Used for determining which way the RPG is rotating and at what velocity
#define velocity(v) (v < 0 ? -v : v)
#define MAX_DOUBLE_PRESS_TIME 0xFFFF //temporary

    // PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_RPGCounter = newValue;
    return;
}

/* //I don't think this is necessary


inline void _esos_uiF14_setLastRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_lastRPGCounter = newValue;
    return;
}

*/



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
  return; /* Check the velocity vs the velocity required to be slow */
}

inline BOOL esos_uiF14_isRpgTurningMedium( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return; /* Check the velocity vs the velocity required to be medium */
}

inline BOOL esos_uiF14_isRpgTurningFast( void ) {
  int16_t v = velocity(_st_esos_uiF14Data.i16_RPGVelocity);
  return; /* Check the velocity vs the velocity required to be fast */
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

// Debounce RPG and increment/decrement i16_RPGCounter
// 3 = start for rpg_value
static uint8_t u8_rpg_value = 3;
ESOS_USER_TIMER(__esos_uiF14_rpg_poll) {
    __RPGA_NEW = RPGA;
    __RPGB_NEW = RPGB;

    if (u8_rpg_value == 0 && (__RPG_VALUE == 1 || __RPG_VALUE == 2)) {
        if (__RPG_VALUE == 1)
            _st_esos_uiF14Data.u16_RPGCounter += 1;
        else 
            _st_esos_uiF14Data.u16_RPGCounter -= 1;
    }
}

// Calculate RPG velocity
static int32_t i32_prev_position = 0;
static int32_t i32_cur_position = 0;
//static int32_t i32_avg_velocity = 0; // Using the average might make the velocity measurement more accurate?
static int32_t i32_cur_velocity = 0;
ESOS_USER_TIMER(__esos_uiF14_rpg_velocity) {
    i32_cur_position = ((int32_t)_st_esos_uiF14Data.u16_RPGCounter) << 12;

    i32_cur_velocity = (i32_cur_position - i32_prev_position);
    //i32_avg_velocity = ((3 * i32_cur_velocity) / 8) + ((5 * i32_avg_velocity) / 8);
    _st_esos_uiF14Data.i16_RPGVelocity = i32_cur_velocity;
}

// This is more of an RPG function, but it needs to be below the velocity calculation I think
inline void esos_uiF14_resetRPG( void ) {
    _st_esos_uiF14Data.u16_RPGCounter = 0;
    _st_esos_uiF14Data.i16_RPGVelocity = 0;
    i32_prev_position = 0;
    i32_cur_position = 0;
    //i32_avg_velocity = 0;
    i32_cur_velocity = 0;
    return;
}

/* // Commented out because this is the second defitinion of the _esos_uiF14_task timer
ESOS_USER_TIMER(_esos_uiF14_task) { //UI Task called my timer every 10ms
    if(SW1_PRESSED) { // Switch states do not need to be reset. This is done when the state is read
        _st_esos_uiF14Data.b_SW1Pressed = TRUE;
        _st_esos_uiF14Data.b_SW1Released = FALSE; //temp
    }
    else {
        _st_esos_uiF14Data.b_SW1Released = TRUE;
        _st_esos_uiF14Data.b_SW1Pressed = FALSE; //temp
    }
}
*/


// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14() {
    __esos_unsafe_PutString(HELLO_MSG);
    CONFIG_LED1();
    CONFIG_LED2();
    CONFIG_LED3();
    CONFIG_SW1();
    CONFIG_SW2();
    CONFIG_SW3();
    //CONFIG_RGB(); //I assume this is supposed to be CONFIG_RPG?
    RPG_NEW_CONFIG();
    
    config_interrupts();
    
    esos_RegisterTimer(__esos_uiF14_task,10); //in ESOS, 1 tick/ms, so run this task every 10ms

    //esos_RegisterTask(update_LED1);
    //esos_RegisterTask(update_LED2);
    //esos_RegisterTask(update_LED3);
    return;

}


/* // Commented out because it was throwing errors
void config_interrupts() {
    // ESOS_REGISTER_PIC24_USER_INTERRUPT definition in esos_pic24_irq.h
    ESOS_REGISTER_PIC24_USER_INTERRUPT(SW1_DOUBLE_PRESS, ESOS_USER_IRQ_LEVEL1, _INT1); //TODO: dont know what _INT1 should be or if it matters in this case.
    //CONFIG_IC1_TO_RP(SW1); //Set IC1 input as SW1 (from pic24_ports.h
    CONFIG_IC1_TO_RP(_st_esos_uiF14Data.b_SW1Pressed); //Set *debounced IC1 input as SW1 (from pic24_ports.h (not sure if this will work at all, let alone debounce)
    IC1CON1.ICM = 0b000;    //Begin with IC1 off
    IC1CON1.ICSIDL = 0b1;   //Continue, even in idle mode (likely not used)
    IC1CON1.ICTSEL = 0b111; //Use system clock as counter source
    IC1CON1.ICI = 0b00;     //Interrupt every capture event (rising edge from ICM) //TODO: verify if this works with how we process button presses. Debounce likely necessary
    IC1CON1.ICM = 0b011;    //Turn IC1 on and capture every rising edge
//    IC1CON2.IC32 = 0b0;     //32 bit cascade mode disabled
    IC1CON2.ICTRIG = 0b1;   //Set to triggr mode (instead of sync mode) TODO: is this correct? Or should I do sync mode?
//    //IC1CON2.TRIGSTAT == TRUE if IC1 has been triggered and is running
    IC1CON2.SYNCSEL = 0b00000; //TODO: I'm not too sure of what to set this to
    IC1CON2 = 0x0000; //TODO: maybe?
    ESOS_ENABLE_PIC24_USER_INTERRUPT(SW1_DOUBLE_PRESS);
    
//    CONFIG_IC3_TO_RP(SW2);
//    CONFIG_IC5_TO_RP(SW3);
    return;
}
*/

/* // Commented out because it was throwing errors
unsigned int curr_capture, prev_capture; //TODO: is this where I need to define this?
ESOS_USER_INTERRUPT(SW1_DOUBLE_PRESS) {
//    IFS0bits.IC1IF = 0; //Reset interrupt flag
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(SW1_DOUBLE_PRESS); //Reset interrupt flag
    curr_capture = IC1BUF; //get latest timer val
    if(IC1CON1.ICOV) { //IC buffer overflow occurred
        //I don't think I need to do anything here
        _st_esos_uiF14Data.b_LED2On = TRUE; //for debugging
    }
    else if((curr_capture - prev_capture) < MAX_DOUBLE_PRESS_TIME) { //TODO: replace MAX_DOUBLE_PRESS_TIME
        _st_esos_uiF14Data.b_SW1DoublePressed = TRUE;
        _st_esos_uiF14Data.b_LED1On = TRUE; //for debugging
    }
    else {
        _st_esos_uiF14Data.b_LED1On = FALSE; //for debugging
        _st_esos_uiF14Data.b_LED2On = FALSE; //for debugging
    }
    if(IC1CON1.ICBNE) { //Input buffer capture not empty
        _st_esos_uiF14Data.b_LED3On = TRUE; //for debugging
    }
    else {
        _st_esos_uiF14Data.b_LED3On = FALSE; //for debugging
    }
    IC1CON1.ICM = 0b000; //Reset IC1 buffer FIFO
    prev_capture = curr_capture;
}
*/

/* //Commented out because UPDATE_LED() throws an error

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

*/

