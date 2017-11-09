/*
 * BBeacon.c
 *
 * Created: 04.10.2017 23:46:39
 * Author : bond
 */ 

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdlib.h>

#include "USI_TWI_Slave.h"
#include "mySPI.h"
#include "debug_helpers.h"
#include "lora.h"


void io_init(){
	
	DDRA = 0x00;
	DDRB = 0x00;
	
	DDRA =		(1 << LED_BIT)			//Led on				pin	13
			|	(0 << ADC1_BIT)			//battery voltage		pin	12
			|	(1 << RXEN_BIT)			//RX EN Lora			pin	11
			|	(1 << TXEN_BIT)			//TX EN Lora			pin	10
			|	(0 << USCK_BIT )		//i2c SCK slave			pin	9
			|	(0 << ARMING_BIT)		//Arming motor input	pin	8
			|	(1 << SDA_BIT)			//i2c SDA slave			pin	7
			|	(1 << SPI_SCK_BIT);		//SPI Mast SCK to LoRa	pin 6
	DDRB =		(1 << SPI_NSEL_BIT)		//SPI Mast SS to LoRa	pin 2
			|	(1 << SPI_MOSI_BIT)		//SPI Mast MOSI to LoRa	pin 3
			|	(0 << SPI_MISO_BIT);		//SPI Mast MISO to LoRa	pin 5
}

ISR (WATCHDOG_vect) {
	cli();
	wdt_disable();
}

void powerof_delay(int i_wdt_time){
	wdt_reset(); // сбрасываем
	wdt_enable(i_wdt_time); // разрешаем ватчдог
	_WD_CONTROL_REG |= _BV(WDIE);
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // если спать - то на полную
	sleep_enable(); // разрешаем сон
	sleep_mode(); // спать!
}

void test_powerof(){
	
	LED_ON;
	_delay_ms(50);
	LED_OFF;
	_delay_ms(100);
	LED_ON;
	_delay_ms(50);
	LED_OFF;
	
	while(1) {
		powerof_delay(WDTO_4S);
		LED_ON;
		powerof_delay(WDTO_15MS);
		LED_OFF;
	}
}


int main(void)
{
	unsigned char TWI_slaveAddress;
	uint8_t c;
	
	io_init();
	//clock_prescale_set(clock_div_32);
	sei(); // разрешаем прерывания
	
	RXEN_OFF;
	TXEN_ON;
	
//test_powerof();
	
	TWI_slaveAddress = 0x10;
	c = 0;
	
	USI_TWI_Slave_Initialise( TWI_slaveAddress );
	
	debug_str("BBeacon\n");
	//LoRa_entry_tx();	
	
	GFSK_entry_tx();
	
	
	while(1){	
		
		LED_ON;
		
		GFSK_tx_packet(0x80);_delay_ms(20);
		GFSK_tx_packet(0x82);_delay_ms(20);
		GFSK_tx_packet(0x88);_delay_ms(20);
		GFSK_tx_packet(0x8F);_delay_ms(20);
		
		LED_OFF;
		
		_delay_ms(800);
	}
	
	while(1){
		
		//debug_str("\n--->\n");
		/*c = SPI_read(0x42);
		debug_str("REG_LR_VERSION  - "); debug_b_ln(c);
		debug_str("RegOpMode - "); debug_b_ln(SPI_read(0x01));
		debug_str("RegFrfMsb - "); debug_b_ln(SPI_read(0x06));
		debug_str("RegRssiThresh - "); debug_b_ln(SPI_read(0x10));
		debug_str("RegRxTimeout1 - "); debug_b_ln(SPI_read(0x20));*/
		
		debug_b(c);debug_str(" - ");debug_b_ln(SPI_read(c));
		
		if(c++ > 0x70){
			 c = 0;
			 debug_str("\n -------- \n");
		}
		//USI_TWI_Transmit_Byte(c++);
		_delay_ms(300);
	}
	//test_powerof();
}

