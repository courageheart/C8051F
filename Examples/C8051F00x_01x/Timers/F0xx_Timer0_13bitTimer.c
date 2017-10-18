//-----------------------------------------------------------------------------
// F0xx_Timer0_13bitTimer.c
//-----------------------------------------------------------------------------
//
// Copyright 2005 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer0 of the C8051F0xx's
// in 13-bit counter/timer mode. It uses the 'F000DK as HW platform and blinks
// a LED. To do so it used an interrupt driven by the Timer0 which toggles the
// LED. (using an auxiliary counter inside the interrupt)
//
//
// Pinout:
//
//    P1.6 -> LED (pin 3 on the 'F005 TB)
//
//    all other port pins unused
//
// How To Test:
//
// This code enables the Timer0 as a 13-bit timer that uses the system clock
// (SYSCLK, in this case the internal oscillator / 8) with a 1:12 prescaler
// to generate an interrupt.
// The interrupt routine then toggles the LED. To execute the test please
// follow these steps:
//
// 1) Open the F0xx_Timer0_13bitTimer.c file in the Silicon Labs IDE.
// 2) If a different LED blink rate is required change the following constant:
//       -> LED_TOGGLE_RATE in milliseconds.
// 3) Compile and download the code to a 'F0xx
// 4) Verify J3 is populated on the 'F005 TB.
// 5) Run
// 6) Check the LED's behavior.
//
//
// FID:            00X000029
// Target:         C8051F0xx
// Tool chain:     KEIL C51 7.20 / KEIL EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CG)
//    -7 DEC 2005
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F000.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK             16000000/8  // SYSCLK in Hz (16 MHz internal
                                       // oscillator / 8)
                                       // the internal oscillator has a
                                       // tolerance of +/- 20%

#define TIMER_PRESCALER            12  // Based on Timer CKCON settings

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000

// Note: TIMER_TICKS_PER_MS should not exceed 8191 (0x1FFF) for the 13-bit
// timer

#define AUX1     TIMER_TICKS_PER_MS
#define AUX2     0x1FFF-AUX1
#define AUX3     AUX2&0x001F
#define AUX4     ((AUX2&0x1FFF)>>5)

#define LED_TOGGLE_RATE          1000  // LED toggle rate in milliseconds
                                       // if LED_TOGGLE_RATE = 1, the LED will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

#define TIMER0_RELOAD_HIGH       AUX4  // Reload value for Timer0 high byte
#define TIMER0_RELOAD_LOW        AUX3  // Reload value for Timer0 low byte

sbit LED = P1^6;                       // LED='1' means ON

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void Port_Init (void);                 // Port initialization routine
void Timer0_Init (void);               // Timer0 initialization routine

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   WDTCN = 0xDE;                       // Disable watchdog timer
   WDTCN = 0xAD;

   Timer0_Init ();                     // Initialize the Timer0
   Port_Init ();                       // Init Ports

   EA = 1;                             // Enable global interrupts

   while (1);                          // Loop forever
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
// Pinout:
//
//    P1.6 -> LED
//
//    all other port pins unused
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
   // Enable crossbar
   XBR2 = 0x40;
   PRT1CF = 0x40;                      // Set P1.6(LED) to push-pull
}

//-----------------------------------------------------------------------------
// Timer0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Timer0 as a 13-bit timer, interrupt enabled.
// Using the SYSCLK at 16MHz/8 and reloading the T0 register with
// TIMER0_RELOAD_xxxx it will toggle the LED.
//
// Note: The Timer0 uses a 1:12 prescaler.  If this setting changes, the
// TIMER_PRESCALER constant must also be changed.
//-----------------------------------------------------------------------------
void Timer0_Init(void)
{
   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 High register
   ET0 = 1;                            // Timer0 interrupt enabled
   TCON = 0x10;                        // Timer0 ON
}


//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer0_ISR
//-----------------------------------------------------------------------------
//
// Here we process the Timer0 interrupt and toggle the LED
//
//-----------------------------------------------------------------------------
void Timer0_ISR (void) interrupt 1
{
   static int counter = 0;

   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 register
   TL0 = TIMER0_RELOAD_LOW;
   if((counter++) == LED_TOGGLE_RATE)
   {
      LED = ~LED;                      // Toggle the LED
      counter = 0;
   }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------