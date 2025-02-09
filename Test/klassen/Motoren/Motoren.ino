/*

5V an R_EN 
5V an L_EN
5V an VCC
GPIO an R_PWM
GPIO an L_PWM
GND an GND
*/

#include "motor_control.h"

void setup() {
  motorSetup();
}

void loop() {
  Serial.println("Starte Schleife");
  
  motorAForward(128);  // Motor A - Halbe Geschwindigkeit vorwärts
  motorBForward(128);  // Motor B - Halbe Geschwindigkeit vorwärts
  delay(2000);
  
  motorABackward(76);  // Motor A - 30% Rückwärts
  motorBBackward(76);  // Motor B - 30% Rückwärts
  delay(2000);
  
  motorStop();
  delay(1000);
}
