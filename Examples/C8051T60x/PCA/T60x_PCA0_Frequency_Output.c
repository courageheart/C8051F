//-----------------------------------------------------------------------------
// T60x_PCA0_Frequency_Output.c
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program sends a square wave out of an I/O pin, using the PCA's
// Frequency Output Mode.
//
// In this example, PCA Module 0 is used to generate the waveform, and the
// crossbar is configured to send the CEX0 pin out on P0.1.
//
// How To Test:
//
// 1) Download code to a 'T60x device which has an oscilloscope monitoring P0.1
// 2) Run the program - the waveform should be visible on the oscilloscope.
//
//
// Target:         C8051T60x
// Tool chain:     Keil C51 8.0 / Keil EVAL C51
// Command Line:   None
//
// Release 1.1 / 04 NOV 2008 (BD)
//    - Changed to use P0.1 as output so example runs on 'T606 also.
//
// Release 1.0 / 30 JUL 2008 (ADT)
//    -Initial Revision
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <C8051T600_defs.h>            // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK       24500000          // Internal oscillator frequency in Hz

#define CEX0_FREQUENCY  50000          // Frequency to output on CEX0 (Hz)

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void OSCILLATOR_Init (void);
void PORT_Init (void);
void PCA0_Init (void);


//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   PCA0MD = 0x00;                      // Disable watchdog timer

   REG0CN |= 0x01;                     // OTP Power Controller Enable

   PORT_Init ();                       // Initialize crossbar and GPIO
   OSCILLATOR_Init ();                 // Initialize oscillator
   PCA0_Init ();                       // Initialize PCA0

   while (1);
}


//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function initializes the system clock to use the internal oscillator
// at 24.5 MHz.
//
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void)
{
   OSCICN = 0x07;                      // Set internal oscillator to run
                                       // at its maximum frequency
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the crossbar and GPIO ports.
//
// P0.0   digital   push-pull     PCA0 CEX0
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   XBR0    = 0x01;                     // Skip P0.0
   XBR1    = 0x40;                     // Route CEX0 to P0.1,
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups

   P0MDOUT |= 0x02;                    // Set CEX0 (P0.1) to push-pull
}


//-----------------------------------------------------------------------------
// PCA0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the PCA time base, and sets up frequency output
// mode for Module 0 (CEX0 pin).
//
// The frequency generated at the CEX0 pin is equal to CEX0_FREQUENCY Hz,
// which is defined in the "Global Constants" section at the beginning of the
// file.
//
// The PCA time base in this example is configured to use SYSCLK / 12.
// The frequency range that can be generated using this example is ~4 kHz to
// ~1 MHz when the processor clock is 24.5 MHz.  Using different PCA clock
// sources or a different processor clock will generate different frequency
// ranges. Note that 24.5 MHz is the internal oscillator frequency on devices
// with a calibrated internal oscillator.  If this code is run on a device
// which does not have a calibrated internal oscillator, the SYSCLK frequency
// wll be different.
//
//    -------------------------------------------------------------------------
//    How "Frequency Output Mode" Works:
//
//       The PCA's Frequency Output Mode works by toggling an output pin every
//    "N" PCA clock cycles.  The value of "N" should be loaded into the PCA0CPH
//    register for the module being used (in this case, module 0).  Whenever
//    the register PCA0L (PCA counter low byte) and the module's PCA0CPL value
//    are equivalent, two things happen:
//
//    1) The port pin associated with the PCA module toggles logic state
//    2) The value stored in PCA0CPH is added to PCA0CPL.
//
//    Using this mode, a square wave is produced at the output port pin of the
//    PCA module. The speed of the waveform can be changed by changing the
//    value of the PCA0CPH register.
//    -------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void PCA0_Init (void)
{
   // Configure PCA time base; overflow interrupt disabled
   PCA0CN = 0x00;                      // Stop counter; clear all flags
   PCA0MD = 0x00;                      // Use SYSCLK/12 as time base

   PCA0CPM0 = 0x46;                    // Module 0 = Frequency Output mode

   // Configure frequency for CEX0
   // PCA0CPH0 = (SYSCLK/12)/(2*CEX0_FREQUENCY), where:
   // SYSCLK/12 = PCA time base
   // CEX0_FREQUENCY = desired frequency
   PCA0CPH0 = ((SYSCLK/12)/(2*CEX0_FREQUENCY));

   // Start PCA counter
   CR = 1;
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------