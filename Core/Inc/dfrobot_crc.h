#ifndef __DFROBOT_CRC_H__
#define __DFROBOT_CRC_H__

#include "main.h"

//CRC-32/MPEG-2

uint32_t doCrc32MPEG2Table(uint8_t *ptr, int len);
uint32_t doCrc32MPEG2Calculate(uint8_t *buff,uint8_t num);

#endif
