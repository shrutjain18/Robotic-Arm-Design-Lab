#include <Arduino.h>

// ------------------ Pins ------------------
const int encA = 32;
const int encB = 33;

const int in1 = 27;
const int in2 = 26;
const int enablePin = 25;   // PWM pin (NOT 34)

const int potPin = 14;

// ---------------- Encoder Setup -----------
const int pulsesPerRev = 1340;   // make configurable
const float potRangeDeg = 300.0;
const float degPerPulse = potRangeDeg / pulsesPerRev;

volatile long encoderCount = 0;
long zeroCount = 0;

// ---------------- PID ---------------------
float Kp = 2.0;
float Ki = 0.0;
float Kd = 0.01;

float integral = 0;
float previousError = 0;
unsigned long lastTime = 0;

// ---------------- PWM (ESP32 new core) ----
const int pwmFreq = 20000;
const int pwmResolution = 8;

// ---------------- Encoder ISR -------------
void IRAM_ATTR readEncoder() {
  if (digitalRead(encB)) encoderCount++;
  else encoderCount--;
}

// ---------------- Angle -------------------
float getAngle() {
  noInterrupts();
  long count = encoderCount - zeroCount;
  interrupts();
  return count * degPerPulse;
}

// ---------------- Motor Control -----------
void motorStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  ledcWrite(enablePin, 0);
}

void motorBackward(int pwm) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  ledcWrite(enablePin, pwm);
}

void motorForward(int pwm) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  ledcWrite(enablePin, pwm);
}

// ---------------- Setup -------------------
void setup() {
  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA), readEncoder, RISING);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  ledcAttach(enablePin, pwmFreq, pwmResolution);

  zeroCount = encoderCount;

  Serial.begin(115200);
  lastTime = millis();

  Serial.println("Potentiometer → Motor Absolute Position Control Ready");
}

// ---------------- Loop --------------------
void loop() {
  int potVal = analogRead(potPin)/10;
  float targetAngle = map(potVal, 0, 408, 0, 300);

  float actualAngle = getAngle();
  float error = targetAngle - actualAngle;

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt <= 0) dt = 0.001;

  integral += error * dt;
  float derivative = (error - previousError) / dt;
  float output = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  int pwm = constrain(abs((int)output), 165, 255);  // MIN PWM = 175

  if (error > 2) motorForward(pwm);
  else if (error < -2) motorBackward(pwm);
  else motorStop();

  Serial.print("Target: "); Serial.print(targetAngle);
  Serial.print("  Actual: "); Serial.print(actualAngle);
  Serial.print("  Error: "); Serial.print(error);
  Serial.print("  PWM: "); Serial.println(pwm);

  delay(10);
}
