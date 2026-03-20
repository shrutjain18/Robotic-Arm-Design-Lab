#include <Arduino.h>

// ------------------ Motor 1 Pins ------------------
const int encA1 = 5;
const int encB1 = 18;

const int in1_1 = 27;
const int in2_1 = 15;
const int enablePin1 = 32;

const int potPin1 = 36;

// ------------------ Motor 2 Pins ------------------
const int encA2 = 17;
const int encB2 = 16;

const int in1_2 = 14;
const int in2_2 = 12;
const int enablePin2 = 33;

const int potPin2 = 39;

// ---------------- Encoder Setup -------------------
const int pulsesPerRev = 1340;
const float potRangeDeg = 300.0;
const float degPerPulse = potRangeDeg / pulsesPerRev;

// ---------------- Encoder Variables ----------------
volatile long encoderCount1 = 0;
volatile long encoderCount2 = 0;

long zeroCount1 = 0;
long zeroCount2 = 0;

// ---------------- PID ------------------------------
float Kp = 2.0;
float Ki = 0.01;
float Kd = 0.01;

float integral1 = 0, previousError1 = 0;
float integral2 = 0, previousError2 = 0;

unsigned long lastTime = 0;

// ---------------- PWM ------------------------------
const int pwmFreq = 20000;
const int pwmResolution = 8;

// ---------------- Encoder ISRs ---------------------
void IRAM_ATTR readEncoder1() {
  if (digitalRead(encB1)) encoderCount1++;
  else encoderCount1--;
}

void IRAM_ATTR readEncoder2() {
  if (digitalRead(encB2)) encoderCount2++;
  else encoderCount2--;
}

// ---------------- Angle Functions ------------------
float getAngle1() {
  noInterrupts();
  long count = encoderCount1 - zeroCount1;
  interrupts();
  return count * degPerPulse;
}

float getAngle2() {
  noInterrupts();
  long count = encoderCount2 - zeroCount2;
  interrupts();
  return count * degPerPulse;
}

// ---------------- Motor Control --------------------
void motor1Forward(int pwm) {
  digitalWrite(in1_1, LOW);
  digitalWrite(in2_1, HIGH);
  ledcWrite(enablePin1, pwm);
}

void motor1Backward(int pwm) {
  digitalWrite(in1_1, HIGH);
  digitalWrite(in2_1, LOW);
  ledcWrite(enablePin1, pwm);
}

void motor1Stop() {
  digitalWrite(in1_1, LOW);
  digitalWrite(in2_1, LOW);
  ledcWrite(enablePin1, 0);
}

void motor2Forward(int pwm) {
  digitalWrite(in1_2, LOW);
  digitalWrite(in2_2, HIGH);
  ledcWrite(enablePin2, pwm);
}

void motor2Backward(int pwm) {
  digitalWrite(in1_2, HIGH);
  digitalWrite(in2_2, LOW);
  ledcWrite(enablePin2, pwm);
}

void motor2Stop() {
  digitalWrite(in1_2, LOW);
  digitalWrite(in2_2, LOW);
  ledcWrite(enablePin2, 0);
}

// ---------------- Setup ----------------------------
void setup() {
  // Encoder pins
  pinMode(encA1, INPUT_PULLUP);
  pinMode(encB1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA1), readEncoder1, RISING);

  pinMode(encA2, INPUT_PULLUP);
  pinMode(encB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA2), readEncoder2, RISING);

  // Motor pins
  pinMode(in1_1, OUTPUT);
  pinMode(in2_1, OUTPUT);

  pinMode(in1_2, OUTPUT);
  pinMode(in2_2, OUTPUT);

  // PWM
  ledcAttach(enablePin1, pwmFreq, pwmResolution);
  ledcAttach(enablePin2, pwmFreq, pwmResolution);

  zeroCount1 = encoderCount1;
  zeroCount2 = encoderCount2;

  Serial.begin(115200);
  lastTime = millis();

  Serial.println("2 Motor Absolute Position Control Ready");
}

// ---------------- Loop -----------------------------
void loop() {
  // ---------- POT READ ----------
  int potVal1 = analogRead(potPin1) / 10;
  int potVal2 = analogRead(potPin2) / 10;

  float target1 = map(potVal1, 0, 408, 0, 300);
  float target2 = map(potVal2, 0, 408, 0, 300);

  float actual1 = getAngle1();
  float actual2 = getAngle2();

  float error1 = target1 - actual1;
  float error2 = target2 - actual2;

  // ---------- TIME ----------
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt <= 0) dt = 0.001;

  // ---------- PID 1 ----------
  integral1 += error1 * dt;
  float derivative1 = (error1 - previousError1) / dt;
  float output1 = Kp * error1 + Ki * integral1 + Kd * derivative1;
  previousError1 = error1;

  int pwm1 = constrain(abs((int)output1), 165, 255);

  if (error1 > 2) motor1Forward(pwm1);
  else if (error1 < -2) motor1Backward(pwm1);
  else motor1Stop();

  // ---------- PID 2 ----------
  integral2 += error2 * dt;
  float derivative2 = (error2 - previousError2) / dt;
  float output2 = Kp * error2 + Ki * integral2 + Kd * derivative2;
  previousError2 = error2;

  int pwm2 = constrain(abs((int)output2), 165, 255);

  if (error2 > 2) motor2Forward(pwm2);
  else if (error2 < -2) motor2Backward(pwm2);
  else motor2Stop();

  // ---------- PARALLEL PRINT ----------
  Serial.print("M1 T:"); Serial.print(target1);
  Serial.print(" A:"); Serial.print(actual1);
  Serial.print(" | ");

  Serial.print("M2 T:"); Serial.print(target2);
  Serial.print(" A:"); Serial.print(actual2);

  Serial.println();

  delay(10);
}
