#include "device_system.h"

/* LED*/
static int LedDeviceInit(LedDevice *pLedDevice)
{
    return KAL_LedDeviceInit(pLedDevice);
}

static int LedDeviceControl(LedDevice *pLedDevice, int iStatus)
{
    return KAL_LedDeviceControl(pLedDevice, iStatus);
}

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

/* OLED*/
/* 在内存中分配一块区域专门写数据，然后通过I2C将数据刷到LCD*/
static int DisplayDeviceInit(DisplayDevice *pDisplayDevice)
{
    return KAL_DisplayDeviceInit(pDisplayDevice);
}

static void DisplayDeviceFlash(DisplayDevice *pDisplayDevice)
{
    KAL_DisplayDeviceFlash(pDisplayDevice);
}

static int DisplayDeviceSetPixel(DisplayDevice *pOledDevice, int iX, int iY, int iColor)
{
    unsigned char *buf = pOledDevice->FrameBufferBase;
    int page = 0, bit = 0;
    unsigned char *byte;

    if(iX>pOledDevice->iXresolution || iY>pOledDevice->iYresolution)
    {
        return NOT_FOUND;
    }

    page = iY / 8;
    byte = buf + page*128 + iX;
    bit = iY % 8;

    if(iColor)
        *byte |= (1 << bit);
    else
        *byte &= ~(1 << bit);

    
    return 0;
}

/* 根据oled屏幕大小， 168*64/8 定义一个数组 */
static unsigned char g_FrameBuffer[1024];

static DisplayDevice g_OledDevice = 
{
    .name = "OLED",
    .FrameBufferBase = &g_FrameBuffer,
    .iXresolution = 128,
    .iYresolution = 64,
    .iBitPerPic = 1,
    .Init = DisplayDeviceInit,
    .Flash = DisplayDeviceFlash,
    .SetPixel = DisplayDeviceSetPixel
};


/*定义一个链表，若有多个显示器，可进行管理*/
DisplayDevice* g_DisplayDeviceList = NULL;

static void DisplayDeviceRegister(DisplayDevice* displayDevice)
{
    if (g_DisplayDeviceList == NULL)
    {
        g_DisplayDeviceList = displayDevice;
    }else
    {
        DisplayDevice* tmp = g_DisplayDeviceList;
        while (tmp->next!=NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = displayDevice;
    }
}

static void AddOledToDisplayDevice()
{
    DisplayDeviceRegister(&g_OledDevice);
}

void AddDisplayDevice()
{
    AddOledToDisplayDevice();
}

void InitDisplayDevices()
{
    DisplayDevice* tmp = g_DisplayDeviceList;

    while (tmp !=NULL)
    {
        tmp->Init(&g_OledDevice);
        tmp = tmp ->next;
    }
}

DisplayDevice* GetDisplayDevice(char *which)
{
    DisplayDevice* pTmp = g_DisplayDeviceList;
    while (pTmp != NULL)
    {
        if(strcmp(pTmp->name, which) == 0)
            return pTmp;
        else
            pTmp = pTmp->next;
    }
    
    return NULL;
}


/* LED*/