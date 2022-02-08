#define led 16    // LOW sends the signal
#define button 5  // pressed is LOW
#define relay 4   // HIGH switches on
#define light 2 

int ledState = 0; // 0 = off; 1 = fade in; 2 = pulse
int lastButtonState = HIGH; // HIGH by default because of INPUT_PULLUP

void setup() {
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  
  delay(1000);

  digitalWrite(light, HIGH); // light is off on HIGH
  digitalWrite(led, HIGH);   // switch is active LOW, so we need HIGH by default
  digitalWrite(relay, HIGH); // turn on light strip by switching on the relay
}

void loop() {
  int value = digitalRead(button);

// handle button press
  if (value != lastButtonState) {
    lastButtonState = value;

    if (value == LOW) {
      toggleLedState();   
    }
  }

// Toggle light on NodeMCU for debugging
  if (ledState == 0) {
    digitalWrite(light, HIGH);
  } else {
    digitalWrite(light, LOW);
  }
}

void toggleLedState() {
  if (ledState == 0) {
    simulateButtonPress();
    ledState = 1;
  } else {
    simulateButtonPress();
    simulateButtonPress();
    ledState = 0;
  }
}

void simulateButtonPress() {
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);   
  delay(100);
}
