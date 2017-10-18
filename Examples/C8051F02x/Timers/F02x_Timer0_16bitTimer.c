//-----------------------------------------------------------------------------
// F02x_Timer0_16bitTimer.c
//-----------------------------------------------------------------------------
//
// Copyright 2005 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer0 of the C8051F02x's in
// 16-bit counter/timer mode. It uses the 'F020DK as HW platform.
// In this example the LED is toggled at a rate defined by the
// LED_TOGGLE_RATE constant.(in milliseconds)
//
// The timer is set with this values and counts until an overflow when it
// generates an interrupt. This interrupt reloads the timer values and toggles
// the LED.
//
// Pinout:
//
//    P1.6 -> LED
//
//    all other port pins unused
//
// How To Test:
//
// 1) Open the F02x_Timer0_16bitTimer.c file in the Silicon Labs IDE.
// 2) If another rate is required change LED_TOGGLE_RATE (in msec)
// 3) Compile the project and download to the device.
// 4) Verify J3 is populated on the 'F02x TB.
// 5) Run the code.
// 6) Check that the LED is blinking at a constant rate .
//
//
// FID:            02X000027
// Target:         C8051F02x
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

#include <C8051F020.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK             16000000/8  // SYSCLK in Hz (16 MHz internal
                                       // oscillator / 8)
                                       // the internal oscillator has a
                                       // tolerance of +/- 20%

#define TIMER_PRESCALER            12  // Based on Timer CKCON settings

#define LED_TOGGLE_RATE            50  // LED toggle rate in milliseconds
                                       // if LED_TOGGLE_RATE = 1, the LED will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000

// Note: LED_TOGGLE_RATE*TIMER_TICKS_PER_MS should not exceed 65535 (0xFFFF)
// for the 16-bit timer

#define AUX1     TIMER_TICKS_PER_MS*LED_TOGGLE_RATE
#define AUX2     -AUX1
#define AUX3     AUX2&0x00FF
#define AUX4     ((AUX2&0xFF00)>>8)

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
   P1MDOUT = 0x40;                     // Set P1.6(LED) to push-pull
}

//-----------------------------------------------------------------------------
// Timer0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Timer0 as a 16-bit timer, interrupt enabled.
// Using the SYSCLK at 16MHz/8 and reloading the T0 register with
// TIMER0_RELOAD_xxxx. The number of interrupts to toggle the LED is defined
// by INTERRUPTCOUNTER.
//
// Note: The Timer0 uses a 1:12 prescaler.  If this setting changes, the
// TIMER_PRESCALER constant must also be changed.
//-----------------------------------------------------------------------------
void Timer0_Init(void)
{
   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 High register
   ET0 = 1;                            // Timer0 interrupt enabled
   TMOD = 0x01;                        // 16-bit Mode Timer0
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
   TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 register
   TL0 = TIMER0_RELOAD_LOW;
   LED = ~LED;                         // Toggle the LED
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------