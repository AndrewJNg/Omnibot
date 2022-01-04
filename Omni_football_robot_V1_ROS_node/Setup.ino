void setup() {
  analogReadResolution(12);
  Serial.begin(115200);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("01:02:03:04:05:06");

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // movement setup
  for (int x = 0; x < sizeof(motorSTBY); x++)
  {
    pinMode(motorSTBY[x], OUTPUT);
  }
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    pinMode(motorPin1[x], OUTPUT);
    pinMode(motorPin2[x], OUTPUT);
    ledcSetup(motorChannel[x], 5000, PWM_resolution);
    ledcAttachPin(motorPWM[x] , motorChannel[x] );
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // User_interface setup
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  OLED.clearDisplay();
  OLED.display();


  while (!Ps3.isConnected())
  {
    motor(motor_Speed);
    OLED_display();
  }
}