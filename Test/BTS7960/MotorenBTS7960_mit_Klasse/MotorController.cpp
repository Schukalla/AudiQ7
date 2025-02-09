#include "MotorController.h"
#include <Arduino.h>  // für PinMode, analogWrite

// Konstruktor
MotorController::MotorController() {
  // Setze die Pin-Modi
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
}

// Motoren initialisieren und stoppen
void MotorController::motorSetup() {
  // Setze alle Motoren zunächst auf STOP (0 Geschwindigkeit)
  analogWrite(RPWM1, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM2, 0);
  analogWrite(LPWM2, 0);
}

// Motor A vorwärts steuern
void MotorController::motorAForward(int speed) {
  analogWrite(RPWM1, speed);  // Vorwärts
  analogWrite(LPWM1, 0);      // Keine Rückwärtsbewegung
}

// Motor A rückwärts steuern
void MotorController::motorABackward(int speed) {
  analogWrite(RPWM1, 0);      // Keine Vorwärtsbewegung
  analogWrite(LPWM1, speed);  // Rückwärts
}

// Motor B vorwärts steuern
void MotorController::motorBForward(int speed) {
  analogWrite(RPWM2, speed);  // Vorwärts
  analogWrite(LPWM2, 0);      // Keine Rückwärtsbewegung
}

// Motor B rückwärts steuern
void MotorController::motorBBackward(int speed) {
  analogWrite(RPWM2, 0);      // Keine Vorwärtsbewegung
  analogWrite(LPWM2, speed);  // Rückwärts
}

// Beide Motoren stoppen
void MotorController::motorStop() {
  analogWrite(RPWM1, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM2, 0);
  analogWrite(LPWM2, 0);
}
