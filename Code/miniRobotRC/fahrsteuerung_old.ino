void manualDigitalDrive() {
  bool goOn = false;
 // while(!tasten.getButtonCycle(buttonL1)) {
    clearCommands();
    if(!tasten.getAnyPressed()) {
      //lcd.clear();
      lcd.println("Warte...");
    }
    if(tasten.checkButton(buttonB) || tasten.checkButton(buttonUp)) {
            pwmA = -215;
            pwmB = -255;
            //lcd.clear();
            lcd.println("geradeaus fahren");
            goOn =true;
    }
    if(tasten.checkButton(buttonC) || tasten.checkButton(buttonDown)) {
            pwmA = 100;
            pwmB = 255;
            //lcd.clear();
            lcd.println("rueckwaerts fahren");
            goOn =true;
     }
    if(tasten.checkButton(buttonRight)) {
        pwmA = -100;  //rechter Motor
        pwmB = 100;
        //lcd.clear();
        lcd.println("rechts lenken");
            goOn =true;
    } 
    if(tasten.checkButton(buttonLeft)) {
        pwmB = -100;
        pwmA = 100;
        //lcd.clear();
        lcd.println("links lenken");
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
  //  }
  //  tasten.clearAllButtons();
}
