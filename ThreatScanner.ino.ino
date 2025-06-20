#include <Servo.h>

Servo servo;  // SG90 Servo
const int greenPin = 2;
const int redPin = 12;
const int trigPin = 9;   // HC-SR04
const int echoPin = 10;  // HC-SR04
const int servoPin = 6;  // SG90 Servo
long duration;
long distance;
int threatThresholdCm = 30;

void setPinMode()  // Grouping all pin-related setup in one place to keep setup() clean
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
}

void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(150);
  digitalWrite(pin, LOW);
  delay(150);
}

float readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2.0;
}

void setup() {

  setPinMode();
}

bool scanAt(int angle) {
  servo.write(angle);
  delay(300);

  float distance = readDistance();
  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" | Distance: ");
  Serial.println(distance);

  if (distance <= threatThresholdCm) {
    blinkLED(redPin);
    digitalWrite(greenPin, LOW);
    Serial.print("Threat Detected!");
    Serial.print(" | Distance: ");
    Serial.println(distance);
    return true;  // threat detected
  } else {
    blinkLED(greenPin);
    digitalWrite(redPin, LOW);
    return false;
  }
}


void loop() {

  for (int pos = 0; pos <= 180; pos++)  // First sweep from left to right
  {
    if (scanAt(pos))  // Stay at this angle while threat is present
    {

      while (readDistance() <= threatThresholdCm) {
        blinkLED(redPin);
        delay(100);  // Keep alerting
      }
    }
  }
  for (int pos = 180; pos >= 0; pos--)  // Second sweep from right to left
  {
    if (scanAt(pos)) {
      while (readDistance() <= threatThresholdCm) {
        blinkLED(redPin);
      }
    }
  }
}
