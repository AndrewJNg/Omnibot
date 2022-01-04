
int pot_Value = 0;
const int pot_Pin = 36;
const byte battMonitor_Pin = 32;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PS3
#include <Ps3Controller.h>

int player = 0;
int battery = 0;

int stick_LX;
int stick_LY;
int stick_RX;
int stick_RY;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  motor control pin layout   [ Left Front, Right Front , Back Left , Back Right]
const byte motorPin1[] =  {26, 4, 14, 16};
const byte motorPin2[] = {25, 2, 12, 17};
const byte motorPWM[] = {33, 15, 13, 5};
const byte motorChannel[] = {0, 1, 2, 3};
const byte motorSTBY[] = {27};

int motor_Speed[] = {0, 0, 0, 0};
const byte PWM_resolution = 8;//16;
const int PWM_resolution_max_value = 255;//65536;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ROS message system
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

//geometry_msgs::Twist node_msg;
//ros::Publisher chatter("chatter", &str_msg);

float LX_node = 0;
float LY_node = 0;
float RX_node = 0;
float RY_node = 0;

void received_move( const geometry_msgs::Twist& node_msg) {

  LX_node = node_msg.linear.x;
  LY_node = node_msg.linear.y;
  RX_node = node_msg.angular.z;
  RY_node = 0;
  //digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
}

ros::Subscriber<geometry_msgs::Twist> sub("robot_move", &received_move );


void loop() {

  //  pot_Value = map(analogRead(pot_Pin), 0, 4095, -65535, 65535) ;
  //    int Speed[] = {pot_Value, -pot_Value, -pot_Value, pot_Value};
  //  Serial.println(pot_Value);
  // Speed[] = {0, 0, 0, 0};

  //  OLED_display();
  PS3_move(LX_node, LY_node, RX_node, RY_node);
  //PS3_move(stick_LX, stick_LY, stick_RX , stick_RY);

  nh.spinOnce();
  OLED.clearDisplay();
  OLED.setTextSize(1);      // Normal 1:1 pixel scale
  OLED.setTextColor(SSD1306_WHITE); // Draw white text
  OLED.setCursor(0, 0);     // Start at top-left corner
  LX_node =500;
  OLED.print(LX_node);
  OLED.display();
  delay(1000);
}
