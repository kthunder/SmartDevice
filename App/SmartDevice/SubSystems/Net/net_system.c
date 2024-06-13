#include "net_system.h"

InputDevice* g_InputDeviceList = NULL;

static void GpioKeyInit(void)
{
    KAL_GpioKeyInit();
}

static void StdIoInit(void)
{
    KAL_StdIoInit();
}

static InputDevice g_KeyDevice=
{
    .name = "key",
    .GetInputEvent = NULL,
    .DeviceInit = GpioKeyInit,
    .DeviceDeInit = NULL
};

static void InputDeviceRegister(InputDevice* inputDevice)
{
    if (g_InputDeviceList == NULL)
    {
        g_InputDeviceList = inputDevice;
    }else
    {
        InputDevice* tmp = g_InputDeviceList;
        while (tmp->next!=NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = inputDevice;
    }
}

void AddKeyToInputDevice()
{
    InputDeviceRegister(&g_KeyDevice);
}

void InitInputDevices()
{
    InputDevice* tmp = g_InputDeviceList;

    while (tmp !=NULL)
    {
        tmp->DeviceInit();
        tmp = tmp ->next;
    }

    printf("init devices.\r\n");
}

