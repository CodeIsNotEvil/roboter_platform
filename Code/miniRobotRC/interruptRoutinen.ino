//HIER KOMMT ALLES REIN WAS 1 MAL PRO ms AUFGERUFEN WERDEN SOLL!!!
ISR(TIMER2_COMPA_vect) {
  tasten.checkButtons();
  renderTime++;
  if(renderTime >= renderTimeout) {
    lcd.clear();
    for(uint8_t i = 0; i < sizeof(lcdLines); i++) {
      lcd.gotoXY(0, i);
      lcd.print(lcdLines[i]);  
    }
    lcd.renderAll();
    renderTime = 0;
  }
}
//ALLE anderen ISR kommen HIER drunter!!!
