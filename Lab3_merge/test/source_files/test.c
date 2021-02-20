#include "esos.h"
#include "esos_pic24.h"
#include "revF14.h"
#include "pic24_ports.h"
#include "esos_irq.h"
#include "esos_pic24_rs232.h"
#include "pic24_timer.h"
#include "esos_comm.h"

#ifndef __dsPIC33EP512GP806__
#define __dsPIC33EP512GP806__
#endif

inline void IO_config() {
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
}

inline void timer_config() {
    T2CON = T2_OFF | T2_IDLE_CON | T2_GATE_OFF | T2_32BIT_MODE_ON | T2_SOURCE_INT | T2_PS_1_1;
    PR2 = 0xFFFF;
    PR3 = 0xFFFF;
    TMR3HLD = 0;
    TMR2 = 0;
    ESOS_MARK_PIC24_USER_INTERRUPT_SERVICED(ESOS_IRQ_PIC24_T3);
    T2CONbits.TON = 1;
}

ESOS_USER_TASK(task1) {
ESOS_TASK_BEGIN();
    while(1) {
//        if(SW1) LED1_ON();
//        else LED1_OFF();
        if(SW2) LED2_ON();
        else LED2_OFF();
        if(SW3) LED3_ON();
        else LED3_OFF();
        ESOS_TASK_YIELD();
    }
ESOS_TASK_END();
}

//volatile BOOL SW1_Pressed, SW2_Pressed, SW3_Pressed, tempFlag;
//volatile UINT32 prevCapture, currCapture, delta;

ESOS_USER_TASK(DOUBLE_PRESS) {
    static BOOL SW1_Pressed = 0;
    //, SW2_Pressed, SW3_Pressed
    static UINT32 prevCapture, currCapture;
    static uint32_t delta;
    static char psz_out[] = "\n";
ESOS_TASK_BEGIN();
    while(1) {
        delta = 0xFFFFFFFF;
        if(SW1) {
            if (!SW1_Pressed) { //if new press
                currCapture.u16LoWord = TMR2;
                currCapture.u16HiWord = TMR3HLD;
                delta = currCapture.u32 - prevCapture.u32;
                if(delta < 0x00FFFFFF) {
                    LED1_ON(); //check for double press
                    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                    ESOS_TASK_WAIT_ON_SEND_UINT32_AS_HEX_STRING(delta);
                    ESOS_TASK_WAIT_ON_SEND_STRING(psz_out);
                    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                    delta = 0xFFFFFFFF;
                }
                prevCapture = currCapture;
//                ESOS_TASK_WAIT_TICKS(50);
            }
            SW1_Pressed = 1;
        }
        else SW1_Pressed = 0;
        if(SW2) LED1_OFF();
        ESOS_TASK_YIELD();
    }
ESOS_TASK_END();
}

//ESOS_USER_TASK(echo) {
////    static uint8_t u8_char;
//ESOS_TASK_BEGIN();
//    while(1) {
//        if(tempFlag) {
//            tempFlag = 0;
////            u8_char++;
////            ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
////            ESOS_TASK_WAIT_ON_GET_UINT8(u8_char);
////            ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
//            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
////            ESOS_TASK_WAIT_ON_SEND_UINT8(u8_char);
//            ESOS_TASK_WAIT_ON_SEND_UINT32(delta);
//            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
//        ESOS_TASK_YIELD();
//    }
//ESOS_TASK_END();
//}

void user_init(void) {
    IO_config();
    timer_config();
    
    esos_RegisterTask(task1);
//    esos_RegisterTask(echo);
    esos_RegisterTask(DOUBLE_PRESS);
//    esos_RegisterTimer(SW_CHECK,10);
}
