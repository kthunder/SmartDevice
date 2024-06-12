#include "ring_Buffer.h"

InputEventBuffer g_inputEventBuffer;

int PutEventIntoBuffer(InputEvent inputEvent)
{
    int index = (g_inputEventBuffer.pWrite + 1)%BUFFER_SIZE;
    if( index == g_inputEventBuffer.pRead)
    {
        return BUFFER_FULL;
    }

    g_inputEventBuffer.buffer[g_inputEventBuffer.pWrite] = inputEvent;
    g_inputEventBuffer.pWrite = index;

    return 0;
}


int GetEventFromBuffer(InputEvent *pInputEvent)
{
    if(pInputEvent == NULL)
    {
        return NULL_POINT;
    }

    if(g_inputEventBuffer.pRead == g_inputEventBuffer.pWrite)
    {
        return BUFFER_EMPTY;
    }

    *pInputEvent = g_inputEventBuffer.buffer[g_inputEventBuffer.pRead];
    g_inputEventBuffer.pRead = (g_inputEventBuffer.pRead + 1)%BUFFER_SIZE;

    return 0;
}