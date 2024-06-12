#include "led_driver.h"

int Led_Init(LedDevice *pLedDevice)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

      /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    switch (pLedDevice->which)
    {
    case LED_WHITE:
        GPIO_InitStruct.Pin = WHITE_Pin;
        break;

    case LED_BLUE:
        GPIO_InitStruct.Pin = BLUE_Pin;
        break;

    case LED_GREEN:
        GPIO_InitStruct.Pin = GREEN_Pin;
        break;
    
    default:
        return NOT_FOUND;
        break;
    }

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    // 初始化引脚配置
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    return RETURN_SUCCESS;
}

int LedControl(LedDevice *pLedDevice, int iStatus)
{
    switch (pLedDevice->which)
    {
        case LED_WHITE:
            HAL_GPIO_WritePin(WHITE_GPIO_Port, WHITE_Pin, !iStatus);
            break;

        case LED_BLUE:
            HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, !iStatus);
            break;

        case LED_GREEN:
            HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, !iStatus);
            break;
    
    default:
        return NOT_FOUND;
    }
    
    return 0;
}