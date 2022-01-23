
void motor(int Speed[])
{ // Translate Speed from  -255 to 255 or higher resolution to motor driver
  for (int x = 0; x < sizeof(motorSTBY); x++)
  {
    digitalWrite(motorSTBY[x], HIGH);
  }

  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    if (Speed[x] > PWM_resolution_max_value) Speed[x] = PWM_resolution_max_value;
    else if (Speed[x] < -PWM_resolution_max_value) Speed[x] = -PWM_resolution_max_value;

    if (Speed[x] > 0)
    { // Forward
      digitalWrite(motorPin1[x], LOW);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else if (Speed[x] < 0)
    { // Reverse
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], LOW);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else
    { //Stop
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , 0);
    }
  }
}

void PS3_move(int LX, int LY, int RX , int RY)
{
  float angle = PS3_LeftAnalogStickAngle (LX, LY)  ;
  float Speed_total_percent = PS3_LeftAnalogStickSpeed(LX, LY);
  float turn_Speed = 0;
  if (abs(RX) > 15) turn_Speed = map(RX, -128, 127 , -PWM_resolution_max_value, PWM_resolution_max_value);


  motor_Speed[0] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[1] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[2] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[3] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);

  motor_Speed[0] = motor_Speed[0] + turn_Speed;
  motor_Speed[1] = motor_Speed[1] - turn_Speed;
  motor_Speed[2] = motor_Speed[2] + turn_Speed;
  motor_Speed[3] = motor_Speed[3] - turn_Speed;

  //  float Speed_Y_percent = Speed_total_percent * cos(angle);
  //  float Speed_X_percent = Speed_total_percent * sin(angle);
  //  long Speed_Y_motor = map(Speed_Y_percent * 100, 0, 10000, 0, PWM_resolution_max_value*2);
  //  long Speed_X_motor = map(Speed_X_percent * 100, 0, 10000, 0, PWM_resolution_max_value*2);
  //      motor_Speed[0] =  Speed_X_percent/2;
  //      motor_Speed[1] = Speed_Y_percent - Speed_X_percent/2;
  //      motor_Speed[2] = Speed_Y_percent - Speed_X_percent/2;
  //      motor_Speed[3] = Speed_X_percent/2;

  /*Serial.print(angle * 180 / PI);
  Serial.print("    ");
  Serial.print(Speed_total_percent);
  Serial.print("    ");
  Serial.print(motor_Speed[0] );
  Serial.print("    ");
  Serial.print(motor_Speed[1]);
  Serial.print("    ");
  Serial.print(motor_Speed[2] );
  Serial.print("    ");
  Serial.print(motor_Speed[3] );
  Serial.print("    ");
  Serial.println();
*/

  //  Serial.print(Speed_X_motor);
  //  Serial.print("    ");
  //  Serial.print(Speed_Y_motor);
  //  Serial.print("    ");
  //  Serial.println("");





  motor(motor_Speed);

}

void PS3_move_DPAD()
{
  int Speed = pot_Value = map(analogRead(pot_Pin), 0, 4095, 0, PWM_resolution_max_value) ;

  if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0) && (Ps3.data.button.l1 == 0) && (Ps3.data.button.r1 == 0))
  {
    motor_Speed[0] = 0;
    motor_Speed[1] = 0;
    motor_Speed[2] = 0;
    motor_Speed[3] = 0;
  }
  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
  {
    motor_Speed[0] = +Speed;
    motor_Speed[1] = +Speed;
    motor_Speed[2] = +Speed;
    motor_Speed[3] = +Speed;
  }
  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
  {
    motor_Speed[0] = +Speed;
    motor_Speed[1] = 0;
    motor_Speed[2] = 0;
    motor_Speed[3] = +Speed;
  }
  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
  {
    motor_Speed[0] = +Speed;
    motor_Speed[1] = -Speed;
    motor_Speed[2] = -Speed;
    motor_Speed[3] = +Speed;
  }
  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 0))
  {
    motor_Speed[0] = 0;
    motor_Speed[1] = -Speed;
    motor_Speed[2] = -Speed;
    motor_Speed[3] = 0;
  }
  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 0))
  {
    motor_Speed[0] = -Speed;
    motor_Speed[1] = -Speed;
    motor_Speed[2] = -Speed;
    motor_Speed[3] = -Speed;
  }
  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 1))
  {
    motor_Speed[0] = -Speed;
    motor_Speed[1] = 0;
    motor_Speed[2] = 0;
    motor_Speed[3] = -Speed;
  }
  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 1))
  {
    motor_Speed[0] = -Speed;
    motor_Speed[1] = +Speed;
    motor_Speed[2] = +Speed;
    motor_Speed[3] = -Speed;
  }
  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 1))
  {
    motor_Speed[0] = 0;
    motor_Speed[1] = Speed;
    motor_Speed[2] = Speed;
    motor_Speed[3] = 0;
  }
  else if ((Ps3.data.button.l1 == 1) && (Ps3.data.button.r1 == 0))
  {
    motor_Speed[0] = -Speed;
    motor_Speed[1] = Speed;
    motor_Speed[2] = -Speed;
    motor_Speed[3] = Speed;
  }
  else if ((Ps3.data.button.l1 == 0) && (Ps3.data.button.r1 == 1))
  {
    motor_Speed[0] = Speed;
    motor_Speed[1] = -Speed;
    motor_Speed[2] = Speed;
    motor_Speed[3] = -Speed;
  }
  else
  {
    motor_Speed[0] = 0;
    motor_Speed[1] = 0;
    motor_Speed[2] = 0;
    motor_Speed[3] = 0;
  }

  motor(motor_Speed);
}
