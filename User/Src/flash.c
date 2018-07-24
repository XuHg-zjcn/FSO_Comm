#include "flash.h"

volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;/*FLASH擦除完成标志*/
void FLASH_Erase(u32 Erase_START_ADDR,u16 NbrOfPage)
{
	uint32_t EraseCounter = 0x00;
	u16 N=FLASH_ReadN()+1;
	Erase_START_ADDR+=WRITE_START_ADDR;
  /*解锁FLASH*/
	FLASH_Unlock();
  /* 清除所有挂起标志位 */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);        
  /* 擦除FLASH 页*/
	for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		FLASHStatus = FLASH_ErasePage(Erase_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
	}
	// 写入FLASH
	/* 锁定FLASH  */
	FLASH_Lock();
}

u16 FLASH_ReadN()
{
	u16 n=0,bs=0,TempV;
	do{
		TempV=FLASH_ReadHalfWord(FLASH_PAGE_SIZE*n);
		if(TempV==bs+1)
			bs++;
		n++;
	}
	while(TempV==bs && n < 32);
	return n*0x10000+bs;
}

int FLASH_ReadArray(u32 Adress,u8 *Data,u16 length)
{
	Adress+=WRITE_START_ADDR;
	if(Adress+length>FLASH_End_ADDR)
		return 1; //Adress over range
	while(length)
	{
		*Data=*(u8 *)Adress;
		Data++;
		Adress++;
		length--;
		
	}
	return 0;
}

/*int FLASH_WriteArray(u32 Adress,u8 *Data,u16 length)
{
	Adress+=WRITE_START_ADDR;
	if(Adress+length>FLASH_End_ADDR)
		return 1; //Adress over range
	while(length)
	{
		*(u8 *)Adress=*Data;
		Data++;
		Adress++;
		length--;
		
	}
	return 0;
}*/

int FLASH_WriteHalfWord(u32 Adress,u16 Data)
{
	Adress += WRITE_START_ADDR;
	if(Adress+1>FLASH_End_ADDR)
		return 1;
	if(Adress%2==1)
		return 2;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ProgramHalfWord(Adress,Data);
	FLASH_Lock();
	return 0;
}
int FLASH_WriteWord(u32 Adress,u32 Data)
{
	Adress += WRITE_START_ADDR;
	if(Adress+3>FLASH_End_ADDR)
		return 1;
	if(Adress%2==1)
		return 2;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ProgramWord(Adress,Data);
	FLASH_Lock();
	return 0;
}

u32 FLASH_Read_last(void)
{
	u32 i=0;
	while(FLASH_ReadByte(i)!=0xff && i<FLASH_End_ADDR-WRITE_START_ADDR)
	{
		i++;
	}
	return i;
}
