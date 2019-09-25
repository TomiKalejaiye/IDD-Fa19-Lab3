// This borrows code from the SwitchState2 code provided in class

int endAddr;
float measuredVoltage[100];
const int voltage = A1;

void recordSetup() {
  state = 2;
  Serial.println("Writing to EEPROM");
  
  endAddr = min(sizeof(measuredVoltage), EEPROMSIZE);
}

void recordLoop() {
  if (analogRead(voltage) > 0){
    getVoltage();
    for (int i = 0; i < endAddr; i++) {
      EEPROM.write(i, measuredVoltage[i]);
    }
  Serial.println("Data committed to EEPROM!");  
  }
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void record() {
  if (switched == HIGH) {recordSetup();}
  recordLoop();
}

void getVoltage()
{
  for(int i=0; i<100; i++){
    measuredVoltage[i] = analogRead(voltage);
  }
}
