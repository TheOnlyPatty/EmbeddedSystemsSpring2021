#ifndef   ESOS_UIF14_H
#define ESOS_UIF14_H

#include "esos_pic24.h"
#include "esos_pic24_rs232.h"
#include "pic24_timer.h"
//#include "revF14.h"
#include "esos.h"

//from Alex's:
#include <all_generic.h>


    // STRUCTURES

typedef struct {
    BOOL b_SW1Pressed;
    BOOL b_SW1DoublePressed;
    uint16_t u16_SW1DoublePressedPeriod;
    BOOL b_SW2Pressed;
    BOOL b_SW2DoublePressed;
    uint16_t u16_SW2DoublePressedPeriod;
    BOOL b_SW3Pressed;
    BOOL b_SW3DoublePressed;
    uint16_t u16_SW3DoublePressedPeriod;
    
    BOOL b_RPGALast; // Last signal received from RPGA (0 or 1)
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


    // PRIVATE DATA
 
//_st_esos_uiF14Data_t _st_esos_uiF14Data;

    // PRIVATE FUNCTION PROTOTYPES

 // I don't think these are needed for Lab 3
int16_t esos_uiF14_getRPGCounter_i16(void);
void esos_ui_setRPGCounter_i16(uint16_t);
/*
uint16_t esos_uiF14_getLastRPGCounter (void);
void esos_ui_setLastRPGCounter (uint16_t);
*/

    // PUBLIC API FUNCTION PROTOTYPES

inline BOOL esos_uiF14_isSW1Pressed (void);
inline BOOL esos_uiF14_isSW1Released (void);
inline BOOL esos_uiF14_isSW1DoublePressed (void);
inline void esos_uiF14_setSW1DoublePressedPeriod (uint16_t);
inline uint16_t esos_uiF14_getSW1DoublePressedPeriod (void);

inline BOOL esos_uiF14_isSW2Pressed (void);
inline BOOL esos_uiF14_isSW2Released (void);
inline BOOL esos_uiF14_isSW2DoublePressed (void);
inline void esos_uiF14_setSW2DoublePressedPeriod (uint16_t);
inline uint16_t esos_uiF14_getSW2DoublePressedPeriod (void);

inline BOOL esos_uiF14_isSW3Pressed (void);
inline BOOL esos_uiF14_isSW3Released (void);
inline BOOL esos_uiF14_isSW3DoublePressed (void);
inline void esos_uiF14_setSW3DoublePressedPeriod (uint16_t);
inline uint16_t esos_uiF14_getSW3DoublePressedPeriod (void);

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
inline void esos_uiF14_setRPG_noVelocity (uint16_t);
inline uint16_t esos_uiF14_getRPGSlowThreshold (void);
inline void esos_uiF14_setRPG_medVelocity (uint16_t);
inline uint16_t esos_uiF14_getRPGMediumThreshold (void);
inline void esos_uiF14_setRPG_fastVelocity (uint16_t);
inline uint16_t esos_uiF14_getRPGFastThreshold (void);
inline BOOL esos_uiF14_isRPGTurning (void);
inline BOOL esos_uiF14_isRPGTurningSlow (void);
inline BOOL esos_uiF14_isRPGTurningMedium (void);
inline BOOL esos_uiF14_isRPGTurningFast (void);
inline BOOL esos_uiF14_isRPGTurningCW (void);
inline BOOL esos_uiF14_isRPGTurningCCW (void);

void config_esos_uiF14();
void init_defaults();
void config_ui_menu();
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

#define SW_IC_BUFFER_RESET(ODD, EVEN)                                            \
    {                                                                            \
        IC##ODD##CON2bits.ICTRIG = IC##EVEN##CON2bits.ICTRIG = 1;                \
        IC##ODD##CON1bits.ICM = IC##EVEN##CON1bits.ICM = 0b000;                  \
        IC##ODD##CON1bits.ICM = IC##EVEN##CON1bits.ICM = 0b001;                  \
    }                                                                            \

#define SW1_DEBOUNCED _RD1
#define SW1_IC_BUFFER (((uint32_t)IC12TMR << 16) | (uint32_t)IC11TMR)
#define CONFIG_SW1_DEBOUNCE_AND_IC()                                             \
    {                                                                            \
        CONFIG_SW1();                                                            \
        CONFIG_RD1_AS_DIG_OUTPUT();                                              \
        _IC11R = RD1_RP;                                                         \
        IC11CON1bits.ICM = IC12CON1bits.ICM = 0b000;                             \
        IC11CON1bits.ICTSEL = IC12CON1bits.ICTSEL = 0b111;                       \
        IC11CON2bits.IC32 = IC12CON2bits.IC32 = 1;                               \
        IC11CON2bits.ICTRIG = IC12CON2bits.ICTRIG = 1;                           \
        IC11CON2bits.SYNCSEL = IC12CON2bits.SYNCSEL = 0b00000;                   \
        IC11CON1bits.ICI = 0b00;                                                 \
        IC11CON1bits.ICM = IC12CON1bits.ICM = 0b001;                             \
        ESOS_REGISTER_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC11, ESOS_USER_IRQ_LEVEL1, _IC11Interrupt);   \
        ESOS_ENABLE_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC11);                   \
    }

