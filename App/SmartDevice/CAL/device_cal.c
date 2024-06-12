#include "device_cal.h"

int CAL_LedDeviceInit(LedDevice *pLedDevice)
{
#if defined(CONFIG_SUPPORT_HAL)
    return Led_Init(pLedDevice);
#endif
}

int CAL_LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
#if defined(CONFIG_SUPPORT_HAL)
    return LedControl(pLedDevice, iStatus);

#endif
}

int CAL_DisplayDeviceInit(DisplayDevice *pDisplayDevice)
{
#if defined(CONFIG_SUPPORT_HAL)
    IIC_Init();
    Oled_Init();

    return 0;
#endif
}

int CAL_DisplayDeviceFlash(DisplayDevice *pDisplayDevice)
{
#if defined(CONFIG_SUPPORT_HAL)

#endif
}