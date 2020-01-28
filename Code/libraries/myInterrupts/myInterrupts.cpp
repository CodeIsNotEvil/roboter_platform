#include "myInterrupts.h"

	myInterrupts::myInterrupts(){}

	myInterrupts::initTimer1(){
		// reset a timer unit (replace X by timer number)
		TCCR1A = 0; // set TCCRXA register to 0
		TCCR1B = 0; // set TCCRXB register to 0
		TCNT1  = 0; // reset counter value

		// 1:1
		TCCR1B |= (1 << CS10);

		OCR1A = 15999; // set compare match register of timer 1 (max. value: 65536 = 2^16 - 1), 16000 ~ 1 millisecond

		//enable timer
		TCCR1B |= (1 << WGM12); // enable timer1 CTC mode
		TIMSK1 |= (1 << OCIE2A); // enable timer1 compare interrupt
	}

	myInterrupts::disableTimer1Interrupt(){
		TIMSK1 &= ~(1 << OCIE2A); // disable timer1 compare interrupt
	}

	myInterrupts::enableTimer1Interrupt(){
		TIMSK1 |= (1 << OCIE2A); // enable timer1 compare interrupt
	}
//Timer2
	myInterrupts::initTimer2(){
		// reset a timer unit (replace X by timer number)
		TCCR2A = 0; // set TCCRXA register to 0
		TCCR2B = 0; // set TCCRXB register to 0
		TCNT2  = 0; // reset counter value

		TCCR2A |= (1 << WGM21); // enable timer1 CTC mode
		TCCR2A |= (1 << WGM20);
		// 1:64
		TCCR2B |= (1 << CS22);

		OCR2A = 249; // set compare match register of timer 1 (max. value: 65536 = 2^16 - 1), 16000 ~ 1 millisecond

		//enable timer
		TIMSK2 |= (1 << OCIE2A); // enable timer1 compare interrupt
	}

	myInterrupts::initTimer2SoftPWM(){
		// reset a timer unit (replace X by timer number)
		TCCR2A = 0; // set TCCRXA register to 0
		TCCR2B = 0; // set TCCRXB register to 0
		TCNT2  = 0; // reset counter value

		TCCR2A |= (1 << WGM21); // enable timer1 CTC mode
		//TCCR2A |= (1 << WGM20);
		// 1:8
	//	TCCR2B |= (1 << CS20);
		TCCR2B |= (1 << CS21);
		//TCCR2B |= (1 << CS20);

		OCR2A = 100; // set compare match register of timer 2 (max. value: 255 = 2^8 - 1) (100µs) ca. 78Hz

		//enable timer
		TIMSK2 |= (1 << OCIE2A); // enable timer1 compare interrupt

	}

	myInterrupts::disableTimer2Interrupt(){
		TIMSK2 &= ~(1 << OCIE2A); // disable timer1 compare interrupt
	}

	myInterrupts::enableTimer2Interrupt(){
		TIMSK2 |= (1 << OCIE2A); // enable timer1 compare interrupt
	}
//OCR1B

	myInterrupts::initOCR1B(){
		// reset a timer unit (replace X by timer number)
		TCCR1A = 0; // set TCCRXA register to 0
		TCCR1B = 0; // set TCCRXB register to 0
		TCNT1  = 0; // reset counter value

		//OC1B behaviour
		TCCR1A |= (1 << COM1B1);
	//	TCCR1A |= (1 << COM1B0);
		TCCR1A |= (1 << WGM10);
	//	TCCR1A |= (1 << WGM11);

		// 1:1, 62.5kHz
		TCCR1B |= (1 << CS10);

		TCCR1B |= (1 << WGM12);
	//	TCCR1B |= (1 << WGM13);

		OCR1B = 127; // set compare match register of timer 1 (max. value: 65536 = 2^16 - 1), 16000 ~ 1 millisecond

		//enable timer
		TIMSK1 = 0;		//no Interrupts
	}
