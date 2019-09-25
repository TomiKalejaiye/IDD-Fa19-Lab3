// This borrows code from the SwitchState2 code provided in class
float value;

void playSetup() {
  state = 1;
  Serial.println("Reading from EEPROM");
  for (int i = 0; i < EEPROMSIZE; i++) {
    value = EEPROM.read(i);
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("Done reading from EEPROM");
}

void playLoop() {
  
}

void play() {
  if (switched == HIGH) { playSetup(); }
  playLoop();
}
