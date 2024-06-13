#include "uart_Driver.h"

static char temp[INPUT_BUF_LEN] = {0};
static int count = 0;

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

// void USART1_IRQHandler(void)
// {
//     char c = 0;
//     if ((USART1->SR & (1 << 5)) != 0)
//     {
//         c = USART1->DR;
//         if (c != '\n')
//         {
//             temp[count++] = c;
//         }
//         else
//         {
//             temp[count-1] = '\0';
//             HAL_UART_Callback(&huart1);
//         }
//     }
//     HAL_UART_IRQHandler(&huart1);
// }

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

RingBuffer rx_buffer1 = { { 0 }, 0, 0};
RingBuffer tx_buffer1 = { { 0 }, 0, 0};
RingBuffer rx_buffer2 = { { 0 }, 0, 0};
RingBuffer tx_buffer2 = { { 0 }, 0, 0};

RingBuffer *_rx_buffer1;
RingBuffer *_tx_buffer1;
RingBuffer *_rx_buffer2;
RingBuffer *_tx_buffer2;

void ring_buffer_init(void)
{
  _rx_buffer1 = &rx_buffer1;
  _tx_buffer1 = &tx_buffer1;
  _rx_buffer2 = &rx_buffer2;
  _tx_buffer2 = &tx_buffer2;

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(USART3_IRQn);

  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
  __HAL_UART_ENABLE_IT(&huart3, UART_IT_ERR);

  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
}

void store_char(unsigned char c, RingBuffer *buffer)
{
  int i = (unsigned int)(buffer->pr + 1) % RING_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the pr (meaning that the pw would advance to the
  // current location of the pr), we're about to overflow the buffer
  // and so we don't write the character or advance the pw.
  if(i != buffer->pr) 
  {
    buffer->ringBuffer[buffer->pw] = c;
    buffer->pw = i;
  }
}

int uart_read(UART_HandleTypeDef *uart)
{
	if (uart == &huart1)
	{
		  // if the pw isn't ahead of the pr, we don't have any characters
		  if(_rx_buffer1->pw == _rx_buffer1->pr)
		  {
		    return -1;
		  }
		  else
		  {
		    unsigned char c = _rx_buffer1->ringBuffer[_rx_buffer1->pr];
		    _rx_buffer1->pr = (unsigned int)(_rx_buffer1->pr + 1) % RING_BUFFER_SIZE;
		    return c;
		  }
	}

	else if (uart == &huart3)
	{
		  // if the pw isn't ahead of the pr, we don't have any characters
		  if(_rx_buffer2->pw == _rx_buffer2->pr)
		  {
		    return -1;
		  }
		  else
		  {
		    unsigned char c = _rx_buffer2->ringBuffer[_rx_buffer2->pr];
		    _rx_buffer2->pr = (unsigned int)(_rx_buffer2->pr + 1) % RING_BUFFER_SIZE;
		    return c;
		  }
	}

	else return -1;
}

void uart_write(int c, UART_HandleTypeDef *uart)
{
	if (c>=0)
	{
		if (uart == &huart1){
		int i = (_tx_buffer1->pw + 1) % RING_BUFFER_SIZE;

		// If the output ringBuffer is full, there's nothing for it other than to
		// wait for the interrupt handler to empty it a bit
		// ???: return 0 here instead?
		while (i == _tx_buffer1->pr);

		_tx_buffer1->ringBuffer[_tx_buffer1->pw] = (uint8_t)c;
		_tx_buffer1->pw = i;

		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE); // Enable UART transmission interrupt
		}

		else if (uart == &huart3){
			int i = (_tx_buffer2->pw + 1) % RING_BUFFER_SIZE;

			// If the output ringBuffer is full, there's nothing for it other than to
			// wait for the interrupt handler to empty it a bit
			// ???: return 0 here instead?
			while (i == _tx_buffer2->pr);

			_tx_buffer2->ringBuffer[_tx_buffer2->pw] = (uint8_t)c;
			_tx_buffer2->pw = i;

			__HAL_UART_ENABLE_IT(&huart3, UART_IT_TXE); // Enable UART transmission interrupt
			}
	}
}

int is_data_available(UART_HandleTypeDef *uart)
{
	if (uart == &huart1) 
		return (uint16_t)(RING_BUFFER_SIZE + _rx_buffer1->pw - _rx_buffer1->pr) % RING_BUFFER_SIZE;
	else if (uart == &huart3) 
		return (uint16_t)(RING_BUFFER_SIZE + _rx_buffer2->pw - _rx_buffer2->pr) % RING_BUFFER_SIZE;
	return -1;
}

void Uart_isr(UART_HandleTypeDef *huart)
{
	  uint32_t isrflags   = READ_REG(huart->Instance->SR);
	  uint32_t cr1its     = READ_REG(huart->Instance->CR1);
	  uint32_t cr3its     = READ_REG(huart->Instance->CR3);

    /* if DR is not empty and the Rx Int is enabled */
    if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
	  //if (((isrflags & USART_SR_RXNE) != RESET) && (((cr3its & USART_CR3_EIE) != RESET) || (cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET))
    {
		READ_REG(huart->Instance->SR);
		
        unsigned char c = huart->Instance->DR;     /* Read data register */
        if (huart == &huart1)
        {
        	store_char (c, _rx_buffer1);  // store data in ringBuffer
        }
        else if (huart == &huart3)
        {
           	store_char (c, _rx_buffer2);  // store data in ringBuffer
        }

        //return;
    }
    /* If interrupt is caused due to Transmit Data Register Empty */
    else if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
    	if (huart == &huart1)
    	{
			if(tx_buffer1.pw == tx_buffer1.pr)
			{
				__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
			}

			else
			{
				// There is more data in the output ringBuffer. Send the next byte
				unsigned char c = tx_buffer1.ringBuffer[tx_buffer1.pr];
				tx_buffer1.pr = (tx_buffer1.pr + 1) % RING_BUFFER_SIZE;

				huart->Instance->SR;
				huart->Instance->DR = c;
			}
		}
		else if (huart == &huart3)
		{
			if(tx_buffer2.pw == tx_buffer2.pr)
			{
				__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

			}

			else
			{
				// There is more data in the output ringBuffer. Send the next byte
				unsigned char c = tx_buffer2.ringBuffer[tx_buffer2.pr];
				tx_buffer2.pr = (tx_buffer2.pr + 1) % RING_BUFFER_SIZE;

				huart->Instance->SR;
				huart->Instance->DR = c;
			}
		}
	//return;
    }
}
