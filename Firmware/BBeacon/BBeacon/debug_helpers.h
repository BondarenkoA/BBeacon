/*
 * debug_helpers.h
 *
 * Created: 07.11.2017 20:21:08
 *  Author: bond
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "USI_TWI_Slave.h"
#include <avr/pgmspace.h>


extern uint8_t log_level;

extern const char str_space[];
extern const char str_call[];
extern const char str_ret[];
extern const char str_eol[];

#ifndef DEBUG_HELPERS_H_
#define DEBUG_HELPERS_H_


 
void debug_str(char* c );

void debug_str_p(const char *c );

void debug_strln(char* c );

void debug_b(uint8_t value8 );

void debug_b_ln(uint8_t value8 );

void debug_b_hex(uint8_t value8 );

void debug_u_hex_ln(uint16_t value16 );

void debug_u(uint16_t value16 );

void debug_u_ln(uint16_t value16 );

void debug_ul_ln(uint32_t value32 );


//LOGER ============================================================================
#define I2C_LOGGER 1
#define I2C_WAIT_IF_BUFFER_FULL

#ifdef I2C_LOGGER

#ifdef I2C_WAIT_IF_BUFFER_FULL

#define I2C_OUT_BYTE(V) USI_TWI_Transmit_Byte(V);

#else

#define I2C_OUT_BYTE(V) USI_TWI_Transmit_Byte_no_check(V);

#endif //I2C_WAIT_IF_BUFFER_FULL


#define PROC(str) if(I2C_LOGGER == 1) {	\
	log_level++;\
	for (int i=1; i <= log_level ;i++) debug_str_p(str_space); \
	debug_str_p(str_call); \
	debug_str_p(PSTR(str)); \
	debug_str_p(str_eol); \
	};

#define RETURN_V(ret) { \
	if(I2C_LOGGER == 1) {	\
		for (int i=1; i <= log_level ;i++) debug_str_p(str_space);	\
		debug_str_p(str_ret);	\
		debug_b_ln(ret);	\
		log_level--;}; \
	return(ret);}

#define RETURN { if(I2C_LOGGER == 1) {	for (int i=1; i <= log_level ;i++) debug_str_p(str_space);	\
		debug_str_p(str_ret);	\
		debug_str_p(str_eol);	\
	log_level--;};return ;}

#define LOG_HEX(T, v) if(I2C_LOGGER == 1) { for (int i=1; i <= log_level ;i++) debug_str_p(str_space); debug_str_p(PSTR(T)); debug_u_hex_ln(v); };
#define LOG_DEC(T, v) if(I2C_LOGGER == 1) { for (int i=1; i <= log_level ;i++) debug_str_p(str_space); debug_str_p(PSTR(T)); debug_ul_ln(v); };
#define LOG_STR(T) if(I2C_LOGGER == 1)    { for (int i=1; i <= log_level ;i++) debug_str_p(str_space); debug_str_p(PSTR(T)); debug_str_p(str_eol);}

#else //I2C_LOGGER

#define PROC(str) ;

#define RETURN_V(ret) {return(ret);}

#define RETURN {return ;}

#define LOG_HEX(T, v) ;
#define LOG_DEC(T, v) ;
#define LOG_STR(T) ;
	
#endif //I2C_LOGGER


//END of LOGGER ===========================================================


#endif /* DEBUG_HELPERS_H_ */