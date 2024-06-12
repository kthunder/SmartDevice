#include "input_cal.h"

void CAL_GpioKeyInit()
{
    /* 调用芯片相关的代码，注册GPIO中断 */
    Key_Init();
}


void CAL_StdIoInit()
{
    EnablePrintfIRQ();
}

