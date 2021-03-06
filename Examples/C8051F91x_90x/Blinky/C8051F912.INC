;------------------------------------------------------------------------------
; C8051F912.INC
;------------------------------------------------------------------------------
; Copyright 2009 Silicon Laboratories, Inc.
; http://www.silabs.com
;
; Program Description:
;
; Register/bit definitions for the C8051F91x family.
;
;
; Target:         C8051F912, 'F911, 'F902, 'F901
; Tool chain:     Keil
; Command Line:   None
;
;
; Release 1.0
;    -Initial Revision (FB)
;    -28 JUL 2009
;

;------------------------------------------------------------------------------
; Byte Registers
;------------------------------------------------------------------------------

P0          DATA 080H                      ; Port 0 Latch
SP          DATA 081H                      ; Stack Pointer
DPL         DATA 082H                      ; Data Pointer Low
DPH         DATA 083H                      ; Data Pointer High
SPI1CFG     DATA 084H                      ; SPI1 Configuration
SPI1CKR     DATA 085H                      ; SPI1 Clock Rate Control
TOFFL       DATA 085H                      ; Temperature Offset Low
SPI1DAT     DATA 086H                      ; SPI1 Data
TOFFH       DATA 086H                      ; Temperature Offset High
PCON        DATA 087H                      ; Power Control
TCON        DATA 088H                      ; Timer/Counter Control
TMOD        DATA 089H                      ; Timer/Counter Mode
TL0         DATA 08AH                      ; Timer/Counter 0 Low
TL1         DATA 08BH                      ; Timer/Counter 1 Low
TH0         DATA 08CH                      ; Timer/Counter 0 High
TH1         DATA 08DH                      ; Timer/Counter 1 High
CKCON       DATA 08EH                      ; Clock Control
PSCTL       DATA 08FH                      ; Program Store R/W Control
P1          DATA 090H                      ; Port 1 Latch
TMR3CN      DATA 091H                      ; Timer/Counter 3 Control
CRC0DAT     DATA 091H                      ; CRC0 Data
TMR3RLL     DATA 092H                      ; Timer/Counter 3 Reload Low
CRC0CN      DATA 092H                      ; CRC0 Control
TMR3RLH     DATA 093H                      ; Timer/Counter 3 Reload High
CRC0IN      DATA 093H                      ; CRC0 Input
TMR3L       DATA 094H                      ; Timer/Counter 3 Low
DC0MD       DATA 094H                      ; DC0 (DC/DC Converter) Mode
CRC0FLIP    DATA 095H                      ; CRC0 Flip
TMR3H       DATA 095H                      ; Timer/Counter 3 High
CRC0AUTO    DATA 096H                      ; CRC0 Automatic Control
DC0CF       DATA 096H                      ; DC0 (DC/DC Converter) Configuration
DC0CN       DATA 097H                      ; DC0 (DC/DC Converter) Control
CRC0CNT     DATA 097H                      ; CRC0 Automatic Flash Sector Count
SCON0       DATA 098H                      ; UART0 Control
SBUF0       DATA 099H                      ; UART0 Data Buffer
CPT1CN      DATA 09AH                      ; Comparator1 Control
CPT0CN      DATA 09BH                      ; Comparator0 Control
CPT1MD      DATA 09CH                      ; Comparator1 Mode Selection
CPT0MD      DATA 09DH                      ; Comparator0 Mode Selection
CPT1MX      DATA 09EH                      ; Comparator1 Mux Selection
CPT0MX      DATA 09FH                      ; Comparator0 Mux Selection
P2          DATA 0A0H                      ; Port 2 Latch
SPI0CFG     DATA 0A1H                      ; SPI0 Configuration
SPI0CKR     DATA 0A2H                      ; SPI0 Clock Rate Control
SPI0DAT     DATA 0A3H                      ; SPI0 Data
P0MDOUT     DATA 0A4H                      ; Port 0 Output Mode Configuration
P0DRV       DATA 0A4H                      ; Port 0 Drive Strength
P1MDOUT     DATA 0A5H                      ; Port 1 Output Mode Configuration
P1DRV       DATA 0A5H                      ; Port 1 Drive Strength
P2MDOUT     DATA 0A6H                      ; Port 2 Output Mode Configuration
P2DRV       DATA 0A6H                      ; Port 2 Drive Strength
SFRPAGE     DATA 0A7H                      ; SFR Page
IE          DATA 0A8H                      ; Interrupt Enable
CLKSEL      DATA 0A9H                      ; Clock Select
EMI0CN      DATA 0AAH                      ; EMIF Control
RTC0ADR     DATA 0ACH                      ; RTC0 Address
RTC0DAT     DATA 0ADH                      ; RTC0 Data
RTC0KEY     DATA 0AEH                      ; RTC0 Key
ONESHOT     DATA 0AFH                      ; ONESHOT Timing Control
SPI1CN      DATA 0B0H                      ; SPI1 Control
OSCXCN      DATA 0B1H                      ; External Oscillator Control
OSCICN      DATA 0B2H                      ; Internal Oscillator Control
OSCICL      DATA 0B3H                      ; Internal Oscillator Calibration
PMU0CF      DATA 0B5H                      ; PMU0 Configuration
PMU0MD      DATA 0B5H                      ; PMU0 Mode
FLSCL       DATA 0B6H                      ; Flash Scale Register
FLKEY       DATA 0B7H                      ; Flash Lock And Key
IP          DATA 0B8H                      ; Interrupt Priority
IREF0CN     DATA 0B9H                      ; Current Reference IREF0 Control
IREF0CF     DATA 0B9H                      ; Current Reference IREF0 Configuration
ADC0AC      DATA 0BAH                      ; ADC0 Accumulator Configuration
ADC0PWR     DATA 0BAH                      ; ADC0 Burst Mode Power-Up Time
ADC0MX      DATA 0BBH                      ; AMUX0 Channel Select
ADC0CF      DATA 0BCH                      ; ADC0 Configuration
ADC0TK      DATA 0BDH                      ; ADC0 Tracking Control
ADC0L       DATA 0BDH                      ; ADC0 Low
ADC0H       DATA 0BEH                      ; ADC0 High
P1MASK      DATA 0BFH                      ; Port 1 Mask
SMB0CN      DATA 0C0H                      ; SMBus0 Control
SMB0CF      DATA 0C1H                      ; SMBus0 Configuration
SMB0DAT     DATA 0C2H                      ; SMBus0 Data
ADC0GTL     DATA 0C3H                      ; ADC0 Greater-Than Compare Low
ADC0GTH     DATA 0C4H                      ; ADC0 Greater-Than Compare High
ADC0LTL     DATA 0C5H                      ; ADC0 Less-Than Compare Word Low
ADC0LTH     DATA 0C6H                      ; ADC0 Less-Than Compare Word High
P0MASK      DATA 0C7H                      ; Port 0 Mask
TMR2CN      DATA 0C8H                      ; Timer/Counter 2 Control
REG0CN      DATA 0C9H                      ; Voltage Regulator (REG0) Control
TMR2RLL     DATA 0CAH                      ; Timer/Counter 2 Reload Low
TMR2RLH     DATA 0CBH                      ; Timer/Counter 2 Reload High
TMR2L       DATA 0CCH                      ; Timer/Counter 2 Low
TMR2H       DATA 0CDH                      ; Timer/Counter 2 High
PCA0CPM5    DATA 0CEH                      ; PCA0 Module 5 Mode Register
P1MAT       DATA 0CFH                      ; Port 1 Match
PSW         DATA 0D0H                      ; Program Status Word
REF0CN      DATA 0D1H                      ; Voltage Reference Control
PCA0CPL5    DATA 0D2H                      ; PCA0 Capture 5 Low
PCA0CPH5    DATA 0D3H                      ; PCA0 Capture 5 High
P0SKIP      DATA 0D4H                      ; Port 0 Skip
P1SKIP      DATA 0D5H                      ; Port 1 Skip
P0MAT       DATA 0D7H                      ; Port 0 Match
PCA0CN      DATA 0D8H                      ; PCA0 Control
PCA0MD      DATA 0D9H                      ; PCA0 Mode
PCA0CPM0    DATA 0DAH                      ; PCA0 Module 0 Mode Register
PCA0CPM1    DATA 0DBH                      ; PCA0 Module 1 Mode Register
PCA0CPM2    DATA 0DCH                      ; PCA0 Module 2 Mode Register
PCA0CPM3    DATA 0DDH                      ; PCA0 Module 3 Mode Register
PCA0CPM4    DATA 0DEH                      ; PCA0 Module 4 Mode Register
PCA0PWM     DATA 0DFH                      ; PCA0 PWM Configuration
ACC         DATA 0E0H                      ; Accumulator
XBR0        DATA 0E1H                      ; Port I/O Crossbar Control 0
XBR1        DATA 0E2H                      ; Port I/O Crossbar Control 1
XBR2        DATA 0E3H                      ; Port I/O Crossbar Control 2
IT01CF      DATA 0E4H                      ; INT0/INT1 Configuration
EIE1        DATA 0E6H                      ; Extended Interrupt Enable 1
EIE2        DATA 0E7H                      ; Extended Interrupt Enable 2
ADC0CN      DATA 0E8H                      ; ADC0 Control
PCA0CPL1    DATA 0E9H                      ; PCA0 Capture 1 Low
PCA0CPH1    DATA 0EAH                      ; PCA0 Capture 1 High
PCA0CPL2    DATA 0EBH                      ; PCA0 Capture 2 Low
PCA0CPH2    DATA 0ECH                      ; PCA0 Capture 2 High
PCA0CPL3    DATA 0EDH                      ; PCA0 Capture 3 Low
PCA0CPH3    DATA 0EEH                      ; PCA0 Capture 3 High
RSTSRC      DATA 0EFH                      ; Reset Source Configuration/Status
B           DATA 0F0H                      ; B Register
P0MDIN      DATA 0F1H                      ; Port 0 Input Mode Configuration
P1MDIN      DATA 0F2H                      ; Port 1 Input Mode Configuration
SMB0ADR     DATA 0F4H                      ; SMBus Slave Address
SMB0ADM     DATA 0F5H                      ; SMBus Slave Address Mask
EIP1        DATA 0F6H                      ; Extended Interrupt Priority 1
EIP2        DATA 0F7H                      ; Extended Interrupt Priority 2
SPI0CN      DATA 0F8H                      ; SPI0 Control
PCA0L       DATA 0F9H                      ; PCA0 Counter Low
PCA0H       DATA 0FAH                      ; PCA0 Counter High
PCA0CPL0    DATA 0FBH                      ; PCA0 Capture 0 Low
PCA0CPH0    DATA 0FCH                      ; PCA0 Capture 0 High
PCA0CPL4    DATA 0FDH                      ; PCA0 Capture 4 Low
PCA0CPH4    DATA 0FEH                      ; PCA0 Capture 4 High
VDM0CN      DATA 0FFH                      ; VDD Monitor Control




