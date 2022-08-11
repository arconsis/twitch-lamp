int milliSecondsPerMinute = 60 * 1000;
int microSecondsPerMinute = milliSecondsPerMinute * 1000;

double offlinePollingInterval = 1; // in minutes
double onlinePollingInterval = 1;

// current consumption
// controller             ~30 mA
// relay                  ~60 mA
// internet connection    ~50 mA
// leds                   ~50 mA

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