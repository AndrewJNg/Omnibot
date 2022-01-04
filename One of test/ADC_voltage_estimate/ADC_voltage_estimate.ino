float R2 = 10.00;  // in kOhm
float R1 = 9.85 + 9.77;

void setup() {
  analogReadResolution(12);
  Serial.begin(115200);
}

void loop() {
  float voltage = ((map(analogRead(15), 0, 4095, 0, 3300)) / 1000.0000 + 0.15) / (R2 / (R1 + R2));
  Serial.println(voltage, 4);
}
