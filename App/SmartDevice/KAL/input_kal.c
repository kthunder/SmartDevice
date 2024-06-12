#include "input_kal.h"

void KAL_GpioKeyInit()
{
    /* 针对裸机，注册中断*/
    CAL_GpioKeyInit();

    /* 针对RTOS，创建任务*/
}

void KAL_StdIoInit()
{
    /* 针对裸机，注册中断*/
    CAL_StdIoInit();

    /* 针对RTOS，创建任务*/
}