;------------------------------------------------------------------------------
; Bit Definitions
;------------------------------------------------------------------------------

; TCON  088H
TF1     BIT     TCON.7                 ; Timer1 overflow flag
TR1     BIT     TCON.6                 ; Timer1 on/off control
TF0     BIT     TCON.5                 ; Timer0 overflow flag
TR0     BIT     TCON.4                 ; Timer0 on/off control
IE1     BIT     TCON.3                 ; Ext. Interrupt 1 edge flag
IT1     BIT     TCON.2                 ; Ext. Interrupt 1 type
IE0     BIT     TCON.1                 ; Ext. Interrupt 0 edge flag
IT0     BIT     TCON.0                 ; Ext. Interrupt 0 type

; SCON0  098H
S0MODE  BIT     SCON0.7                ; Serial mode control bit 0
                                       ; Bit 6 unused
MCE0    BIT     SCON0.5                ; Multiprocessor communication enable
REN0    BIT     SCON0.4                ; Receive enable
TB80    BIT     SCON0.3                ; Transmit bit 8
RB80    BIT     SCON0.2                ; Receive bit 8
TI0     BIT     SCON0.1                ; Transmit interrupt flag
RI0     BIT     SCON0.0                ; Receive interrupt flag

; IE  0A8H
EA      BIT     IE.7                   ; Global interrupt enable
ESPI0   BIT     IE.6                   ; Bit 6 unused
ET2     BIT     IE.5                   ; Bit 5 unused
ES0     BIT     IE.4                   ; UART0 interrupt enable
ET1     BIT     IE.3                   ; Timer1 interrupt enable
EX1     BIT     IE.2                   ; External interrupt 1 enable
ET0     BIT     IE.1                   ; Timer0 interrupt enable
EX0     BIT     IE.0                   ; External interrupt 0 enable

