/*
 * lora.h
 *
 * Created: 07.11.2017 22:50:25
 *  Author: bond
 */ 


#ifndef LORA_H_
#define LORA_H_


#define FREQ_STEP 20

//Error Coding rate (CR)setting
#define CR_4_5
//#define CR_4_6 0
//#define CR_4_7 0
//#define CR_4_8 0
#ifdef CR_4_5
#define CR 0x01 // 4/5
#else
#ifdef CR_4_6
#define CR 0x02 // 4/6
#else
#ifdef CR_4_7
#define CR 0x03 // 4/7
#else
#ifdef CR_4_8
#define CR 0x04 // 4/8
#endif
#endif
#endif
#endif
//CRC Enable
#define CRC_EN
#ifdef CRC_EN
#define CRC 0x01 //CRC Enable
#else
#define CRC 0x00
#endif
//RFM98 Internal registers Address
/********************Lroa mode***************************/
#define LR_RegFifo 0x00
// Common settings
#define LR_RegOpMode 0x01
#define LR_RegFrMsb 0x06
#define LR_RegFrMid 0x07
#define LR_RegFrLsb 0x08
// Tx settings
#define LR_RegPaConfig 0x09
#define LR_RegPaRamp 0x0A
#define LR_RegOcp 0x0B
// Rx settings
#define LR_RegLna 0x0C
// LoRa registers
#define LR_RegFifoAddrPtr 0x0D
#define LR_RegFifoTxBaseAddr 0x0E
#define LR_RegFifoRxBaseAddr 0x0F
#define LR_RegFifoRxCurrentaddr 0x10
#define LR_RegIrqFlagsMask 0x11
#define LR_RegIrqFlags 0x12
#define LR_RegRxNbBytes 0x13
#define LR_RegRxHeaderCntValueMsb 0x14
#define LR_RegRxHeaderCntValueLsb 0x15
#define LR_RegRxPacketCntValueMsb 0x16
#define LR_RegRxPacketCntValueLsb 0x17
#define LR_RegModemStat 0x18
#define LR_RegPktSnrValue 0x19
#define LR_RegPktRssiValue 0x1A
#define LR_RegRssiValue 0x1B
#define LR_RegHopChannel 0x1C
#define LR_RegModemConfig1 0x1D
#define LR_RegModemConfig2 0x1E
#define LR_RegSymbTimeoutLsb 0x1F
#define LR_RegPreambleMsb 0x20
#define LR_RegPreambleLsb 0x21
#define LR_RegPayloadLength 0x22
#define LR_RegMaxPayloadLength 0x23
#define LR_RegHopPeriod 0x24
#define LR_RegFifoRxByteAddr 0x25
#define LR_RegModemConfig3 0x26
// I/O settings
#define REG_LR_DIOMAPPING1 0x40
#define REG_LR_DIOMAPPING2 0x41
// Version
#define REG_LR_VERSION 0x42
// Additional settings
#define REG_LR_PLLHOP 0x44
#define REG_LR_TCXO 0x4B
#define REG_LR_PADAC 0x4D
#define REG_LR_FORMERTEMP 0x5B
#define REG_LR_AGCREF 0x61
#define REG_LR_AGCTHRESH1 0x62
#define REG_LR_AGCTHRESH2 0x63
#define REG_LR_AGCTHRESH3 0x64


void set_freq_kHz(uint32_t freq_kHz);
 
unsigned char LoRa_entry_tx(void);

unsigned char LoRa_tx_packet(void);

unsigned char GFSK_entry_tx(void);

unsigned char GFSK_tx_packet();

void GFSK_set_power(uint8_t power);
void GFSK_set_dev(uint8_t fdev_msb, uint8_t fdev_lsb);

#endif /* LORA_H_ */