const byte LED1 = 4; const byte Led1Channel = 0;
const byte LED2 = 18; const byte Led2Channel = 1;
const byte LED3 = 23; const byte Led3Channel = 2;



void setup() {
    // LED 1
    ledcSetup(Led1Channel , 5000, 8);
    ledcAttachPin(LED1, Led1Channel);

  // LED 2
  ledcSetup(Led2Channel, 5000, 8);
  ledcAttachPin(LED2, Led2Channel);

  // LED 3
  ledcSetup(Led3Channel, 5000, 8);
  ledcAttachPin(LED3, Led3Channel);

}

void loop() {
  for (int x = 0; x < 255; x++)
  {
    ledcWrite(Led1Channel , x);
    delay(15);
  } 
  ledcWrite(Led1Channel , 0);

  for (int x = 0; x < 255; x++)
  {
    ledcWrite(Led2Channel, x);
    delay(15);
  }
  ledcWrite(Led2Channel , 0);

  for (int x = 0; x < 255; x++)
  {
    ledcWrite(Led3Channel, x);
    delay(15);
  }
  ledcWrite(Led3Channel , 0);

}
