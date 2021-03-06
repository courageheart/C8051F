//-----------------------------------------------------------------------------
// F06x_SPI_EEPROM_Polled_Mode.c
//-----------------------------------------------------------------------------
// Copyright 2006 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program accesses a SPI EEPROM using polled mode access. The 'F06x MCU
// is configured in 4-wire Single Master Mode, and the EEPROM is the only
// slave device connected to the SPI bus. The read/write operations are
// tailored to access a Microchip 4 kB EEPROM 25LC320. The relevant hardware
// connections of the 'F06x MCU are shown here:
//
// P0.0 - UART TXD   (digital output, push-pull)
// P0.1 - UART RXD   (digital input, open-drain)
// P0.2 - SPI SCK    (digital output, push-pull)
// P0.3 - SPI MISO   (digital input, open-drain)
// P0.4 - SPI MOSI   (digital output, push-pull)
// P0.5 - SPI NSS    (digital output, push-pull)
// P1.6 - LED        (digital output, push-pull)
//
//
// How To Test:
//
// Method1:
// 1) Download the code to a 'F06x device that is connected as above.
// 2) Run the code. The LED will blink fast during the write/read/verify
//    operations.
// 3) If the verification passes, the LED will blink slowly. If it fails,
//    the LED will be OFF.
//
// Method2 (optional):
// 1) Download code to a 'F06x device that is connected as above, and
//    also connected to a RS232 transceiver.
// 2) Connect a straight serial cable from the RS232 transceiver to a PC.
// 3) On the PC, open HyperTerminal (or any other terminal program) and connect
//    to the COM port at <BAUDRATE> and 8-N-1.
// 4) HyperTerminal will print the progress of the write/read operation, and in
//    the end will print the test result as pass or fail. Additionally, if the
//    verification passes, the LED will blink slowly. If it fails, the LED will
//    be OFF.
//
//
// Target:         C8051F06x
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (PKC / TP)
//    -25 JULY 2006
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <C8051F060.h>                 // SFR declarations
#include <stdio.h>                     // printf is declared here

//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for the 'F06x
//-----------------------------------------------------------------------------
sfr16 TMR2     = 0xCC;                 // Timer2 low and high bytes together

//-----------------------------------------------------------------------------
// User-defined types, structures, unions etc
//-----------------------------------------------------------------------------
#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef UINT
#define UINT unsigned int
#endif

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define BAUDRATE           115200      // Baud rate of UART in bps
#define SYSCLK             24500000    // Internal oscillator frequency in Hz

// Microchip 25AA320 Slave EEPROM Parameters
#define  F_SCK_MAX         1450000     // Max SCK freq (Hz)
#define  T_NSS_DISABLE_MIN 500         // Min NSS disable time (ns)
#define  EEPROM_CAPACITY   4096        // EEPROM capacity (bytes)

// EEPROM Instruction Set
#define  EEPROM_CMD_READ   0x03        // Read Command
#define  EEPROM_CMD_WRITE  0x02        // Write Command
#define  EEPROM_CMD_WRDI   0x04        // Reset Write Enable Latch Command
#define  EEPROM_CMD_WREN   0x06        // Set Write Enable Latch Command
#define  EEPROM_CMD_RDSR   0x05        // Read Status Register Command
#define  EEPROM_CMD_WRSR   0x01        // Write Status Register Command

sbit LED = P1^6;                       // LED='1' means ON
sbit SW1 = P3^7;                       // SW1='0' means switch pressed (unused)

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
// The following functions DO NOT save and restore SFRPAGE:
void Reset_Sources_Init (void);
void OSCILLATOR_Init (void);
void PORT_Init (void);
void TIMER2_Init (void);
void UART0_Init (void);
void SPI0_Init (void);
void Init_Device (void);

