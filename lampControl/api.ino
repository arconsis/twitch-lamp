#include "./secrets.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient sender;
WiFiClient wifiClient;

void setupAPI() {
  Serial.println();

  Serial.print("Connecting");
  WiFi.begin(wifiSSID, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  //wifiClient.setInsecure();
}

bool isOnline() {
  if (sender.begin(wifiClient, "http://192.168.2.138:8000/online.json")) {
    int httpStatusCode = sender.GET();
    bool success;
    
    if (httpStatusCode == 200) {
      String payload = sender.getString();

      Serial.println("Received:");
      Serial.println(payload);

      DynamicJsonDocument response(1024);
      DeserializationError error = deserializeJson(response, payload);
      if (error) {
        success = false;
      } else {
        bool online = response["online"];
        Serial.print("Online state: ");
        Serial.println(online);
        
        success = online;
      }
    } else {
      Serial.print("Failed to get response from backend. Failed with");
      Serial.println(httpStatusCode);

      success = false;
    }
    
    sender.end();

    return success;
  }

  return false;
}
