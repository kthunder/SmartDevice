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

#endif
    return 0;
}

void CAL_DisplayDeviceFlash(DisplayDevice *pDisplayDevice)
{
#if defined(CONFIG_SUPPORT_HAL)
    Oled_CopyBuffer(pDisplayDevice->FrameBufferBase);
#endif
}

int CAL_FanDeviceInit(FanDevice *pFanDevice)
{
#if defined(CONFIG_SUPPORT_HAL)
    Fan_Init(pFanDevice);
#endif

    return 0;
}

void CAL_FanDeviceControl(FanDevice *pFanDevice, FAN_DIRECTION direct)
{
#if defined(CONFIG_SUPPORT_HAL)
    Fan_SetSpeed(pFanDevice, direct);
#endif
}