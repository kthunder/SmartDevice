#include "key_Driver.h"


void PendCallback(void)
{
    printf("PendCallback.\r\n");
}


void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStruct.Pin = KEY1_Pin;         // 选择LED的引脚
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; // 设置为推挽输出模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;         // 默认上拉

    // 初始化引脚配置
    HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

    /* 1.设置中断优先级 */
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 2);
    /* 2.使能外部中断 */
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* 3.重定向中断服务函数 */
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
    HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    InputEvent inputEvent;

    /* 消除按键抖动 */

    if(GPIO_Pin == KEY1_Pin)
    {
        inputEvent.time = KAL_GetTime();
        inputEvent.eType = INPUT_EVENT_TYPE_KEY;
        inputEvent.iKey = KEY1;
        inputEvent.iPressure = !KEY1_STATE;

        PutEventIntoBuffer(inputEvent);        
    }
    else if (GPIO_Pin == KEY2_Pin)
    {
        inputEvent.time = KAL_GetTime();
        inputEvent.eType = INPUT_EVENT_TYPE_KEY;
        inputEvent.iKey = KEY2;
        inputEvent.iPressure = !KEY2_STATE;

        PutEventIntoBuffer(inputEvent);   
    }
    
}


 