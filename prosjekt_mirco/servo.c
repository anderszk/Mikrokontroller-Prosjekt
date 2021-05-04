include "servo.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16MHz system clock
#define T1_PRESCALE 8 // Timer 1 clock prescaler

// servo period = 20ms = 20000us (=50Hz):
#define SERVO_PERIOD F_CPU/1000000*20000/T1_PRESCALE

#define SERVO_MAX F_CPU/1000000*2000/T1_PRESCALE
#define SERVO_MIN F_CPU/1000000*460/T1_PRESCALE

//Timer initialization
void Timer1_PWM_init()
{

DDRB = (1<<DDB1); // Set OC1A/PB1 as output.

/* Fast PWM non-inverting mode. Clear OC1A on Compare Match, set at TOP=ICR1.

Pre-scale 16Mhz by 8 -> 2MHz = 0.5us/tick */

TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10);
TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12);

ICR1 = SERVO_PERIOD; // Servo period = 20ms (50Hz)

}

//Moves servo to desired position
void moveServo(int position){
    OCR1A = ((((position - positionMin)*(SERVO_MAX - SERVO_MIN))/(positionMax - positionMin)) + SERVO_MIN);
}

