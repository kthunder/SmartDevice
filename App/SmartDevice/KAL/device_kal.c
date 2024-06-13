#include "device_kal.h"

int KAL_LedDeviceInit(LedDevice *pLedDevice)
{
    /* 针对裸机，注册中断*/
#if defined(CONFIG_NO_OS)
    return CAL_LedDeviceInit(pLedDevice);

    /* 针对RTOS，创建任务*/

#elif defined(CONFIG_FREERTOS)

#endif
}

int KAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
#if defined(CONFIG_NO_OS)
    return CAL_LedDeviceControl(pLedDevice, iStatus);

#elif defined(CONFIG_FREERTOS)

#endif
}

int KAL_DisplayDeviceInit(DisplayDevice *pDisplayDevice)
{
#if defined(CONFIG_NO_OS)
    return CAL_DisplayDeviceInit(pDisplayDevice);

#elif defined(CONFIG_FREERTOS)

#endif
}


void KAL_DisplayDeviceFlash(DisplayDevice *pDisplayDevice)
{
#if defined(CONFIG_NO_OS)
    CAL_DisplayDeviceFlash(pDisplayDevice);

#elif defined(CONFIG_FREERTOS)

#endif
}