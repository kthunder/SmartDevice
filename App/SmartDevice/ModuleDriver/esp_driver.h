#ifndef ESP_DRIVER_H
#define ESP_DRIVER_H

#include "stm32f1xx_hal.h"
#include "system_type.h"
#include "stdio.h"
#include "string.h"

extern int ATInterfaceInit();
extern int ATCommandSend(char *cmd, int iTimeoutMs);
extern int ATDataReceive(NetDevice * pNetDevice, unsigned char *data, int *pLen, int iTimeoutMs);

#endif