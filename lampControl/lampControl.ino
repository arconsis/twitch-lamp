#define button 5  // pressed is LOW

int lastButtonState = HIGH; // HIGH by default because of INPUT_PULLUP
int lastCheck = 0;

void setup() {
  Serial.begin(9600);

  setupAPI();
  setupLEDs();

  pinMode(button, INPUT_PULLUP);
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
    Serial.println("Checking API");
    lastCheck = currentTime;

    bool online = isOnline();

    if (online) {
      turnOn();
    } else {
      turnOff();
    }
  }
}
