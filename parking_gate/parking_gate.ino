#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

#define DETECT_DISTANCE 20  // cm
#define GATE_OPEN_ANGLE  90
#define GATE_CLOSE_ANGLE 0
#define GATE_DELAY 3000     // ms，開門後等待時間

Servo gate;

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  gate.attach(SERVO_PIN);
  gate.write(GATE_CLOSE_ANGLE);
  Serial.begin(9600);
}

void loop() {
  long distance = measureDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= DETECT_DISTANCE) {
    gate.write(GATE_OPEN_ANGLE);
    delay(GATE_DELAY);
  } else {
    gate.write(GATE_CLOSE_ANGLE);
  }

  delay(200);
}
