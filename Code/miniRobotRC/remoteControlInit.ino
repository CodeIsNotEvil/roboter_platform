void remoteControlInit() {
//Timer2 fuer 1ms initialisieren
  Timer2.initTimer2();
  Timer2.enableTimer2Interrupt();
//Hintergrundbeleuchtung pwm
  pwmBL.initOCR1B();
//Pegelwandler ein
  pinMode(_OE_LEVEL, OUTPUT);
  digitalWrite(_OE_LEVEL, HIGH);
//Hintergrundbeleuchtung an  
  pinMode(BL, OUTPUT);
  BRIGHTNESS = 30;
//LCD init,   invert, vop, tempcoef, bias  
  lcd.begin(false, 0xB1, 0x04, 0x12);
  lcd.clear();
//erster Taster check
  tasten.checkButtons();
}
