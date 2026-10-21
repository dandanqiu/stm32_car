#ifndef APP_BAT.H
#define APP_BAT.H
#include "stm32f10x.h"
/*这个模块用于对电池电压进行检测 */
void APP_BAT_Init(void);//模块初始化
void ADC1_2_IRQHandler(void);//中断函数

#endif // !APP_BAT.H 防止头文件被重复引用

