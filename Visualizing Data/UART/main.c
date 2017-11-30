/*
*Upside Down World Team
*Kishan Patel
*Josh Band
*Last Revision: 11/22/17
*/

* ============================================================================ */
/* Copyright (c) 2017, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430FR6989 devices.
***********************************************************************************/

#include <msp430g2553.h>
//Used for storing the raw Temperature value
unsigned volatile int rawTemp=0;
//Used to store each digit of the temperature ( tens, ones, decimal point, tenths, space)
unsigned volatile int asciiTemp [5] ;

// Function prototypes
void ConfigureAdc(void);
void configureUART(void);




void main(void)
{
    {

        WDTCTL = WDTPW + WDTHOLD;       // Stop WDT
        BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
        BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
        P1SEL |= BIT3;                  // ADC input pin P1.3
        
		//Function to set up UART
        configureUART();
        __enable_interrupt();           // Enable interrupts.

        while(1)
        {
			//Function to set up ADC
            ConfigureAdc();
			//Delay between ADC conversions.
            __delay_cycles(100000);               
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
            __bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled


        }

    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	//Ensure that we are not doing any ADC calculations during this interrupt
    ADC10CTL0 &= ~(ENC + ADC10SC);
	//Convert the raw temperature to a voltage value in millivolts.
	//This code is configured for the LM35 Temperature Sensor.
    rawTemp = ADC10MEM*3.47;
	
	//Take the tens place
    asciiTemp[0] = rawTemp/100;
	//Take the ones place
    asciiTemp[1] = (rawTemp/10)%10;
	//Ascii value for period
    asciiTemp[2] = 71;
	//Take the tenths place
    asciiTemp[3] = rawTemp%10;
	//Ascii value for space
    asciiTemp[4] = 32;
    

        for(i=0;i<5;i++){
            while (!(IFG2&UCA0TXIFG));
           //Transmit the contents of the asciitemp array
            UCA0TXBUF = convertToASCII(asciiTemp[i]);
        }
       

	//reset the ADC interrupt flag
    ADC10CTL0 &=~ADC10IFG;
    __bic_SR_register_on_exit(CPUOFF + GIE);        // Return to active mode }
}
//Function for converting an int to its respective ASCII value.
int convertToASCII(int converting){
    switch(converting){
                    case 0:
                        return 48;
                        break;
                    case 1:
                        return 49;
                        break;
                    case 2:
                        return 50;
                        break;
                    case 3:
                        return 51;
                        break;
                    case 4:
                        return 52;
                        break;
                    case 5:
                        return 53;
                        break;
                    case 6:
                        return 54;
                        break;
                    case 7:
                        return 55;
                        break;
                    case 8:
                        return 56;
                        break;
                    case 9:
                        return 57;
                        break;
                    case 71:
                        return 46;
                        break;
                    default:
                        return 32;
                        break;
    }

}

// Function containing ADC set up
void ConfigureAdc(void)
{

    ADC10CTL1 = INCH_3 + ADC10DIV_3 + CONSEQ_1 ;         // ADC input channel 3, divider of 3, single channel, repeated
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE + MSC;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
    ADC10AE0 |= BIT3;                         // ADC input enable P1.3
}
//Funciton containing UART set up
void configureUART(void){
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 104;                            // 1MHz 9600
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
