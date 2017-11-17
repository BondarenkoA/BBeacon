/*
 * lora.c
 *
 * Created: 07.11.2017 22:50:08
 *  Author: bond
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "mySPI.h"
#include "USI_TWI_Slave.h"
#include "debug_helpers.h"
#include "config.h"

#include "lora.h"

#define FSTEP (49.59106445)

static unsigned char sx1276_7_8FreqTbl[][3] =
{
	{0x6C, 0x80, 0x00}, //434MHz
	{0x85, 0x3B, 0x13}, //433MHz OSC 26 MHZ
	{0x85, 0x40, 0xFC}, //433,075MHz 01 chanel LPD OSC 26 MHZ
	{0x85, 0x40, 0xFC}, //433,200MHz 06 chanel LPD OSC 26 MHZ
};
static unsigned char sx1276_7_8PowerTbl[4] =
{
	0xFF, //20dbm
	0xFC, //17dbm
	0xF9, //14dbm
	0xF6, //11dbm
};
static unsigned char sx1276_7_8SpreadFactorTbl[] =
{
	7,8,9,10,11,12
};
static unsigned char sx1276_7_8LoRaBwTbl[10] =
{
	//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
	0,		 1,		 2,		 3,		 4,		 5,		 6,		 7,		8,	   9
};


static unsigned char sx1276_7_8Data[] = {"Lora sx1276 1234567890"};
static unsigned char data_size = 2;

void set_freq_kHz(uint32_t freq_kHz){
	uint32_t frf = 0;
	uint8_t reg_freq[3];
	
	PROC("set_freq_kHz");
	
	frf = (uint32_t) ( (float)freq_kHz*1000 / FSTEP );
	
	for (int i = 2; i >=0; i--){
		reg_freq[i] = frf & 0xff;
		frf >>= 8;
		
		LOG_HEX("F ", reg_freq[i]);
	}
	
	SPI_burst_write(LR_RegFrMsb, reg_freq, 3);
	
	RETURN;
}

unsigned char LoRa_entry_tx(void)
{
	unsigned char temp;
	
	PROC("LoRa_entry_tx");
	
	//setting base parameter
	
	SPI_write(LR_RegOpMode, 0x08); //Sleep//Low Frequency Mode //Change modem mode Must in Sleep mode
	
	_delay_ms(5);
	
	SPI_write(LR_RegOpMode, 0x88); //lora mode

	SPI_write(LR_RegPaConfig, 0x70); //Setting output power parameter
	//SPI_write(REG_LR_PADAC,0x87); //Tx for 20dBm
	
	SPI_write(LR_RegOcp, 0x0B); //RegOcp, Close Ocp
	
	SPI_write(LR_RegModemConfig1, ((sx1276_7_8LoRaBwTbl[4]<<4)       + (CR<<1)  + 0x00));//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
	SPI_write(LR_RegModemConfig2, ((sx1276_7_8SpreadFactorTbl[0]<<4) + (CRC<<2) + 0x03)); //SFactor & LNA gain set by the internal AGC loop
	SPI_write(LR_RegModemConfig3, 0x08);

	LOG_HEX("MC1 = ", SPI_read(LR_RegModemConfig1));
	LOG_HEX("MC2 = ", SPI_read(LR_RegModemConfig2));
	
	SPI_write(LR_RegPreambleMsb, 0x00); //RegPreambleMsb
	SPI_write(LR_RegPreambleLsb, 0x00); //RegPreambleLsb 8+4=12byte Preamble
	
	//SPI_write(REG_LR_DIOMAPPING1, 0x41); //PIN_DIO0=01, DIO1=00,DIO2=00, DIO3=01
	//SPI_write(REG_LR_DIOMAPPING2, 0x01); //RegDioMapping2 DIO5=00, DIO4=01
	
	SPI_write(LR_RegIrqFlagsMask, 0xF7); //Open TxDoneinterrupt
	
	SPI_write(LR_RegPayloadLength, data_size); //RegPayloadLength data_sizebyte
	
	while(1)
	{
		temp=SPI_read(LR_RegPayloadLength);
		
		LOG_DEC("PayloadLen = ", temp);
		
		if(temp == data_size) break;
		
		_delay_ms(100);
	}
	
	RETURN_V(0);
}
/**********************************************************
**Name: LoRa_tx_packet
**Function: Send data in LoRa mode
**Input: None
**Output: 1- Send over
**********************************************************/
unsigned char LoRa_tx_packet(void)
{
	unsigned char addr;
	
	PROC("LoRa_tx_packet");
	
	SPI_write(LR_RegOpMode,0x09); //Entry Standby mode
	
	LOG_DEC("1 ", SPI_read(LR_RegFifoAddrPtr));
	
	addr = SPI_read(LR_RegFifoTxBaseAddr); //RegFiFoTxBaseAddr
	SPI_write(LR_RegFifoAddrPtr, addr); //RegFifoAddrPtr
	
	SPI_burst_write(0x00, (unsigned char *)sx1276_7_8Data, data_size);
	
	LOG_DEC("2 ", SPI_read(LR_RegFifoAddrPtr));
	
	LOG_HEX("=", SPI_read(LR_RegIrqFlags));
	SPI_write(LR_RegOpMode,0x8b); //Tx Mode 8b

	//while(!digitalRead(PIN_DIO0))
	while(SPI_read(LR_RegIrqFlags) != 0x08)
	{
		_delay_ms(10);
	}
	
	SPI_write(LR_RegIrqFlags, 0xFF); //Clear irq
	SPI_write(LR_RegOpMode,0x09); //Entry Standby mode
	
	RETURN_V(0);
}

