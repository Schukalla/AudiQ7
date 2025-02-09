// Pinbelegung auf dem ESP32 für zwei Motoren
#define RPWM1  23  // Pin für RPWM Motor 1 (BTS7960 #1)
#define LPWM1  22  // Pin für LPWM Motor 1 (BTS7960 #1)

#define RPWM2  19  // Pin für RPWM Motor 2 (BTS7960 #2)
#define LPWM2  5   // Pin für LPWM Motor 2 (BTS7960 #2)

void setup() {
  // Setze die Pin-Modi für Motor 1
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);

  // Setze die Pin-Modi für Motor 2
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);

  // Beide Motoren sind über EN1 und EN2 direkt an 5V angeschlossen,
  // daher müssen wir die Pins für EN1 und EN2 nicht steuern.

  Serial.begin(115200);
}

void loop() {
  // Beide Motoren vorwärts (5 Sekunden)
  analogWrite(RPWM1, 255);  // Maximale Geschwindigkeit für Motor 1
  analogWrite(LPWM1, 0);    // Keine Rückwärtsbewegung für Motor 1
  analogWrite(RPWM2, 255);  // Maximale Geschwindigkeit für Motor 2
  analogWrite(LPWM2, 0);    // Keine Rückwärtsbewegung für Motor 2
  delay(5000);               // 5 Sekunden warten

  // Motor 1 rückwärts, Motor 2 vorwärts (5 Sekunden)
  analogWrite(RPWM1, 0);    // Keine Vorwärtsbewegung für Motor 1
  analogWrite(LPWM1, 255);  // Maximale Rückwärtsgeschwindigkeit für Motor 1
  analogWrite(RPWM2, 255);  // Maximale Geschwindigkeit für Motor 2
  analogWrite(LPWM2, 0);    // Keine Rückwärtsbewegung für Motor 2
  delay(5000);               // 5 Sekunden warten

  // Motor 1 vorwärts, Motor 2 rückwärts (5 Sekunden)
  analogWrite(RPWM1, 255);  // Maximale Geschwindigkeit für Motor 1
  analogWrite(LPWM1, 0);    // Keine Rückwärtsbewegung für Motor 1
  analogWrite(RPWM2, 0);    // Keine Vorwärtsbewegung für Motor 2
  analogWrite(LPWM2, 255);  // Maximale Rückwärtsgeschwindigkeit für Motor 2
  delay(5000);               // 5 Sekunden warten
}
