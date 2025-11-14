#include <Arduino.h>

const int AO_PIN = 33; 

unsigned long previousSensorMillis = 0;
const long intervalSensor = 2000;

int gasNumber;


void setupSensor() {
  Serial.begin(9600);
  pinMode(AO_PIN, INPUT);
}

int loopSensor() {
  unsigned long currentSensorMillis = millis();

  if (currentSensorMillis - previousSensorMillis >= intervalSensor) {
    previousSensorMillis = currentSensorMillis;

    gasNumber = analogRead(AO_PIN);
  }
  
  return gasNumber;
}