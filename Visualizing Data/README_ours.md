#Visualising Data
##Methods chosen
In order to visualise the data being read from the sensors, three different methods are used.
1. UART
2. LCD screen
3. MATLAB

###Bill of Materials
The three data visualisation techniques all require different materials. Below each section will be a set of numbers
that will be keys to the Materials listed below, designating what is needed to implement the different data 
visualisation techniques.
1. MSP430G2553
2. MSP430FR6989
3. LM35 Temperature sensor
4. Subscription to MATLAB
5. Putty

####LM35 Temperature sensor
In order to understand how to implement any of these data visualisation methods, it is important to understand
how the LM35 works. The pinout for the LM35 can be seen below:
[![LM35 pinout](/pictures/LM35.jpg)]
VCC represents the reference voltage (in this case taken directly from the 3.3 rail of the MSP430,
Out connects to the ADC pin on the board,
GND connects to the Ground pin on the board.

The LM35 is a linear temperature sensor, meaning that the measured output voltage will vary linearly with temperature.
The linear constant by with the temperature varies with voltage is 10mV/C.
According to the datasheet, the sensor is rated for temperatures between -55C and 150C. Note, there are two
different ways to set up this circuit. They are both shown below:
[![LM35 pinout](/pictures/LM35_basic.jpg)]
[![LM35 pinout](/pictures/LM35_with_neg.jpg)]

The basic configuration is used in this case. This will give us a voltage range between 2C to 150C. Since this 
is a linear sensor, a negative voltage would be needed to measure negative temperatures. For these implementations,
we are limited to temperatures between 0C and 99C, as it is not expected to need to go outside this range 
for this particular implementation.

####UART
Required: 1,3,5
Data is streamed via UART over a serial connection to the laptop. UART is configured at a 9600 Baud Rate. For the
purpose of this demonstration, 10 bit ADC is used on the MSP430G2553. Externally, an LM35 Temperature sensor
is used to measure the temperature. This temperature is then manipulated to represent degrees celsius, and sent
over UART to the PC. The values that are read by the MSP are converted to ASCII representations, and displayed
on a serial communication application. In this case, Putty is used. An example of this can be seen below:
[![LM35 pinout](/pictures/example_UART.jpg)]

####LCD
Required: 2,3
