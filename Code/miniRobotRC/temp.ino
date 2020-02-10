 //Temperatur <3
    void updateTemp(){
      unsigned long currentMillis = millis();
      if((unsigned long)(currentMillis - temp_time) >= 1000){ // jede  Sekunden
        temp_time = millis();
        bool err = false;
        clearCommands();
        
        commands[0] = getTemp;
        radio.write(&commands, sizeof(commands) /* && !err */);
        unsigned long start = micros();
        radio.startListening();
        while(!radio.available()){
          //Serial.println("nix");
          unsigned long currentMicros = micros();
          if((unsigned long)(currentMicros - start) >= 1){
            
            err = true;
          } 
/*
          int16_t readData;
          radio.read(&readData, sizeof(int16_t));
          temperature = readData; */
        }
        if(!err){
          int16_t readData;
          radio.read(&readData, sizeof(int16_t));
          temperature = readData;
        } 
        radio.stopListening();
        clearCommands();
      }
    }
