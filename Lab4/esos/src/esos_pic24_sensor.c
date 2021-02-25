#include "esos_pic24_sensor.h"


//Configure and enable the sensor module for hwxxx hardware.
// e_senCh   specifies sensor channel
// e_senVRef specifies sensor voltage reference
void esos_sensor_config_hw (esos_sensor_ch_t e_senCh, esos_sensor_vref_t e_senVRef) {
    CONFIG_ADC();
    AD1CON1bits.ADON = 0; //Turn ADC off
    AD1CHS0bits.CH0SA = e_senCh; //Set CH0+ input AN[e_senCh]
    AD1CHS0bits.CH0NA = 0; //Set CHO- input to VREFL (AVss)
    AD1CHS123 = 0; //Disable CH's 1,2,&3
    AD1CSSH = 0x0000; //No inputs are scanned
    AD1CSSL = 0x0000; //Set input scan select register low
//    IFS1CLR = 2; //Clear ADC conversion interrupt
    AD1CON1bits.ADON = 1; //Turn ADC on
}

//Determine if the sensor is currently converting
BOOL esos_sensor_is_converting_hw (void) {
    
}

//Initiate a conversion for a configured sensor
void esos_sensor_initiate_conversion_hw (void) {
    
    esos_SetUserFlag(__ESOS_SYS_ADC_IS_BUSY);
    AD1CON1bits.SAMP = 1; //Take sample from ADC
}

//Receive the value from a conversion that has already been initiated
uint16_t esos_sensor_getvalue_u16_hw (void) {
    
}

//Release any pending conversions for the sensor
void esos_sensor_release_hw (void) {
    
}
