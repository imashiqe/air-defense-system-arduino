#include <Servo.h>

// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;
const int buzzerPin = 7;

const int detectionDistance = 15; // in centimeters

Servo myservo;
long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  myservo.attach(servoPin);
}

void loop() {
  // Sweep from 0° to 180°
  for (int pos = 0; pos <= 180; pos += 10) {
    myservo.write(pos);
    delay(300);
    
    distance = getDistance();
    Serial.print("Angle: ");
    Serial.print(pos);
    Serial.print(" Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance <= detectionDistance) {
      triggerAlarm();
      break;
    }
  }

  // Sweep from 180° back to 0°
  for (int pos = 180; pos >= 0; pos -= 10) {
    myservo.write(pos);
    delay(300);
    
    distance = getDistance();
    Serial.print("Angle: ");
    Serial.print(pos);
    Serial.print(" Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance <= detectionDistance) {
      triggerAlarm();
      break;
    }
  }
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return 0; // timeout means no object

  return duration * 0.034 / 2;
}

// Function to activate the buzzer alarm
void triggerAlarm() {
  Serial.println("⚠️ Object Detected!");
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
  delay(500); // Optional pause
}
