//=============================================================================
// mainRx.c
//-----------------------------------------------------------------------------
// Copyright 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// C File Description:
//
//  This file is specific to the Si100x hardware.
//
// Target:
//    Si1000
//
// IDE:
//    Silicon Laboratories IDE   version 3.3
//
// Tool Chains:
//    Keil
//       c51.exe     version 8.0.8
//       bl51.exe    version 6.0.5
//    SDCC
//       sdcc.exe    version 2.8.0
//       aslink.exe  version 1.75
//
// Project Name:
//    Run-Time PHY
//
// This software must be used in accordance with the End User License Agreement.
//
//=============================================================================
//-----------------------------------------------------------------------------
// Includes
//
// These includes must be in a specific order. Dependencies listed in comments.
//-----------------------------------------------------------------------------
#include <compiler_defs.h>
#include "hardware_defs.h"             // requires compiler_defs.h
#include "rtPhy.h"
#include "rtPhy_const.h"
#include <stdio.h>
//-----------------------------------------------------------------------------
// Baud rate macros
//-----------------------------------------------------------------------------
#define BAUD               (115200L)
#if (SYSCLK_HZ/BAUD/2/1)<256
   #define T1_RELOAD -((SYSCLK_HZ/BAUD/1+1)/2)
#else
   #error "error: baud rate too low!"
#endif
//-----------------------------------------------------------------------------
SEGMENT_VARIABLE (RxBuffer[64], U8, BUFFER_MSPACE);
//-----------------------------------------------------------------------------
// Internal Function Prototypes
//-----------------------------------------------------------------------------
void PortInit (void);
void SYSCLK_Init (void);
void SPI1_Init (void);
void UART0_Init (void);
//-----------------------------------------------------------------------------
// SDCC needs ISR Prototype in main module
// SDCC needs putchar() prototype and function
//-----------------------------------------------------------------------------
#ifdef SDCC
void putchar (char c);
INTERRUPT_PROTO(Receiver_ISR, INTERRUPT_INT0);
INTERRUPT_PROTO(T0_ISR, INTERRUPT_TIMER0);
#endif

//=============================================================================
// Functions
//=============================================================================
//-----------------------------------------------------------------------------
// main ()
//-----------------------------------------------------------------------------
void main (void)
{
   U8 status;
   U8 RxPacketLength;
   U8 i;

   PCA0MD   &= ~0x40;                  // disable F930 watchdog
   // Configure DC/DC
   // Needed for Si1004/5 support only
#ifdef SI1004_DAUGHTER_CARD
   DC0CN = 0x43;                       // 20ns min, big SW, 2.1V
   DC0CF = 0x04;                       // Local osc, High-Peak Current
#endif


   SYSCLK_Init();
   SPI1_Init();
   PortInit();
   UART0_Init();

   status = rtPhyInit();

   // Set the TRX_FREQUENCY first
   rtPhySet (TRX_FREQUENCY, 915000000);

   // Set the TRX_DATA_RATE second
   rtPhySet (TRX_DATA_RATE, 40000L);

   // Set the TRX_DEVIATION third (optional)
   rtPhySet (TRX_DEVIATION, 20000L);

   // Set the RX_BAND_WIDTH last (optional)
   rtPhySet (RX_BAND_WIDTH, 80000L);

   // If desired, also set the TRX_CHANNEL_SPACING
   // rtPhySet (TRX_CHANNEL_SPACING, 100000L);

   status = rtPhyInitRadio();

   EA = 1;

   status = rtPhyRxOn();

   printf("\RunTimePhy Rx Started!\r\n");

   while(1)
   {
      if(RxPacketReceived)
      {
         LED15 = ILLUMINATE;
         rtPhyGetRxPacket(&RxPacketLength, RxBuffer);

         printf("\rPacket Length = %i \r\n", (U16)RxPacketLength);

         for(i=0;i<RxPacketLength;i++)
         {
            printf("%02X ", (U16)RxBuffer[i]);
         }

         printf("\r\n");
         printf("\r\n");
         LED15 = EXTINGUISH;

      }
   }
}

