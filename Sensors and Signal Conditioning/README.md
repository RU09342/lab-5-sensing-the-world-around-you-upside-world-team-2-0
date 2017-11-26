# Sensors and Signal Conditioning
## Summary
The purpose of this lab was to understand how to bring a microcontroller over to the analog world.  In order to talk with analog components there needs to be a translation from digital to analog.  In order to for this conversion to work a sensor is used to read a voltage, current, or resistance.  A signal conditioning block is then used convert that measurement into a voltage.  That voltage may be too high or too low for the microcontroller to read so the signal may need to be changed, whether amplified of filtered.

## Sensors

### Temperature Sensor - Voltage
#### Hardware
The temperature sensor that was used in this lab was an LM35.  The LM35 can be shown in the picture below.  The LM35 reads every 10 mV as one degree celcius.  The output of the LM35 is hooked up directly to the ADC on the microcontroller.  The temperature sensor reads out a voltage. 
![LM35 Circuit](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Voltage_LM35_Temp/LM35Circuit.JPG "LM35 Circuit")

#### Software

### Phototransistor - Current
#### Hardware
The phototransitor is made up of an OP805SL.  The circuit is shown below.  The phototransitor is sensitive to light in that it allows more current to pass through when more light shines on it.  When less light shines on it it doesn't allow as much current to go through.  Depending on the resistor size would determine how sensitive the phototransitor would be.
![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Current_PhotoTransistor/PhotoResistorCircuit.JPG "PhotoResistor Circuit")

#### Software

### Thermistor - Resistance
#### Hardware

![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/Sensors%20and%20Signal%20Conditioning/Resistance_Thermistor/Thermistor%20Circuit.JPG "Thermistor Circuit")

#### Software
