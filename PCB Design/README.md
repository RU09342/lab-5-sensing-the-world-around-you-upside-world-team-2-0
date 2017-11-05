# PCB Design
This PCB consists of an MSP430FR2311 chip, a bulk and bypass capacitor, two 8-pin headers, a capacitor to stop debouncing and a pull-up resistor.  This PCB was designed to be a breakout board for the MSP430FR2311.  Each part is helps the chip function correctly. The 10 uF capacitor provides emergency voltage to the MSP430 in case there is a voltage drop from a power supply.  The bypass capacitor filters out an noise.  The 1 nF capacitor is used to send any AC noise to ground.  There is also a reset header on this PCB design which is created from a 47k Ohm pullup resistor.  This occurs because the MSP430 reads a logic "ON" when the reset button is turned off, and is reset when a certain button is pressed. 

Below is a link to the cart that has all of the parts that are needed to be bought.  Also below is a table for a bill of materials for this breakout board.

https://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=6f11333891

![](https://github.com/RU09342/lab-5-sensing-the-world-around-you-upside-world-team-2-0/blob/master/PCB%20Design/Bill%20of%20Materials.PNG)
