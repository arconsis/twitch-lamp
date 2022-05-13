#define led 0    // LOW sends the signal
#define relay 4   // HIGH switches on
#define light 2

#define DEBUG 1

int ledState = 0; // 0 = off; 1 = fade in; 2 = pulse

void initializeLEDs() {
  Serial.println("Initializing LEDs");
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);

  delay(1000);

  digitalWrite(light, HIGH); // light is off on HIGH
  digitalWrite(led, HIGH);   // switch is active LOW, so we need HIGH by default
  digitalWrite(relay, HIGH); // turn on light strip by switching on the relay
  Serial.println("Initializing LEDs done");
}

void turnOnLamp() {
  digitalWrite(relay, HIGH);

  turnOnLed();
}

void turnOffLamp() {
  turnOffLed();
  
  digitalWrite(relay, LOW);
}

void turnOnLed() {
  if (ledState == 0) {
    Serial.println("Turning on light");
    simulateButtonPress();
    ledState = 1;
  }
}

void turnOffLed() {
  if (ledState == 1) {
    Serial.println("Turning off light");
    simulateButtonPress();
    simulateButtonPress();
    ledState = 0;
  } else if (ledState == 2) {
    Serial.println("Turning off light");
    simulateButtonPress();
    ledState = 0;
  }
}

void toggleLedState() {
  if (ledState == 0) {
    turnOnLed();
  } else {
    turnOffLed();
  }

// Toggle light on NodeMCU for debugging
  if (DEBUG && ledState == 0) {
    digitalWrite(light, HIGH);
  } else if (DEBUG) {
    digitalWrite(light, LOW);
  }
}

void simulateButtonPress() {
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);   
  delay(100);
}