unsigned char GFSK_entry_tx(void){
	PROC("GFSK_entry_tx");
	
	SPI_write(LR_RegOpMode, 0x08);
	_delay_ms(5);
	//SPI_write(LR_RegFrMsb, 0x85); //setting frequency parameter
	//SPI_write(LR_RegFrMid, 0x40); //setting frequency parameter
	//SPI_write(LR_RegFrLsb, 0xFC); //setting frequency parameter
	
	//SPI_write(RegFdevMsb, 0x00);//RegFdevMsb
	//SPI_write(RegFdevLsb, 0x74);//RegFdevLsb
	
	SPI_write(LR_RegPaConfig, 0x80); //Setting output power parameter
	SPI_write(LR_RegOcp, 0x0B); //RegOcp, Close Ocp
	
	SPI_write(RegPaRamp, 0x49);//RegPaRamp GAUSSIAN 0,5
	
	SPI_write(RegPreambleMsb, 0x00);//RegPreambleMsb
	SPI_write(RegPreambleLsb, 0x32);//RegPreambleLsb
	
	SPI_write(RegPacketConfig1, 0x00);//RegPacketConfig1
	SPI_write(RegPacketConfig2, 0x40);//RegPacketConfig2
	
	SPI_write(RegFifoThresh, 0x80);
	
	SPI_write(RegPayloadLength, data_size);//RegPayloadLength
	
	
	
	RETURN_V(0);
}

unsigned char GFSK_tx_packet(){
	
	unsigned char addr;
	
	PROC("GFSK_tx");
	
	SPI_write(LR_RegOpMode,0x09); //Entry Standby mode
	
	//LOG_DEC("1 ", SPI_read(LR_RegFifoAddrPtr));
	
	//addr = SPI_read(LR_RegFifoTxBaseAddr); //RegFiFoTxBaseAddr
	//SPI_write(LR_RegFifoAddrPtr, addr); //RegFifoAddrPtr
	LOG_HEX("1 ", SPI_read(RegIrqFlags2));//RegIrqFlags2
	
	SPI_burst_write(RegFIFO, (unsigned char *)sx1276_7_8Data, data_size);
	//SPI_burst_write(RegFIFO, (unsigned char *)sx1276_7_8Data, data_size);
	
	LOG_HEX("2 ", SPI_read(RegIrqFlags2));//RegIrqFlags2
	LOG_HEX("Op1 ", SPI_read(RegOpMode));//RegOpMode
	
	SPI_write(RegOpMode,0x0b); //Tx Mode 8b
	
	LOG_HEX("3 ", SPI_read(RegIrqFlags2));//RegIrqFlags2
	LOG_HEX("Op2 ", SPI_read(RegOpMode));//RegOpMode

	while((SPI_read(RegIrqFlags2) & (1 << 3)) != (1 << 3)) //RegIrqFlags2
	{
		LOG_HEX("4 ", SPI_read(RegIrqFlags2));//RegIrqFlags2
		_delay_ms(10);
	}
	
	SPI_write(LR_RegOpMode,0x09); //Entry Standby mode
	
	RETURN_V(0);
}

void GFSK_set_power(uint8_t power){
	
	SPI_write(LR_RegOpMode, 0x08);
	_delay_ms(1);
	SPI_write(LR_RegPaConfig, power);
	
}

void GFSK_set_dev(uint8_t fdev_msb, uint8_t fdev_lsb){
	
	SPI_write(LR_RegOpMode, 0x08);
	_delay_ms(1);
	
	SPI_write(RegFdevMsb, fdev_msb);//RegFdevMsb
	SPI_write(RegFdevLsb, fdev_lsb);//RegFdevLsb
}