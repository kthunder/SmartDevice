#ifndef DEVICE_KAL_H
#define DEVICE_KAL_H

#include "device_cal.h"

extern int KAL_LedDeviceInit(LedDevice *pLedDevice);
extern int KAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus);

extern int KAL_DisplayDeviceInit(DisplayDevice *pDisplayDevice);
extern void KAL_DisplayDeviceFlash(DisplayDevice *pDisplayDevice);

extern int KAL_FanDeviceInit(FanDevice *pFanDevice);
extern void KAL_FanDeviceControl(FanDevice *pFanDevice, FAN_DIRECTION direct);

#endif