//-----------------------------------------------------------------------------
// T60x_ADC0_ExternalInput.c
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
// --------------------
//
// This example code takes and averages 2048 analog measurements from input
// P0.1 using ADC0, then prints the results to a terminal window via the UART.
//
// The system is clocked by the internal 24.5MHz oscillator.  Timer 2 triggers
// a conversion on ADC0 on each overflow.  The completion of this conversion
// in turn triggers an interrupt service routine (ISR).  The ISR averages 
// 2048 measurements, then prints the value to the terminal via printf before
// starting another average cycle.
//
// The analog multiplexer selects P0.1 as the positive ADC0 input.  This 
// port is configured as an analog input in the port initialization routine.
// The negative ADC0 input is connected via mux to ground, which provides
// for a single-ended ADC input.
//
// A 100kohm potentiometer may be connected as a voltage divider between 
// VDD and AGND on the terminal strip as shown below:
//
// ---------
//          |        
//         o| P0.0 
//         o| GND-------------------|
//         o| AIN.6                 |<----|
//         o| P0.1/AIN.1-|    Vdd---|     |
//          |            |                |
//          |            |----------------| 
//          |
//----------   
// C8051T600-TB
//
// Terminal output is done via printf, which directs the characters to 
// UART0.  A UART initialization routine is therefore necessary.
//
// ADC Settling Time Requirements, Sampling Rate:
// ----------------------------------------------
//
// The total sample time per input is comprised of an input setting time 
// (Tsettle), followed by a conversion time (Tconvert): 
//
// Tsample  = Tsettle + Tconvert
//
// |--------Settling-------|==Conversion==|----Settling--- . . .
// Timer 2 overflow        ^                          
// ADC0 ISR                               ^       
//
// The ADC input voltage must be allowed adequate time to settle before the 
// conversion is made.  This settling depends on the external source
// impedance, internal mux impedance, and internal capacitance.
// Settling time is given by:
//
//                   | 2^n |
//    Tsettle =   ln | --- | * Rtotal * Csample
//                   | SA  |       
//
// In this application, assume a 100kohm potentiometer as the voltage divider.
// The expression evaluates to:
//
//                   | 2^8  |
//    Tsettle =   ln | ---- | * 105e3 * 5e-12 = 3.6uS
//                   | 0.25 |    
//
// In addition, one must allow at least 1.5uS after changing analog mux 
// inputs or PGA settings.  The settling time in this example, then, is 
// dictated by the large external source resistance.
//
// The conversion is 10 periods of the SAR clock <SAR_CLK>.  At 3 MHz, 
// this time is 10 * 400nS = 3.3 uS.
//
// 
// Tsample, minimum  = Tsettle + Tconvert
//                   = 3.6uS + 3.3uS
//                   = 6.9 uS
// 
// Timer 2 starts a conversion every 100uS, which is far longer 
// than the minimum required.
//
// T600 Resources:
// ---------------
// Timer1: clocks UART
// Timer2: overflow initiates ADC conversion
// Timer3: mS wait function
//
// How To Test:
// ------------
// 1) Download code to a 'T600 device on a C8051T600-TB development board
// 2) Connect serial cable from the transceiver to a PC
// 3) On the PC, open HyperTerminal (or any other terminal program) and connect
//    to the COM port at <BAUDRATE> and 8-N-1
// 4) Connect a variable voltage source (between 0 and Vref) 
//    to P0.1, or a potentiometer (J7) as shown above.
// 5) HyperTerminal will print the voltage measured by the device if
//    everything is working properly
//
// Target:         C8051T600
// Tool chain:     Keil C51 8.00 / Keil EVAL C51
// Command Line:   None
//
//
// Release 1.0 / 01 AUG 2008 (ADT)
//    - Initial Revision
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <compiler_defs.h>
#include <C8051T600_defs.h>            // SFR declarations
#include <stdio.h>

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK       24500000          // SYSCLK frequency in Hz
#define BAUDRATE     115200            // Baud rate of UART in bps

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SYSCLK_Init (void);
void PORT_Init (void);
void Timer2_Init(void);
void ADC0_Init(void);
void UART0_Init (void);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) 
{
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 
                                       // enable)

   SYSCLK_Init ();                     // Initialize system clock to 
                                       // 24.5MHz
   PORT_Init ();                       // Initialize crossbar and GPIO
   Timer2_Init();                      // Init Timer2 to generate 
                                       // overflows to trigger ADC
   UART0_Init();                       // Initialize UART0 for printf's
   ADC0_Init();                        // Initialize ADC0

   EA = 1;							         // enable global interrupts
   while (1);                          // spin forever

}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock to use the internal 24.5MHz 
// oscillator as its clock source.  Also enables missing clock detector reset.
//
//-----------------------------------------------------------------------------

