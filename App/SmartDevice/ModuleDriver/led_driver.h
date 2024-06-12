#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "stm32f1xx_hal.h"
#include "system_type.h"
#include "stdio.h"

#define READ_K1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)

extern int Led_Init(LedDevice *pLedDevice);
extern int LedControl(LedDevice *pLedDevice, int iStatus);

#endif