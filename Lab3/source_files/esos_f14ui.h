/*******************************************************************
 * 
 * C header file for ESOS user-interface (UI) service
 * 
 *    requires the EMBEDDED SYSTEMS target rev. F14
 * 
 * ****************************************************************/

#ifndef   ESOS_UIF14_H
#define ESOS_UIF14_H //What are these lines doing?
// The above lines check to see if ESOS_UIF14_H has been defined previously in this file or an included file.
// If it has not previously been defined then everything down the the #endif runs. The #endif is at the very bottom of this file.

// STRUCTURES

typedef struct {
    BOOL b_SW1Pressed;
    BOOL b_SW1DoublePressed;
    BOOL b_SW2Pressed;
    BOOL b_SW2DoublePressed;
    BOOL b_SW3Pressed;
    BOOL b_SW3DoublePressed;    
    
    BOOL b_RPGAHigh;
    BOOL b_RPGBHigh;
    
    BOOL b_LED1On;
    uint16_t u16_LED1FlashPeriod;    
    BOOL b_LED2On;
    uint16_t u16_LED2FlashPeriod;        
    BOOL b_LED3On;
    uint16_t u16_LED3FlashPeriod;        
    
    uint16_t u16_RPGCounter;
    uint16_t u16_lastRPGCounter;
    int16_t i16_RPGVelocity;
} _st_esos_uiF14Data_t;

// DEFINEs and CONSTANTs
#define __ESOS_TICKS_TO_MS(x)           (x/1)
#define __ESOS_MS_TO_TICKS(x)           (x*1)
#define __ESOS_UIF14_UI_PERIOD_MS       10

// PRIVATE DATA 
 
_st_esos_uiF14Data_t _st_esos_uiF14Data;

// PRIVATE FUNCTION PROTOTYPES

uint16_t esos_uiF14_getRPGCounter (void);
void esos_ui_setRPGCounter (uint16_t);

uint16_t esos_uiF14_getLastRPGCounter (void);
void esos_ui_setLastRPGCounter (uint16_t);

ESOS_USER_TASK __uiF14_task;

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

inline void esos_uiF14_turnLED2On (void);
inline void esos_uiF14_turnLED2Off (void);
inline void esos_uiF14_toggleLED2 (void);
inline void esos_uiF14_flashLED2 (uint16_t);

inline void esos_uiF14_turnLED3On (void);
inline void esos_uiF14_turnLED3Off (void);
inline void esos_uiF14_toggleLED3 (void);
inline void esos_uiF14_flashLED3 (uint16_t);

inline void esos_uiF14_turnRedLEDOn (void);
inline void esos_uiF14_turnRedLEDOff (void);
inline void esos_uiF14_turnGreenLEDOn (void);
inline void esos_uiF14_turnGreenLEDOff (void);
inline void esos_uiF14_turnYellowLEDOn (void);
inline void esos_uiF14_turnYellowLEDOff (void);

inline uint16_t esos_uiF14_getRPGValue_u16 (void);
inline int16_t esos_uiF14_getRPGVelocity_i16 (void);
inline BOOL esos_uiF14_isRPGTurning (void);
inline BOOL esos_uiF14_isRPGTurningSlow (void);
inline BOOL esos_uiF14_isRPGTurningMedium (void);
inline BOOL esos_uiF14_isRPGTurningFast (void);
inline BOOL esos_uiF14_isRPGTurningCW (void);
inline BOOL esos_uiF14_isRPGTurningCCW (void);

void config_esos_uiF14();

// PUBLIC API ESOS TASK MACROS

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED_AND_RELEASED() {               \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW1_PRESSED();                                   \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW1_RELEASED();                                  \
}
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW1_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW1DoublePressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED_AND_RELEASED() {               \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW2_PRESSED();                                   \ 
  ESOS_TASK_WAIT_UNTIL_UIF14_SW2_RELEASED();                                  \
}
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW2_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW2DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED()              ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Pressed() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED()             ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3Released() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED_AND_RELEASED() {               \
  ESOS_TASK_WAIT_UNTIL_UIF14_SW3_PRESSED();                                   \ 
  ESOS_TASK_WAIT_UNTIL_UIF14_SW3_RELEASED();                                  \
}
#define ESOS_TASK_WAIT_UNTIL_UIF14_SW3_DOUBLE_PRESSED()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isSW3DoublePressed() )

#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS()          ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurning() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CW()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_UNTIL_TURNS_CCW()      ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningCCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM()         ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningMedium() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CW()      ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningMedium() && esos_uiF14_isRPGTurningCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_MEDIUM_CCW()     ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningMedium() && esos_uiF14_isRPGTurningCCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST()           ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningFast() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CW()        ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningFast() && esos_uiF14_isRPGTurningCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_TURNS_FAST_CCW()       ESOS_TASK_WAIT_UNTIL( esos_uiF14_isRPGTurningFast() && esos_uiF14_isRPGTurningCCW() )
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_REV(y) {                                                                             \
  uint16_t u16_start = _esos_uiF14_getRPGValue_i16();                                                                             \
  ESOS_TASK_WAIT_UNTIL( _esos_uiF14_getRPGCounter() == u16_start + (y /* * The number of turns it takes for one revolution*/) ||  \
                        _esos_uiF14_getRPGCounter() == u16_start - (y /* * The number of turns it takes for one revolution*/) )   \
}
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CW_REV(y) {                                                                          \
  int16_t i16_start = _esos_uiF14_getRPGValue_i16();                                                                              \
  ESOS_TASK_WAIT_UNTIL( _esos_uiF14_getRPGCounter() == i16_start + (y /* * The number of turns it takes for one revolution*/) )   \
}
#define ESOS_TASK_WAIT_UNTIL_UIF14_RPG_MAKES_CCW_REV(y) {                                                                         \
  int16_t i16_start = _esos_uiF14_getRPGValue_i16();                                                                              \
  ESOS_TASK_WAIT_UNTIL( _esos_uiF14_getRPGCounter() == i16_start - (y /* * The number of turns it takes for one revolution*/) )   \
}

#define UPDATE_LED(num)
{
    if(_st_esos_uiF14Data.u16_LED##num##FlashPeriod != 0) {
        LED##num## = !LED##num##;
        ESOS_TASK_WAIT_TICKS(_st_esos_uiF14Data.u16_LED##num##FlashPeriod / 2);
    }
    else {
        if(_st_esos_uiF14Data.b_LED##num##On == TRUE) {
            LED##num## = TRUE;
        }
        else {
            LED##num## = FALSE;
        }
    }
}


#endif    // ESOS_UIF14_H
