#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "stm32f1xx.h"
#include "usart.h"

#include "stdio.h"
#include "string.h"
#include "stddef.h"
#include "system_Type.h"

#include "ring_Buffer.h"
#include "general_kal.h"

#define RING_BUFFER_SIZE 100

typedef struct RingBuffer
{
    char ringBuffer[RING_BUFFER_SIZE];
    uint32_t pw;
    uint32_t pr;
}RingBuffer;

extern void EnablePrintfIRQ();
extern void DisablePrintfIRQ();

extern int getDataFromBuffer(RingBuffer *g_RingBuffer, char *c);
extern int putDataIntoBuffer(RingBuffer *g_RingBuffer, char c);

extern RingBuffer dataBuffer;

#endif