void SYSCLK_Init (void)
{
   OSCICN |= 0x07;                        // configure internal oscillator for
                                          // its lowest frequency
   RSTSRC = 0x04;                         // enable missing clock detector
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
// P0.4 - UART TX (push-pull)
// P0.5 - UART RX 
// P0.1 - ADC0 analog input
// P0.2 - LED (push-pull)
// 
//-----------------------------------------------------------------------------

void PORT_Init (void)
{
   XBR0    = 0x0c;                     // skip Switch in crossbar 
                                       // assignments
   XBR1    = 0x03;                     // UART0 TX and RX pins enabled
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups
   P0MDOUT |= 0x10;                    // enable TX0 as a push-pull output
   P0MDIN &= ~0x01;                    // set P0.1 as an analog input
}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure Timer2 to 16-bit auto-reload and generate an interrupt at 100uS 
// intervals.  Timer 2 overflow automatically triggers ADC0 conversion.
// 
//-----------------------------------------------------------------------------

void Timer2_Init (void)
{
   TMR2CN  = 0x00;                      // Stop Timer2; Clear TF2;
                                        // use SYSCLK as timebase, 16-bit 
                                        // auto-reload
   CKCON |= 0x20;                       // Timer2 uses SYSCLK as its timebase
   TMR2RL  = 65536 - (SYSCLK / 10000);  // init reload value for 10uS
   TMR2    = 0xffff;                    // set to reload immediately
   ET2 = 0;                             // disable Timer2 interrupts
   TR2 = 1;		                         // start Timer2
}

//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configures ADC0 to make single-ended analog measurements on pin P0.1
//  
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   ADC0CN = 0x02;                      // ADC0 disabled, normal tracking, 
                                       // conversion triggered on TMR2 overflow

   REF0CN = 0x0A;                      // Enable VDD as VREF and buffer
   AMX0SL = 0x81;					         // ADC0 positive input = P0.1
   						                  // ADC0 negative input = GND
                                       // i.e., single ended mode

   ADC0CF = ((SYSCLK/3000000)-1)<<3;   // set SAR clock to 3MHz
   ADC0CF |= 0x04;                     // ADC 8 bit mode
   ADC0CF |= 0x01;                     // set internal amplifer gain to 1

   EIE1 |= 0x04;                       // enable ADC0 EOC interrupt

   AD0EN = 1;                          // enable ADC0
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
//-----------------------------------------------------------------------------

void UART0_Init (void)
{
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |= 0x10;                   // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON |=  0x01;                  // T1M = 0; SCA1:0 = 01
      CKCON &= ~0x12;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x13;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON |=  0x02;                  // T1M = 0; SCA1:0 = 10
      CKCON &= ~0x11;
   }

   TL1 = 0xff;                         // set Timer1 to overflow immediately
   TMOD |= 0x20;                       // TMOD: timer 1 in 8-bit autoreload
   TMOD &= ~0xD0;                      // mode
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ADC0_ISR
//-----------------------------------------------------------------------------
// 
// This ISR averages 2048 samples then prints the result to the terminal.  The 
// ISR is called after each ADC conversion which is triggered by Timer2.
//
//-----------------------------------------------------------------------------
INTERRUPT (ADC0_ISR, INTERRUPT_ADC0_EOC)
{

   static U32 accumulator = 0;         // Accumulator for averaging
   static U16 measurements = 2048;     // Measurement counter
   U32 result=0;
   U32 mV;                             // Measured voltage in mV
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conv. complete flag

   accumulator += ADC0H;
   measurements--;

   if(measurements == 0)
   {  
      measurements = 2048;
      result = accumulator / 2048;
      accumulator=0;

      // The 8-bit ADC value is averaged across 2048 measurements.  
      // The measured voltage applied to P0.1 is then:
      //
      //                           Vref (mV)
      //   measurement (mV) =   --------------- * result (bits) 
      //                       (2^8)-1 (bits)

      mV =  result * 3270 / 255;   
      printf("P0.1 voltage: %ld mV\n",mV);
   }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
