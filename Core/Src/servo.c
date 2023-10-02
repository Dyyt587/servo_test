#include "servo.h"



void Servo_Init(TIM_HandleTypeDef *htim, uint32_t Channel)
{
		HAL_TIM_PWM_Start(htim,Channel);
}

void Servo_set(TIM_HandleTypeDef *htim, uint32_t Channel,int pulse)
{
		__HAL_TIM_SetCompare(htim,Channel,pulse);	//20000 500   20 0.5
}