; SPI1CN  0B0H
SPIF1   BIT     SPI1CN.7               ; SPI1 Interrupt Flag
WCOL1   BIT     SPI1CN.6               ; SPI1 Write Collision Flag
MODF1   BIT     SPI1CN.5               ; SPI1 Mode Fault Flag
RXOVRN1 BIT     SPI1CN.4               ; SPI1 RX Overrun Flag
NSS1MD1 BIT     SPI1CN.3               ; SPI1 Slave Select Mode 1
NSS1MD0 BIT     SPI1CN.2               ; SPI1 Slave Select Mode 0
TXBMT1  BIT     SPI1CN.1               ; SPI1 TX Buffer Empty Flag
SPI1EN  BIT     SPI1CN.0               ; SPI1 Enable

; IP  0B8H
                                       ; Bit 7 unused
PSPI0   BIT     IP.6                   ; SPI0 interrupt priority
PT2     BIT     IP.5                   ; Timer2 priority
PS0     BIT     IP.4                   ; UART0 priority
PT1     BIT     IP.3                   ; Timer1 priority
PX1     BIT     IP.2                   ; External interrupt 1 priority
PT0     BIT     IP.1                   ; Timer0 priority
PX0     BIT     IP.0                   ; External interrupt 0 priority

; SMB0CN  0C0H
MASTER  BIT     SMB0CN.7               ; Master/slave indicator
TXMODE  BIT     SMB0CN.6               ; Transmit mode indicator
STA     BIT     SMB0CN.5               ; Start flag
STO     BIT     SMB0CN.4               ; Stop flag
ACKRQ   BIT     SMB0CN.3               ; Acknowledge request
ARBLOST BIT     SMB0CN.2               ; Arbitration lost indicator
ACK     BIT     SMB0CN.1               ; Acknowledge flag
SI      BIT     SMB0CN.0               ; SMBus interrupt flag

