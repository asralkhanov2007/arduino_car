#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo S1;

int pos;
const int trig = 6;
const int echo = 10;
int right, left;

float timing, distance;

void setup() {
  // put your setup code here, to run once:
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  S1.attach(9);
  S1.write(90);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);

  digitalWrite(trig, LOW);
  Serial.begin(9600);
}

void loop() {
  float d = get_distance();
  Serial.println(d);
  if (d < 15 and (d != 4.44) and (d!=4.42))
  {
    Serial.print("stop!");
    release();
    look(S1);
  }
  else 
  {
    int speed = 45;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);

    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
}

void look(Servo servo)
{

  servo.write(0);
  delay(1000);
  float d1 = get_distance(), d2, d3;
  Serial.println("Right: ");
  Serial.println(d1);
  servo.write(90);
  delay(1000);
  d2 = get_distance();
  Serial.println("Forward: ");
  Serial.println(d2);
  servo.write(180);
  delay(1000);
  d3 = get_distance();
  Serial.println("Left: ");
  Serial.println(d3);
  S1.write(90);
  if ((d2 < 15) and ((d1<10) or (d3<10)))
  {
    if (d1 > 10 and d3 < 10)
    {
      turn_right();
      delay(450);
      release();
    }
    else if (d3> 10  and d1 < 10)
    {
      turn_left();
      delay(450);
      release();
    }

  }
  else
  {
    turn_left();
    delay(450);
    release();
  }
  delay(1000);
}

float get_distance()
{
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  timing = pulseIn(echo, HIGH);
  distance = (timing * 0.034)/2;
  return distance;
}

int turn_left()
{
  int speed = 200;
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

int turn_right()
{
  int speed = 200;
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void release()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
