		 --------------------------------------------------
                            USB Bulk Example Readme File
                     Copyright (C) 2005 Silicon Laboratories, Inc.
		 --------------------------------------------------


This release contains the following components:

        * USB Bulk Driver Example  
        * USB Bulk Firmware Example
        * Host Application (F32x_BulkFileTransfer.exe)
        * Host Application Source


Last updated: 25 MAY 2005

Running the Example on the C8051F32x target board
------------------------------------------------------------

	1) Connect the hardware:

		a) Connect the target board to a PC through a Debug Adapter.

		b) Install shorting blocks at the following positions: 
		   J3[1-2] (P2.0 Switch), J3[3-4] (P2.1 Switch), 
		   J3[5-6] (P2.2 LED), J3[7-8] (P2.3 LED), J9 (P0.2), J10 (P0.3) 
		   and J13 (P1.7 Potentiometer).

		c) Connect a USB cable between the target device and the host PC.

		d) To power the target board from an wall-powered source, place a 
		   shorting block at J2 and NO shorting block at J11. Next, connect 
		   a DC power adapter to the target board at P1.

		e) To power the target board from the USB bus, place a shorting block 
		   on the target board at J11 and NO shorting block on J2.

	2) Build and download the Bulk Example firmware:

		a) Open the Silicon Laboratories IDE (v1.72 or later).

		b) Open the Connection Options window by selecting Options->
		   Connection Options... in the IDE menus. In the Debug Interface 
		   section, select C2.

		c) Connect to the target C8051F32x device (Alt+C, or IDE menu 
		   Debug->Connect).

		d) From the Project menu, select "Open Project" and browse to the 
		   Bulk Example Firware project "BulkFirmware.wsp", located by default in the 
		   "Silabs\MCU\Examples\C8051F32x\USB_Bulk\Firmware" directory.

		e) Build the project (F7, or through IDE menu Project->Build/Make Project).
		
		f) Download the firmware (Alt+D).

	3) Run the Bulk Example firmware:

		a) In the IDE, Run the firmware (F5, or IDE menu Debug->Go).

		b) When Windows detects the device and the driver installation wizard opens:
		   a. Choose "Search for a suitable driver for my device", and click Next.
		   b. Check the box "Specify a location", and click Next.
		   c. Browse to directory ..\USB_Bulk and select the file SilabsBulk.inf, and click OK.
		   d. Follow the dialogue to finish driver installation.

		c) Once the firmware has been downloaded and is running, the IDE is no 
		   longer needed. Disconnect from the target device with the IDE and 
		   press the Reset button on the Target Board.

	4) Run the Bulk Example host application:

		a) Run the F32x_BulkFileTransfer.exe application located by default in the
		   "Silabs\MCU\Examples\C8051F32x\USB_Bulk" directory.

		b) The F32x_BulkFileTransfer application will display the current USB
		   devices connected to the PC. Select the device to be used for the 
		   file transfer.

		c) Select file names for Transferring or Receiving data.  




