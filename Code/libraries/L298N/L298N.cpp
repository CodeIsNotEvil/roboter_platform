#include "L298N.h"

 L298N::L298N() {
   DDR_A |= PIN_A;
   PORT_A &= ~PIN_A;
   DDR_B |= PIN_B;
   PORT_B &= ~PIN_B;

   DDRB |= 6;		//set OC1A and OC1B as output
   PORTB &= ~6;		//clear OC1A and OC1B

   //
   TCCR1A = 0; // set TCCRXA register to 0
   TCCR1B = 0; // set TCCRXB register to 0
   TCNT1  = 0; // reset counter value

   //OC1B behaviour
   TCCR1A |= (1 << COM1B1);
   //OCC1A behaviour
   TCCR1A |= (1 << COM1A1);
   TCCR1A |= (1 << WGM10);

   // 1:1, 62.5kHz
   TCCR1B |= (1 << CS10);

   TCCR1B |= (1 << WGM12);
   //enable timer
   TIMSK1 = 0;		//no Interrupts
 }
 L298N::setPWM_A(int16_t pwmA) {
   if(pwmA < 0) {
     PWMA = 0xFF + pwmA;
     PORT_A |= PIN_A;
   } else {
     if(pwmA == 0) {
       PWMA = 0;
       PORT_A &= ~PIN_A;
     } else {
       PWMA = pwmA;
       PORT_A &= ~PIN_A;
     }
   }
 }
 L298N::setPWM_B(int16_t pwmB) {
   if(pwmB < 0) {
     PWMB = 0xFF + pwmB;
     PORT_B |= PIN_B;
   } else {
     if(pwmB == 0) {
       PWMB = 0;
       PORT_B &= ~PIN_B;
     } else {
       PWMB = pwmB;
       PORT_B &= ~PIN_B;
     }
   }
 }
