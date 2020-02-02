//HIER KOMMT ALLES REIN WAS 1 MAL PRO ms AUFGERUFEN WERDEN SOLL!!!
ISR(TIMER2_COMPA_vect) {
  tasten.checkButtons();
  lcd.renderAll();
}
//ALLE anderen ISR kommen HIER drunter!!!
