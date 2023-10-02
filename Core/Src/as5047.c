#include "as5047.h"

// ��ʼ��AS5047��CS����
void AS5047_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  
  // ����GPIOAʱ��
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  // ����CS����
  GPIO_InitStruct.Pin = AS5047_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AS5047_CS_PORT, &GPIO_InitStruct);
  
  // Ĭ�Ͻ���CS
 // HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);
}

//// ��ȡAS5047����
//uint16_t AS5047_ReadData(void) {
//  uint16_t data;
//  
//  // ����CS
//  HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_RESET);
//  
//  // ���Ͷ�ȡ���ͨ����0x3FFF
//  uint16_t cmd = 0x3FFF;
//  HAL_SPI_Transmit(&hspi1, (uint8_t*)&cmd, 2, HAL_MAX_DELAY);
//  
//  // ��������
//  HAL_SPI_Receive(&hspi1, (uint8_t*)&data, 2, HAL_MAX_DELAY);
//  
//  // ����CS
//  HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);
//  
//  return data;
//}

// ������ż����
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
// SPI���Ͷ�ȡ����
uint16_t SPI_ReadWrite_OneByte(uint16_t _txdata)
{

	HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_RESET);	// cs����
	uint16_t rxdata;
	if(HAL_SPI_TransmitReceive(&hspi1,(uint8_t *)&_txdata,(uint8_t *)&rxdata,1,1000) !=HAL_OK)
		rxdata=0;
    HAL_GPIO_WritePin(AS5047_CS_PORT, AS5047_CS_PIN, GPIO_PIN_SET);		// cs����
	return rxdata;
}
uint16_t AS5047_read(uint16_t add)
{
	uint16_t data;
	add |= 0x4000;	// ��ָ�� bit14 ��1
	if(Parity_bit_Calculate(add)==1) add=add|0x8000; // ���ǰ15λ 1�ĸ���λż������Bit15 ��1
	SPI_ReadWrite_OneByte(add);		// ����һ��ָ����ܶ��ص�����
		data=SPI_ReadWrite_OneByte(0x0000|0x4000); // ����һ����ָ���ȡ��һ��ָ��ص����ݡ�
	data &=0x3fff;
	return data;
}
