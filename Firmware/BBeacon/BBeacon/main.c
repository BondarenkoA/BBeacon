/*
 * BBeacon.c
 *
 * Created: 04.10.2017 23:46:39
 * Author : bond
 */ 

#define F_CPU 250000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

//FUSES = 
//{
	//.low = 0xE6,
	//.high = 0xD9,
	//.extended = 0xFF,
//};

int main(void)
{
	clock_prescale_set(clock_div_32);
	
	DDRA |= (1 << PA0);
	
    while(1)
    {
        PORTA ^= (1 << PA0);
		_delay_ms(50);
		PORTA ^= (1 << PA0);
		_delay_ms(5000); 
    }
}

