/**
*Upside Down World Team
*Kishan Patel
*Josh Band
*Last Revision: 11/22/17
**/

#include <msp430FR6989.h>
#include <LCDDriver.h>

//Variable to hold the rawTemperature value
volatile unsigned int rawTemp = 0;

//Function prototypes
void configureLCD(void);
void configureADC(void);
void configureTimer(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
	 // Disable the GPIO power-on default high-impedance mode to activate
      // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;


     
	  //Configure the LCD , ADC , and Timer
      configureLCD();
      configureADC();
      configureTimer();
	  //Turn the LCD On
      LCDCCTL0 |= LCDON;
      // Startup clock system with max DCO setting ~8MHz
      CSCTL0_H = CSKEY >> 8;                    // Unlock clock registers
      CSCTL1 = DCOFSEL_3 | DCORSEL;             // Set DCO to 8MHz
      CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
      CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
      CSCTL0_H = 0;                             // Lock CS registers


      
      int i = 0;
      while(1){
	  //Just Keep encoding repeatedly
          ADC12CTL0 |= ADC12ENC | ADC12SC;
      __bis_SR_register(LPM3_bits | GIE);       // Enter LPM3, interrupts enabled

      }







    return 0;
}
void configureLCD(void){
    PJSEL0 = BIT4 | BIT5;                   // For LFXT

       // Initialize LCD segments 0 - 21; 26 - 43
       LCDCPCTL0 = 0xFFFF;
       LCDCPCTL1 = 0xFC3F;
       LCDCPCTL2 = 0x0FFF;

       // Disable the GPIO power-on default high-impedance mode
       // to activate previously configured port settings
       PM5CTL0 &= ~LOCKLPM5;

       // Configure LFXT 32kHz crystal
       CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
       CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
       do
       {
         CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
         SFRIFG1 &= ~OFIFG;
       }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
       CSCTL0_H = 0;                           // Lock CS registers

       // Initialize LCD_C
       // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
       LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

       // VLCD generated internally,
       // V2-V4 generated internally, v5 to ground
       // Set VLCD voltage to 2.60v
       // Enable charge pump and select internal reference for it
       LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

       LCDCCPCTL = LCDCPCLKSYNC;               // Clock synchronization enabled

       LCDCMEMCTL = LCDCLRM;                   // Clear LCD memory

      




}

