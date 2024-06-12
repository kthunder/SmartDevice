#include "general_cal.h"

int CAL_GetTime()
{
    return HAL_GetTick();
}

void CAL_Delay(int count)
{
    HAL_Delay(count);
}