; TMR2CN  0C8H
TF2H    BIT     TMR2CN.7               ; Timer2 high byte overflow flag
TF2L    BIT     TMR2CN.6               ; Timer2 low byte overflow flag
TF2LEN  BIT     TMR2CN.5               ; Timer2 low byte interrupt enable
T2CE    BIT     TMR2CN.4               ; Timer2 capture enable
T2SPLIT BIT     TMR2CN.3               ; Timer2 split mode enable
TR2     BIT     TMR2CN.2               ; Timer2 on/off control
T2CSS   BIT     TMR2CN.1               ; Timer 2 Capture Source select
T2XCLK  BIT     TMR2CN.0               ; Timer2 external clock select

; PSW  0D0H
CY      BIT     PSW.7                  ; Carry flag
AC      BIT     PSW.6                  ; Auxiliary carry flag
F0      BIT     PSW.5                  ; User flag 0
RS1     BIT     PSW.4                  ; Register bank select 1
RS0     BIT     PSW.3                  ; Register bank select 0
OV      BIT     PSW.2                  ; Overflow flag
F1      BIT     PSW.1                  ; User flag 1
P       BIT     PSW.0                  ; Accumulator parity flag

; PCA0CN  0D8H
CF      BIT     PCA0CN.7               ; PCA0 counter overflow flag
CR      BIT     PCA0CN.6               ; PCA0 counter run control
                                       ; Bit5 UNUSED
CCF4    BIT     PCA0CN.4               ; PCA0 module4 capture/compare flag
CCF3    BIT     PCA0CN.3               ; PCA0 module3 capture/compare flag
CCF2    BIT     PCA0CN.2               ; PCA0 module2 capture/compare flag
CCF1    BIT     PCA0CN.1               ; PCA0 module1 capture/compare flag
CCF0    BIT     PCA0CN.0               ; PCA0 module0 capture/compare flag

; ADC0CN  0E8H
AD0EN   BIT     ADC0CN.7               ; ADC0 Enable
BURSTEN BIT     ADC0CN.6               ; ADC0 Burst Enable
AD0INT  BIT     ADC0CN.5               ; ADC0 EOC Interrupt Flag
AD0BUSY BIT     ADC0CN.4               ; ADC0 Busy Flag
AD0WINT BIT     ADC0CN.3               ; ADC0 Window Interrupt Flag
AD0CM2  BIT     ADC0CN.2               ; ADC0 Convert Start Mode Bit 2
AD0CM1  BIT     ADC0CN.1               ; ADC0 Convert Start Mode Bit 1
AD0CM0  BIT     ADC0CN.0               ; ADC0 Convert Start Mode Bit 0

; SPI0CN  0F8H
SPIF0    BIT     SPI0CN.7               ; SPI0 interrupt flag
WCOL0    BIT     SPI0CN.6               ; SPI0 write collision flag
MODF0    BIT     SPI0CN.5               ; SPI0 mode fault flag
RXOVRN0  BIT     SPI0CN.4               ; SPI0 rx overrun flag
NSS0MD1  BIT     SPI0CN.3               ; SPI0 slave select mode 1
NSS0MD0  BIT     SPI0CN.2               ; SPI0 slave select mode 0
TXBMT0   BIT     SPI0CN.1               ; SPI0 transmit buffer empty
SPI0EN   BIT     SPI0CN.0               ; SPI0 SPI enable

;------------------------------------------------------------------------------
; End Of File
;------------------------------------------------------------------------------