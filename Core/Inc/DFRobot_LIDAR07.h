#ifndef __DFRobot_LIDAR07_H__
#define __DFRobot_LIDAR07_H__

#include "main.h"

// #define LIDAR07_ADDRESS 0x62
// #define LIDAR07_MEASURE_DISTANCE 0x00
// #define LIDAR07_MEASURE_DISTANCE_AND_INTENSITY 0x04

//指令
#define LIDAR07_READ_VERSION 0X43
#define LIDAR07_FILITER 0X59
#define LIDAR07_DISTANCE_SWITCH 0X60
#define LIDAR07_CHOICE_MEASUREMODE 0X61
#define LIDAR07_FRE 0X62
#define LIDAR07_STATES 0X65

#define READ   0X00
#define WRITE  0X80
// //命令
// #define READ_VERSION 0X43|0X00
// #define MEASURE_MODE 0X61|0X80
// #define SWITCH 0X60|0X80
// #define FILTER 0X59|0X80
// #define READ_VERSION 0X43|0X00
// #define READ_VERSION 0X43|0X00
// #define READ_VERSION 0X43|0X00

typedef struct {
    uint32_t version;
    uint32_t fre;
    uint16_t distance_mm;
    uint16_t temperature;
    uint16_t amplitude;
    uint16_t Backlight;
    uint32_t crc;
    float distance_m;
} DFRobot_LIDAR07_packet;

void LIDAR07_read_version(DFRobot_LIDAR07_packet *lidar);
void LIDAR07_fre(DFRobot_LIDAR07_packet *lidar,int8_t mode,uint32_t fre); //mode表示读或写  1是写 0是读
void LIDAR07_mode_set(uint8_t mode);    //mode表示连续或单次  1为连续 0为单次
void LIDAR07_measure_switch(DFRobot_LIDAR07_packet *lidar,uint8_t mode); 
void LIDAR07_filter_switch(uint8_t mode);

#endif

