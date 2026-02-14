// ---------------- Encoder Pins ----------------
const int encoderChA = 32;  // Channel A connected to digital pin 2
const int encoderChB = 33;  // Channel B connected to digital pin 3

volatile long encoderCount = 0;  

void setup() {
  Serial.begin(115200);

  pinMode(encoderChA, INPUT);
  pinMode(encoderChB, INPUT);

  // Attach interrupt on rising edge of channel A
  attachInterrupt(digitalPinToInterrupt(encoderChA), encoderISR, RISING);

  Serial.println("Rotate the motor shaft manually for one full revolution...");
}

void loop() {
  // Print encoder count continuously
  Serial.print("Encoder Count: ");
  Serial.println(encoderCount);
  delay(2);  // slow updates for readability
}

void encoderISR() {
  // Direction detection
  if (digitalRead(encoderChB) == HIGH) {
    encoderCount++;   // One direction
  } else {
    encoderCount--;   // Opposite direction
  }
}
