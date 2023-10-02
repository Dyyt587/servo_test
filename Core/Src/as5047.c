#include "as5047.h"

// 初始化AS5047的CS引脚
void AS5047_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  
  // 启用GPIOA时钟
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  // 配置CS引脚
  GPIO_InitStruct.Pin = AS5047_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AS5047_CS_PORT, &GPIO_InitStruct);
  
  // 默认禁用CS
 // HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);
}

//// 读取AS5047数据
//uint16_t AS5047_ReadData(void) {
//  uint16_t data;
//  
//  // 启用CS
//  HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_RESET);
//  
//  // 发送读取命令，通常是0x3FFF
//  uint16_t cmd = 0x3FFF;
//  HAL_SPI_Transmit(&hspi1, (uint8_t*)&cmd, 2, HAL_MAX_DELAY);
//  
//  // 接收数据
//  HAL_SPI_Receive(&hspi1, (uint8_t*)&data, 2, HAL_MAX_DELAY);
//  
//  // 禁用CS
//  HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);
//  
//  return data;
//}

// 计算奇偶函数
uint16_t Parity_bit_Calculate(uint16_t data_2_cal)
{
	uint16_t parity_bit_value=0;
	while(data_2_cal != 0)
	{
		parity_bit_value ^= data_2_cal; 
		data_2_cal >>=1;
	}
	return (parity_bit_value & 0x1); 
}
// SPI发送读取函数
uint16_t SPI_ReadWrite_OneByte(uint16_t _txdata)
{

	HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_RESET);	// cs拉低
	uint16_t rxdata;
	if(HAL_SPI_TransmitReceive(&hspi1,(uint8_t *)&_txdata,(uint8_t *)&rxdata,1,1000) !=HAL_OK)
		rxdata=0;
    HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);		// cs拉高
	return rxdata;
}
uint16_t AS5047_read(uint16_t add)
{
	uint16_t data;
	add |= 0x4000;	// 读指令 bit14 置1
	if(Parity_bit_Calculate(add)==1) add=add|0x8000; // 如果前15位 1的个数位偶数，则Bit15 置1
	SPI_ReadWrite_OneByte(add);		// 发送一条指令，不管读回的数据
		data=SPI_ReadWrite_OneByte(0x0000|0x4000); // 发送一条空指令，读取上一次指令返回的数据。
	data &=0x3fff;
	return data;
}
