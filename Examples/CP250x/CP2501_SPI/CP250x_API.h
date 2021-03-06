//-----------------------------------------------------------------------------
// CP250x_API.h
//-----------------------------------------------------------------------------
// Copyright 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Target: CP2501
//
// Tool chain: Raisonance
//
// Contains function prototypes, macro definitions, constants, and variables
// necessary to utilize the CP250x System Firmware routines.
//
// This file is statically generated by the CP250x Configuration Wizard.
// Do not edit this file.
//

#ifndef _CP250X_API_H_
#define _CP250X_API_H_

//-----------------------------------------------------------------------------
// Header Files
//-----------------------------------------------------------------------------

#include "compiler_defs.h"

//-----------------------------------------------------------------------------
// CP250x_Status Return Values
//-----------------------------------------------------------------------------

#define  FUNC_SUCCESS              0x00
#define  FUNC_BUSY                 0x01
#define  FUNC_OUT_OF_RANGE         0x02
#define  FUNC_SPI_IDLE             0x10
#define  FUNC_SPI_MODE_FAULT       0x11
#define  FUNC_SPI_NSS_BUSY         0x12
#define  FUNC_SMBUS_IDLE           0x20
#define  FUNC_SMBUS_SCL_TO         0x21
#define  FUNC_SMBUS_NO_ACK         0x22
#define  FUNC_SMBUS_ARB_LOST       0x23
#define  FUNC_UART_IDLE            0x30
#define  FUNC_UART_NO_DATA         0x31
#define  FUNC_REMOTE_WAKE_DISABLE  0x40
#define  FUNC_NO_SUPPORT           0xFF

//-----------------------------------------------------------------------------
// API Function Parameters
//-----------------------------------------------------------------------------

// Power Options
#define  BUSPOW                    0x00     // BUS powered  (VREG enabled)
#define  SELFPOW_VREGOFF           0x01     // SELF powered (VREG disabled)
#define  SELFPOW_VREGON            0x02     // SELF powered (VREG enabled)

// Oscillator Option
#define  OSC_48                    0x00     // 48 MHz System Clock
#define  OSC_24                    0x01     // 24 MHz System Clock

// Default Operating Mode
#define  ENUM_MOUSE_MODE           0x00
#define  ENUM_SINGLE_POINT_MODE    0x01

// UART Parity Option
#define  NO_PARITY                 0x00
#define  ODD_PARITY                0x01
#define  EVEN_PARITY               0x02
#define  MARK_PARITY               0x03
#define  SPACE_PARITY              0x04

// UART Data Bits Options
#define  FIVE_DATA_BITS            0x00
#define  SIX_DATA_BITS             0x01
#define  SEVEN_DATA_BITS           0x02
#define  EIGHT_DATA_BITS           0x03

// UART Stop Bits Options
#define  ONE_STOP_BIT              0x00
#define  TWO_STOP_BITS             0x01

// SPI Transfer Options
#define  SPI_WRITE                 0x00     // Write Only
#define  SPI_READ                  0x01     // Read Only
#define  SPI_WRITEREAD             0x02     // Write and Read

// SPI Polarity / Phase Options
#define  PH1_POLLO                 0x00     // Phase = 0; Polarity = Low
#define  PH1_POLHI                 0x01     // Phase = 0; Polarity = High
#define  PH2_POLLO                 0x02     // Phase = 1; Polarity = Low
#define  PH2_POLHI                 0x03     // Phase = 1; Polarity = High

// SMBus Transfer Options
#define  SMBUS_FUNC_WRITE          0x00     // Write
#define  SMBUS_FUNC_READ           0x01     // Read

//-----------------------------------------------------------------------------
// GPIO Pin Definitions
//-----------------------------------------------------------------------------

#define GPIO_LO_ADDR  0x90
#define GPIO_HI_ADDR  0xA0

SFR  (GPIO_LO, 0x90);
SBIT (GPIO0, GPIO_LO_ADDR, 0);
SBIT (GPIO1, GPIO_LO_ADDR, 1);
SBIT (GPIO2, GPIO_LO_ADDR, 2);
SBIT (GPIO3, GPIO_LO_ADDR, 3);
SBIT (GPIO4, GPIO_LO_ADDR, 4);
SBIT (GPIO5, GPIO_LO_ADDR, 5);
SBIT (GPIO6, GPIO_LO_ADDR, 6);
SBIT (GPIO7, GPIO_LO_ADDR, 7);

SFR  (GPIO_HI, 0xA0);
SBIT (GPIO8,  GPIO_HI_ADDR, 0);
SBIT (GPIO9,  GPIO_HI_ADDR, 1);
SBIT (GPIO10, GPIO_HI_ADDR, 2);
SBIT (GPIO11, GPIO_HI_ADDR, 3);
SBIT (GPIO12, GPIO_HI_ADDR, 4);
SBIT (GPIO13, GPIO_HI_ADDR, 5);
SBIT (GPIO14, GPIO_HI_ADDR, 6);
SBIT (GPIO15, GPIO_HI_ADDR, 7);

//-----------------------------------------------------------------------------
// 8051 Registers
//-----------------------------------------------------------------------------

SFR (SP,  0x81);                        // Stack Pointer
SFR (DPL, 0x82);                        // Data Pointer Low
SFR (DPH, 0x83);                        // Data Pointer High
SFR (PSW, 0xD0);                        // Program Status Word
SFR (ACC, 0xE0);                        // Accumulator
SFR (B,   0xF0);                        // B Register

//-----------------------------------------------------------------------------
// API Function Locations
//-----------------------------------------------------------------------------

