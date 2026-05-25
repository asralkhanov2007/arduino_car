int s1 = 2;
int s2 = 3;
int s3 = 4;
int s4 = 7;

void setup() {

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  Serial.begin(9600);
}

void loop() {

  Serial.print(digitalRead(s1));
  Serial.print(" ");

  Serial.print(digitalRead(s2));
  Serial.print(" ");

  Serial.print(digitalRead(s3));
  Serial.print(" ");

  Serial.println(digitalRead(s4));

  delay(200);
}
