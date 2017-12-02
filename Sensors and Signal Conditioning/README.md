# Sensors and Signal Conditioning
## Summary
The purpose of this lab was to understand how to bring a microcontroller over to the analog world.  In order to talk with analog components there needs to be a translation from digital to analog.  In order to for this conversion to work a sensor is used to read a voltage, current, or resistance.  A signal conditioning block is then used convert that measurement into a voltage.  That voltage may be too high or too low for the microcontroller to read so the signal may need to be changed, whether amplified of filtered.

## Sensors
There are three different types of sensors that are used in this lab.  The first being a temperature sensor.  A temperature sensor, which can also be called a thermistor are thermally sensitvive resistors that change resistance when there is a change in termperature.  Another sensor being used is a phototransistor.  A phototransistor or photodiode is a semiconductor device that converts light into an electrical current.  More current is generated when more light shines on the diode.

## ADC
The analog to digital converter (ADC) will create a proper voltage that a MSP board can read.  The MSP430g2553 uses ADC10, which is a 10 bit converter. It has a voltage range from 0=5V and can be divided by the number of total bits.  The MSP4305994 uses an ADC12, which means the data has a 12 bit limit.  This allows more bits to be availble to provide more detailed values.


### Temperature Sensor - Voltage
#### Hardware
![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/pictures/LM35.jpg)
The temperature sensor that was used in this lab was an LM35.  The LM35 can be shown in the picture below.  The LM35 reads every 10 mV as one degree celcius.  The output of the LM35 is hooked up directly to the ADC on the microcontroller.  The temperature sensor reads out a voltage depending on a certain temperature.    The 6989 board was used since it had a LCD to read out the temperatures.  An LCD display driver was given in lab to output the temperature on this LCD.  A conversion rate based on the temperature sensor and its output was found with the following equation:  Temp (F) = Temp (C) * 9f/5f +32f.
![LM35 Circuit](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Voltage_LM35_Temp/LM35Circuit.JPG "LM35 Circuit")


### Phototransistor - Current
![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/pictures/phototransistor.jpg)
#### Hardware

The phototransitor is made up of an OP805SL.  The circuit is shown below.  The phototransitor is sensitive to light in that it allows more current to pass through when more light shines on it.  When less light shines on it it doesn't allow as much current to go through.  Depending on the resistor size would determine how sensitive the phototransitor would be.
![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Current_PhotoTransistor/PhotoResistorCircuit.JPG "PhotoResistor Circuit")


### Thermistor - Resistance
![]https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/pictures/Thermistor.jpg)
#### Hardware
A thermistor is a type of resistor whose resistance is dependent on temperature.  The thermisor decreases electrical resistance when the average temperature increases.  Thermistors are the preffered sensor for many applications that involve temperature measurement and control.

![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Resistance_Thermistor/Thermistor%20Circuit.JPG "Thermistor Circuit")

### Software
All of the software for this portion was relatively the same. ADC is used, and the voltage that is measured is then converted to a physical quantity (eg, voltage to temperature, and voltage to luminosity)
