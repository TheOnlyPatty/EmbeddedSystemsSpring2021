#ifndef ESOS_PIC24_SENSOR_H
#define ESOS_PIC24_SENSOR_H

#include <esos_sensor.h>
#include "revF14.h"

#define ESOS_SENSOR_IS_CONVERTING ESOS_USER_FLAG_0

void esos_sensor_config_hw (esos_sensor_ch_t, esos_sensor_vref_t);
void esos_sensor_initiate_hw (void);
uint16_t esos_sensor_getvalue_u16_hw (void);
void esos_sensor_release_hw (void);
BOOL esos_sensor_is_converting_hw (void);

int uint32_to_str(uint32_t u32_val, char *str, uint32_t len, uint16_t base);


#endif
