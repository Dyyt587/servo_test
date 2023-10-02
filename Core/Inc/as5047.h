#ifndef __AS5047_H__
#define __AS5047_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
	
	// 定义AS5047的CS引脚
#define AS5047_CS_PIN GPIO_PIN_4
#define AS5047_CS_PORT GPIOA
	
/* USER CODE END Private defines */
void AS5047_Init(void);
//uint16_t AS5047_ReadData(void);
	
uint16_t Parity_bit_Calculate(uint16_t data_2_cal);
uint16_t SPI_ReadWrite_OneByte(uint16_t _txdata);
uint16_t AS5047_read(uint16_t add);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif 
