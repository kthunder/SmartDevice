#include "input_kal.h"

void KAL_GpioKeyInit()
{
    /* 针对裸机，注册中断*/
#if defined(CONFIG_NO_OS)
    CAL_GpioKeyInit();

    /* 针对RTOS，创建任务*/
#elif defined(CONFIG_FREERTOS)

#endif
}

void KAL_StdIoInit()
{
    /* 针对裸机，注册中断*/
#if defined(CONFIG_NO_OS)
    CAL_StdIoInit();

    /* 针对RTOS，创建任务*/
#elif defined(CONFIG_FREERTOS)

#endif
}