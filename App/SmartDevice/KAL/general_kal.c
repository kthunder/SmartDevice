#include "general_kal.h"

int KAL_GetTime()
{
#if defined(CONFIG_NO_OS)
    return CAL_GetTime();

#elif defined(CONFIG_FREERTOS)

#endif
}

void KAL_Delay(int count)
{
#if defined(CONFIG_NO_OS)
    return CAL_Delay(count);

#elif defined(CONFIG_FREERTOS)

#endif
}