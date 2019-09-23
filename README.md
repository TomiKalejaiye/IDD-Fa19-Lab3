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
3. Wires run from the other ends of the resistors to utput pins on the Arduino.

By addressing the output pins in an Arduino sketch we can now control the LED and display different colors. A demonstration
can be seen above.

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**

### 3. IR Proximity Sensor

**a. Describe the voltage change over the sensing range of the sensor. A sketch of voltage vs. distance would work also. Does it match up with what you expect from the datasheet?**

**b. Upload your merged code to your lab report repository and link to it here.**

## Optional. Graphic Display

**Take a picture of your screen working insert it here!**

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

**c. How many byte-sized data samples can you store on the Atmega328?**

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
