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
// SERVO
// ======================================================
#define SERVO_PIN 13

Servo scanner;

// ======================================================
// VARIABLES
// ======================================================
int distanceFront;
int distanceLeft;
int distanceRight;

int speedCar = 200;

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

  // Ultrasonic
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo
  scanner.attach(SERVO_PIN);

  scanner.write(90);

  delay(1000);
}

// ======================================================
// MAIN LOOP
// ======================================================
void loop() {

  distanceFront = readDistance();

  Serial.print("Front: ");
  Serial.println(distanceFront);

  // ==================================================
  // PATH CLEAR
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

    backward();
    delay(400);

    stopMotors();
    delay(200);

    // =======================
    // LOOK LEFT
    // =======================
    scanner.write(160);
    delay(700);

    distanceLeft = readDistance();

    Serial.print("Left: ");
    Serial.println(distanceLeft);

    // =======================
    // LOOK RIGHT
    // =======================
    scanner.write(20);
    delay(700);

    distanceRight = readDistance();

    Serial.print("Right: ");
    Serial.println(distanceRight);

    // CENTER SERVO
    scanner.write(90);
    delay(300);

    // ==================================================
    // DECISION
    // ==================================================

    // BOTH OPEN
    if (distanceLeft > 30 && distanceRight > 30) {

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

    // BOTH BLOCKED
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
// DISTANCE FUNCTION
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
// FORWARD
// ======================================================
void forward() {

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  // LEFT SIDE
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // RIGHT SIDE
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================================
// BACKWARD
// ======================================================
void backward() {

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  // LEFT SIDE
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // RIGHT SIDE
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================================================
// LEFT TURN
// ======================================================
void left() {

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  // LEFT WHEELS BACKWARD
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // RIGHT WHEELS FORWARD
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ======================================================
// RIGHT TURN
// ======================================================
void right() {

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  // LEFT WHEELS FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // RIGHT WHEELS BACKWARD
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ======================================================
// STOP
// ======================================================
void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}