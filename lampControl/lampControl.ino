int milliSecondsPerMinute = 60 * 1000;
int microSecondsPerMinute = milliSecondsPerMinute * 1000;

double offlinePollingInterval = 5; // in microseconds
double onlinePollingInterval = 1;

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  initializeLEDs();
  initializeAPI();
}

void loop() {
  bool online = isOnlineOnTwitch();

  if (online) {
    Serial.println("Toggle LED because we are online");
    turnOnLamp();
    delay(onlinePollingInterval * milliSecondsPerMinute);
  } else {
    Serial.println("We are not online");
    turnOffLamp();
    Serial.print("Going to bed");
    ESP.deepSleep(offlinePollingInterval * microSecondsPerMinute);   
  }
}