#ifndef INPUT_CAL_H
#define INPUT_CAL_H

#include "led_driver.h"

#if defined(CONFIG_NO_OS)
extern int CAL_LedDeviceInit(LedDevice *pLedDevice);
extern int CAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus);

extern int CAL_DisplayDeviceInit(DisplayDevice *pDisplayDevice);
extern int CAL_DisplayDeviceFlash(DisplayDevice *pDisplayDevice);

#elif defined(CONFIG_FREERTOS)

#endif

#endif