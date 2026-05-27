# Arduino Smart Car Project

## Overview

This project is a collection of Arduino programs developed for a smart robotic car system. The repository contains multiple test modules and functional implementations used to build and verify different components of the car, including:

- DC motor control
- PWM speed control
- Ultrasonic obstacle detection
- Servo motor testing
- IR sensor testing
- Autonomous Emergency Braking (AEB)
- Advanced object detection and obstacle avoidance

The project is designed for educational and experimental purposes using Arduino-compatible hardware.

---

# Project Structure

```text
arduino_car-main/
│
├── AEB/                        # Autonomous Emergency Braking system
│   └── AEB.ino
│
├── IR_sesor/                   # IR sensor testing program
│   └── IR_sesor.ino
│
├── PWMspeed_test/              # PWM motor speed control test
│   └── PWMspeed_test.ino
│
├── motortest/                  # Basic motor functionality test
│   └── motortest.ino
│
├── objectDetectionPro/         # Advanced object detection project
│   └── objectDetectionPro.ino
│
├── obst/                       # Obstacle avoidance system
│   └── obst.ino
│
├── servo_test/                 # Servo motor testing
│   └── servo_test.ino
│
├── ultrasonic_test/            # Ultrasonic sensor distance measurement
│   └── ultrasonic_test.ino
│
├── AEB.pdf                     # Supporting documentation
└── Ultrasonic.pdf              # Ultrasonic sensor documentation
```

---

# Hardware Requirements

The following components are recommended for this project:

## Main Components

- Arduino UNO / Nano
- L298N motor driver or Adafruit Motor Shield
- HC-SR04 ultrasonic sensor
- SG90 servo motor
- IR obstacle or line tracking sensors
- DC motors with wheels
- Smart car chassis
- Jumper wires
- Battery pack

---

# Software Requirements

- Arduino IDE
- Servo Library
- AFMotor Library (required for `obst.ino`)

## Installing Required Libraries

### Servo Library
The Servo library is included by default in the Arduino IDE.

### AFMotor Library
To install the Adafruit Motor Shield library:

1. Open Arduino IDE
2. Go to:

```text
Sketch → Include Library → Manage Libraries
```

3. Search for:

```text
Adafruit Motor Shield Library
```

4. Install the library.

---

# Module Descriptions

## 1. Motor Test (`motortest`)

This program verifies that both DC motors are connected correctly and moving forward.

### Features

- Tests left and right motor rotation
- Uses PWM speed control
- Useful for initial hardware verification

### Main Pins

| Component | Pins |
|---|---|
| ENA | 5 |
| ENB | 6 |
| IN1 | 8 |
| IN2 | 9 |
| IN3 | 10 |
| IN4 | 11 |

---

## 2. Ultrasonic Sensor Test (`ultrasonic_test`)

This program measures distance using the HC-SR04 ultrasonic sensor.

### Features

- Reads object distance
- Displays results on Serial Monitor
- Useful for obstacle detection calibration

### Main Pins

| Component | Pins |
|---|---|
| Trigger Pin | A0 |
| Echo Pin | A1 |

### Output Example

```text
Distance: 23
Distance: 22
Distance: 24
```

---

## 3. Servo Test (`servo_test`)

This program tests servo motor movement.

### Features

- Rotates servo to multiple angles
- Useful for sensor scanning systems

### Servo Angles

- 0°
- 90°
- 180°

---

## 4. IR Sensor Test (`IR_sesor`)

This module reads values from four IR sensors.

### Features

- Reads digital sensor outputs
- Displays readings in Serial Monitor
- Useful for line tracking or object detection

### Sensor Pins

| Sensor | Pin |
|---|---|
| S1 | 2 |
| S2 | 3 |
| S3 | 4 |
| S4 | 7 |

---

## 5. PWM Speed Test (`PWMspeed_test`)

This module demonstrates speed control using PWM signals.

### Features

- Adjustable motor speed
- Combines motor driver control with sensors
- Useful for tuning car movement

---

## 6. Autonomous Emergency Braking (`AEB`)

This module implements a basic Autonomous Emergency Braking system.

### Features

- Detects obstacles using ultrasonic sensor
- Automatically stops motors when an object is too close
- Improves safety and collision prevention

### Main Functions

- Distance measurement
- Obstacle detection
- Automatic motor stopping

---

## 7. Obstacle Avoidance (`obst`)

This program enables autonomous obstacle avoidance.

### Features

- Uses ultrasonic sensor with servo scanning
- Detects left and right free space
- Controls four motors through Adafruit Motor Shield
- Automatically changes direction to avoid collisions

### Included Libraries

```cpp
#include <Servo.h>
#include <AFMotor.h>
```

---

## 8. Advanced Object Detection (`objectDetectionPro`)

This module is an advanced implementation combining:

- Ultrasonic sensing
- IR sensors
- Motor control
- Servo scanning

### Purpose

Designed for smarter navigation and improved autonomous driving behavior.

---

# Wiring Overview

## Typical Motor Driver Connections

| Arduino Pin | Motor Driver |
|---|---|
| 5 | ENA |
| 6 | ENB |
| 8 | IN1 |
| 9 | IN2 |
| 10 | IN3 |
| 11 | IN4 |

---

## Ultrasonic Sensor Connections

| Ultrasonic Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| Trig | A0 |
| Echo | A1 |

---

## IR Sensor Connections

| IR Sensor | Arduino Pin |
|---|---|
| OUT1 | 2 |
| OUT2 | 3 |
| OUT3 | 4 |
| OUT4 | 7 |

---

# How to Run

## Step 1 — Open Arduino IDE

Launch the Arduino IDE on your computer.

## Step 2 — Connect Arduino

Connect your Arduino board using USB.

## Step 3 — Open Desired Project

Open one of the `.ino` files.

Example:

```text
motortest/motortest.ino
```

## Step 4 — Select Board and Port

Go to:

```text
Tools → Board
```

Select your Arduino board.

Then select the correct COM/USB port:

```text
Tools → Port
```

## Step 5 — Upload Code

Click the Upload button.

## Step 6 — Open Serial Monitor

For sensor testing modules, open:

```text
Tools → Serial Monitor
```

Set baud rate to:

```text
9600
```

---

# Educational Objectives

This project demonstrates several important robotics and embedded systems concepts:

- Embedded programming with Arduino
- PWM motor speed control
- Sensor integration
- Obstacle detection algorithms
- Autonomous navigation
- Real-time hardware interaction
- Basic robotics system design

---

# Future Improvements

Possible future enhancements include:

- Bluetooth remote control
- Mobile application integration
- Wi-Fi communication
- Line following algorithm
- AI-based object recognition
- Camera integration
- Battery monitoring system
- PID motor control

---

# Troubleshooting

## Motors Not Moving

- Check motor driver wiring
- Verify external power supply
- Confirm PWM pins are connected correctly

## Ultrasonic Sensor Returns Zero

- Check Trigger and Echo connections
- Verify sensor power
- Ensure correct pin definitions

## Servo Not Rotating

- Confirm servo signal pin
- Check power supply stability
- Verify Servo library installation

## Upload Errors

- Select correct COM port
- Close Serial Monitor before uploading
- Ensure Arduino drivers are installed

---

# License

This project is intended for educational and learning purposes.

---

