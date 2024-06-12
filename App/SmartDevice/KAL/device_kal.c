#include "device_kal.h"

int KAL_LedDeviceInit(LedDevice *pLedDevice)
{
    /* 针对裸机，注册中断*/
    return CAL_LedDeviceInit(pLedDevice);

    /* 针对RTOS，创建任务*/
}

int KAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
    return CAL_LedDeviceControl(pLedDevice, iStatus);
}