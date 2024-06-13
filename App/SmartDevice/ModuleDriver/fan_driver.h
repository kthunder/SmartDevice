#ifndef FAN_DRIVER_H
#define FAN_DRIVER_H

#include "stm32f1xx_hal.h"
#include "system_type.h"
#include "stdio.h"

extern int Fan_Init(FanDevice *pFanDevice);
extern int Fan_SetSpeed(FanDevice *pFanDevice, FAN_DIRECTION direct);

#endif