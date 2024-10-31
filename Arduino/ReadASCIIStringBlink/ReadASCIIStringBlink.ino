// READ ASCII STRING AND BLINK X TIMES

void setup() {
  // initialize serial:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(8000);
  Serial.println(__FILE__);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int blink = Serial.parseInt();

    if (Serial.read() == '\n') {

      Serial.printf("blink %d times\n", blink);
      for (int i = 0; i < blink; i++) {
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
        delay(500);                      // wait for a second
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
        delay(500);                      // wait for a second
      }
    }
  }
}
