#include "MotorController.h"

// Erstelle ein MotorController-Objekt
MotorController motorController;

void setup() {
  // Setup der Motoren
  motorController.motorSetup();

  // Beispiel: Motor A vorwärts mit 150 Geschwindigkeit
  motorController.motorAForward(150);
  delay(5000);  // 5 Sekunden laufen lassen

  // Beispiel: Motor A rückwärts mit 150 Geschwindigkeit
  motorController.motorABackward(150);
  delay(5000);  // 5 Sekunden laufen lassen

  // Beispiel: Motor B vorwärts mit 100 Geschwindigkeit
  motorController.motorBForward(100);
  delay(5000);  // 5 Sekunden laufen lassen

  // Beispiel: Motor B rückwärts mit 100 Geschwindigkeit
  motorController.motorBBackward(100);
  delay(5000);  // 5 Sekunden laufen lassen

  // Stoppe beide Motoren
  motorController.motorStop();
}

void loop() {
  // Keine weiteren Befehle im Loop, nur einmal im Setup ausführen.
}
