#ifndef INPUT_CAL_H
#define INPUT_CAL_H

#include "led_driver.h"

extern int CAL_LedDeviceInit(LedDevice *pLedDevice);
extern int CAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus);


#endif