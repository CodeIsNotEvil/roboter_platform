#define xPin A5
#define yPin A6
int16_t xValue = 0;
int16_t yValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  koordinaten(analogRead(xPin), analogRead(yPin));

  Serial.println("X: ");
  Serial.println(xValue);
  Serial.println("Y: ");
  Serial.println(yValue);

  delay(200);

}

void koordinaten(uint16_t x, uint16_t y) {
  //9-bit reichen, der ADC schafft bestenfalls 8-bit praezision
  x = x >> 1;
  y = y >> 1;
  xValue = map(x, 0, 511, -255, 255);
  yValue = map(y, 0, 511, 255, -255);
}
