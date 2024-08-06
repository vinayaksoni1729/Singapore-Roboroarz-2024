# Singapore Roboroarz 2024 - Line Follower Robot

This project features a cutting-edge line-following robot powered by HuskyLens and Smorphi technologies. The robot is designed to detect colored tags and perform corresponding maneuvers with high precision and reliability.


https://github.com/user-attachments/assets/3255ec22-ee8a-4995-b4d2-8ad2d00e9feb




## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Project Overview
The Singapore Roboroarz 2024 Line Follower Robot utilizes a HuskyLens vision sensor and Smorphi modules to navigate a track by detecting color tags. Depending on the detected color, the robot executes specific commands such as turning left, right, or making a U-turn. The project demonstrates advanced integration of sensor data processing and motor control for autonomous navigation.

https://github.com/user-attachments/assets/22dcfa16-bd1f-4482-98b0-e09ea3e68597

## Hardware Requirements
- [HuskyLens](https://www.husky-lens.com/) Vision Sensor
- [Smorphi Single](https://www.smorphi.com/) Modules
- Microcontroller (e.g., Arduino)
- Transistor-based sensors for color detection
- LEDs for visual feedback
- Robot chassis and motors

## Software Requirements
- Arduino IDE
- HuskyLens Library
- Smorphi Library
- SoftwareSerial Library

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Roboroarz2024-LineFollower.git
   cd Roboroarz2024-LineFollower
   ```
2. Install the required libraries in the Arduino IDE:
   - HuskyLens
   - Smorphi
   - SoftwareSerial

https://github.com/user-attachments/assets/72f20679-041d-4ffe-a7cf-b168f209a9d2


3. Open the `line_follower.ino` file in the Arduino IDE and upload it to your microcontroller.

## Usage
1. Set up your hardware according to the [Hardware Requirements](#hardware-requirements) section.
2. Upload the code to your microcontroller.
3. Power on the robot and place it on the track.
4. Observe the robot as it follows the line and responds to colored tags with corresponding maneuvers.

## Code Explanation
The code initializes the HuskyLens and Smorphi modules and sets up the necessary sensor inputs and LED outputs. In the `loop` function, the robot continuously checks for detected color tags and executes the corresponding movement commands. The results are printed to the Serial Monitor for debugging and analysis.

```cpp
#include "HUSKYLENS.h"       // Library for HuskyLens
#include <smorphi_single.h>  // Library for Smorphi
#include "SoftwareSerial.h"  // Library for Software Serial

#define MAX_SPEED 170

Smorphi_single my_robot;
HUSKYLENS huskylens;
SoftwareSerial myHuskySerial(16, 17);

int right_sensor_status = my_robot.module1_sensor_status(4);
int bottom_right_sensor_status = my_robot.module1_sensor_status(2);
int left_sensor_status = my_robot.module1_sensor_status(10);
int bottom_left_sensor_status = my_robot.module1_sensor_status(0);

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
  Serial.begin(115200);
  myHuskySerial.begin(9600);
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
  sensor_initialisation();
  int x = 0;
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      if (result.command == COMMAND_RETURN_BLOCK) {
        x = result.ID;
      }
    }
  } else {
    Serial.println("Error!");
  }
  switch (x) {
    case 1:
      red_detected();
      RED_COUNT += 1;
      break;
    case 2:
      green_detected();
      GREEN_COUNT += 1;
      break;
    case 3:
      blue_detected();
      BLUE_COUNT += 1;
      break;
    case 4:
      Serial.println("LEFT TURN");
      last_command = 1;
      left_turn();
      LEFT_COUNT += 1;
      break;
    case 5:
      Serial.println("STRAIGHT");
      white_on();
      last_command = 2;
      delay(4000);
      STRAIGHT_COUNT += 1;
      led_off();
      break;
    case 6:
      Serial.println("RIGHT");
      last_command = 3;
      right_turn();
      RIGHT_COUNT += 1;
      break;
    case 7:
      Serial.println("U TURN");
      last_command = 4;
      u_turn();
      UTURN_COUNT += 1;
      break;
    default:
      movements();
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
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println("Wrong mode");
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
  red_on();
  Serial.println("RED");
  delay(500);
  led_off();
}
void green_detected() {
  green_on();
  Serial.println("GREEN");
  delay(500);
  led_off();
}
void blue_detected() {
  blue_on();
  Serial.println("BLUE");
  delay(500);
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
void u_turn() {
  white_on();
  Flag += 1;
  my_robot.CenterPivotLeft(MAX_SPEED);
  delay(6000);
  led_off();
}
```

## Contributing
We welcome contributions from the community! If you'd like to contribute, please fork the repository and create a pull request with your changes.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements
- [HuskyLens](https://www.husky-lens.com/)
- [Smorphi](https://www.smorphi.com/)
- All team members and contributors

---

Feel free to customize this README to better fit your project and add any additional sections or details you find necessary.
