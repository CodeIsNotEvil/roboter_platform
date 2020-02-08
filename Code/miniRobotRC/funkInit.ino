void funkInit() {
  radio.begin();
  
  radio.openWritingPipe(address);
  radio.openReadingPipe(0, address2);
  radio.setPALevel(RF24_PA_MAX); 
  radio.stopListening();
}