#define SW2_DEBOUNCED _RD2
#define SW2_IC_BUFFER (((uint32_t)IC14TMR << 16) | (uint32_t)IC13TMR)
#define CONFIG_SW2_DEBOUNCE_AND_IC()                                             \
    {                                                                            \
        CONFIG_SW2();                                                            \
        CONFIG_RD2_AS_DIG_OUTPUT();                                              \
        _IC13R = RD2_RP;                                                         \
        IC13CON1bits.ICM = IC14CON1bits.ICM = 0b000;                             \
        IC13CON1bits.ICTSEL = IC14CON1bits.ICTSEL = 0b111;                       \
        IC13CON2bits.IC32 = IC14CON2bits.IC32 = 1;                               \
        IC13CON2bits.ICTRIG = IC14CON2bits.ICTRIG = 1;                           \
        IC13CON2bits.SYNCSEL = IC14CON2bits.SYNCSEL = 0b00000;                   \
        IC13CON1bits.ICI = 0b00;                                                 \
        IC13CON1bits.ICM = IC14CON1bits.ICM = 0b001;                             \
        ESOS_REGISTER_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC13, ESOS_USER_IRQ_LEVEL1, _IC13Interrupt);   \
        ESOS_ENABLE_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC13);                   \
    }
#define SW3_DEBOUNCED _RD3
#define SW3_IC_BUFFER (((uint32_t)IC16TMR << 16) | (uint32_t)IC15TMR)
#define CONFIG_SW3_DEBOUNCE_AND_IC()                                             \
    {                                                                            \
        CONFIG_SW3();                                                            \
        CONFIG_RD3_AS_DIG_OUTPUT();                                              \
        _IC15R = RD3_RP;                                                         \
        IC15CON1bits.ICM = IC16CON1bits.ICM = 0b000;                             \
        IC15CON1bits.ICTSEL = IC16CON1bits.ICTSEL = 0b111;                       \
        IC15CON2bits.IC32 = IC16CON2bits.IC32 = 1;                               \
        IC15CON2bits.ICTRIG = IC16CON2bits.ICTRIG = 1;                           \
        IC15CON2bits.SYNCSEL = IC16CON2bits.SYNCSEL = 0b00000;                   \
        IC15CON1bits.ICI = 0b00;                                                 \
        IC15CON1bits.ICM = IC16CON1bits.ICM = 0b001;                             \
        ESOS_REGISTER_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC15, ESOS_USER_IRQ_LEVEL1, _IC15Interrupt);   \
        ESOS_ENABLE_PIC24_USER_INTERRUPT(ESOS_IRQ_PIC24_IC15);                   \
    }

#endif    // ESOS_UIF14_H
