void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  //set the resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // read the analog / millivolts value for pin 2:
  int analogValue1 = analogRead(12)/10;

  // print out the values you read:
  Serial.printf("ADC analog value = %d,  ", analogValue1);
   int analogValue2 = analogRead(14)/10;

  // print out the values you read:
  Serial.printf("ADC analog value = %d,  ", analogValue2);
   int analogValue3 = analogRead(27)/10;

  // print out the values you read:
  Serial.printf("ADC analog value = %d,  ", analogValue3);
   int analogValue4 = analogRead(26)/10;

  // print out the values you read:
  Serial.printf("ADC analog value = %d\n", analogValue4);
  //Serial.printf("ADC millivolts value = %d\n", analogVolts);

  delay(100);  // delay in between reads for clear read from serial
}
