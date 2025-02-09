#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

class MotorController {
  public:
    // Konstruktor
    MotorController();

    // Setup für Motoren
    void motorSetup();

    // Motor A vorwärts steuern (mit übergebener Geschwindigkeit)
    void motorAForward(int speed);

    // Motor A rückwärts steuern (mit übergebener Geschwindigkeit)
    void motorABackward(int speed);

    // Motor B vorwärts steuern (mit übergebener Geschwindigkeit)
    void motorBForward(int speed);

    // Motor B rückwärts steuern (mit übergebener Geschwindigkeit)
    void motorBBackward(int speed);

    // Stoppe beide Motoren
    void motorStop();

  private:
    // Motor Pins für Motor 1
    const int RPWM1 = 23;
    const int LPWM1 = 22;

    // Motor Pins für Motor 2
    const int RPWM2 = 19;
    const int LPWM2 = 18;
};

#endif
