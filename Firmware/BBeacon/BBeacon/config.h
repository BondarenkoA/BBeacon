/*
 * IncFile1.h
 *
 * Created: 02.11.2017 23:36:53
 *  Author: bond
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


//#define F_CPU 1000000UL
//#define F_CPU ((uint32_t)1000000)


//#define UNO 1
//#define NANO 1
#define BBEACON 1

#define LED_BIT PORTA0
#define RXEN_BIT PORTA2
#define TXEN_BIT PORTA3
#define ARMING_BIT PORTA5

#define LED_ON PORTA |= (1 << LED_BIT);
#define LED_OFF PORTA &=~ (1 << LED_BIT);

#define RXEN_ON PORTA |= (1 << RXEN_BIT);
#define RXEN_OFF PORTA &=~ (1 << RXEN_BIT);

#define TXEN_ON PORTA |= (1 << TXEN_BIT);
#define TXEN_OFF PORTA &=~ (1 << TXEN_BIT);


#endif /* CONFIG_H_ */