#include "device_cal.h"

int CAL_LedDeviceInit(LedDevice *pLedDevice)
{
    /* 针对裸机，注册中断*/
    return Led_Init(pLedDevice);

    /* 针对RTOS，创建任务*/
}

int CAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
    /* 针对裸机，注册中断*/
    return LedControl(pLedDevice, iStatus);

    /* 针对RTOS，创建任务*/
}
