#define led 16    // LOW sends the signal
#define relay 4   // HIGH switches on
#define light 2 

int ledState = 0; // 0 = off; 1 = fade in; 2 = pulse


void setupLEDs() {
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);
  
  delay(1000);

  digitalWrite(light, HIGH); // light is off on HIGH
  digitalWrite(led, HIGH);   // switch is active LOW, so we need HIGH by default
  digitalWrite(relay, HIGH); // turn on light strip by switching on the relay

  Serial.println("LEDs initialized");
}

void turnOn() {
  digitalWrite(relay, HIGH);
  delay(200);
  
  if (ledState == 0) {
    simulateButtonPress();
    ledState = 1;
  }

  updateOnBoardLamp();
}

void turnOff() {
  digitalWrite(relay, LOW);
  ledState = 0;

  updateOnBoardLamp();
}

void toggleLedState() {
  digitalWrite(relay, HIGH);
  delay(100);
  
  if (ledState == 0) {
    Serial.println("Turning on LEDs");
    simulateButtonPress();
    ledState = 1;
  } else {
    Serial.println("Turning off LEDs");
    simulateButtonPress();
    simulateButtonPress();
    ledState = 0;
  }

  updateOnBoardLamp();
}

void updateOnBoardLamp() {
  if (ledState == 0) {
    digitalWrite(light, HIGH);
  } else {
    digitalWrite(light, LOW);
  }
}

void simulateButtonPress() {
  Serial.println("Pressing button");
  
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);   
  delay(100);
}
