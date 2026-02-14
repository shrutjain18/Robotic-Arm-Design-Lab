// Motor A pins
int motorA_IN1 = 27;
int motorA_IN2 = 26;
int motorA_EN  = 14;

// Motor B pins
int motorB_IN3 = 25;
int motorB_IN4 = 33;
int motorB_EN  = 32;

void setup() {
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorA_EN, OUTPUT);

  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);
  pinMode(motorB_EN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Testing 2 DC Motors (Simultaneous)");
}

void loop() {

  // Both motors forward
  Serial.println("Both motors FORWARD");
  digitalWrite(motorA_EN, HIGH);
  digitalWrite(motorB_EN, HIGH);

  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);

  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);

  delay(3000);

  // Stop both motors
  Serial.println("Both motors STOP");
  digitalWrite(motorA_EN, LOW);
  digitalWrite(motorB_EN, LOW);
  delay(1000);

  // Both motors backward
  Serial.println("Both motors BACKWARD");
  digitalWrite(motorA_EN, HIGH);
  digitalWrite(motorB_EN, HIGH);

  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);

  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);

  delay(3000);

  // Stop both motors
  Serial.println("Both motors STOP");
  digitalWrite(motorA_EN, LOW);
  digitalWrite(motorB_EN, LOW);
  delay(1000);
}
