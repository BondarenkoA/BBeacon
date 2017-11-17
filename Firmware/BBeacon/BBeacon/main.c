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
#include "millis.h"
#include "lora.h"
#include "battery.h"


void io_init(){
	
	DDRA = 0x00;
	DDRB = 0x00;
	
	DDRA =		(1 << LED_BIT)			//Led on				pin	13
			|	(0 << ADC1_BIT)			//battery voltage		pin	12
			|	(1 << RXEN_BIT)			//RX EN Lora			pin	11
			|	(1 << TXEN_BIT)			//TX EN Lora			pin	10
			|	(0 << USCK_BIT )		//i2c SCK slave			pin	9
			|	(0 << ARMING_BIT)		//Arming motor input	pin	8
			|	(0 << SDA_BIT)			//i2c SDA slave			pin	7
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

/*
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


void out_str_p(const char *c_p ){

	while(pgm_read_byte(c_p) != '\0'){
		USI_TWI_Transmit_Byte(pgm_read_byte(c_p));
		c_p++;
	}
}

void test_strings(){

	LED_ON;
	USI_TWI_Transmit_Byte_no_check('T');//_delay_ms(10);
	USI_TWI_Transmit_Byte_no_check('e');//_delay_ms(10);
	USI_TWI_Transmit_Byte_no_check('s');//_delay_ms(10);
	USI_TWI_Transmit_Byte_no_check('t');//delay_ms(10);
	USI_TWI_Transmit_Byte_no_check('\n');//
	_delay_ms(10);
	LED_OFF;
	_delay_ms(200);
	
	while(1){
		out_str_p(PSTR(">>")); 
		out_str_p(PSTR("1234567890")); 
		out_str_p(PSTR("\n"));
		_delay_ms(100);
	}

}*/

void test_adc(){
	
	debug_str_p(PSTR("test_adc\n"));
	
	while(1){
		_delay_ms(400);
		adc_start();
		LED_ON
		_delay_ms(200);
		LED_OFF
		
		LOG_DEC("ADCW - ", ADCW * 12 );
	}
}

int main(void)
{
	unsigned char TWI_slaveAddress = 0x10;
	
	io_init();
	millis_init();
	//clock_prescale_set(clock_div_32);
	sei(); // разрешаем прерывания
	 
	RXEN_OFF;
	TXEN_ON;
	
//test_powerof();
	
	USI_TWI_Slave_Initialise( TWI_slaveAddress );
	
	debug_str_p(PSTR("BBeacon\n"));
	
	LOG_DEC("F_CPU = ", F_CPU);
	
	LED_ON;_delay_ms(400);LED_OFF
	
	LOG_DEC("400ms - ", millis());
	
	test_adc();
	//LoRa_entry_tx();	
	/*
	GFSK_entry_tx();
	
	set_freq_kHz(433200);
	
	millis_reset();
	
	LED_ON;_delay_ms(400);LED_OFF
	
	LOG_DEC("400ms - ", millis());
	
	GFSK_set_power(0xF0);
	
	while(1){	
		
		LED_ON;
		
		millis_reset();
		
		//LoRa_tx_packet();
		GFSK_set_dev(0x01, 0x4F);GFSK_tx_packet();_delay_ms(300);
		GFSK_set_dev(0x01, 0x7f);GFSK_tx_packet();_delay_ms(300);
		GFSK_set_dev(0x02, 0xff);GFSK_tx_packet();_delay_ms(300);
		GFSK_set_dev(0x03, 0xff);GFSK_tx_packet();_delay_ms(300);
		
		LOG_DEC("ToA - ", millis());
		
		LED_OFF;
		
		_delay_ms(200);
		
		//LOG_DEC("- ", millis());
		
		millis_reset();
		
		_delay_ms(800);
		
		LOG_DEC("800ms - ", millis());
	}
	*/

}

