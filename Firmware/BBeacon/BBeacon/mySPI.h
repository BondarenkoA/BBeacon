/*
 * mySPI.h
 *
 * Created: 02.11.2017 20:14:08
 *  Author: bond
 */ 


#ifndef MYSPI_H_
#define MYSPI_H_

#include <avr/io.h>

#ifdef UNO
#define PIN_NSEL 10
#define PIN_SCK 13
#define PIN_MOSI 11
#define PIN_MISO 12
#endif

#ifdef NANO
#define PIN_NSEL 5
#define PIN_SCK 2
#define PIN_MOSI 4
#define PIN_MISO 3
#endif

#ifdef BBEACON //=================================================

#define PORT_SCK PORTA
#define PIN_SCK PINA
#define SPI_SCK_BIT PORTA7

#define PORT_NSEL PORTB
#define PIN_NSEL PINB
#define SPI_NSEL_BIT PORTB0

#define PORT_MOSI PORTB
#define PIN_MOSI PINB
#define SPI_MOSI_BIT PORTB1

#define PORT_MISO PORTB
#define PIN_MISO PINB
#define SPI_MISO_BIT PORTB2


#define NSEL_HIGH PORT_NSEL |= (1 << SPI_NSEL_BIT);
#define NSEL_LOW PORT_NSEL &=~ (1 << SPI_NSEL_BIT);

#define SCK_HIGH PORT_SCK |= (1 << SPI_SCK_BIT);
#define SCK_LOW PORT_SCK &=~ (1 << SPI_SCK_BIT);

#define MOSI_HIGH PORT_MOSI |= (1 << SPI_MOSI_BIT);
#define MOSI_LOW PORT_MOSI &=~ (1 << SPI_MOSI_BIT);

#define READ_MISO ( ( (PIN_MISO & (1 << SPI_MISO_BIT)) > 0 ) ? 0x01 : 0x00 );

#endif //=================================================

void SPI_cmd_8bit(uint8_t WrPara);
uint8_t SPI_read_8bit(void);
uint8_t SPI_read(uint8_t adr);
void SPI_write(unsigned char adr, unsigned char WrPara);
void SPI_burst_read(unsigned char adr, unsigned char *ptr, unsigned char leng);
void SPI_burst_write(unsigned char adr, unsigned char *ptr, unsigned char leng);



#endif /* MYSPI_H_ */