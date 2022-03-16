#include "./secrets.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient client;
WiFiClient wifiClient;

void initializeAPI() {
  Serial.print("Connecting");
  WiFi.begin(wifiSSID, wifiPassword);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected with IP address: ");
  Serial.println(WiFi.localIP());
}

bool isOnline() {
  if (client.begin(wifiClient, "http://192.168.2.138:8000/online.json")) {
    int statusCode = client.GET();
    bool online;

    Serial.print("Request finished with: ");
    Serial.println(statusCode);

    if (statusCode == 200) {
      String payload = client.getString();
      Serial.print("Received from server: ");
      Serial.println(payload);

      DynamicJsonDocument response(1024);
      DeserializationError error = deserializeJson(response, payload);

      if (error) {
        Serial.println("JSON parsing failed");
        return false;
      }

      online = response["online"];
      Serial.print("Online state: ");
      Serial.println(online);
    } else {
      Serial.println("Failed to read online status from server");
      online = false;
    }

    return online;
  } 

  return false;
}
