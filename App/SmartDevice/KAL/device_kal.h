#ifndef DEVICE_KAL_H
#define DEVICE_KAL_H

#include "device_cal.h"

extern int KAL_LedDeviceInit(LedDevice *pLedDevice);
extern int KAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus);

#endif