#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Pin-Definitionen
#define AIN1 2
#define AIN2 4
#define PWMA 15
#define BIN1 18
#define BIN2 19
#define PWMB 21
#define STBY 5

void motorSetup();
void motorAForward(int speed);
void motorABackward(int speed);
void motorBForward(int speed);
void motorBBackward(int speed);
void motorStop();

#endif
