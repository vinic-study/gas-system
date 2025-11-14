#include <Arduino.h>
#include <ArduinoJson.h>

#ifndef JSON_H
#define JSON_H

String parseToJson(bool limit);
JsonDocument parseToString(String data);

#endif