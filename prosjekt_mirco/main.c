/*
* prosjekt_mirco.c
*
* Created: 22.04.2021 16:29:27
* Author : nixxo

*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "sensorlogic.h"
#include "usart.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void readPin(int pin1, int pin2, int pin3){
	printString(" lightSensor1: ");
	printWord(pin1);
	printString(",");
	printString(" lightSensor2: ");
	printWord(pin2);
	printString(",");
	printString(" potMeter: ");
	printWord(pin3);
	printString("\r\n");
	_delay_ms(1000);
}

int main(void) {
	
	uint8_t position = 90;
	uint16_t potMeter;
	uint16_t lightSensor1;
	uint16_t lightSensor2;
	
	
	UBRR0 = BAUD_PRESCALE;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	initUSART();
	ADC_Init();
	Timer1_PWM_init();
	
	do{
		
		potMeter = ADC_Conversion(0);
		lightSensor1 = ADC_Conversion(1);
		
		lightSensor2 = ADC_Conversion(2);
		readPin(lightSensor1, lightSensor2, potMeter);
		
		//position = lightSensor1>>3;
		position = correctPosition(300, lightSensor1, lightSensor2, position);
		if (validatePosition(position) == true){
			moveServo(position);
			} else {
			//return;
		}
		
		
		
		/*
		moveServo(1);
		_delay_ms(30000);
		moveServo(179);
		_delay_ms(30000);
		*/
		
		//interrupts

	} while(1);
}

