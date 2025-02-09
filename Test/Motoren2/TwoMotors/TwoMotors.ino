// Arduino TB6612FNG Steuerung - 2 Motoren

// Pin-Definitionen
#define AIN1 2
#define AIN2 4
#define PWMA 15
#define BIN1 18
#define BIN2 19
#define PWMB 21
#define STBY 5

void setup() {
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

   // TB6612FNG aktivieren
  digitalWrite(STBY, HIGH);
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

void loop() {
  Serial.println("Starte schleife");
  motorAForward(128); // Motor A - Halbe Geschwindigkeit vorwärts
  motorBForward(128); // Motor B - Halbe Geschwindigkeit vorwärts
  delay(2000);
  motorABackward(76); // Motor A - 30% Rückwärts
  motorBBackward(76); // Motor B - 30% Rückwärts
  delay(2000);
  motorStop();
  delay(1000);
}
