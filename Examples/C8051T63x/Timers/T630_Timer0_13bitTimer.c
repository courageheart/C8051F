//-----------------------------------------------------------------------------
// T630_Timer0_13bitTimer.c
//-----------------------------------------------------------------------------
//
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer0 of the C8051T630's
// in 13-bit counter/timer mode. It uses the 'T630DK as HW platform and blinks
// a LED. To do so it used an interrupt driven by the Timer0 which toggles the
// LED every 100msec.
//
// Pinout:
//
//    P1.3 -> LED
//
//    all other port pins unused
//
// How To Test:
//
// This code enables the Timer0 as a 13-bit timer that uses the system clock
// (SYSCLK, in this case the internal clock @24.5MHz/8 or about 3MHz) with a
// 1:48 prescaler.
// The interrupt routine then toggles the LED. To execute the test please
// follow these steps:
//
// 1) Open the T630_Timer0_13bitTimer.c file in the Silicon Labs IDE.
// 2) If another rate is required change LED_TOGGLE_RATE (in msec)
// 3) Compile the project and download to the device.
// 4) Verify the LED/P1.3 pin of J9 is populated on the 'T630 MB.
// 5) Run the code.
// 6) Check that the LED is blinking at a constant rate .
//
//
// Target:         C8051T630
// Tool chain:     KEIL C51 7.20 / KEIL EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (BD)
//    -24 JAN 2008
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <C8051T630_defs.h>              // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK             24500000/8  // SYSCLK in Hz (24.5 MHz internal
                                       // oscillator / 8)
                                       // the internal oscillator has a
                                       // tolerance of +/- 2%

#define TIMER_PRESCALER            48  // Based on Timer CKCON settings

#define LED_TOGGLE_RATE           100  // LED toggle rate in milliseconds
                                       // if LED_TOGGLE_RATE = 1, the LED will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000

// Note: LED_TOGGLE_RATE*TIMER_TICKS_PER_MS should not exceed 8191 (0x1FFF)
// for the 13-bit timer

#define AUX1     TIMER_TICKS_PER_MS*LED_TOGGLE_RATE
#define AUX2     0x1FFF-AUX1
#define AUX3     AUX2&0x001F
#define AUX4     ((AUX2&0x1FFF)>>5)

#define TIMER0_RELOAD_HIGH       AUX4  // Reload value for Timer0 high byte
#define TIMER0_RELOAD_LOW        AUX3  // Reload value for Timer0 low byte

SBIT (LED1, SFR_P1, 3);                 // LED==1 means ON

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void Port_Init (void);                 // Port initialization routine
void Timer0_Init (void);               // Timer0 initialization routine
INTERRUPT_PROTO (TIMER0_ISR, INTERRUPT_TIMER0);

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   PCA0MD &= ~0x40;                    // Clear watchdog timer enable

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
// P1.3   digital  push-pull   LED
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
   XBR1 = 0x40;                        // Enable crossbar
   P1MDOUT = 0x08;                     // Set LED to push-pull
}

//-----------------------------------------------------------------------------
// Timer0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Timer0 as a 13-bit timer, interrupt enabled.
// Using the internal osc. at 24.5MHz with a prescaler of 1:8 and reloading
// the TH0 register with TIMER0_RELOAD_HIGH it will interrupt and then toggle
// the LED.
//
// Note: The Timer0 uses a 1:48 prescaler.  If this setting changes, the
// TIMER_PRESCALER constant must also be changed.
//-----------------------------------------------------------------------------
void Timer0_Init(void)
{
   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 High register
   TL0 = TIMER0_RELOAD_LOW;            // Reinit Timer0 Low register
   TMOD = 0x00;                        // Timer0 in 13-bit mode
   CKCON = 0x02;                       // Timer0 uses a 1:48 prescaler
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
INTERRUPT(TIMER0_ISR, INTERRUPT_TIMER0)
{
   LED1 = ~LED1;                       // Toggle the LED
   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 High register
   TL0 = TIMER0_RELOAD_LOW;            // Reinit Timer0 Low register
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------