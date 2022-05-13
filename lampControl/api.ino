#include "./secrets.h"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

String twitchApiEndpoint = "https://api.twitch.tv/helix/streams?user_login=arconsis";
const char *twitchApiFingerprint = "0E 27 ED A3 7D CA 6E FF 17 37 5D B9 9C B4 CC 71 80 80 B3 D7";

String twitchOAuthEndpoint = "https://id.twitch.tv/oauth2/token";
const char *twitchOAuthFingerprint = "AC 27 C3 66 4E 3D 98 3C 11 48 05 6E 02 AC 68 DE B6 01 6D D6";

String twitchOAuthToken = "";

HTTPClient client;

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

void refreshToken() {
  WiFiClientSecure oAuthWifiClient;

  oAuthWifiClient.setFingerprint(twitchOAuthFingerprint);

  String endpoint = twitchOAuthEndpoint + "?client_id=" + twitchClientId + "&client_secret=" + twitchSecret + "&grant_type=client_credentials";

  Serial.println("Getting new access token");

  if (client.begin(oAuthWifiClient, endpoint.c_str())) {
    int statusCode = client.POST("");
    Serial.print("Status is ");
    Serial.println(statusCode);

    if (statusCode == 200) {
      String payload = client.getString();

      int responseSize = client.getSize();
      Serial.print("Response size is: ");
      Serial.println(responseSize);

      DynamicJsonDocument response(responseSize * 2);
      DeserializationError error = deserializeJson(response, payload);

      if (error) {
        Serial.print("JSON parsing failed with ");
        Serial.println(error.c_str());
      }

      String accessToken = response["access_token"];
      int expiresIn = response["expires_in"];
      String substring = accessToken.substring(0, 5);
      Serial.println("Access token beginning is " + substring + " and is valid for " + expiresIn);      

      twitchOAuthToken = "Bearer " + accessToken;
    } else {
      String payload = client.getString();
      Serial.println("Refreshing token failed with:\n" + payload);
    }
  }

  client.end();
}

bool isOnlineOnTwitch() {
  if (twitchOAuthToken.length() == 0) {
    refreshToken();
  }
  
  WiFiClientSecure wifiClient;

  wifiClient.setFingerprint(twitchApiFingerprint);

  Serial.println("Checking online status");

  if (client.begin(wifiClient, twitchApiEndpoint.c_str())) {
    client.addHeader("Client-Id", twitchClientId);
    client.addHeader("Authorization", twitchOAuthToken);
    
    int statusCode = client.GET();
    Serial.print("Status is ");
    Serial.println(statusCode);

    if (statusCode == 200) {
      String payload = client.getString();
      Serial.println("Got from twitch:\n" + payload);

      int responseSize = client.getSize();
      Serial.print("Response size is: ");
      Serial.println(responseSize);

      DynamicJsonDocument response(responseSize * 2);
      DeserializationError error = deserializeJson(response, payload);

      if (error) {
        Serial.print("JSON parsing failed with ");
        Serial.println(error.c_str());
        return false;
      }

      JsonArray twitchResponseDataArray = response["data"];

      if (twitchResponseDataArray.size() == 0) {
        return false;
      }

      String twitchStreamType = twitchResponseDataArray[0]["type"];
      Serial.println("Our stream is: " + twitchStreamType);

      return twitchStreamType == "live";
    } else if (statusCode == 401) {
      Serial.println("Checking online status failed with unauthorized. Resetting token");
      twitchOAuthToken = "";      
      return false;
    } else {
      String payload = client.getString();
      Serial.println("Request failed with:\n" + payload);
      return false;
    }
  }

  return false;
}