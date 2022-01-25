
//#define relayPin 1

int relayPin = 1;

int lampState = 2; // 0 = aus, 1 = fade-in-on, 2 = pulse

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  if (lampState == 0) {
    delay(1000);
    toggleNextState();
  } else if (lampState == 1) {
    delay(5000);
    toggleNextState();
  } else {
    toggleNextState();
  }
}

void toggleNextState() {
  Serial.print("current state: ");
  Serial.print(lampState);
  Serial.print("\n");
  
  digitalWrite(relayPin, LOW);
  delay(100);
  digitalWrite(relayPin, HIGH);
  delay(100);
  digitalWrite(relayPin, LOW); 

  lampState = (lampState + 1) % 3;
}
