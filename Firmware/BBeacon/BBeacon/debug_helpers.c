/*
 * debug_helpers.c
 *
 * Created: 07.11.2017 20:21:19
 *  Author: bond
 */ 

#include "debug_helpers.h"
#include "USI_TWI_Slave.h"

void debug_str(char* c ){
	while(*c) USI_TWI_Transmit_Byte_no_check(*c++);
}

void debug_strln(char* c ){
	while(*c) USI_TWI_Transmit_Byte_no_check(*c++);
	USI_TWI_Transmit_Byte_no_check('\n');
}

void debug_b(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 10);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
}

void debug_b_ln(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 10);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
	
	USI_TWI_Transmit_Byte_no_check('\n');
}

void debug_b_hex(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 16);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
}

void debug_b_hex_ln(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 16);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
	
	USI_TWI_Transmit_Byte_no_check('\n');
}

void debug_u(uint16_t value16 ){
	char buffer[6];
	int i = 0;
	
	utoa(value16, buffer, 10);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
}

void debug_u_ln(uint16_t value16 ){
	char buffer[6];
	int i = 0;
	
	utoa(value16, buffer, 10);
	
	while(buffer[i]) USI_TWI_Transmit_Byte_no_check(buffer[i++]);
	
	USI_TWI_Transmit_Byte_no_check('\n');
}