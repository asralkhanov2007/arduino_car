#include <Servo.h>

// ======================================================
// MOTOR DRIVER PINS
// ======================================================
#define ENA 5
#define IN1 9
#define IN2 11

#define ENB 6
#define IN3 10
#define IN4 8

// ======================================================
// IR SENSOR PINS
// ======================================================
#define IR1 2
#define IR2 3
#define IR3 4
#define IR4 7

// ======================================================
// ULTRASONIC SENSOR PINS
// ======================================================
#define TRIG A0
#define ECHO A1

// ======================================================
// SERVO PIN
// ======================================================
#define SERVO_PIN 13

Servo scanner;

// ======================================================
// PWM SPEED CONTROL (0-255)
// ======================================================
int forwardSpeed = 220;
int turnSpeed = 180;
int reverseSpeed = 170;

// ======================================================
// DISTANCE VARIABLES
// ======================================================
int distanceFront;
int distanceLeft;
int distanceRight;

// ======================================================
// SETUP
// ======================================================
void setup() {

  Serial.begin(9600);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // IR Sensors
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  // Ultrasonic
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo
  scanner.attach(SERVO_PIN);

  // Center position
  scanner.write(90);

  delay(1000);
}

// ======================================================
// MAIN LOOP
// ======================================================
void loop() {

  // Read front obstacle distance
  distanceFront = readDistance();

  Serial.print("Front Distance: ");
  Serial.println(distanceFront);

  // ==================================================
  // PATH CLEAR -> MOVE FORWARD
  // ==================================================
  if (distanceFront > 30 || distanceFront == 0) {

    forward();
  }

  // ==================================================
  // OBSTACLE DETECTED
  // ==================================================
  else {

    stopMotors();
    delay(300);

    // Move backward slightly
    backward();
    delay(400);

    stopMotors();
    delay(200);

    // ==================================================
    // LOOK LEFT
    // ==================================================
    scanner.write(160);
    delay(700);

    distanceLeft = readDistance();

    Serial.print("Left Distance: ");
    Serial.println(distanceLeft);

    // ==================================================
    // LOOK RIGHT
    // ==================================================
    scanner.write(20);
    delay(700);

    distanceRight = readDistance();

    Serial.print("Right Distance: ");
    Serial.println(distanceRight);

    // Return servo to center
    scanner.write(90);
    delay(300);

    // ==================================================
    // DECISION MAKING
    // ==================================================

    // BOTH SIDES OPEN
    if (distanceLeft > 30 && distanceRight > 30) {

      // Choose larger free space
      if (distanceLeft >= distanceRight) {

        left();
        delay(900);

      } else {

        right();
        delay(900);
      }
    }

    // ONLY LEFT OPEN
    else if (distanceLeft > 30) {

      left();
      delay(900);
    }

    // ONLY RIGHT OPEN
    else if (distanceRight > 30) {

      right();
      delay(900);
    }

    // BOTH SIDES BLOCKED
    else {

      backward();
      delay(800);

      right();
      delay(1400);
    }

    stopMotors();
    delay(200);
  }
}

// ======================================================
// ULTRASONIC DISTANCE FUNCTION
// ======================================================
int readDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  int distance = duration * 0.034 / 2;

  return distance;
}

// ======================================================
// MOVE FORWARD
// ======================================================
void forward() {

  analogWrite(ENA, forwardSpeed);
  analogWrite(ENB, forwardSpeed);

  // LEFT MOTORS FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // RIGHT MOTORS FORWARD
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================================
// MOVE BACKWARD
// ======================================================
void backward() {

  analogWrite(ENA, reverseSpeed);
  analogWrite(ENB, reverseSpeed);

  // LEFT MOTORS BACKWARD
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // RIGHT MOTORS BACKWARD
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================================================
// TURN LEFT
// ======================================================
void left() {

  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);

  // LEFT SIDE BACKWARD
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // RIGHT SIDE FORWARD
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================================
// TURN RIGHT
// ======================================================
void right() {

  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);

  // LEFT SIDE FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // RIGHT SIDE BACKWARD
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================================================
// STOP MOTORS
// ======================================================
void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
