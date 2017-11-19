/*
 * debug_helpers.c
 *
 * Created: 07.11.2017 20:21:19
 *  Author: bond
 */ 

#include "debug_helpers.h"
#include "USI_TWI_Slave.h"

uint8_t log_level = 0;

const char str_space[] PROGMEM = "  ";
const char str_call[] PROGMEM = ">> ";
const char str_ret[] PROGMEM = "<< Ret ";
const char str_eol[] PROGMEM = "\n";

/*
void debug_str(char* c ){
	while(*c != '\0' ){
		 I2C_OUT_BYTE(*c);
		 c++;
	}
}
*/
void debug_str_p(const char *c_p ){

	while(pgm_read_byte(c_p) != '\0'){
		I2C_OUT_BYTE(pgm_read_byte(c_p));
		c_p++;
	}
}
/*
void debug_strln(char* c ){
	while(*c != '\0'){
		I2C_OUT_BYTE(*c);
		c++;
	}
	I2C_OUT_BYTE('\n');
}

void debug_b(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 10);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
}

void debug_b_ln(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 10);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
	
	I2C_OUT_BYTE('\n');
}

void debug_b_hex(uint8_t value8 ){
	char buffer[4];
	int i = 0;
	
	utoa(value8, buffer, 16);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
}
*/
void debug_u_hex_ln(uint16_t value16 ){
	char buffer[6];
	uint8_t i = 0;
	
	utoa(value16, buffer, 16);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
	
	I2C_OUT_BYTE('\n');
}

/*
void debug_u(uint16_t value16 ){
	char buffer[6];
	int i = 0;
	
	utoa(value16, buffer, 10);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
}
*/
void debug_u_dec_ln(uint16_t value16 ){
	char buffer[6];
	uint8_t i = 0;
	
	utoa(value16, buffer, 10);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
	
	I2C_OUT_BYTE('\n');
}

/*
void debug_ul_ln(uint32_t value32 ){
	char buffer[6];
	int i = 0;
	
	ultoa(value32, buffer, 10);
	
	while(buffer[i]) I2C_OUT_BYTE(buffer[i++]);
	
	I2C_OUT_BYTE('\n');
}*/