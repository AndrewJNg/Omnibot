
int potValue = 0;
const int potPin = 36;

const int LPWMA = 33; const byte FrontLeft = 0;
int LAIN2 = 25;
int LAIN1 = 26;
int LSTBY = 27;
int LBIN1 = 14;
int LBIN2 = 12;
const int LPWMB = 13; const byte BackLeft = 1;

const int RPWMA = 5; const byte FrontRight = 2;
int RAIN2 = 17;
int RAIN1 = 16;
//int RSTBY = 34;
int RBIN1 = 4;
int RBIN2 = 2;
const int RPWMB = 15; const byte BackRight = 3;

void setup() {

  analogReadResolution(12);
  Serial.begin(115200);

  pinMode(LAIN2, OUTPUT);
  pinMode(LAIN1, OUTPUT);
  pinMode(LSTBY, OUTPUT);
  pinMode(LBIN1, OUTPUT);
  pinMode(LBIN2, OUTPUT);

  ledcSetup(FrontLeft, 5000, 16);
  ledcAttachPin(LPWMA , FrontLeft );

  ledcSetup(BackLeft, 5000, 16);
  ledcAttachPin(LPWMB, BackLeft);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode(RAIN2, OUTPUT);
  pinMode(RAIN1, OUTPUT);
  //  pinMode(RSTBY, OUTPUT);
  pinMode(RBIN1, OUTPUT);
  pinMode(RBIN2, OUTPUT);

  ledcSetup(FrontRight, 5000, 16);
  ledcAttachPin(RPWMA , FrontRight );

  ledcSetup(BackRight, 5000, 16);
  ledcAttachPin(RPWMB, BackRight);

}

void loop() {
  potValue = map(analogRead(potPin), 0, 4095, 0, 65535) ;
  //  ledcWrite(Led1Channel , potValue);
  Serial.println(potValue);

  digitalWrite(LSTBY, HIGH);
  
  digitalWrite(LAIN2, HIGH);
  digitalWrite(LAIN1, LOW);
  digitalWrite(LBIN1, HIGH);
  digitalWrite(LBIN2, LOW);
  ledcWrite(FrontLeft , potValue);
  ledcWrite(BackLeft , potValue);

  //  digitalWrite(RSTBY, HIGH);
  
  digitalWrite(RAIN2, HIGH);
  digitalWrite(RAIN1, LOW);
  digitalWrite(RBIN1, HIGH);
  digitalWrite(RBIN2, LOW);
  ledcWrite(FrontRight, potValue);
  ledcWrite(BackRight, potValue);
}
