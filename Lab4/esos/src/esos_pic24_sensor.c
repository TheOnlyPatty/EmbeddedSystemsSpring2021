#include "esos_pic24_sensor.h"


//Configure and enable the sensor module for hwxxx hardware.
// e_senCh   specifies sensor channel
// e_senVRef specifies sensor voltage reference
void esos_sensor_config (esos_sensor_ch_t e_senCh, esos_sensor_vref_t e_senVRef)
{

}

//Determine if the sensor is currently converting
BOOL esos_sensor_is_converting (void)
{

}

//Initiate a conversion for a configured sensor
void esos_sensor_initiate_conversion (void)
{

}

//Receive the value from a conversion that has already been initiated
uint16_t esos_sensor_getvalue_u16 (void)
{

}

//Release any pending conversions for the sensor
void esos_sensor_release (void)
{

}
