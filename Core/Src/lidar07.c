#include "DFRobot_LIDAR07.h"

void LIDAR07_read_version(DFRobot_LIDAR07_packet *lidar)
{
    uint8_t Send[10] = {0};
    uint8_t Receive[12];
    uint32_t crc;
    Send[0] = 0xF5;
    Send[1] = LIDAR07_READ_VERSION | READ;

    //发出校验
    crc = doCrc32MPEG2Calculate(Send, 6);   //参数二是不算冗余码的长度

    Send[6] = crc & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    crc = crc >> 8;
    Send[7] = crc & 0xFF;
    crc = crc >> 8;
    Send[8] = crc & 0xFF;
    crc = crc >> 8;
    Send[9] = crc & 0xFF;

    //   Send[6]=0xAC;
    //   Send[7]=0x45;
    //   Send[8]=0x62;
    //   Send[9]=0x3B;

    HAL_UART_Transmit(&huart6, (uint8_t *)Send, 10, 100);
    HAL_UART_Receive(&huart6, (uint8_t *)Receive, 12, 2000);

    //接收校验
    crc = (uint32_t)Receive[8] | ((uint32_t)Receive[8 + 1] << 8) |
          ((uint32_t)Receive[8 + 2] << 16) | ((uint32_t)Receive[8 + 3] << 24);

    if(crc==doCrc32MPEG2Calculate(Receive, 8))
    {
        lidar->version = (uint32_t)Receive[4] | ((uint32_t)Receive[4 + 1] << 8) |
          ((uint32_t)Receive[4 + 2] << 16) | ((uint32_t)Receive[4 + 3] << 24);
        // for (int i = 0; i < 4; i++)
        // {
        //     printf("%x ", Receive[i + 4]);
        // }    
    }
    //   printf("\r\n");
}

void LIDAR07_fre(DFRobot_LIDAR07_packet *lidar,int8_t mode,uint32_t fre)
{
    if(mode==1)
    {
      mode = WRITE;  
    }
    else
    {
      mode = READ;
    }

    uint8_t Send[10] = {0};
    uint8_t Receive[12];
    uint32_t crc;
    Send[0] = 0xF5;
    Send[1] = LIDAR07_FRE | WRITE;

    Send[2] = fre & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    fre = fre >> 8;
    Send[3] = fre & 0xFF;
    fre = fre >> 8;
    Send[4] = fre & 0xFF;
    fre = fre >> 8;
    Send[5] = fre & 0xFF;

    //发出校验
    crc = doCrc32MPEG2Calculate(Send, 6);   //参数二是不算冗余码的长度

    Send[6] = crc & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    crc = crc >> 8;
    Send[7] = crc & 0xFF;
    crc = crc >> 8;
    Send[8] = crc & 0xFF;
    crc = crc >> 8;
    Send[9] = crc & 0xFF;

    // printf("%x ", Send[1]);
    //         for (int i = 0; i < 4; i++)
    //     {
    //         printf("%x ", Send[i + 6]);
    //     }

    HAL_UART_Transmit(&huart6, (uint8_t *)Send, 10, 100);
    HAL_UART_Receive(&huart6, (uint8_t *)Receive, 12, 2000);

    //接收校验
    crc = (uint32_t)Receive[8] | ((uint32_t)Receive[8 + 1] << 8) |
          ((uint32_t)Receive[8 + 2] << 16) | ((uint32_t)Receive[8 + 3] << 24);
        //     for (int i = 0; i < 4; i++)
        // {
        //     printf("%x ", Receive[i + 8]);
        // }
    if(crc==doCrc32MPEG2Calculate(Receive, 8))
    {

    }
    lidar->fre = (uint32_t)Receive[4] | ((uint32_t)Receive[4 + 1] << 8) |
                 ((uint32_t)Receive[4 + 2] << 16) | ((uint32_t)Receive[4 + 3] << 24);

}

void LIDAR07_mode_set(uint8_t mode)
{
    uint8_t Send[10] = {0};
    uint32_t crc;
    Send[0] = 0xF5;
    Send[1] = LIDAR07_CHOICE_MEASUREMODE | WRITE;
    Send[2] = mode;
    crc = doCrc32MPEG2Calculate(Send,6);
    
    Send[6] = crc & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    crc = crc >> 8;
    Send[7] = crc & 0xFF;
    crc = crc >> 8;
    Send[8] = crc & 0xFF;
    crc = crc >> 8;
    Send[9] = crc & 0xFF;

    // Send[6] = 0xA5;
    // Send[7] = 0x8D;
    // Send[8] = 0x89;
    // Send[9] = 0xA7;

    HAL_UART_Transmit(&huart6, (uint8_t *)Send, 10, 100);
}

void LIDAR07_measure_switch(DFRobot_LIDAR07_packet *lidar, uint8_t mode) // 1是开
{
    uint8_t Send[10] = {0};
    uint8_t Receive[24];
    uint32_t crc;
    Send[0] = 0xF5;
    Send[1] = LIDAR07_DISTANCE_SWITCH | WRITE;
    Send[2] = mode;
    
    crc = doCrc32MPEG2Calculate(Send,6);
    
    Send[6] = crc & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    crc = crc >> 8;
    Send[7] = crc & 0xFF;
    crc = crc >> 8;
    Send[8] = crc & 0xFF;
    crc = crc >> 8;
    Send[9] = crc & 0xFF;

    // for (int i = 0; i < 4; i++)
    // {
    //     printf("%x ", Send[i + 6]);
    // }

    // Send[6] = 0x9F;
    // Send[7] = 0x70;
    // Send[8] = 0xE9;
    // Send[9] = 0x32;
    
    HAL_UART_Transmit(&huart6, (uint8_t *)Send, 10, 100);
    HAL_UART_Receive(&huart6, (uint8_t *)Receive, 24, 2000);
    //接收校验
    crc = (uint32_t)Receive[20] | ((uint32_t)Receive[20 + 1] << 8) |
          ((uint32_t)Receive[20 + 2] << 16) | ((uint32_t)Receive[20 + 3] << 24);
    if(crc==doCrc32MPEG2Calculate(Receive, 20))
    {

    }
    lidar->distance_mm = (((uint16_t)Receive[5]) << 8) | ((uint16_t)Receive[4]);
    lidar->distance_m = ((float)lidar->distance_mm)/1000;
    lidar->temperature = (((uint16_t)Receive[7]) << 8) | ((uint16_t)Receive[6]);
    lidar->amplitude = (((uint16_t)Receive[9]) << 8) | ((uint16_t)Receive[8]);
    lidar->Backlight = (((uint16_t)Receive[11]) << 8) | ((uint16_t)Receive[10]);
}

void LIDAR07_filter_switch(uint8_t mode)
{
    uint8_t Send[10] = {0};
    uint32_t crc;
    Send[0] = 0xF5;
    Send[1] = LIDAR07_FILITER | WRITE;
    Send[2] = mode;

    crc = doCrc32MPEG2Calculate(Send,6);
    
    Send[6] = crc & 0xFF;       //32位 高位可能是0 用与操作 防止高位的0被改了
    crc = crc >> 8;
    Send[7] = crc & 0xFF;
    crc = crc >> 8;
    Send[8] = crc & 0xFF;
    crc = crc >> 8;
    Send[9] = crc & 0xFF;

    // Send[6] = 0xB7;
    // Send[7] = 0x1F;
    // Send[8] = 0xBA;
    // Send[9] = 0xBA;
    HAL_UART_Transmit(&huart6, (uint8_t *)Send, 10, 100);
}
