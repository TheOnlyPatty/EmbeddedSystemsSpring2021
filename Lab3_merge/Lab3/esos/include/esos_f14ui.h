#ifndef   ESOS_UIF14_H
#define ESOS_UIF14_H

#include "esos_pic24.h"
#include "esos_pic24_rs232.h"
#include "pic24_timer.h"
#include "revF14.h"
#include "esos.h"

//from Alex's:
#include <all_generic.h>


    // STRUCTURES

typedef struct {
    BOOL b_SW1Pressed;
    BOOL b_SW1DoublePressed;
    BOOL b_SW2Pressed;
    BOOL b_SW2DoublePressed;
    BOOL b_SW3Pressed;
    BOOL b_SW3DoublePressed;
    
    //BOOL b_RPGAHigh;
    BOOL b_RPGALast; // Last signal received from RPGA (0 or 1)
    //BOOL b_RPGBHigh;
    BOOL b_RPGBLast; // Last signal received from RPGB (0 or 1)
    BOOL b_RPGMoving; // Is the RPG moving?
    BOOL b_RPGMoving_slow; // Is the RPG moving slowly?
    BOOL b_RPGMoving_med; // Is the RPG moving at a medium speed?
    BOOL b_RPGMoving_fast; // Is the RPG moving at a medium quickly?
    BOOL b_RPGTurning_CW; // Is the RPG turning clockwise?
    BOOL b_RPGTurning_CCW; // Is the RPG turning counter-clockwise?
    uint16_t u16_noVelocity; // Threshold for no RPG movement
    uint16_t u16_medVelocity; // Threshold for medium speed RPG movement
    uint16_t u16_fastVelocity; // Threshold for high speed RPG movement
    
    BOOL b_LED1On;
    uint16_t u16_LED1FlashPeriod;    
    BOOL b_LED2On;
    uint16_t u16_LED2FlashPeriod;        
    BOOL b_LED3On;
    uint16_t u16_LED3FlashPeriod;        
    
    uint16_t i16_RPGCounter;
    uint16_t i16_lastRPGCounter;
    uint16_t u16_RPGPeriod_ms; // Time between RPG movements
    uint16_t u16_RPGLastPeriod_ms; // Previous time between RPG movements used to approximate velocity
} _st_esos_uiF14Data_t;

    // DEFINEs and CONSTANTs
#define __ESOS_TICKS_TO_MS(x)           (x/1)
#define __ESOS_MS_TO_TICKS(x)           (x*1)
#define __ESOS_UIF14_UI_PERIOD_MS       10
#define __RPG_TURNS_PER_REV             12
#define __DEBOUNCE_TIMER                20

    // PRIVATE DATA
 
_st_esos_uiF14Data_t _st_esos_uiF14Data;

    // PRIVATE FUNCTION PROTOTYPES

/* // I don't think these are needed for Lab 3
uint16_t esos_uiF14_getRPGCounter (void);
void esos_ui_setRPGCounter (uint16_t);

uint16_t esos_uiF14_getLastRPGCounter (void);
void esos_ui_setLastRPGCounter (uint16_t);
*/

    // PUBLIC API FUNCTION PROTOTYPES

inline BOOL esos_uiF14_isSW1Pressed (void);
inline BOOL esos_uiF14_isSW1Released (void);
inline BOOL esos_uiF14_isSW1DoublePressed (void);

inline BOOL esos_uiF14_isSW2Pressed (void);
inline BOOL esos_uiF14_isSW2Released (void);
inline BOOL esos_uiF14_isSW2DoublePressed (void);

inline BOOL esos_uiF14_isSW3Pressed (void);
inline BOOL esos_uiF14_isSW3Released (void);
inline BOOL esos_uiF14_isSW3DoublePressed (void);

inline void esos_uiF14_turnLED1On (void);
inline void esos_uiF14_turnLED1Off (void);
inline void esos_uiF14_toggleLED1 (void);
inline void esos_uiF14_flashLED1 (uint16_t);
inline uint16_t esos_uiF14_getLED1FlashPeriod (void);

inline void esos_uiF14_turnLED2On (void);
inline void esos_uiF14_turnLED2Off (void);
inline void esos_uiF14_toggleLED2 (void);
inline void esos_uiF14_flashLED2 (uint16_t);
inline uint16_t esos_uiF14_getLED2FlashPeriod (void);

inline void esos_uiF14_turnLED3On (void);
inline void esos_uiF14_turnLED3Off (void);
inline void esos_uiF14_toggleLED3 (void);
inline void esos_uiF14_flashLED3 (uint16_t);
inline uint16_t esos_uiF14_getLED3FlashPeriod (void);

inline void esos_uiF14_turnRedLEDOn (void);
inline void esos_uiF14_turnRedLEDOff (void);
inline void esos_uiF14_turnGreenLEDOn (void);
inline void esos_uiF14_turnGreenLEDOff (void);
inline void esos_uiF14_turnYellowLEDOn (void);
inline void esos_uiF14_turnYellowLEDOff (void);

inline uint16_t esos_uiF14_getRPGValue_u16 (void);
inline void esos_uiF14_setRPG_noVelocity(uint16_t);
inline void esos_uiF14_setRPG_medVelocity(uint16_t);
inline void esos_uiF14_setRPG_fastVelocity(uint16_t);
inline BOOL esos_uiF14_isRPGTurning (void);
inline BOOL esos_uiF14_isRPGTurningSlow (void);
inline BOOL esos_uiF14_isRPGTurningMedium (void);
inline BOOL esos_uiF14_isRPGTurningFast (void);
inline BOOL esos_uiF14_isRPGTurningCW (void);
inline BOOL esos_uiF14_isRPGTurningCCW (void);

void config_esos_uiF14();
//int16_t esos_uiF14_getRPGVelocity_i16 (void);

    // PUBLIC API ESOS TASK MACROS

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED_AND_RELEASED() do {              \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED();                                     \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED();                                    \
} while (0);
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED_AND_RELEASED() do {             \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED();                                    \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED();                                   \
} while (0);
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED_AND_RELEASED()  do {           \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED();                                   \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED();                                  \
} while (0);
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3DoublePressed() )

/* // I don't these these are needed for Lab 3
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS()          // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CW()       // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CCW()      // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM()         // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CW()      // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CCW()     // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST()           // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CW()        // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CCW()       // not yet implemented

//I don't think we need these for lab 3
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_REV(y)           // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CW_REV(y)        // not yet implemented
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CCW_REV(y)       // not yet implemented
*/

#endif    // ESOS_UIF14_H