//=============================================================================
//
// Init Functions
//
//=============================================================================
//-----------------------------------------------------------------------------
//
// Init_MCU()
//
//-----------------------------------------------------------------------------
//
// P0.0  -  /IRQ input
//
// P1.0  -  SCK  (SPI1), Push-Pull,  Digital
// P1.1  -  MISO (SPI1), Open-Drain, Digital
// P1.2  -  MOSI (SPI1), Push-Pull,  Digital
// P1.3  -  skipped
// P1.4  -  NSS, Push-Pull,  Digital
//
// P2.6  -  SDN Open Drain,  Digital
//
//-----------------------------------------------------------------------------
void PortInit (void)
{
   // Init UART
   XBR0    |= 0x01;                    // enable UART
   P0MDOUT |= 0x10;                    // TX push-pull
   SFRPAGE   = CONFIG_PAGE;
   P1DRV     = 0x10;                    // TX high-current mode
   SFRPAGE   = LEGACY_PAGE;

   // Init SPI
   XBR1    |= 0x40;                     // Enable SPI1 (3 wire mode)
   P1MDOUT |= 0x15;                    // SCK1, MOSI1, & NSS1,push-pull
   SFRPAGE   = CONFIG_PAGE;
   P1DRV     = 0x15;                   // MOSI1, SCK1, NSS1, high-current mode
   SFRPAGE   = LEGACY_PAGE;

   // Initialize SDN
#ifdef   SI1000_DAUGHTER_CARD
   P2MDOUT |= 0x40;                    // SDN P2.6 push-pull
   SFRPAGE  = CONFIG_PAGE;
   P2DRV   |= 0x40;                    // SDN  P2.6 high-current mode
   SFRPAGE  = LEGACY_PAGE;
#endif
#ifdef   SI1002_DAUGHTER_CARD
   P2MDOUT |= 0x40;                    // SDN P2.6 push-pull
   SFRPAGE  = CONFIG_PAGE;
   P2DRV   |= 0x40;                    // SDN  P2.6 high-current mode
   SFRPAGE  = LEGACY_PAGE;
#endif
#ifdef   SI1004_DAUGHTER_CARD
   P1MDOUT |= 0x40;                    // SDN P1.6 push-pull
   SFRPAGE  = CONFIG_PAGE;
   P1DRV   |= 0x40;                    // SDN  P1.6 high-current mode
   SFRPAGE  = LEGACY_PAGE;
#endif
   SDN = 0;

   P2 = 0xFF;                          // P2 bug fix for SDCC and Raisonance

   XBR2    |= 0x40;                    // enable Crossbar

   IT01CF    = 0x01;                   // INT0 P0.1
   IE0 = 0;
   IT0 =0;
}
//-----------------------------------------------------------------------------
// SYSCLK_Init ()
//-----------------------------------------------------------------------------
void SYSCLK_Init (void)
{
   OSCICN |= 0x80;                     // Enable the precision internal osc.

   CLKSEL = 0x00;                      // use 24,5 MHz clock
   FLSCL = 0x40; // Bypass one-shot
}
//-----------------------------------------------------------------------------
// SPI1_Init ()
//-----------------------------------------------------------------------------
void SPI1_Init()
{

   SPI1CFG   = 0x40;                   // master mode
   SPI1CN    = 0x00;                   // 3 wire master mode
   SPI1CKR   = 0x00;                   // Use SYSWCLK/2r
   SPI1CN   |= 0x01;                   // enable SPI
   NSS1 = 1;                           // set NSS high
}
//-----------------------------------------------------------------------------
// UART0_Init ()
//-----------------------------------------------------------------------------
void   UART0_Init (void)
{

   SCON0  = 0x10;                      // SCON0: 8-bit variable bit rate, no receiver
   CKCON |= 0x08;                      // T1 uses SYSCLK
   TH1    = T1_RELOAD;                 // reload value calculated from BAUD
   TL1    = T1_RELOAD;                 // also load into TL1
   TMOD  &= ~0xF0;                     // clear T1 bits in TMOD
   TMOD  |=  0x20;                     // set TMOD for 8 bit reload
   TR1    = 1;                         // START Timer1
   TI0    = 1;                         // Transciever ready
}
//-----------------------------------------------------------------------------
// putchar
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : character to send to UART
//
// This function outputs a character to the UART.
// Used for SDCC build only.
//-----------------------------------------------------------------------------
#ifdef SDCC
void putchar (char c)
{
   while (!TI0);
   TI0 = 0;
   SBUF0 = c;
}
#endif
//=============================================================================
