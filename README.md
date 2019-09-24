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

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

The voltage values range from about 0 to 990, corresponding to 0V to about 4.8V

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship of voltage to force applied appears not to be linear. It seems to be more exponential. However it is very difficult to tell, because I am likely not increasing the force linearly.

The resistance of the sensor has an inverse relationship with the force applied (k/F, where k is some constant). From voltage divider equation, we know that the Vout = (R2/(R1+R2))Vin. In this case, R2 is the constant resistor, and R1 is the force sensor. Subsitituting 1/F for R1 we get: Vout = (R2/((k/F)+R2))Vin. This is the relationship of voltage as a function of force applied. This implies an approximately linear response that asymptotically approaches Vin.

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

Assuming we are taking the input from the FSR's voltage divider circuit into the Arduino and outputting a voltage to the LED based on this, we could use Arduino's map() function to map the input voltages from the FSR's range of 0 to 990 to the LED's full range of 0 to 255. 

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

### 2. Accelerometer
 
[Accelerometer Readout Code](https://github.com/TomiKalejaiye/IDD-Fa19-Lab3/blob/master/LCDacceldemo.ino)

## Graphic Display

![Working OLED Display](https://imgur.com/QwcrOHM.jpg)

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

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

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
