#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f10x.h"
#define FLASH_PAGE_SIZE    ((uint16_t)0x400) //如果一页为1K大小
#define WRITE_START_ADDR   ((uint32_t)0x08008000)//写入的起始地址
#define FLASH_End_ADDR     ((uint32_t)0x0801FFFF)
#define FLASH_ReadByte(x) *(u8 *)(WRITE_START_ADDR+x)
#define FLASH_ReadHalfWord(x) *(u16 *)(WRITE_START_ADDR+x)
#define FLASH_ReadWord(x) *(u32 *)(WRITE_START_ADDR+x)
void FLASH_Erase(u32 Erase_START_ADDR,u16 NbrOfPage);
u16 FLASH_ReadN(void);
int FLASH_ReadArray(u32 Adress,u8 *Data,u16 length);
//int FLASH_WriteArray(u32 Adress,u8 *Data,u16 length);
int FLASH_WriteHalfWord(u32 Adress,u16 Data);
int FLASH_WriteWord(u32 Adress,u32 Data);
u32 FLASH_Read_last(void);

#endif
