#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(A0, 3); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";

    radio.read(&text, sizeof(text));
   
    Serial.print("received: ");
    Serial.println(text);
  }
}
