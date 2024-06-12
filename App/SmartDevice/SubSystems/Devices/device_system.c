#include "device_system.h"

static int LedDeviceInit(LedDevice *pLedDevice)
{
    return KAL_LedDeviceInit(pLedDevice);
}

static int LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
    return KAL_LedDeviceControl(pLedDevice, iStatus);
}


/* 在内存中分配一块区域专门写数据，然后通过I2C将数据刷到LCD*/
// static int DisplayDeviceInit(DisplayDevice *pDisplayDevice)
// {
//     return KAL_DisplayDeviceInit(pDisplayDevices);
// }

// static int DisplayDeviceFlash(DisplayDevice *pDisplayDevice)
// {
//     return KAL_DisplayDeviceInit(pDisplayDevices);
// }

static LedDevice g_ledDevices[]={
    {
       LED_WHITE, LedDeviceInit,LedDeviceControl,NULL
    },
    {
       LED_BLUE, LedDeviceInit,LedDeviceControl,NULL
    },
    {
       LED_GREEN, LedDeviceInit,LedDeviceControl,NULL
    },
};

LedDevice* GetLedDevice(int which)
{
    if((which<LED_WHITE)&&(which>LED_GREEN))
        return (LedDevice*)NOT_FOUND;
    
    return &g_ledDevices[which];
}

// DisplayDevice* GetDisplayDevice(int which)
// {

// }