#ifndef __SERVO_H__
#define __SERVO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define servo_1 TIM_CHANNEL_1
#define servo_2 TIM_CHANNEL_2
#define servo_3 TIM_CHANNEL_3
#define servo_4 TIM_CHANNEL_4
	
	
/* USER CODE END Private defines */

void Servo_Init(TIM_HandleTypeDef *htim, uint32_t Channel);
void Servo_set(TIM_HandleTypeDef *htim, uint32_t Channel,int pulse);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif 

