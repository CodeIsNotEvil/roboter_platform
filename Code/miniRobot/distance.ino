#define maxDistance 400

int trig;
int echo;

//ISR for PCINT2
ISR(PCINT2_vect) {
  if((PIND & 64) > 0) {
    pulseStart = micros();
  } else {
    startNewMeasurement = true;
    pulseLength = micros() - pulseStart;
    newResult = true;
  }
  PCIFR = 0;
}

void setEchoPins(int pin1, int pin2){
  
  trig = pin1;
  echo = pin2;
  PCIFR = 0;
  PCICR |= 0b00000100;
  PCMSK2 |= (1 << echo);

    // Initializing Trigger Output and Echo Input
   pinMode(trig, OUTPUT);
   pinMode(echo, INPUT);

   // Reset the trigger pin and wait a half a second
   digitalWrite(trig, LOW);
   delayMicroseconds(500);
}


int16_t calculateDistance(){
  int16_t result = 1;

  if(pulseLength > 0) {
    result = (int16_t)(pulseLength / 58);
  }
  if(result > maxDistance){
    result = maxDistance;
  }
  newResult = false;
  //Serial.println(result);
  return result;
}

void measureDistance(){
    
    digitalWrite(trig, HIGH);
    // ... wait for 10 µs ...
    
    delayMicroseconds(10);
    // ... put the trigger down ...
    
    digitalWrite(trig, LOW); 
    
    //Serial.println("messe...");

    startNewMeasurement = false;
    
}
