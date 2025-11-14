#include <Arduino.h>
#include <BluetoothSerial.h>
#include "led.h"
#include "slave.h"
#include <json.h>
#include <servo.h>

BluetoothSerial BTSlave;

float gasLimit = false;
bool lastState = false;

void setupSlave() {
    Serial.begin(9600);
    Serial.setTimeout(5000);

    setupLED(2);
    servSetup();

    if (BTSlave.begin("webvinicDevice"))
    {
        Serial.println("Bluetooth iniciado com sucesso");
        Serial.print("ESP MAC Address: ");

        Serial.println(BTSlave.getBtAddressString());
    } else
    {
        Serial.println("Error para iniciar o Bluetooth");
    }
}

void loopSlave() {
    if (BTSlave.available())
    {

        String receivedMessage = BTSlave.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Evento Recebido: %s\n", receivedMessage.c_str());

        JsonDocument doc = parseToString(receivedMessage);

        if (!doc.isNull()) {
            if (doc.containsKey("gasLimit")) {

                gasLimit = doc["gasLimit"];

                if (gasLimit == true) {
                    iniciateRotation(lastState);
                    blinkLed(2);

                    lastState = !lastState;
                } else {
                    stopRotation();
                    turnOffLED(2);
                }

                Serial.printf("Gas %2.f", gasLimit);

            } else {
                Serial.println("Erro: JSON recebido não contém as chaves.'");
            }
        }
    }

}