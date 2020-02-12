#include <OneWire.h>

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
