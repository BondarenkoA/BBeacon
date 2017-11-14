/*
 * debug_helpers.h
 *
 * Created: 07.11.2017 20:21:08
 *  Author: bond
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "USI_TWI_Slave.h"

#ifndef DEBUG_HELPERS_H_
#define DEBUG_HELPERS_H_

void debug_str(char* c );

void debug_strln(char* c );

void debug_b(uint8_t value8 );

void debug_b_ln(uint8_t value8 );

void debug_b_hex(uint8_t value8 );

void debug_b_hex_ln(uint8_t value8 );

void debug_u(uint16_t value16 );

void debug_u_ln(uint16_t value16 );

void debug_ul_ln(uint32_t value32 );


//LOGER ============================================================================
#define I2C_LOGGER 1
static uint8_t log_level = 0;

#define PROC(str) if(I2C_LOGGER == 1) {	log_level++;for (int i=1; i <= log_level ;i++) debug_str("  "); debug_str(">> "); debug_strln(str);};

#define RETURN_V(ret) { if(I2C_LOGGER == 1) {	for (int i=1; i <= log_level ;i++)	debug_str("  ");	debug_str("<< Return ");	debug_b_ln(ret);	log_level--;};return(ret);}

#define RETURN { if(I2C_LOGGER == 1) {	for (int i=1; i <= log_level ;i++)	debug_str("  ");	debug_strln("<< Return");	log_level--;};return ;}

#define LOG_HEX(T, v) if(I2C_LOGGER == 1) { for (int i=1; i <= log_level+1 ;i++) debug_str("  "); debug_str(T); debug_b_hex_ln(v); };
#define LOG_DEC(T, v) if(I2C_LOGGER == 1) { for (int i=1; i <= log_level+1 ;i++) debug_str("  "); debug_str(T); debug_ul_ln(v); };
#define LOG_STR(T) if(I2C_LOGGER == 1) { for (int i=1; i <= log_level+1 ;i++) debug_str("  "); debug_strln(T);}


//END of LOGGER ===========================================================


#endif /* DEBUG_HELPERS_H_ */