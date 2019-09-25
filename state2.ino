// This borrows code from Examples->EEPROM->eeprom_write

//String textarray = "hello cornell tech!";
int endAddr;
float measuredVoltage[100];
const int voltage = A1;

void state2Setup() {
  digitalWrite(ledPin, LOW);
  Serial.println("Writing to EEPROM");
  
  //if any of the pin settings for the different states differed for the different states, you could change those settings here.
  endAddr = min(sizeof(measuredVoltage), EEPROMSIZE);
}

void state2Loop() {
  if (analogRead(voltage) > 0){
    getVoltage();
    for (int i = 0; i < endAddr; i++) {
      EEPROM.write(i, measuredVoltage[i]);
    }
  Serial.println("Data committed to EEPROM!");  
  }
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void doState2() {
  if (lastState != 2) state2Setup();
  state2Loop();
}

void getVoltage()
{
  for(int i=0; i<100; i++){
    measuredVoltage[i] = analogRead(voltage);
  }
}
