 //Temperatur <3
    void updateTemp(){
      if((unsigned long)(millis() - temp_time) >= 1000){ // jede  Sekunden
        temp_time = millis();
        bool err = false;
        clearCommands();
        
        commands[0] = getTemp;
        radio.write(&commands, sizeof(commands));
        unsigned long start = micros();
        radio.startListening();
        while(!radio.available()){
          //Serial.println("nix");
        /*  unsigned long currentMicros = micros();
          if((unsigned long)(currentMicros - start) >= 1){
            
            err = true;
          } */
          if((millis() - temp_time) >= 10) break;
        }
        if(/* !err */ true){
          int16_t readData;
          radio.read(&readData, sizeof(int16_t));
          temperature = readData;
        } 
        radio.stopListening();
        clearCommands();
      }
    }
