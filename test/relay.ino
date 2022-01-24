#define relayPin 2

void setup() {
  setMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, LOW)

  delay(1000);

  digitalWrite(relayPin, HIGH)
}
