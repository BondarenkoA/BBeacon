/*
 * battery.h
 *
 * Created: 14.11.2017 23:28:04
 *  Author: bond
 */ 

#include <avr/io.h>

#ifndef BATTERY_H_
#define BATTERY_H_

#define RES_DEVIDER 1
#define MAX_VOLTAGE 1024
#define MIN_VOLTAGE 512
#define THRESOLD_LOW_VOLTAGE 700

uint16_t get_voltage();

void adc_start(void);

#endif /* BATTERY_H_ */