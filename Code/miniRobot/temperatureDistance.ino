#include <OneWire.h>

#define maxDistance 400

int trig;
int echo;

unsigned long distance3 = 0;
unsigned long distance2 = 0;

//ISR for PCINT2
ISR(PCINT2_vect) {
  distance3 = pulseIn(echo, HIGH);
  if(distance3 > 0){
    distance2 = distance3;
  }
  
  
  PCICR &= ~0b00000111;
  PCMSK2 &= ~0b00010000;
  delayMicroseconds(10);
}

void setEchoPins(int pin1, int pin2){
  
  trig = pin1;
  echo = pin2;
  
}

int16_t calculateDistance(){
  int16_t result2 = (int16_t)(((float) distance2/ 58.0));
  if(result2 > maxDistance){
    result2 = maxDistance;
  }
  return result2;
}

void measureDistance(){
    
    digitalWrite(trig, HIGH);
    // ... wait for 10 µs ...
    
    delayMicroseconds(10);
    // ... put the trigger down ...

    digitalWrite(trig, LOW); 

    Serial.println("messe...");
    PCICR |= 0b00000100;
    PCMSK2 |= (1 << echo);
    
    
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
    }
    
    result = (data[1]<<8)|data[0];

    result = result/16; //DS1820 2 DS18B20 16
    
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44, 1); //start conversion
    if(start){
      delay(1000);
    }
  } while(start--);
  return result; 
}

void tempDistSetup(){
  dallas(4, 1);

  // Initializing Trigger Output and Echo Input
   pinMode(trig, OUTPUT);
   pinMode(echo, INPUT);

   // Reset the trigger pin and wait a half a second
   digitalWrite(trig, LOW);
   delayMicroseconds(500);

   sei();
 
}

void runMeasurements(){
  long run_time = micros();
  if(millis() - timer >= 100){
    measureDistance();
    timer = millis();
  } 
  
  Serial.print("Temperatur: ");
  Serial.println(dallas(4, 0));
  
  Serial.print("Distanz: ");
  Serial.print(calculateDistance());
  Serial.println("cm");
  
  run_time = micros() - run_time;
  Serial.print("Zeit für Durchlauf: ");
  Serial.println(run_time);
  Serial.println();
  delay(1000);

}
