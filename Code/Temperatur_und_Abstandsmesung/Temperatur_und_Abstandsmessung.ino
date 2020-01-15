#include <OneWire.h>

#define trig PD3
#define echo PD4

long distance = 0;
int count = 0;

// ISR For Timer
ISR(TIMER0_COMPA_vect){

  //set count depending on tcnt0 and the prescaler
  if(count == 96){
    count = 0;
    TCNT0 = 0;

    digitalWrite(trig, HIGH);
    // ... wait for 10 µs ...
    
    delayMicroseconds(10);
    // ... put the trigger down ...
    digitalWrite(trig, LOW);

    PCICR |= 0b00000100;
    PCMSK2 |= 0b00010000;
    
  } else {
    count++;
  }  
}

//ISR for PCINT20
ISR(PCINT2_vect) {
  distance = pulseIn(echo, HIGH);
  
  PCICR &= ~0b00000100;
  PCMSK2 &= ~0b00010000;
  delayMicroseconds(10);
}

long calculateDistance(){
  return (long) (((float) distance/ 58.0));
}

int16_t dallas(int x, byte start){
  
  OneWire ds(x);
  byte i;
  byte data[2];
  int16_t result;

  do{
    ds.reset();
    ds.write(0xCC); //skip Command
    ds.write(0xBE); //Read 1st 2 bytes of Scratchpad
    result = 0;
    for(i = 0; i < 2; i++){
      data[i] = ds.read();
      result += data[i];
    }

    result = result/2;
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44, 1); //start conversion
    if(start){
      delay(1000);
    }
  } while(start--);
  return result; 
}

void initS(){
  
  TCNT0 = 0; // reset timer
  TCCR0A |= 0b00000010;
  TCCR0B |= 0b0000011; //set prescaler to 64 becasue 256 does not work
  OCR0A = 255;
  TIMSK0 |= 0b00000010;
  sei();  
}

void setup(){
  Serial.begin(9600);
  dallas(2, 1);

  // Initializing Trigger Output and Echo Input
   pinMode(trig, OUTPUT);
   pinMode(echo, INPUT);

   // Reset the trigger pin and wait a half a second
   digitalWrite(trig, LOW);
   delayMicroseconds(500);

   initS();
}

void loop(){

  long run_time = micros();

  Serial.print("Temperatur: ");
  Serial.println(dallas(2, 0));

  Serial.print("Distanz: ");
  Serial.print(calculateDistance());
  Serial.println("cm");
  
  run_time = micros() - run_time;
  Serial.print("Zeit für Durchlauf: ");
  Serial.println(run_time);
  Serial.println();
  delay(1000);

}
