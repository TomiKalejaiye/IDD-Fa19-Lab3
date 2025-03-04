# Data Logger (and using cool sensors!)

*A lab report by Tomi Kalejaiye.*

## In The Report

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**

The raw analog values being read are from 0 to 1024. These correspond to voltages from 0V to 5V.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**

The ADC on Arduino Uno has a max resolution of 10 bits. A table for bit resolution on each Arduino board can be seen on the documentation for the analogRead() function.

## Part B. RGB LED

[![RGB LED Lightshow](http://img.youtube.com/vi/viU_miL-xek/0.jpg)](https://www.youtube.com/watch?v=viU_miL-xek)

**How might you use this with only the parts in your kit? Show us your solution.**

1. A cable must be run from the power rail to the common anode pin (longest pin) on the LED.
2. Resistors placed at each of the three remaining pins. This is to prevent too large of a voltage drop across the LED.
3. Wires run from the other ends of the resistors to output pins on the Arduino.

By addressing the output pins in an Arduino sketch we can now control the LED and display different colors. A demonstration
can be seen above.

The code used was from Adafruit Arduino Lesson 3.

```
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE;
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
```

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

[![Flex Sensor Response on Serial Plotter](http://img.youtube.com/vi/iBb9lkzekFg/0.jpg)](https://www.youtube.com/watch?v=iBb9lkzekFg)

**a. What voltage values do you see from your force sensor?**

The voltage values range from about 0 to 990, corresponding to 0V to about 4.8V

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship of voltage to force applied appears not to be linear. It seems to be more exponential. However it is very difficult to tell, because I am likely not increasing the force linearly.

The resistance of the sensor has an inverse relationship with the force applied (k/F, where k is some constant). From voltage divider equation, we know that the Vout = (R2/(R1+R2))Vin. In this case, R2 is the constant resistor, and R1 is the force sensor. Subsitituting 1/F for R1 we get: Vout = (R2/((k/F)+R2))Vin. This is the relationship of voltage as a function of force applied. This implies an approximately linear response that asymptotically approaches Vin.

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

Assuming we are taking the input from the FSR's voltage divider circuit into the Arduino and outputting a voltage to the LED based on this, we could use Arduino's map() function to map the input voltages from the FSR's range of 0 to 990 to the LED's full range of 0 to 255. 

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

I used 10K resistors for all of the sensors. 

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

The softpot appears to have a linear relationship. For the others, it is unclear, as I was not entirely sure I was varying their properties uniformly in the first place.

### 2. Accelerometer

[![LCD Accelerometer Readout](http://img.youtube.com/vi/sdidXR9ATxI/0.jpg)](https://www.youtube.com/watch?v=sdidXR9ATxI)

[Accelerometer Readout Code](https://github.com/TomiKalejaiye/IDD-Fa19-Lab3/blob/master/LCDacceldemo.ino)

[![Accelerometer LED Mapped Lightshow](http://img.youtube.com/vi/m6MSwwDDkrs/0.jpg)](https://www.youtube.com/watch?v=m6MSwwDDkrs)

*Accelerometer mapped to LED.*

## Graphic Display

![Working OLED Display](https://imgur.com/QwcrOHM.jpg)

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

*Note, as the SwitchState2 code currently functions, in state1, all that will be read out is byte values from the EEPROM. In order to actually see the string saved to the EEPROM the type of the variable "value" has to be changed to type char, and that can be typecast to String. The code that implements this can be seen below. It is a modification of the state1 code.*

```
// This borrows code from Examples->EEPROM->eeprom_read

char value;

void state1Setup() {
  Serial.println("Reading from EEPROM");

  for (int i = 0; i < EEPROMSIZE; i++) {
    value = EEPROM.read(i);
    Serial.print(String(value));
  }
  Serial.println();

  Serial.println("Done reading from EEPROM");
}

void state1Loop() {
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}

void doState1() {
  if (lastState != 1) { state1Setup(); }
  state1Loop();
}
```



**a. Does it matter what actions are assigned to which state? Why?**

It doesn't matter which actions are assigned to which state, as long as we know, and keep track of that information. That is to say, if we changed which action was associated with each state, the potentiometer position associated with each state would also be different. 

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

The code in state0.ino, state1.ino, and state2.ino is being called in SwitchState2.ino. The other files are simply defining these functions. They won't be called independently, so they don't need a loop() function.

**c. How many byte-sized data samples can you store on the Atmega328?**

Since the Atmega328's EEPROM can store 1024 bytes of data, we can store 1024 byte sized data samples.

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

The default resolution of the Arduino's ADC is its max of 10 bits, so the analogRead() funtion returns 10 bit values (0-1023) from the analog pins. However the EEPROM stores and addresses data in bytes which are 8 bits (representing values 0-255). To get around this we can use the analogReadResolution() function to set the analogRead() resolution to 8 bits, so it will return 8 bit values.  According to the I2C protocol, data is always sent in 8-bit chunks anwyays, so we wouldn't need to do anything to the analog data from I2C devices.

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

We would have to use multiple addresses. We would start at one address, write a byte, then continue to the next and write until we've written the entire value.

**I modified the code in state2.ino from the SwitchState2 code which uses a pot to switch between reading, writing, and clearing states. I modified state2, the writing state, to write 100 analog values to the EEPROM rather than a constant string. I used the force sensor voltage divider circuit from before to test this code. The code can be found [here](https://github.com/TomiKalejaiye/IDD-Fa19-Lab3/blob/master/state2.ino)**

### 2. Design your logger

My logger simply takes an analog input from a force sensor and writes it to the EEPROM. You can than read it back by changing the mode or "state" of the Arduino sketch. I controlthe state by pressing a button. I use the button on a rotary encoder because I already happened to have it wired but any button can be used.

 ![Logger State Diagram](https://github.com/TomiKalejaiye/IDD-Fa19-Lab3/blob/master/StateDiagram.jpg)
 
 There are actually 4 states here. The way my code is written does not make this explicit so I'd like to clarify here. When initially uploaded to the Arduino, my code reads the EEPROM and outputs its contents to the serial monitor. This state is what I call S1 or "READING". When it is finished reading, it goes into the state I call S2 or "READ". In this state nothing happens. If I then press the button I've wired to the Arduino, the state changes to S3 which is "WRITE". In this state, nothing will happen, unless a force is applied to the force sensor. Once a force is applied, we wnter S4 or "WRITING". In this state, the force sensor's analog values are actually being written to the EEPROM. Once no more force is being applied to the sensor, we re-enter "WRITE", and will remain there doing nothing until either a force is applied again (which would repeat the loop), or the button is pressed, which would take us back to "READING" and read out what we have written.
 
 The code for my datta logger can be found [here](https://github.com/TomiKalejaiye/IDD-Fa19-Lab3/blob/master/DataLogger.ino).
 
 *Note: I refer to "play" and "record" in my code. This is because I intend to ultimately use a speaker to play the saved analog voltages. For now it simply displays them on the serial monitor.*

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**

[![My Datalogger](http://img.youtube.com/vi/fgMbgL2Uqwc/0.jpg)](https://www.youtube.com/watch?v=fgMbgL2Uqwc)
