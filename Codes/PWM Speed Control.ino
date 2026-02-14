// Motor A pins
int motorA_IN1 = 27;
int motorA_IN2 = 26;
int motorA_EN  = 14;

// Motor B pins
int motorB_IN3 = 25;
int motorB_IN4 = 33;
int motorB_EN  = 32;

// PWM properties
const int freq = 30000;
const int resolution = 8;   // 0–255
const int pwmChannelA = 0;
const int pwmChannelB = 1;

// Duty cycle limits
const int MIN_DUTY = 177;    // ~30%
const int MAX_DUTY = 255;

void setup() {
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);

  // Attach PWM channels
  ledcAttachChannel(motorA_EN, freq, resolution, pwmChannelA);
  ledcAttachChannel(motorB_EN, freq, resolution, pwmChannelB);

  Serial.begin(115200);
  Serial.println("2 DC Motors with PWM (Min 30%)");
}

void loop() {

  // Both motors forward
  Serial.println("Both motors FORWARD with PWM");

  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);

  // Ramp speed from 30% to 100%
  for (int duty = MIN_DUTY; duty <= MAX_DUTY; duty += 10) {
    ledcWrite(motorA_EN, duty);
    ledcWrite(motorB_EN, duty);

    Serial.print("Duty cycle: ");
    Serial.println(duty);
    delay(400);
  }

  // Stop motors
  Serial.println("Motors STOP");
  ledcWrite(motorA_EN, 0);
  ledcWrite(motorB_EN, 0);
  delay(2000);

  // Both motors backward (fixed 50%)
  Serial.println("Both motors BACKWARD at 50%");

  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);

  int duty50 = 165; // ~50%
  ledcWrite(motorA_EN, duty50);
  ledcWrite(motorB_EN, duty50);

  delay(3000);

  // Stop again
  ledcWrite(motorA_EN, 0);
  ledcWrite(motorB_EN, 0);
  delay(3000);
}
