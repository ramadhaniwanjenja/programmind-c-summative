// Smart Home System Simulation
const int tempPin = A0;
const int ldrPin = A1;
const int pirPin = 2;

const int fanPin = 9;
const int ledPin = 6;
const int buzzerPin = 7;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Allocate memory for sensor values
  int* tempReading = (int*) malloc(sizeof(int));
  float* temperatureC = (float*) malloc(sizeof(float));
  int* lightLevel = (int*) malloc(sizeof(int));
  int* motionDetected = (int*) malloc(sizeof(int));

  // Use pointers to store readings
  *tempReading = analogRead(tempPin);
  float voltage = (*tempReading) * (5.0 / 1023.0);
  *temperatureC = voltage * 100;

  *lightLevel = analogRead(ldrPin);
  *motionDetected = digitalRead(pirPin);

  // Fan control
  if (*temperatureC > 30) {
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(fanPin, LOW);
  }

  // LED control
  if (*lightLevel < 500) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Buzzer control
  if (*motionDetected == HIGH) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Serial output
  Serial.print("Temp: ");
  Serial.print(*temperatureC);
  Serial.print(" °C | Light: ");
  Serial.print(*lightLevel);
  Serial.print(" | Motion: ");
  Serial.println(*motionDetected);

  // Free dynamically allocated memory
  free(tempReading);
  free(temperatureC);
  free(lightLevel);
  free(motionDetected);

  delay(1000);
}
