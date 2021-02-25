#include "esos_pic24_sensor.h"


//Configure and enable the sensor module for hwxxx hardware.
// e_senCh   specifies sensor channel
// e_senVRef specifies sensor voltage reference
void esos_sensor_config_hw (esos_sensor_ch_t e_senCh, esos_sensor_vref_t e_senVRef) {
//    CONFIG_ADC();
    AD1CON1bits.ADON    = 0b0;    //Turn ADC off
    AD1CON1bits.ADSIDL  = 0b0;    //Continue module operation in Idle mode
    AD1CON1bits.FORM    = 0b0;    //Integer 16-bit (DOUT = 0000 0000 0000 0000 0000 00dd dddd dddd)
    AD1CON1bits.SSRC    = 0b111;  //Internal counter ends sampling and starts conversion (auto convert)
    AD1CON1bits.ASAM    = 0b0;    //Sampling begins when SAMP bit is set (change this to auto-sample)
    AD1CON1bits.SAMP    = 0b0;    //The ADC sample/hold amplifier is holding
    AD1CON1bits.DONE    = 0b0;    //Analog-to-digital conversion is not done or has not started
    AD1CON1bits.ADDMABM = 0b1;    //DMA Buffers written in order of conversion
    AD1CON1bits.AD12B   = 0b1;    //Enable 12 bit mode
    AD1CON1bits.SSRCG   = 0b0;    //Sample clock source group
    
    AD1CON2bits.VCFG    = 0b001;  //Set ADC VR+ to VREF+ pin and VR- to AVSS pin
    AD1CON2bits.CSCNA   = 0b0;    //Do not scan inputs
    AD1CON2bits.SMPI    = 0b0000; //Interrupts at the completion of conversion for each sample/convert sequence
    AD1CON2bits.BUFM    = 0b0;    //Buffer configured as one 16-word buffer ADC1BUF(15...0.)
    AD1CON2bits.ALTS    = 0b0;    //Always use MUX A input multiplexer settings
    AD1CON2bits.CHPS    = 0b00;   //Channel select bits
    
    AD1CON3bits.ADRC    = 0b1;    //ADC internal RC clock
    AD1CON3bits.SAMC    = 0b11111;//Auto-sample Time bits: 31 TAD
    AD1CON4bits.ADDMAEN = 0b0;

    AD1CHS0bits.CH0SA = e_senCh;  //Set CH0+ input AN[e_senCh]
    AD1CHS0bits.CH0NA = 0;        //Set CHO- input to VREFL (AVss)
    AD1CHS123 = 0;                //Disable CH's 1,2,&3
    AD1CSSH = 0x0000;             //No inputs are scanned
    AD1CSSL = 0x0000;             //Set input scan select register low
//    IFS1CLR = 2; //Clear ADC conversion interrupt
    AD1CON1bits.ADON = 1;         //Turn ADC on
}

//Determine if the sensor is currently converting
BOOL esos_sensor_is_converting_hw (void) {
    if (AD1CON1bits.DONE == 1) {
        esos_ClearUserFlag(ESOS_SENSOR_IS_CONVERTING);
        return FALSE;
    }
    return esos_IsUserFlagSet(ESOS_SENSOR_IS_CONVERTING);
}

//Initiate a conversion for a configured sensor
void esos_sensor_initiate_hw (void) {
    esos_SetUserFlag(__ESOS_SYS_ADC_IS_BUSY);
    AD1CON1bits.SAMP = 1;
}

//Receive the value from a conversion that has already been initiated
uint16_t esos_sensor_getvalue_u16_hw (void) {
    if (!esos_IsUserFlagClear(ESOS_SENSOR_IS_CONVERTING)) return 0;
    return ADC1BUF0;
}

//Release any pending conversions for the sensor
void esos_sensor_release_hw (void) {
    esos_ClearUserFlag(ESOS_SENSOR_IS_CONVERTING);
    AD1CON1bits.ADON = 0; // turn off the adc
}
