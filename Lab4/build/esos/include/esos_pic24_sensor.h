#ifndef ESOS_PIC24_SENSOR_H
#define ESOS_PIC24_SENSOR_H

#include <esos_sensor.h>
#include "revF14.h"

void esos_sensor_config_hw (esos_sensor_ch_t, esos_sensor_vref_t);
void esos_sensor_initiate_conversion_hw (void);
uint16_t esos_sensor_getvalue_u16_hw (void);
void esos_sensor_release_hw (void);
BOOL esos_sensor_is_converting_hw (void);

#endif
