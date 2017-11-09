/*
 * mySPI.c
 *
 * Created: 02.11.2017 20:14:28
 *  Author: bond
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "mySPI.h"

/**********************************************************
**Name: SPI_cmd_8bit
**Function: SPI Write one byte
**Input: WrPara
**Output: none
**note: use for burst mode
**********************************************************/
void SPI_cmd_8bit(uint8_t WrPara)
{
	uint8_t bitcnt;
	NSEL_LOW;
	SCK_LOW;
	
	for(bitcnt=8; bitcnt!=0; bitcnt--)
	{
		SCK_LOW;
		
		if( WrPara & 0x80 ){
			MOSI_HIGH;
		}
		else{
			MOSI_LOW;
		}
		
		SCK_HIGH;
		WrPara <<= 1;
		
		//_delay_ms(1);
	}
	
	SCK_LOW;
	MOSI_HIGH;
}
/**********************************************************
**Name: SPI_read_8bit
**Function: SPI Read one byte
**Input: None
**Output: result byte
**Note: use for burst mode
**********************************************************/
uint8_t SPI_read_8bit(void)
{
	uint8_t RdPara = 0;
	uint8_t bitcnt;
	
	NSEL_LOW;
	MOSI_HIGH;
	
	for(bitcnt=8; bitcnt!=0; bitcnt--)
	{
		SCK_LOW;
		RdPara <<= 1;
		
		SCK_HIGH;
		//_delay_ms(1);
		
		RdPara |= READ_MISO;

	}
	
	SCK_LOW;
	
	return RdPara;
}
/**********************************************************
**Name: SPIRead
**Function: SPI Read CMD
**Input: adr -> address for read
**Output: None
**********************************************************/
uint8_t SPI_read(uint8_t adr)
{
	uint8_t tmp;
	
	SPI_cmd_8bit(adr); //Send address first
	tmp = SPI_read_8bit();
	NSEL_HIGH;
	
	return tmp;
}
/**********************************************************
**Name: SPIWrite
**Function: SPI Write CMD
**Input: u8 address & u8 data
**Output: None
**********************************************************/
void SPI_write(unsigned char adr, unsigned char WrPara)
{
	NSEL_LOW;
	
	SPI_cmd_8bit(adr|0x80); 
	SPI_cmd_8bit(WrPara);
	SCK_LOW;
	MOSI_HIGH;
	
	NSEL_HIGH;
}
/**********************************************************
**Name: SPIBurstRead
**Function: SPI burst read mode
**Input: adr-----address for read
** ptr-----data buffer point for read
** length--how many bytes for read
**Output: None
**********************************************************/
void SPI_burst_read(unsigned char adr, unsigned char *ptr, unsigned char leng)
{
	unsigned char i;
	
	if(leng<=1)
		return;
	else
	{
		SCK_LOW;
		NSEL_LOW;
		
		SPI_cmd_8bit(adr);
		
		for( i=0; i<leng; i++ ) ptr[i] = SPI_read_8bit();
		
		NSEL_HIGH;
	}
}
/**********************************************************
**Name: SPIBurstWrite
**Function: SPI burst write mode
**Input: adr-----address for write
** ptr-----data buffer point for write
** length--how many bytes for write
**Output: none
**********************************************************/
void SPI_burst_write(unsigned char adr, unsigned char *ptr, unsigned char leng)
{
	unsigned char i;
	
	if(leng<=1) //length must more than one
		return;
	else
	{
		SCK_LOW;
		NSEL_LOW;
		
		SPI_cmd_8bit(adr|0x80);
		
		for( i=0; i<leng; i++ ) SPI_cmd_8bit(ptr[i]);
		
		NSEL_HIGH;
	}
}