void configureADC(void){
    P1SEL1 |= BIT3;                         // Configure P1.1 for ADC
    P1SEL0 |= BIT3;
    ADC12CTL0 = ADC12SHT0_15 | ADC12ON;       // Sampling time, ADC12 on
      ADC12CTL1 = ADC12SHP | ADC12CONSEQ_2;                     // Use sampling timer
      ADC12CTL2 |= ADC12RES_2;                  // 12-bit conversion results
      ADC12MCTL0 |= ADC12INCH_3 | ADC12VRSEL_0;     // Channel2 ADC input select; Vref=AVCC
     ADC12IER0 |= ADC12IE0;
      ADC12CTL0 |= ADC12ENC | ADC12SC;
}
//ADC ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
    {
        case ADC12IV_NONE:        break;    // Vector  0:  No interrupt
        case ADC12IV_ADC12OVIFG:  break;    // Vector  2:  ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;    // Vector  4:  Conversion time overflow
        case ADC12IV_ADC12HIIFG:  break;    // Vector  6:  ADC12BHI
        case ADC12IV_ADC12LOIFG:  break;    // Vector  8:  ADC12BLO
        case ADC12IV_ADC12INIFG:  break;    // Vector 10:  ADC12BIN
        case ADC12IV_ADC12IFG0:             // Vector 12:  ADC12MEM0 Interrupt
			//Since we are doing ADC 12 bit, we are multiply the value calculated in the 
			//ADCMem register by .8 ( 3.3/2^12)
            rawTemp = ADC12MEM0*.8;
          



                // Exit from LPM0 and continue executing main
                __bic_SR_register_on_exit(LPM3_bits|GIE);
            break;
        case ADC12IV_ADC12IFG1:   break;    // Vector 14:  ADC12MEM1
        case ADC12IV_ADC12IFG2:   break;    // Vector 16:  ADC12MEM2
        case ADC12IV_ADC12IFG3:   break;    // Vector 18:  ADC12MEM3
        case ADC12IV_ADC12IFG4:   break;    // Vector 20:  ADC12MEM4
        case ADC12IV_ADC12IFG5:   break;    // Vector 22:  ADC12MEM5
        case ADC12IV_ADC12IFG6:   break;    // Vector 24:  ADC12MEM6
        case ADC12IV_ADC12IFG7:   break;    // Vector 26:  ADC12MEM7
        case ADC12IV_ADC12IFG8:   break;    // Vector 28:  ADC12MEM8
        case ADC12IV_ADC12IFG9:   break;    // Vector 30:  ADC12MEM9
        case ADC12IV_ADC12IFG10:  break;    // Vector 32:  ADC12MEM10
        case ADC12IV_ADC12IFG11:  break;    // Vector 34:  ADC12MEM11
        case ADC12IV_ADC12IFG12:  break;    // Vector 36:  ADC12MEM12
        case ADC12IV_ADC12IFG13:  break;    // Vector 38:  ADC12MEM13
        case ADC12IV_ADC12IFG14:  break;    // Vector 40:  ADC12MEM14
        case ADC12IV_ADC12IFG15:  break;    // Vector 42:  ADC12MEM15
        case ADC12IV_ADC12IFG16:  break;    // Vector 44:  ADC12MEM16
        case ADC12IV_ADC12IFG17:  break;    // Vector 46:  ADC12MEM17
        case ADC12IV_ADC12IFG18:  break;    // Vector 48:  ADC12MEM18
        case ADC12IV_ADC12IFG19:  break;    // Vector 50:  ADC12MEM19
        case ADC12IV_ADC12IFG20:  break;    // Vector 52:  ADC12MEM20
        case ADC12IV_ADC12IFG21:  break;    // Vector 54:  ADC12MEM21
        case ADC12IV_ADC12IFG22:  break;    // Vector 56:  ADC12MEM22
        case ADC12IV_ADC12IFG23:  break;    // Vector 58:  ADC12MEM23
        case ADC12IV_ADC12IFG24:  break;    // Vector 60:  ADC12MEM24
        case ADC12IV_ADC12IFG25:  break;    // Vector 62:  ADC12MEM25
        case ADC12IV_ADC12IFG26:  break;    // Vector 64:  ADC12MEM26
        case ADC12IV_ADC12IFG27:  break;    // Vector 66:  ADC12MEM27
        case ADC12IV_ADC12IFG28:  break;    // Vector 68:  ADC12MEM28
        case ADC12IV_ADC12IFG29:  break;    // Vector 70:  ADC12MEM29
        case ADC12IV_ADC12IFG30:  break;    // Vector 72:  ADC12MEM30
        case ADC12IV_ADC12IFG31:  break;    // Vector 74:  ADC12MEM31
        case ADC12IV_ADC12RDYIFG: break;    // Vector 76:  ADC12RDY
        default: break;
    }
}
//Set up timer
void configureTimer(void){
    TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
    TA0CCR0 = 1500;
    TA0CTL = TASSEL_1 | MC_1;
}
//Function to display the current temperature saved to the LCD 
void updateDisplay(void){
    showChar( (char) (rawTemp/100)+48 ,3);
    showChar((char)((rawTemp/10)%10)+48,4);
    showChar('A',5);
    showChar((char)(rawTemp%10)+48,6);
}
//ISR for the timer, used to update the display (meaning that the currently displayed temperature
//may not necessarily be the measured temperature
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  updateDisplay();                         // Add Offset to TA0CCR0
}


