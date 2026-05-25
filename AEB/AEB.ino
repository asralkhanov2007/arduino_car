// ==========================
// AEB (Autonomous Emergency Braking)
// Arduino Smart Car Project
// ==========================

// Ultrasonic pins
#define TRIG_PIN A0
#define ECHO_PIN A1

// Motor A
#define ENA 5
#define IN1 8
#define IN2 9

// Motor B
#define ENB 6
#define IN3 10
#define IN4 11

long duration;
float distance;

void setup() {

  Serial.begin(9600);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("AEB System Initialized");
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Emergency braking distance
  if (distance <= 15) {

    stopCar();

    Serial.println("Obstacle detected! BRAKING!");

    delay(1000);


    delay(700);

    stopCar();

  } else {

    moveForward();
  }

  delay(100);
}

// ==========================
// Distance Function
// ==========================
float getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  // d = (0.0343 × t) / 2
  float dist = (0.0343 * duration) / 2;

  return dist;
}

// ==========================
// Motor Functions
// ==========================

void moveForward() {

  analogWrite(ENA, 180);
  analogWrite(ENB, 180);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
