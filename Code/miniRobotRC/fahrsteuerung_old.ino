void manualDigitalDrive() {

  bool goOn = false;
  String temp_str = "T: " + String(temperature) + " Grad C";
  lcdLines[5] = temp_str;
 // while(!tasten.getButtonCycle(buttonL1)) {
    clearCommands();
    if(!tasten.getAnyPressed()) {
      lcdLines[0] = "Warte...";
      
 
    }
    if(tasten.checkButton(buttonB) || tasten.checkButton(buttonUp)) {
            pwmA = -215;
            pwmB = -255;
            lcdLines[0] = "geradeaus fahren";
            goOn =true;
    }
    if(tasten.checkButton(buttonC) || tasten.checkButton(buttonDown)) {
            pwmA = 100;
            pwmB = 255;
            lcdLines[0] = "rueckwaerts fahren";
            goOn =true;
     }
    if(tasten.checkButton(buttonRight)) {
        pwmA = -100;  //rechter Motor
        pwmB = 100;
        lcdLines[0] = "rechts lenken";
            goOn =true;
    } 
    if(tasten.checkButton(buttonLeft)) {
        pwmB = -100;
        pwmA = 100;
        lcdLines[0] = "links lenken";
            goOn =true;
    }
      if(goOn) {
        commands[0] = speedA;
        commands[1] = highByte(pwmA);
        commands[2] = lowByte(pwmA);
        commands[3] = speedB;
        commands[4] = highByte(pwmB);
        commands[5] = lowByte(pwmB);
        commands[6] = timeToDrive;
        commands[7] = highByte(driveTimeout);
        commands[8] = lowByte(driveTimeout);
        commands[9] = goDrive;
        
        radio.write(&commands, sizeof(commands));
        goOn = false;
      }

    //Temperatur <3
    unsigned long currentMillis = millis();
    if((unsigned long)(currentMillis - temp_time) >= 1000){ // jede  Sekunden
      temp_time = millis();
      bool err = false;
      clearCommands();
      
      commands[0] = getTemp;
      radio.write(&commands, sizeof(commands) && !err);
      unsigned long start = micros();
      radio.startListening();
      while(!radio.available()){
        //Serial.println("nix");
        unsigned long currentMicros = micros();
        if((unsigned long)(currentMicros - start) >= 1){
          
          err = true;
        }
      }
      if(!err){
        int16_t readData;
        radio.read(&readData, sizeof(int16_t));
        temperature = readData;
      }
      radio.stopListening();
      clearCommands();
    }
    
  //  }
  //  tasten.clearAllButtons();
}
