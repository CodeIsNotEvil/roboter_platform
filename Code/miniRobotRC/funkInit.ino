void funkInit() {
  radio.begin();
  
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address2);
  radio.setPALevel(RF24_PA_MAX); 
  radio.stopListening();
}