// The following functions save and restore SFRPAGE:
void Delay_us (BYTE time_us);
void Delay_ms (BYTE time_ms);
void EEPROM_Write (UINT address, BYTE value);
BYTE EEPROM_Read (UINT address);

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------
void main (void)
{
   UINT  address;                      // EEPROM address
   BYTE  test_byte;                    // Used as a temporary variable

   Init_Device ();                     // Initializes hardware peripherals

   // The following code will test the EEPROM by performing write/read/verify
   // operations. The first test will write 0xFFs to the EEPROM, and the
   // second test will write the LSBs of the EEPROM addresses.

   SFRPAGE = UART0_PAGE;               // Set to page0 for printf via UART0
                                       // LED on P1.6 is on all pages.

   // Fill EEPROM with 0xFF's
   LED = 1;
   printf("Filling with 0xFF's...\n");
   for (address = 0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = 0xFF;
      EEPROM_Write (address, test_byte);

      // Print status to UART0
      if ((address % 16) == 0)
      {
         printf ("\nWriting 0x%04x: %02x ", address, (UINT)test_byte);
         LED = ~LED;
      }
      else
         printf ("%02x ", (UINT)test_byte);
   }

   // Verify EEPROM with 0xFF's
   printf("\n\nVerifying 0xFF's...\n");
   for (address = 0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = EEPROM_Read (address);

      // Print status to UART0
      if ((address % 16) == 0)
      {
         printf ("\nVerifying 0x%04x: %02x ", address, (UINT)test_byte);
         LED = ~LED;
      }
      else
         printf ("%02x ", (UINT)test_byte);
      if (test_byte != 0xFF)
      {
         LED = 0;
         printf ("Error at %u\n", address);
         while (1);                    // Stop here on error (for debugging)
      }
   }

   // Fill EEPROM with LSB of EEPROM addresses
   printf("\n\nFilling with LSB of EEPROM addresses...\n");
   for (address = 0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = address & 0xFF;
      EEPROM_Write (address, test_byte);

      // Print status to UART0
      if ((address % 16) == 0)
      {
         printf ("\nWriting 0x%04x: %02x ", address, (UINT)test_byte);
         LED = ~LED;
      }
      else
         printf ("%02x ", (UINT)test_byte);
   }

   // Verify EEPROM with LSB of EEPROM addresses
   printf("\n\nVerifying LSB of EEPROM addresses...\n");
   for (address = 0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = EEPROM_Read (address);

      // print status to UART0
      if ((address % 16) == 0)
      {
         printf ("\nVerifying 0x%04x: %02x ", address, (UINT)test_byte);
         LED = ~LED;
      }
      else
         printf ("%02x ", (UINT)test_byte);

      if (test_byte != (address & 0xFF))
      {
         LED = 0;
         printf ("Error at %u\n", address);
         while (1);                    // Stop here on error (for debugging)
      }
   }

   printf ("\n\nVerification success!\n");

   while (1)                           // Loop forever
   {
      LED = ~LED;                      // Flash LED when done (all verified)
      Delay_ms (200);
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PCA0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function disables the watchdog timer.
//
//-----------------------------------------------------------------------------
void Reset_Sources_Init (void)
{
   WDTCN     = 0xDE;
   WDTCN     = 0xAD;
}

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
   SFRPAGE   = CONFIG_PAGE;
   OSCICN    = 0x83;
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
// P0.0  -  TX0 (UART0), Push-Pull,  Digital
// P0.1  -  RX0 (UART0), Open-Drain, Digital
// P0.2  -  SCK  (SPI0), Push-Pull,  Digital
// P0.3  -  MISO (SPI0), Open-Drain, Digital
// P0.4  -  MOSI (SPI0), Push-Pull,  Digital
// P0.5  -  NSS  (SPI0), Push-Pull,  Digital
// P0.6  -  Unassigned,  Open-Drain, Digital
// P0.7  -  Unassigned,  Open-Drain, Digital

// P1.0  -  Unassigned,  Open-Drain, Digital
// P1.1  -  Unassigned,  Open-Drain, Digital
// P1.2  -  Unassigned,  Open-Drain, Digital
// P1.3  -  Unassigned,  Open-Drain, Digital
// P1.4  -  Unassigned,  Open-Drain, Digital
// P1.5  -  Unassigned,  Open-Drain, Digital
// P1.6  -  Unassigned,  Push-Pull,  Digital (LED D3 on Target Board)
// P1.7  -  Unassigned,  Open-Drain, Digital

// P2.0  -  Unassigned,  Open-Drain, Digital
// P2.1  -  Unassigned,  Open-Drain, Digital
// P2.2  -  Unassigned,  Open-Drain, Digital
// P2.3  -  Unassigned,  Open-Drain, Digital
// P2.4  -  Unassigned,  Open-Drain, Digital
// P2.5  -  Unassigned,  Open-Drain, Digital
// P2.6  -  Unassigned,  Open-Drain, Digital
// P2.7  -  Unassigned,  Open-Drain, Digital

// P3.0  -  Unassigned,  Open-Drain, Digital
// P3.1  -  Unassigned,  Open-Drain, Digital
// P3.2  -  Unassigned,  Open-Drain, Digital
// P3.3  -  Unassigned,  Open-Drain, Digital
// P3.4  -  Unassigned,  Open-Drain, Digital
// P3.5  -  Unassigned,  Open-Drain, Digital
// P3.6  -  Unassigned,  Open-Drain, Digital
// P3.7  -  Unassigned,  Open-Drain, Digital (Switch SW2 on Target Board)
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   SFRPAGE   = CONFIG_PAGE;
   P0MDOUT   = 0x35;
   P1MDOUT   = 0x40;
   XBR0      = 0x06;
   XBR2      = 0x40;
}

//-----------------------------------------------------------------------------
// TIMER2_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Initializes Timer2 to be clocked by SYSCLK for use as a delay timer.
//
//-----------------------------------------------------------------------------
void TIMER2_Init (void)
{
   SFRPAGE   = TMR2_PAGE;
   TMR2CF    = 0x08;
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configures the UART0 using Timer1, for <BAUDRATE> and 8-N-1. Once this is
// set up, the standard printf function can be used to output data.
//
//-----------------------------------------------------------------------------
void UART0_Init (void)
{
   SFRPAGE = TIMER01_PAGE;

   CKCON |= 0x10;                      // Timer1 uses SYSCLK as clock source

   TCON &= ~0xC0;                      // Stop Timer1; clear TF1
   TMOD &= ~0xF0;                      // Timer1 in 8-bit autoreload mode
   TMOD |=  0x20;

   TH1 = -(SYSCLK/BAUDRATE/16);        // configure reload rate
   TL1 = TH1;                          // init T1
   TR1 = 1;                            // Start Timer1

   SFRPAGE = UART0_PAGE;

   SCON0 = 0x50;                       // 8-bit variable baud rate;
                                       // 9th bit ignored; RX enabled
                                       // clear all flags
   SSTA0 = 0x10;                       // clear all flags; enable baud rate
                                       // doubler;
                                       // Use Timer1 as RX and TX baud rate
                                       // source;
   TI0   = 1;                          // Indicate TX0 ready
}

//-----------------------------------------------------------------------------
// SPI0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configures SPI0 to use 4-wire Single-Master mode. The SPI timing is
// configured for Mode 0,0 (data centered on first edge of clock phase and
// SCK line low in idle state). The SPI clock is set to 1.75 MHz. The NSS pin
// is set to 1.
//
//-----------------------------------------------------------------------------
void SPI0_Init()
{
   SFRPAGE   = SPI0_PAGE;
   SPI0CFG   = 0x40;
   SPI0CN    = 0x0D;

   // The equation for SPI0CKR is (SYSCLK/(2*F_SCK_MAX))-1, but this yields
   // a SPI frequency that is slightly more than 2 MHz. But, 2 MHz is the max
   // frequency spec of the EEPROM used here. So, the "-1" term is omitted
   // in the following usage:
   SPI0CKR   = (SYSCLK/(2*F_SCK_MAX));
}

//-----------------------------------------------------------------------------
// Init_Device
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Calls all device initialization functions.
//
//-----------------------------------------------------------------------------
void Init_Device (void)
{
   Reset_Sources_Init ();
   OSCILLATOR_Init ();
   PORT_Init ();
   TIMER2_Init ();
   UART0_Init ();
   SPI0_Init ();
}

//-----------------------------------------------------------------------------
// Support Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Delay_us
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : 1. time_us - time delay in microseconds
//                   range: 1 to 255
//
// Creates a delay for the specified time (in microseconds) using TIMER2. The
// time tolerance is approximately +/-50 ns (1/SYSCLK + function call time).
// This function saves and restores SFRPAGE.
//
//-----------------------------------------------------------------------------
void Delay_us (BYTE time_us)
{
   BYTE  save_sfrpage = SFRPAGE;
   SFRPAGE = TMR2_PAGE;

   TR2   = 0;                          // Stop timer
   TF2   = 0;                          // Clear timer overflow flag
   TMR2  = -( (UINT)(SYSCLK/1000000) * (UINT)(time_us) );
   TR2   = 1;                          // Start timer
   while (!TF2);                       // Wait till timer overflow occurs
   TR2   = 0;                          // Stop timer

   SFRPAGE  = save_sfrpage;
}

//-----------------------------------------------------------------------------
// Delay_ms
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : 1. time_ms - time delay in milliseconds
//                   range: 1 to 255
//
// Creates a delay for the specified time (in milliseconds) using TIMER2. The
// time tolerance is approximately +/-50 ns (1/SYSCLK + function call time).
// This function does not use any SFRs (so SFRPAGE is left untouched).
//
//-----------------------------------------------------------------------------
void Delay_ms (BYTE time_ms)
{
   BYTE i;

   while(time_ms--)
      for(i = 0; i< 10; i++)           // 10 * 100 microsecond delay
         Delay_us (100);
}

//-----------------------------------------------------------------------------
// EEPROM_Write
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : 1. address - the destination EEPROM address.
//                   range: 0 to EEPROM_CAPACITY
//                2. value - the value to write.
//                   range: 0x00 to 0xFF
//
// Writes one byte to the specified address in the EEPROM. This function polls
// the EEPROM status register after the write operation, and returns only after
// the status register indicates that the write cycle is complete. This is to
// prevent from having to check the status register before a read operation.
// This function saves and restores SFRPAGE.
//
//-----------------------------------------------------------------------------
void EEPROM_Write (UINT address, BYTE value)
{
   BYTE  save_sfrpage = SFRPAGE;
   SFRPAGE   = SPI0_PAGE;

   // Writing a byte to the EEPROM is a five-step operation.

   // Step1: Set the Write Enable Latch to 1
   NSSMD0   = 0;                       // Step1.1: Activate Slave Select
   SPI0DAT  = EEPROM_CMD_WREN;         // Step1.2: Send the WREN command
   while (!SPIF);                      // Step1.3: Wait for end of transfer
   SPIF     = 0;                       // Step1.4: Clear the SPI intr. flag
   NSSMD0   = 1;                       // Step1.5: Deactivate Slave Select
   Delay_us (1);                       // Step1.6: Wait for at least
                                       //          T_NSS_DISABLE_MIN
   // Step2: Send the WRITE command
   NSSMD0   = 0;
   SPI0DAT  = EEPROM_CMD_WRITE;
   while (!SPIF);
   SPIF     = 0;

   // Step3: Send the EEPROM destination address (MSB first)
   SPI0DAT  = (BYTE)((address >> 8) & 0x00FF);
   while (!SPIF);
   SPIF     = 0;
   SPI0DAT  = (BYTE)(address & 0x00FF);
   while (!SPIF);
   SPIF     = 0;

   // Step4: Send the value to write
   SPI0DAT  = value;
   while (!SPIF);
   SPIF     = 0;
   NSSMD0   = 1;
   Delay_us (1);

   // Step5: Poll on the Write In Progress (WIP) bit in Read Status Register
   do
   {
      NSSMD0   = 0;                    // Activate Slave Select
      SPI0DAT  = EEPROM_CMD_RDSR;      // Send the Read Status Register command
      while (!SPIF);                   // Wait for the command to be sent out
      SPIF     = 0;
      SPI0DAT  = 0;                    // Dummy write to output serial clock
      while (!SPIF);                   // Wait for the register to be read
      SPIF     = 0;
      NSSMD0   = 1;                    // Deactivate Slave Select after read
      Delay_us (1);
   } while( (SPI0DAT & 0x01) == 0x01 );

   SFRPAGE  = save_sfrpage;
}

//-----------------------------------------------------------------------------
// EEPROM_Read
//-----------------------------------------------------------------------------
//
// Return Value : The value that was read from the EEPROM
//                   range: 0x00 to 0xFF
// Parameters   : 1. address - the source EEPROM address.
//                   range: 0 to EEPROM_CAPACITY
//
// Reads one byte from the specified EEPROM address.
// This function saves and restores SFRPAGE.
//
//-----------------------------------------------------------------------------
BYTE EEPROM_Read (UINT address)
{
   BYTE  value;
   BYTE  save_sfrpage = SFRPAGE;
   SFRPAGE   = SPI0_PAGE;

   // Reading a byte from the EEPROM is a three-step operation.

   // Step1: Send the READ command
   NSSMD0   = 0;                       // Activate Slave Select
   SPI0DAT  = EEPROM_CMD_READ;
   while (!SPIF);
   SPIF     = 0;

   // Step2: Send the EEPROM source address (MSB first)
   SPI0DAT  = (BYTE)((address >> 8) & 0x00FF);
   while (!SPIF);
   SPIF     = 0;
   SPI0DAT  = (BYTE)(address & 0x00FF);
   while (!SPIF);
   SPIF     = 0;

   // Step3: Read the value returned
   SPI0DAT  = 0;                       // Dummy write to output serial clock
   while (!SPIF);                      // Wait for the value to be read
   SPIF     = 0;
   NSSMD0   = 1;                       // Deactivate Slave Select
   Delay_us (1);
   value    = SPI0DAT;                 // Store EEPROM value in local var.

   SFRPAGE  = save_sfrpage;
   return value;
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------