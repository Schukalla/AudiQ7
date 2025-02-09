#include "motor_control.h"

// Initialisierung der Motorsteuerung
void motorSetup() {
  Serial.begin(9600);
  Serial.println("Start");
  
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  motorStop();
}

// Motor A vorwärts
void motorAForward(int speed) {
  Serial.println("motorAForward");
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speed);
  digitalWrite(STBY, HIGH);  // TB6612FNG aktivieren
}

// Motor A rückwärts
void motorABackward(int speed) {
  Serial.println("motorABackward");
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speed);
}

// Motor B vorwärts
void motorBForward(int speed) {
  Serial.println("motorBForward");
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speed);
}

// Motor B rückwärts
void motorBBackward(int speed) {
  Serial.println("motorBBackward");
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, speed);
}

// Motoren stoppen
void motorStop() {
  Serial.println("motorStop");
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);
}
