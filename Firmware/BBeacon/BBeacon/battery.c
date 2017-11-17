/*
 * battery.c
 *
 * Created: 14.11.2017 23:27:52
 *  Author: bond
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "battery.h"

static uint8_t voltage_ADC ;

uint16_t get_voltage(){
	
	return ADCW;
	
}

ISR (ADC_vect)//���������� �� ���������� �������������� ���
{
	voltage_ADC = ADCH;//��������� �������� �� ��������������
	ADCSRA |= (0<<ADEN); //���������
}

void adc_start(void)
{

	ADMUX = 0;
	//          7     6     5     4     3     2     1     0
	//ADMUX = REFS1 REFS0 ADLAR   �    MUX3  MUX2  MUX1  MUX0
	ADMUX |= (1<<REFS1) | (0<<REFS0) | (1 << MUX0);//ref 1.1 
		
	//           7    6     5     4     3     2     1     0
	//ADCSRA = ADEN ADSC  ADFR  ADIF  ADIE  ADPS2 ADPS1 ADPS0
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0);//��������� ��������������, ��������� ���, ��������� ���������� �� ���
	//�������� ������� ����� �� 8 - �������� ������� �������������� 125 ���
}

