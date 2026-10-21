#include "stm32f10x.h"
void APP_BAT_Init(void)
{
    /*先对tim2进行初始化*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //对时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct = {0};
    TIM_TimeBaseInitstruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitstruct.TIM_Period = 9999;
    TIM_TimeBaseInitstruct.TIM_Prescaler = 71;
    TIM_TimeBaseInitstruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstruct);
    TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
    TIM_Cmd(TIM2,ENABLE);
    //对adc进行初始化
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    //对电压测量引脚初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    //初始化注入序列
    ADC_InitTypeDef ADC_InitStruct = {0};
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1,&ADC_InitStruct);
    ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_T2_TRGO);
    ADC_InjectedChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_1Cycles5);
    ADC_ExternalTrigInjectedConvCmd(ADC1,ENABLE);
    
    //配置中断
    ADC_ITConfig(ADC1,ADC_IT_JEOC,ENABLE);
    //初始化NVIC
    NVIC_InitTypeDef NVIC_InitStruct = {0};
    NVIC_InitStruct.NVIC_IRQChannel =  ADC1_2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStruct);
    //闭合开关
    ADC_Cmd(ADC1,ENABLE);
}

void ADC1_2_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC1,ADC_FLAG_JEOC) == SET)
    {
        ADC_ClearFlag(ADC1,ADC_FLAG_JEOC);
        uint16_t jdr1 = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
    }

}