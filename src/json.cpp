#include <Arduino.h>
#include <ArduinoJson.h>

String parseToJson(bool limit) {
	JsonDocument doc;

	doc["gasLimit"] = limit;

	String jsonString;
	serializeJson(doc, jsonString);

	return jsonString;
}

JsonDocument parseToString(String data) {
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, data);

  if (erro)
  {
    Serial.print("Erro ao interpretar JSON: ");
    Serial.println(erro.c_str());
	doc.clear();
  }

  return doc;
}
