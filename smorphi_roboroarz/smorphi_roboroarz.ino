// DO NOT DELETE / COMMENT THESE LINES !!!!

#include "HUSKYLENS.h"       // Library for HuskyLens
#include <smorphi_single.h>  // Library for Smorphi
#include "SoftwareSerial.h"  // Library for Software Serial

#define MAX_SPEED 170

// volatile unsigned long delay;
// Structure example to receive data
// Must match the sender structure
Smorphi_single my_robot;
HUSKYLENS huskylens;
//SoftwareSerial myHuskySerial(26, 27);
SoftwareSerial myHuskySerial(16, 17);

// DO NOT DELETE / COMMENT THESE LINES !!!!

// Setting up variables and required flags


int right_sensor_status = my_robot.module1_sensor_status(4);
int bottom_right_sensor_status = my_robot.module1_sensor_status(2);
int left_sensor_status = my_robot.module1_sensor_status(10);
int bottom_left_sensor_status = my_robot.module1_sensor_status(0);
// Husky color_detected status written as variable

int color_signature;
int command_block;

int RED_COUNT;
int GREEN_COUNT;
int BLUE_COUNT;
int LEFT_COUNT;
int STRAIGHT_COUNT;
int RIGHT_COUNT;
int UTURN_COUNT;

extern int Flag;



int last_command = 0;

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  myHuskySerial.begin(9600);  //Baud rate for HuskyLens communication. Can change from GUI of the HuskyLens

  Serial.print("Initializing....");

  my_robot.BeginSmorphi_single();
  while (!huskylens.begin(myHuskySerial)) {
    Serial.println(F("Begin failed!"));
    delay(100);
  }
  my_robot.BeginSmorphi_single();
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  // DO NOT DELETE / COMMENT THESE LINES !!!!


  red_on();
  delay(1000);
  led_off();
  green_on();
  delay(1000);
  led_off();
  blue_on();
  delay(1000);
  led_off();
  white_on();
  delay(1000);
  led_off();
}

void loop() {

  // DO NOT DELETE / COMMENT THESE LINES !!!!
  sensor_initialisation();
  int x = 0;
  if (huskylens.request()) {
    if (huskylens.available()) {
      // HUSKYLENSResult result = huskylens.read();
      // Serial.println(F("###########"));
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      if (result.command == COMMAND_RETURN_BLOCK) {
        x = result.ID;
      }
    }
  } else {
    Serial.println("Error!");
  }
  int i = 1;
  switch (x) {
    case 1:
      //Insert your code here for TagID1
      red_detected();
      RED_COUNT += 1;
      break;
    case 2:
      //Insert your code here for TagID2
      green_detected();
      GREEN_COUNT += 1;
      break;
    case 3:
      //Insert your code here for TagID3
      blue_detected();
      BLUE_COUNT += 1;
      break;
    case 4:
      //Insert your code here for TagID4
      Serial.println("LEFT TURN");
      last_command = 1;
      left_turn();
      LEFT_COUNT += 1;
      break;
    case 5:
      //Insert your code here for TagID5
      Serial.println("STRAIGHT");
      white_on();
      last_command = 2;
      delay(4000);
      //straight_turn();
      STRAIGHT_COUNT += 1;
      led_off();
      break;
    case 6:
      //Insert your code here for TagID6
      Serial.println("RIGHT");
      last_command = 3;
      right_turn();
      RIGHT_COUNT += 1;
      break;
    case 7:
      //Insert your code here for TagID7
      Serial.println("U TURN");
      last_command = 4;
      u_turn();
      UTURN_COUNT += 1;
      break;
    default:
      //Insert your code here for default action when no QR Tag is detected;
      // straight_turn();
      movements();
      1 == 1;  //DUMMY COMMAND (CAN IGNORE)
  }

  if (last_command == 1)

  Serial.print("RED: ");
  Serial.print(RED_COUNT);
  Serial.print("GREEN: ");
  Serial.print(GREEN_COUNT);
  Serial.print("BLUE: ");
  Serial.print(BLUE_COUNT);
  Serial.print("LEFT TURN: ");
  Serial.print(LEFT_COUNT);
  Serial.print("STRAIGHT TURN: ");
  Serial.print(STRAIGHT_COUNT);
  Serial.print("RIGHT TURN: ");
  Serial.println(RIGHT_COUNT);
}

void printResult(HUSKYLENSResult result) {

  // DO NOT DELETE / COMMENT THESE LINES !!!!


  if (result.command == COMMAND_RETURN_BLOCK) {
    // Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    Serial.println(result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println("Wrong mode");
    // Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}

void red_on() {
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}

void green_on() {
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
}

void blue_on() {
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
}

void white_on() {
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
}

void led_off() {
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}

void red_detected() {
  // unsigned long delay = millis();
  red_on();
  Serial.println("RED");
  delay(500);
  // while (delay - millis() <= 2000) {}
  led_off();
}
void green_detected() {
  // unsigned long delay = millis();
  green_on();
  Serial.println("GREEN");
  delay(500);
  // while (delay - millis() <= 2000) {}
  led_off();
}
void blue_detected() {
  // unsigned long delay = millis();
  blue_on();
  Serial.println("BLUE");
  delay(500);
  // while (delay - millis() <= 2000) {}
  led_off();
}

void left_turn() {
  white_on();
  my_robot.CenterPivotLeft(290);
  delay(1000);
  led_off();

}
void right_turn() {
  white_on();
  my_robot.CenterPivotRight(290);
  delay(1000);
  led_off();
}
// void straight_turn() {
//   my_robot.MoveForward(MAX_SPEED);
//   // delay(1000);
// }
void u_turn() {
  white_on();
  Flag+= 1;
  my_robot.CenterPivotLeft(MAX_SPEED);
  delay(6000);
  led_off();
  
}