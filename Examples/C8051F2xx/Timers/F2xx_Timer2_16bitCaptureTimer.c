//-----------------------------------------------------------------------------
// F2xx_Timer2_16bitCaptureTimer.c
//-----------------------------------------------------------------------------
// Copyright 2005 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer2 of the C8051F2xx's in
// 16-bit capture mode. It uses the 'F2xxDK as HW platform.
//
// In this example code the TRIGGER I/O toggles at a fixed rate. This I/O pin
// is connected to the capture input associated with the Timer2. When the
// trigger pin goes up the capture begins and stops when it goes down.
// Once the capture is finished an interrupt is generated and the Timer2 ISR
// reads the captured values from RCAP2H/L into global variables and toggles
// the LED.
//
// Pinout:
//
//    P0.7 - T2EX
//
//    P1.1 - OVERFLOW output (pin toggled if Timer2 overflows)
//
//    P1.5 - TRIGGER output (to be input to T2EX and cause a capture)
//
//    P2.4 - LED (pin 21 on the 'F005 TB)
//
//    all other port pins unused
//
// Connections:
//
// P1.5(TRIGGER) <--> P0.7(T2EX) (pin 6 to pin 12 on the 'F2xx TB)
//
// How To Test:
//
// 1) Open the F2xx_Timer2_16bitCaptureTimer.c file in the IDE
// 2) If a different trigger pulse size is necessary change the value of
//    SOFTWARE_DELAY. If this value is too large, Timer2 will overflow before
//    the capture pulse occurs, causing an unwanted Timer2 interrupt (seen
//    on the OVERFLOW pin).
// 3) Connect P1.5(TRIGGER) <--> P0.7(T2EX)
// 4) Verify the LED jumper is populated on the 'F2xx TB.
// 5) Compile and download the code
// 6) Run the code
// 7) Check the Capture Value in CaptureValue.(LED toggles at every capture)
//
//
// FID:            2XX000012
// Target:         C8051F2xx
// Tool chain:     KEIL C51 7.20 / KEIL EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CG)
//    -13 March 2006
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F200.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SOFTWARE_DELAY           32000 // Number of counts for the software
                                       // timer for capture pulse toggling.
                                       // If this value is too large, Timer2
                                       // will overflow before the capture
                                       // pulse occurs, causing an unwanted
                                       // Timer2 interrupt (seen on the
                                       // OVERFLOW pin).

sbit TRIGGER = P1^5;                   // Pin used to trigger capture by Timer2
sbit LED = P2^4;                       // LED='1' means ON
sbit OVERFLOW = P1^1;                  // Capture counter overflow warning Pin


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

unsigned int CaptureValue;             // Contains the value of the timer
                                       // captured by the external trigger

sfr16 RCAP2 = 0xCA;                    // Timer2 reload register
sfr16 TMR2 = 0xCC;                     // Timer2 register

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void Port_Init (void);                 // Port initialization routine
void Timer2_Init (void);               // Timer2 initialization routine

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   unsigned int captureCounter;

   WDTCN = 0xDE;                       // Disable watchdog timer
   WDTCN = 0xAD;

   Timer2_Init ();                     // Initialize the Timer2
   Port_Init();                        // Init Ports
   EA = 1;                             // Enable global interrupts

   while (1)
   {
      // This loop waits SOFTWARE_DELAY counts before toggling the TRIGGER
      // input.  The positive edge starts the capture process and the negative
      // edge stops the capture and generates the interrupt.
      for(captureCounter=0; captureCounter < SOFTWARE_DELAY; captureCounter++);
      TRIGGER=~TRIGGER;
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the crossbar and GPIO ports.
//
//    P0.7 - T2EX
//
//    P1.1 - OVERFLOW output (pin toggled if Timer2 overflows)
//
//    P1.5 - TRIGGER output (to be input to T2EX and cause a capture)
//
//    P2.4 - LED
//
//    all other port pins unused
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
   PRT1CF = 0x22;                      // Set LED and TRIGGER to push-pull
                                       // and also P1.1 for overflow
   PRT2CF = 0x10;
   PRT0MX = 0x80;                      // Enable T2EX at port pin
}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Timer2 as 16-bit capture,interrupt enabled.
// It uses the SYSCLK at 16MHz/8 and also a timer prescaler of 1:12.
//-----------------------------------------------------------------------------
void Timer2_Init(void)
{
   T2CON = 0x0D;                       // T2EX transition enable capture
                                       // Timer 2 enabled, capture enabled
   ET2=1;                              // Timer2 interrupt enabled
}


//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer2_ISR
//-----------------------------------------------------------------------------
//
// Here we process the timer interrupt and toggle the LED.  If the interrupt is
// caused by a Timer2 overflow, the OVERFLOW pin is toggled.  If the interrupt
// is caused by a capture event, the LED is toggled.
//
//-----------------------------------------------------------------------------
void Timer2_ISR (void) interrupt 5
{
   if(EXF2)
   {
      EXF2 = 0;                        // Reset Capture Flag
      TMR2 = 0;                        // Reset Timer2 reg. to avoid
                                       // interrupt
      CaptureValue = RCAP2;            // Save capture registers
      LED = ~LED;                      // Toggle the LED
   }
   else if(TF2)
   {
      TF2 = 0;
      OVERFLOW = ~OVERFLOW;            // Any eventual overflow will be
                                       // shown in the overflow I/O Pin
   }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------