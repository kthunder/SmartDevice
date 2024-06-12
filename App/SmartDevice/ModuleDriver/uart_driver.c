#include "uart_Driver.h"

static char temp[INPUT_BUF_LEN] = {0};
static int count = 0;

void EnablePrintfIRQ()
{
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void DisablePrintfIRQ()
{
    __HAL_UART_DISABLE_IT(&huart1, UART_IT_TC | UART_IT_RXNE);

    HAL_NVIC_DisableIRQ(USART1_IRQn);
}

uint16_t _write(int fd, const void *ptr, uint16_t len)
{
    (void)fd;
    (void)ptr;

    HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY); // 阻塞式无限等待

    return (uint16_t)len;
}


void HAL_UART_Callback(UART_HandleTypeDef *huart)
{
    InputEvent inputEvent;

    if (huart->Instance == USART1)
    {
        inputEvent.time = KAL_GetTime();
        inputEvent.eType = INPUT_EVENT_TYPE_STDIO;
        memcpy(inputEvent.str, temp, count);
        PutEventIntoBuffer(inputEvent);

        count = 0;
    }
}

void USART1_IRQHandler(void)
{
    char c = 0;

    if ((USART1->SR & (1 << 5)) != 0)
    {
        c = USART1->DR;

        if (c != '\n')
        {
            temp[count++] = c;
        }
        else
        {
            temp[count-1] = '\0';
            HAL_UART_Callback(&huart1);
        }
    }

    HAL_UART_IRQHandler(&huart1);
}

int getDataFromBuffer(RingBuffer *g_RingBuffer, char *c)
{
    if (g_RingBuffer->pr == g_RingBuffer->pw)
    {
        return -1;
    }

    *c = g_RingBuffer->ringBuffer[g_RingBuffer->pr];
    g_RingBuffer->pr = (g_RingBuffer->pr + 1) % RING_BUFFER_SIZE;

    return 0;
}

int putDataIntoBuffer(RingBuffer *g_RingBuffer, char c)
{
    if ((g_RingBuffer->pw + 1) % RING_BUFFER_SIZE == g_RingBuffer->pr)
    {
        return -1;
    }

    g_RingBuffer->ringBuffer[g_RingBuffer->pw] = c;
    g_RingBuffer->pw = (g_RingBuffer->pw + 1) % RING_BUFFER_SIZE;

    return 0;
}