#define CP250X_SMBUS_MASTER_INIT          ((unsigned char code *)0x07A8)
#define CP250X_UART_INIT                  ((unsigned char code *)0x09CB)
#define CP250X_SPI_MASTER_INIT            ((unsigned char code *)0x0B34)
#define CP250X_USB_SUSPEND                ((unsigned char code *)0x1789)
#define CP250X_SPI_MASTER_TRANSFER        ((unsigned char code *)0x1991)
#define CP250X_USB_INIT                   ((unsigned char code *)0x1A07)
#define CP250X_SYSTEM_INIT                ((unsigned char code *)0x1BB1)
#define CP250x_REMOTE_WAKEUP              ((unsigned char code *)0x1C13)
#define CP250X_SMBUS_MASTER_TRANSFER      ((unsigned char code *)0x1C72)
#define CP250X_SMBUS_POLL                 ((unsigned char code *)0x1F57)
#define CP250X_UART_WRITE                 ((unsigned char code *)0x1FF3)
#define CP250X_UART_DEQUEUE               ((unsigned char code *)0x2023)
#define CP250X_START_COUNTER              ((unsigned char code *)0x2248)
#define CP250X_SPI_POLL                   ((unsigned char code *)0x22EC)
#define CP250X_GPIO_INIT                  ((unsigned char code *)0x239D)
#define CP250X_UART_POLL                  ((unsigned char code *)0x23B3)
#define CP250X_STOP_COUNTER               ((unsigned char code *)0x23F9)
#define CP250x_USB_SUSPEND_REMOTE_WAKEUP  ((unsigned char code *)0x2413)

//-----------------------------------------------------------------------------
// Function Macros
//-----------------------------------------------------------------------------

#define CP250x_System_Init(reg, sys)   {              \
                           CP250x_Param1 = reg;       \
                           CP250x_Param2 = sys;       \
                           ((void (*)())CP250X_SYSTEM_INIT)(); }

#define CP250x_GPIO_Init(mode_lo, mode_hi, latch_lo, latch_hi) { \
                           CP250x_Param1 = mode_lo;  \
                           CP250x_Param2 = mode_hi;  \
                           CP250x_Param3 = latch_lo; \
                           CP250x_Param4 = latch_hi; \
                           ((void (*)())CP250X_GPIO_INIT)(); }

#define CP250x_USB_Init(mode) {                          \
                           CP250x_Param1 = mode;         \
                           ((void (*)())CP250X_USB_INIT)(); }

#define CP250x_UART_Init(baud, bits, parity, stop) {     \
                           CP250x_Param1 = baud.U8[b0];  \
                           CP250x_Param2 = baud.U8[b1];  \
                           CP250x_Param3 = baud.U8[b2];  \
                           CP250x_Param4 = baud.U8[b3];  \
                           CP250x_Param5 = bits;         \
                           CP250x_Param6 = parity;       \
                           CP250x_Param7 = stop;         \
                           ((void (*)())CP250X_UART_INIT)(); }

#define CP250x_UART_Write(length) { \
                           CP250x_Param1 = length;  \
                           ((void (*)())CP250X_UART_WRITE)(); }

#define CP250x_UART_Dequeue() { \
                           ((void (*)())CP250X_UART_DEQUEUE)(); }

#define CP250x_UART_Poll() { \
                           ((void (*)())CP250X_UART_POLL)(); }


#define CP250x_SPI_Master_Init(baud, pol_pha) {  \
                           CP250x_Param1 = baud.U8[b0];  \
                           CP250x_Param2 = baud.U8[b1];  \
                           CP250x_Param3 = baud.U8[b2];  \
                           CP250x_Param4 = baud.U8[b3];  \
                           CP250x_Param5 = pol_pha;      \
                           ((void (*)())CP250X_SPI_MASTER_INIT)(); }


#define CP250x_SPI_Master_Transfer(type, length, dummy) { \
                           CP250x_Param1 = type;          \
                           CP250x_Param2 = length;        \
                           CP250x_Param3 = dummy;         \
                           ((void (*)())CP250X_SPI_MASTER_TRANSFER)(); }

#define CP250x_SPI_Poll() { \
                           ((void (*)())CP250X_SPI_POLL)(); }

#define CP250x_SMBus_Master_Init(baud, addr)  { \
                           CP250x_Param1 = baud.U8[b0];   \
                           CP250x_Param2 = baud.U8[b1];   \
                           CP250x_Param3 = baud.U8[b2];   \
                           CP250x_Param4 = baud.U8[b3];   \
                           CP250x_Param5 = addr;          \
                           ((void (*)())CP250X_SMBUS_MASTER_INIT)(); }

#define CP250x_SMBus_Master_Transfer(type, length, slave) { \
                           CP250x_Param1 = type;          \
                           CP250x_Param2 = length;        \
                           CP250x_Param3 = slave;         \
                           ((void (*)())CP250X_SMBUS_MASTER_TRANSFER)(); }

#define CP250x_SMBus_Poll() { \
                           ((void (*)())CP250X_SMBUS_POLL)(); }

#define CP250x_USB_Suspend() { \
                           ((void (*)())CP250X_USB_SUSPEND)(); }

#define CP250x_USB_Suspend_Remote_Wakeup() { \
                           ((void (*)())CP250x_USB_SUSPEND_REMOTE_WAKEUP)(); }

#define CP250x_Remote_Wakeup() { \
                           ((void (*)())CP250x_REMOTE_WAKEUP)(); }

#define CP250x_Start_Counter() { \
                           ((void (*)())CP250X_START_COUNTER)(); }

#define CP250x_Stop_Counter() { \
                           ((void (*)())CP250X_STOP_COUNTER)(); }

#endif   // _CP250X_API_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

