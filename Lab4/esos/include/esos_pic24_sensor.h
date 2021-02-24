#ifndef ESOS_PIC24_SENSOR_H
#define ESOS_PIC24_SENSOR_H

#include <esos_sensor.h>
#include "revF14.h"

void esos_sensor_config (esos_sensor_ch_t, esos_sensor_vref_t);
void esos_sensor_initiate_conversion (void);
uint16_t esos_sensor_getvalue_u16 (void);
void esos_sensor_release (void);
BOOL esos_sensor_is_converting (void);

#endif
