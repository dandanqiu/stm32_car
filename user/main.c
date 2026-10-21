#include "stm32f10x.h"

int main(void)
{
	while(1)
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		
	}
}
