/**
 ******************************************************************************
 * @file      syscalls.c
 * @author    Suroy Wrote with Auto-generated by STM32CubeIDE 
 * @url       https://suroy.cn
 * @brief     STM32CubeIDE Minimal System calls file
 *
 *            For more information about which c-functions
 *            need which of these lowlevel functions
 *            please consult the Newlib libc-manual
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2020-2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "usart.h"


/* Variables */
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

static volatile u_int8_t tx_flag = 0;
static volatile u_int8_t rx_flag = 0;

/* Functions */

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;
  char c=0;
  printf("--%s--len : %d----\r\n", __func__, len);
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    c = __io_getchar();
    *ptr++ = c;
    if (c=='\n')
    {
      break;
    }
    
  }

  return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}



// 条件编译
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */


/**
  * 函数功能: 重定向 c库函数 printf到 DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY); //阻塞式无限等待
    // tx_flag = 0;
    // HAL_UART_Transmit_IT(&huart1, (uint8_t*)&ch, 1);

    // while (tx_flag==0);

    return ch;
}


/**
  * 函数功能: 重定向 c库函数 getchar,scanf到 DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
  printf("--%s--ch : %d----\r\n", __func__, ch);
    // uint8_t ch = 0;
    // rx_flag = 0;
    // HAL_UART_Receive_IT(&huart1, &ch, 1);
    // while (rx_flag==0);

    return ch;
}



/* 非GCC模式才允许编译使用即 Keil、IAR 等 */
#ifndef __GNUC__

/**
 * @brief 重定向 C 标准库 printf 函数到串口 huart1
 * 适用于 Keil、IAR 等IDE；不适用 GCC
 * @author Suroy
 * @param ch 
 * @param f 
 * @return int 
 * 
 * @usage printf("USART1_Target:\r\n");
 */
int fputc(int ch, FILE *f)
{
    //采用轮询方式发送1字节数据，超时时间为无限等待
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY); //huart1是串口的句柄 
    return ch;
}

/**
 * @brief fgets 重定向
 * 重定向 C 标准库 scanf 函数到串口 huart1
 * 注意以 空格 为结束
 * @param f 
 * @return int 
 * 
 * @usage scanf("%c", &RecData);
 */
int fgetc(FILE *f)
{
  uint8_t ch;
  HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY); //huart1是串口的句柄 
  return ch;
}

#endif /* __GNUC__ */


