//Pins
#define OUTPUT_PIN 22  // D22 //output
#define INPUT_PIN1 23  // D23 //input
#define INPUT_PIN2 16  // RX2 (GPIO16) //input

volatile bool input1_detected = false;
volatile bool input2_detected = false;
volatile int pin_state = 0;  // -1, 0 oder 1
unsigned long lastCheck = 0;
const int checkInterval = 1000;  // Überprüfe alle 10 ms

void IRAM_ATTR handleInterrupt1() {
  input1_detected = true;
  if (digitalRead(INPUT_PIN1) == HIGH) {r
    pin_state = -1;
  } else {
    pin_state = 0;
  }
}

void IRAM_ATTR handleInterrupt2() {
  input2_detected = true;
  if (digitalRead(INPUT_PIN2) == HIGH) {
    pin_state = 1;
  } else {
    pin_state = 0;
  }
}

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN1, INPUT);
  pinMode(INPUT_PIN2, INPUT);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN1), handleInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN2), handleInterrupt2, CHANGE);
  Serial.begin(9600);
}

void checkPinState() {
  int output_state = LOW;

  if (pin_state == -1) {
    Serial.println("INPUT_PIN1 liest HIGH, Zustand: -1");
    output_state = HIGH;
  } else if (pin_state == 1) {
    Serial.println("INPUT_PIN2 liest HIGH, Zustand: 1");
    output_state = HIGH;
  } else {
    Serial.println("Beide Pins LOW, Zustand: 0");
  }

  digitalWrite(OUTPUT_PIN, output_state);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastCheck >= checkInterval) {
    lastCheck = currentMillis;
    checkPinState();
  }
}
