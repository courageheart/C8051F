//-----------------------------------------------------------------------------
// F93x_Timer2_two_8bitTimers.c
//-----------------------------------------------------------------------------
// Copyright 2009 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer2 of the C8051F93x's in
// two 8-bit reload counter/timer mode. It uses the 'F930DK as HW platform.
//
// It sets Timer2 to be two 8-bit timers that interrupt every millisecond.
//
// When the Timer2 low interrupts a counter (low_counter) increments and upon
// reaching the value defined by LED_TOGGLE_RATE toggles the LED
// When the Timer2 high interrupts a counter (high_counter) increments and upon
// reaching the value defined by SIGNAL_TOGGLE_RATE toggles the SIGNAL pin
//
// Pinout:
//
//    P1.6 -> LED (toggled by TMR2L)
//    P1.7 -> SIGNAL (toggled by TMR2H)
//
//    all other port pins unused
//
// How To Test:
//
// 1) Open the F93x_Timer2_two_8bitTimers.c file in the Silicon Labs IDE.
// 2) If necessary change the number of interrupts to toggle an output:
//    LED_TOGGLE_RATE
//    SIGNAL_TOGGLE_RATE
// 3) Compile and download the code.
// 4) Verify the LED pins of J8 are populated on the 'F930 TB.
// 5) Run the code.
// 6) Verify that the LED is blinking and SIGNAL is toggling.
//
//
// Target:         C8051F93x
// Tool chain:     Generic
// Command Line:   None
//
//
// Release 1.2 
//    - Updated to be compatible with Raisonance Toolchain (FB)
//    - 14 APR 2010
//
// Release 1.1 
//    - Compiled and tested for C8051F930-TB (JH)
//    - 10 JULY 2009
//
// Release 1.0
//    - Initial Revision (FB)
//    - 20 NOV 2007
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <C8051F930_defs.h>            // SFR declaration

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK             (20000000L/8L)  // SYSCLK in Hz (20 MHz internal
                                       // low power oscillator / 8)
                                       // the low power oscillator has a
                                       // tolerance of +/- 10%
                                       // the precision oscillator has a 
                                       // tolerance of +/- 2%

#define TIMER_PRESCALER            12L  // Based on Timer2 CKCON and TMR2CN
                                       // settings

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS  (SYSCLK/TIMER_PRESCALER/1000L)

// Note: TIMER_TICKS_PER_MS should not exceed 255 (0xFF) for the 8-bit timers

#define AUX1     TIMER_TICKS_PER_MS
#define AUX2     -AUX1

#define LED_TOGGLE_RATE           100  // LED toggle rate in milliseconds
                                       // if LED_TOGGLE_RATE = 1, the LED will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

#define SIGNAL_TOGGLE_RATE         30  // SIGNAL pin toggle rate in
                                       // milliseconds
                                       // if SIGNAL_TOGGLE_RATE = 1, the
                                       // SIGNAL output will be on for 1
                                       // millisecond and off for 1
                                       // millisecond

#define TIMER2_RELOAD_HIGH       AUX2  // Reload value for Timer2 high byte
#define TIMER2_RELOAD_LOW        AUX2  // Reload value for Timer2 low byte

SBIT (LED, SFR_P1, 6);                 // LED==0 means ON
SBIT (SIGNAL, SFR_P1, 7);              // SIGNAL to be used also by Timer2

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void Port_Init (void);                 // Port initialization routine
void Timer2_Init (void);               // Timer2 initialization routine
INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   PCA0MD &= ~0x40;                    // Clear watchdog timer enable

   Timer2_Init ();                     // Initialize the Timer2
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
// P1.6   digital   push-pull   LED
// P1.7   digital   push-pull   SIGNAL
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
   XBR2 = 0x40;                        // Enable crossbar
   P1MDOUT = 0xC0;                     // Set LED and SIGNAL to
                                       // be used as push-pull

}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures Timer2 as two 8-bit reload timers with interrupt.
// Using the internal osc. at 24.5MHz/8 with a timer prescaler of 1:12
// reloading the TMR2H register with TIMER2_RELOAD_HIGH and TMR2L with
// TIMER2_RELOAD_HIGH.
//
// Note: The Timer2 uses a 1:12 prescaler.  If this setting changes, the
// TIMER_PRESCALER constant must also be changed.
//-----------------------------------------------------------------------------
void Timer2_Init(void)
{
   CKCON &= ~0x30;                     // Timer2 uses SYSCLK/12
   TMR2CN &= ~0x03;

   TMR2RLH = (U8) TIMER2_RELOAD_HIGH;  // Init Timer2 Reload High register
   TMR2RLL = (U8) TIMER2_RELOAD_LOW;   // Init Timer2 Reload Low register

   TMR2H = (U8) TIMER2_RELOAD_HIGH;    // Init Timer2 High register
   TMR2L = (U8) TIMER2_RELOAD_LOW;     // Init Timer2 Low register

   TMR2CN = 0x2C;                      // Low byte interrupt enabled
                                       // Timer2 enabled
                                       // and Split-Mode enabled
   ET2 = 1;                            // Timer2 interrupt enabled
}


//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer2_ISR
//-----------------------------------------------------------------------------
//
// This function processes the Timer2 interrupt. It checks both counters for
// matches and, upon a match, toggles the LED and SIGNAL.
//
//-----------------------------------------------------------------------------
INTERRUPT (TIMER2_ISR, INTERRUPT_TIMER2)
{
   static unsigned int low_counter=0;  // Define counter variables
   static unsigned int high_counter=0;

   if(TF2L == 1)
   {
      if((low_counter++) == LED_TOGGLE_RATE)
      {
         low_counter = 0;              // Reset interrupt counter
         LED = !LED;                   // Toggle the LED
      }
      TF2L = 0;
   }
   if(TF2H == 1)
   {
      if((high_counter++) == SIGNAL_TOGGLE_RATE)
      {
         high_counter = 0;             // Reset interrupt counter
         SIGNAL = !SIGNAL;             // Toggle the SIGNAL pin
      }
      TF2H = 0;
   }
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
