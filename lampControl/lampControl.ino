#define button 5  // pressed is LOW


int lastButtonState = HIGH; // HIGH by default because of INPUT_PULLUP
int lastCheck = 0;

void setup() {
  Serial.begin(9600);
  Serial.println();

  pinMode(button, INPUT_PULLUP);
  
  initializeLEDs();
  initializeAPI();
}

void loop() {
  int value = digitalRead(button);

// handle button press
  if (value != lastButtonState) {
    lastButtonState = value;

    if (value == LOW) {
      Serial.println("Button pressed");
      toggleLedState();   
    }
  }

  int currentTime = millis();

  if (currentTime - lastCheck > 5000) {
    bool online = isOnline();
    lastCheck = currentTime;

    if (online) {
      Serial.println("Toggle LED because we are online");
      turnOnLamp();
    } else {
      Serial.println("We are not online");
      turnOffLamp();
    }
  }
}
