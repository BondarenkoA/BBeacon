/*
 * BBeacon.c
 *
 * Created: 04.10.2017 23:46:39
 * Author : bond
 */ 

#ifdef DEBUG
#define F_CPU 2000
#else
#define F_CPU 250000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

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

int main(void)
{
	clock_prescale_set(clock_div_32);
	sei(); // разрешаем прерывания
	
	DDRA |= _BV(PA0);
	
	PORTA |= _BV(PA0);
	_delay_ms(50);
	PORTA ^= _BV(PA0);
	_delay_ms(100);
	PORTA ^= _BV(PA0);
	_delay_ms(50);
	PORTA ^= _BV(PA0);
	
	while(1) {
		powerof_delay(WDTO_4S);
		PORTA |= _BV(PA0);
		powerof_delay(WDTO_15MS);
		PORTA ^= _BV(PA0); 
	 }
}

