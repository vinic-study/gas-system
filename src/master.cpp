#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Sensor.h>
#include <json.h>
#include "led.h"
#include <servo.h>

BluetoothSerial BTSerial;

int gasIntensity = -999;

u_int8_t slaveAddress[] = {0xF4, 0x65, 0x0B, 0x47, 0x1D, 0x6A};

void setupMaster(){
    Serial.begin(9600);
    Serial.setTimeout(5000);

    setupLED(2);

    if (BTSerial.begin("webvinicDevice", true))
    {
        Serial.println("Bluetooth (Master) started successfully");
    } else
    {
        Serial.println("Error initializing Bluetooth");
    }

    Serial.println("Attempting to connect to Slave...");
    if (BTSerial.connect(slaveAddress))
    {
        Serial.println("Connected successfully");
    } else {
        Serial.println("Failed to connect");
    }

    setupSensor();
}

void loopMaster(){

    int sensorGas = loopSensor();

    if (sensorGas > 100 && sensorGas != gasIntensity) {
        String data = parseToJson(true);
        Serial.println(data);
        BTSerial.println(data);

        gasIntensity = sensorGas;
    }

    if (BTSerial.available())
    {
        String receivedMessage = BTSerial.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Message received: %s\n", receivedMessage.c_str());
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSerial.println(messageToSend);
    }
}