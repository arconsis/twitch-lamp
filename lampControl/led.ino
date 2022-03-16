#define led 16    // LOW sends the signal
#define relay 4   // HIGH switches on
<<<<<<< HEAD
#define light 2 

int ledState = 0; // 0 = off; 1 = fade in; 2 = pulse


void setupLEDs() {
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);
  
=======
#define light 2

#define DEBUG 1

int ledState = 0; // 0 = off; 1 = fade in; 2 = pulse

void initializeLEDs() {
  Serial.println("Initializing LEDs");
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);

>>>>>>> main
  delay(1000);

  digitalWrite(light, HIGH); // light is off on HIGH
  digitalWrite(led, HIGH);   // switch is active LOW, so we need HIGH by default
  digitalWrite(relay, HIGH); // turn on light strip by switching on the relay
<<<<<<< HEAD

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
=======
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
  bool relayState = digitalRead();
  
  if (ledState == 0) {
    turnOnLed();
  } else {
    turnOffLed();
  }

// Toggle light on NodeMCU for debugging
  if (DEBUG && ledState == 0) {
    digitalWrite(light, HIGH);
  } else if (DEBUG) {
>>>>>>> main
    digitalWrite(light, LOW);
  }
}

void simulateButtonPress() {
<<<<<<< HEAD
  Serial.println("Pressing button");
  
=======
>>>>>>> main
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);   
  delay(100);
}
