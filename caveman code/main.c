#include <msp430g2553.h>
// Global variables
unsigned volatile int rawTemp=0;
unsigned volatile int ADC_value2 = 0;
volatile int asciiTemp [5] ;

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
                       // ADC set-up function call
        configureUART();
        __enable_interrupt();           // Enable interrupts.

        while(1)
        {
            ConfigureAdc();
            __delay_cycles(100000);               // Wait for ADC Ref to settle
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            __delay_cycles(100000);
            ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
            __bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
//            ADC_value1 = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value

        }

    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    ADC10CTL0 &= ~(ENC + ADC10SC);
    rawTemp = ADC10MEM*3.47;
    asciiTemp[0] = rawTemp/100;
        asciiTemp[1] = (rawTemp/10)%10;
        asciiTemp[2] = 71;
        asciiTemp[3] = rawTemp%10;
        asciiTemp[4] = 32;
        volatile int i=0;
        volatile int j = 0;

        for(i=0;i<5;i++){
            while (!(IFG2&UCA0TXIFG));
           // j = convertToASCII(asciiTemp[i]);
            UCA0TXBUF = convertToASCII(asciiTemp[i]);
        }
        /**
        UCA0TXBUF = convertToASCII(asciiTemp[0]);
        UCA0TXBUF = convertToASCII(asciiTemp[1]);
        UCA0TXBUF = convertToASCII(asciiTemp[2]);
        UCA0TXBUF = convertToASCII(asciiTemp[3]);
        **/
    /**
    asciiTemp[0] = rawTemp/100;
    asciiTemp[1] = (rawTemp/10)%10;
    asciiTemp[2] = 71;
    asciiTemp[3] = rawTemp%10;
    **/
/**
    UCA0TXBUF = rawTemp/100;
    UCA0TXBUF = (rawTemp/10)%10;
    UCA0TXBUF = 71;
    UCA0TXBUF = rawTemp%10;
**/
 //   IE2 |= UCA0TXIE;


    ADC10CTL0 &=~ADC10IFG;
    __bic_SR_register_on_exit(CPUOFF + GIE);        // Return to active mode }
}
/**
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void){
    volatile int i = 0;

      while (!(IFG2&UCA0TXIFG));               // USCI_A0 TX buffer ready?
      volatile int j=0;
      for(j;j<3;j++){
          i = convertToASCII(asciiTemp[j]);



        UCA0TXBUF = (char) i;
      }
      //  UCA0TXBUF = convertToASCII(asciiTemp[1]);
       // UCA0TXBUF = convertToASCII(asciiTemp[2]);
       // UCA0TXBUF = convertToASCII(asciiTemp[3]);
    //UCA0TXBUF = '7';


    IE2 &= ~UCA0TXIE;

}

**/
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

// Function containing ADC set-up
void ConfigureAdc(void)
{

    ADC10CTL1 = INCH_3 + ADC10DIV_3 + CONSEQ_2 ;         // Channel 3, ADC10CLK/3
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE + MSC;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
    ADC10AE0 |= BIT3;                         // ADC input enable P1.3
}

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
  //  IE2 |= UCA0TXIE;                          // Enable USCI_A0 TX interrupt
}
