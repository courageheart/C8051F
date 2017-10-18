//-----------------------------------------------------------------------------
// T620_EPROM_Primitives.h
//-----------------------------------------------------------------------------
// Copyright 2009 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program contains several useful utilities for writing and updating
// EPROM memory.
//
// Target:         C8051T620/1 or C8051T320/1/2/3
// Tool chain:     Keil / Raisonance
// Command Line:   None
//
//
// Release 1.0
//    -Initial Revision (GP / TP)
//    -01 JUL 2008
//

//-----------------------------------------------------------------------------
// Open Header #define
//-----------------------------------------------------------------------------

#ifndef _T620_EPROMPRIMITIVES_H_
#define _T620_EPROMPRIMITIVES_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "compiler_defs.h"

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------

typedef U16 EPROMADDR;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#ifndef EPROM_PAGESIZE
#define EPROM_PAGESIZE 512
#endif

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

void          EPROM_ByteWrite (EPROMADDR addr, char byte);
unsigned char EPROM_ByteRead  (EPROMADDR addr);

//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------

#endif    // _T620_EPROMPRIMITIVES_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------