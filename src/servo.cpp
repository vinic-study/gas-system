#include <Arduino.h>
#include <ESP32Servo.h>

static const int servPin = 18;
Servo serv;

const int minAngle = 10;
const int maxAngle = 170;
const int stepDelay = 19; 

int currentPos = minAngle;
int direction = 1; 

unsigned long previousMillis = 0;
const long interval = 1000;

void servSetup() {
    Serial.begin(9600);
    serv.attach(servPin);
    serv.write(currentPos);
    delay(500);
    Serial.println("Servo ready. Starting cycle...");
}

void iniciateRotation(bool lastState) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (lastState == 0) {
            serv.write(maxAngle);
        } else {
            serv.write(minAngle);
        }
    }
}

void stopRotation() {
    serv.write(0);
}