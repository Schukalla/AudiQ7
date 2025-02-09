//##index##
//startsetup
//startloop

//Library
#include <Bluepad32.h>
#include "motor_control.h"
#include <stdio.h>

char str[20];

//Pins
#define OUTPUT_PIN 22  // D22 //output
#define INPUT_PIN1 23  // D23 //input
#define INPUT_PIN2 16  // RX2 (GPIO16) //input

volatile bool input1_detected = false;
volatile bool input2_detected = false;
volatile int pin_state = 0;  // -1, 0 oder 1
unsigned long lastCheck = 0;
const int checkInterval = 1000;  // Überprüfe alle 10 ms

//controller einrichten
ControllerPtr myControllers[BP32_MAX_GAMEPADS];

volatile int remgang = 0;
volatile int onlyremote = 1;
volatile int speed = 0;

void IRAM_ATTR handleInterrupt1() {
  input1_detected = true;
  if (digitalRead(INPUT_PIN1) == HIGH) {
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

void checkPinState() {
  int output_state = LOW;

  if (pin_state == -1) {
    Serial.println("INPUT_PIN1 liest HIGH, Zustand: -1");
    output_state = HIGH;
    remgang = -1;
  } else if (pin_state == 1) {
    Serial.println("INPUT_PIN2 liest HIGH, Zustand: 1");
    output_state = HIGH;
    remgang = 1;
  } else {
    Serial.println("Beide Pins LOW, Zustand: 0");
    remgang = 0;
  }

  digitalWrite(OUTPUT_PIN, output_state);
}



void IRAM_ATTR onConnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            myControllers[i] = ctl;
            return;
        }
    }
}

void IRAM_ATTR onDisconnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            myControllers[i] = nullptr;
            return;
        }
    }
}

void processGamepad(ControllerPtr ctl) {
    uint8_t dpad = ctl->dpad();
    uint16_t buttons = ctl->buttons();
    uint16_t throttle = ctl->throttle();
    int16_t axisRX = ctl->axisRX();
    uint16_t brake = ctl->brake();

     if(ctl->dpad() == 0x01){
      remgang = 1;
    }
    //Schaltung neutraul = links
    else if(ctl->dpad() == 0x08){
      remgang = 0;
    }
    //Schaltung neutraul = rechts
    else if(ctl->dpad() == 0x04){
      remgang = 0;
    }
    //Schaltung zurück = runter
    else if(ctl->dpad() == 0x02){
      remgang = -1;
    }

    Serial.printf("remgang %4d\n",remgang);

    if (buttons & 0x0001) onlyremote = 0;  // Button A: Control to driver
    if (buttons & 0x0002) onlyremote = 1;  // Button B: Remote control

    speed = (throttle > 150) ? throttle * 255 / 1023 : 0;
    Serial.printf("%4d\n",ctl->brake());
    if (brake > 200) {
        motorStop();
        onlyremote = 1;
    }

    if (onlyremote == 0) {
        unsigned long currentMillis = millis();

        if (currentMillis - lastCheck >= checkInterval) {
          lastCheck = currentMillis;
        checkPinState();
        }
    }

    if (remgang == 1) {
        motorAForward(speed);
    } else if (remgang == -1) {
        motorABackward(speed);
    } else {
        motorStop();
    }

    int var = axisRX * 255 / 512;
    Serial.printf("%d\n", var);

    if (var < -40) {
        motorBBackward(abs(var));
    } else if (axisRX > 40) {
        motorBForward(var);
    }
}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            processGamepad(myController);
        }
    }
}

void setup() {
    Serial.begin(115200);
    BP32.setup(&onConnectedController, &onDisconnectedController);
    BP32.forgetBluetoothKeys();
    BP32.enableVirtualDevice(false);

    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(INPUT_PIN1, INPUT);
    pinMode(INPUT_PIN2, INPUT);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN1), handleInterrupt1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN2), handleInterrupt2, CHANGE);

    motorSetup();
    digitalWrite(OUTPUT_PIN, HIGH);
}

void loop() {
   
    if (BP32.update()) {
        processControllers();
    }
    delay(10);  // Verkleinerung der Verzögerung für schnellere Reaktion
}
