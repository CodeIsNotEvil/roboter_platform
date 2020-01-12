void funkInit() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX); 
  radio.stopListening();
}
