asm {/* See $LK,"::/Doc/Boot.DD"$.
ZenithOS starts in real, calls some BIOS routines, switches to 32 bit, and 64 bit mode and continues in $LK,"CosmiC",A="FI:::/Doc/CosmiC.DD"$ at $LK,"KMain",A="MN:KMain"$().

The boot loader jumps here in real-mode (16-bit).
It actually jumps to the $LK,"CBinFile",A="MN:CBinFile"$ header which is placed just before this by $LK,"the compiler",A="FF:::/Compiler/CMain.CC,16 ALIGN"$.
The header begins with a short jmp to the start of this file's code which begins with the following small jump past some data.

This file is first in the Kernel image because it is #included first.  $LK,"Kernel.PRJ",A="FF:::/Kernel/Kernel.PRJ,KStart16:1"$
*/
USE16
SYS_KERNEL:: //This must match $LK,"CKernel",A="MN:CKernel"$.
		JMP		I16 CORE0_16BIT_INIT

//************************************
//	ASM Global vars required for 16-bit start-up
		ALIGN 	4, OC_NOP

SYS_BOOT_SRC::				DU32	BOOT_SRC_NULL;
SYS_BOOT_BLK::				DU32	0;
SYS_BOOT_PATCH_TABLE_BASE::	DU32	0;
SYS_RUN_LEVEL::				DU32	0;

#exe
{
	StreamPrint("SYS_COMPILE_TIME:: DU64 0x%X;", Now); //See $LK,"BootDVDProbe",A="MN:BootDVDProbe"$
};

#assert SYS_COMPILE_TIME + sizeof(CDate) + sizeof(CBinFile) < DVD_BLK_SIZE

MEM_BOOT_BASE::			DU32	0;	//Offset from start used by reboot
MEM_E801::				DU16	0, 0;
MEM_E820::				DU8 	MEM_E820_ENTRIES_NUM * sizeof(CMemE820) DUP (0);
MEM_PHYSICAL_SPACE::	DU64	0;
SYS_GDT_PTR::			DU16	sizeof(CGDT) - 1;
						DU64	0;
SYS_PCI_BUSES::			DU16	0;

		ALIGN 	16, OC_NOP

SYS_GDT:: //See $LK,"CGDT",A="MN:CGDT"$
GDT_NULL:		DU64	0,0;
GDT_BOOT_DS:	DU64	0x00CF92000000FFFF, 0; //Gets patched.
GDT_BOOT_CS:	DU64	0x00CF9A000000FFFF, 0; //Gets patched.
GDT_CS32: 		DU64	0x00CF9A000000FFFF, 0;
GDT_CS64: 		DU64	0x00209A0000000000, 0; //The $LK,"Charter",A="FI:::/Doc/Charter.DD"$ says just ring0.
GDT_CS64_RING3: DU64	0x0020FA0000000000, 0; //$LK,"Ring3",A="FI:::/Demo/Lectures/Ring3.CC"$, so you can play with.
GDT_DS: 		DU64	0x00CF92000000FFFF, 0;
GDT_DS_RING3: 	DU64	0x00CFF2000000FFFF, 0;
GDT_TR: 		DU8 	MP_PROCESSORS_NUM * 16 DUP(0);
GDT_TR_RING3: 	DU8 	MP_PROCESSORS_NUM * 16 DUP(0);
#assert $$ - SYS_GDT == sizeof(CGDT)

SYS_FONT_PTR::	DU32	0;

SYS_VBE_INFO::			DU8 	sizeof(CVBEInfo)						DUP(0);
SYS_VBE_MODES::			DU8 	sizeof(CVBEModeShort) * VBE_MODES_NUM	DUP(0);
SYS_VBE_FINAL_MODE::	DU8 	sizeof(CVBEMode)						DUP(0);
SYS_VBE_FINAL_MODE_NUM::DU16	0; //mode number of final mode set
#assert $$ - SYS_KERNEL == sizeof(CKernel) - sizeof(CBinFile)

TEMP_VBE_MODE:		DU8 	sizeof(CVBEMode)		DUP(0);
MAX_VBE_MODE:		DU8 	sizeof(CVBEModeShort)	DUP(0);
MAX_SCREEN_HEIGHT:	DU16	0;

#exe
{
	StreamPrint("SCREEN_WIDTH:	DU16		%d;"
				"SCREEN_HEIGHT: DU16		%d;", kernel_config->screen_width, kernel_config->screen_height);
};

//************************************
CORE0_16BIT_INIT::
//EAX is $LK,"SYS_BOOT_SRC",A="FF:::/Kernel/KStart16.CC,[SYS_BOOT_SRC]"$. (Val passed from boot blk, $LK,"BootHD",A="FF:::/Zenith/Boot/BootHD.CC,BOOT_SRC_HARDDRIVE"$, $LK,"BootDVD",A="FF:::/Zenith/Boot/BootDVD.CC,BOOT_SRC_DVD"$, & $LK,"BootRAM",A="FF:::/Zenith/Boot/BootRAM.CC,BOOT_SRC_RAM"$.)
		MOV		ECX, EAX
		MOV		AX, (BOOT_RAM_LIMIT - BOOT_STACK_SIZE) / 16
		MOV		SS, AX
		MOV		SP, BOOT_STACK_SIZE
		PUSH	ECX 		//Will be $LK,"SYS_BOOT_SRC",A="FF:::/Kernel/KStart16.CC,[SYS_BOOT_SRC]"$. See $LK,"BootHD",A="FF:::/Zenith/Boot/BootHD.CC,BOOT_SRC_HARDDRIVE"$, $LK,"BootDVD",A="FF:::/Zenith/Boot/BootDVD.CC,BOOT_SRC_DVD"$ & $LK,"BootRAM",A="FF:::/Zenith/Boot/BootRAM.CC,BOOT_SRC_RAM"$.
		PUSH	EBX
		CALL	U16 GET_IP
GET_IP: POP 	BX
		SUB 	BX, GET_IP
		SHR 	BX, 4
		MOV 	AX, CS
		ADD 	AX, BX
		PUSH	AX
		PUSH	U16 @@04
		RETF

@@04: 	STI
		MOV 	AX, CS
		MOV 	DS, AX
		MOV 	U32 [SYS_RUN_LEVEL], RLF_16BIT

//Our variables are on the data segment, but VBE functions require ES.
//moving DS into ES, while preserving ES
		PUSH	ES
		PUSH	DS
		POP 	ES

//Get VBE implementation information
		MOV		AX, 0x4F00
		MOV		DI, SYS_VBE_INFO
		MOV		CVBEInfo.signature[DI], 'VBE2' //set to 'VBE2' to use VBE 2.0 functionality
		INT		0x10
		POP		ES
		CMP		AX, 0x004F
		JE		@@05
		JMP		$$	//Freeze system if VBE not supported

@@05:

/*Loop variables:
 DI <- Temporary storage for mode information
 CX <- Mode number
 DX <- mode array
 GS <- Segment for video modes list
 SI <- Offset for video modes list
*/
//Obtain segment:offset of list of potential video modes
		MOV		AX, SYS_VBE_INFO
		MOV		SI, CVBEInfo.video_modes[AX]
		MOV		GS, CVBEInfo.video_modes+2[AX]
		MOV		DI, TEMP_VBE_MODE
		MOV		DX, SYS_VBE_MODES

@@06: //Loop through all the mode numbers
		MOV 	AX, GS:[SI]
		CMP 	AX, 0xFFFF //FFFF signifies the end of the list
		JE		@@08

		ADD 	SI, 2 //Increment pointer to read next U16 mode

		MOV 	CX, AX
		BTS 	CX, 14 //Set linear framebuffer bit in the mode number we are about to pass to the BIOS below
		PUSH	ES
		PUSH	DS
		POP 	ES
//Get mode information for mode number
		MOV		AX, 0x4F01
		INT		0x10
		POP		ES
		CMP		AX, 0x004F
		JNE		@@06 //if call to get mode information failed

//filter everything but 32-bit color
		MOV 	AL, CVBEMode.bpp[DI]
		CMP 	AL, 32
		JNE 	@@06

//Check if the mode is actually supported
		MOV 	AX, CVBEMode.attributes[DI]
		AND 	AX, 0x91 //bit 0 = supported, bit 4 = graphics mode, bit 7 = linear framebuffer
		CMP 	AX, 0x91
		JNE 	@@06

//Only want memory model of packed pixel or direct color (RGB)
//		MOV 	AX, CVBEMode.memory_model[DI]
//		CMP 	AX, 4
//		JNE 	@@06
//		CMP 	AX, 6
//		JNE 	@@06
//Copy information about this mode into an element of the mode array
		MOV 	BX, CVBEMode.height[DI]
		MOV 	CVBEModeShort.height[DX], BX
		CMP 	BX, [MAX_SCREEN_HEIGHT]
		JL		@@07

		MOV		[MAX_SCREEN_HEIGHT], BX
		MOV		[MAX_VBE_MODE],      CX

@@07: 	MOV		AX, CVBEMode.width[DI]
		MOV		CVBEModeShort.width[DX], AX
//		MOV		EAX, CVBEMode.max_pixel_clock[DI]
//		MOV		CVBEModeShort.max_pixel_clock[DX], EAX

		MOV 	CVBEModeShort.mode_num[DX], CX
		ADD 	DX, sizeof(CVBEModeShort) //next array element

//Check if width and height match
		CMP		AX, [SCREEN_WIDTH]
		JNE		@@06
		CMP		BX, [SCREEN_HEIGHT]
		JNE		@@06

//If we've made it here we have our mode
		MOV		[SYS_VBE_FINAL_MODE_NUM], CX
		JMP		@@06

@@08: //End of loop
//If there isn't a valid mode set by user through kernel config, set the mode with the biggest height.
		MOV		AX, [SYS_VBE_FINAL_MODE_NUM]
		CMP		AX, 0
		JNE		@@09
		MOV		CX, [MAX_VBE_MODE]
		MOV		[SYS_VBE_FINAL_MODE_NUM], CX

@@09: 	PUSH	ES
		PUSH	DS
		POP 	ES
//Get mode infomration for the mode we want
		MOV 	DI, SYS_VBE_FINAL_MODE
		MOV 	CX, [SYS_VBE_FINAL_MODE_NUM]
		MOV 	AX, 0x4F01
		INT 	0x10
		POP 	ES
		CMP 	AX, 0x004F
		JNE 	@@10 //if called failed

//Set the mode; call takes mode number in BX
		MOV 	AX, 0x4F02
		MOV 	BX, CX
		INT 	0x10
		CMP 	AX, 0x004F
		JNE 	@@10

		BTS 	U32 [SYS_RUN_LEVEL], RLf_VESA
@@10:

//Get pointer to 8x8 VGA ROM font.
		MOV		AX, 0x1130
		MOV		BH, 3
		INT		0x10
		MOV		AX, ES
		SHL		EAX, 16
		MOV		AX, BP
		MOV		U32 [SYS_FONT_PTR], EAX

//Get E801 memory map.
//Output: AX = Memory between 1MiB and 16MiB in KiB (max 0x3C00 == 15 MiB)
//		  BX = Memory after 16MiB until first memory hole in 64KiB blocks.
		XOR		CX, CX
		XOR		DX, DX
		MOV		AX, 0xE801
		INT 	0x15
		JCXZ	@@12 //if CX and DX are zero, use AX and BX instead.
		MOV		AX, CX
		MOV		BX, DX
@@12:	MOV 	U16 [MEM_E801],   AX
		MOV 	U16 [MEM_E801+2], BX

//Get E820 memory map.
		MOV 	CX,  MEM_E820_ENTRIES_NUM - 1 //Leave one to terminate
		XOR 	EBX, EBX
		PUSH	DS
		POP		ES
		MOV 	DI,  MEM_E820
@@15: 	PUSH	CX
		MOV 	EAX, 0xE820
		MOV 	ECX, sizeof(CMemE820)
		MOV 	EDX, 'PAMS'
		INT 	0x15
		JC		@@20
		CMP 	EAX, 'PAMS'
		JNE 	@@20
		TEST	EBX, EBX
		JZ		@@20
		ADD 	DI,  sizeof(CMemE820)
		POP 	CX
		LOOP	@@15
		SUB 	SP,  2
@@20: 	ADD		SP,  2 //if called failed we want to nullify the PUSHed CX value.

//Find how much space to map, start with E801 limit.
		XOR 	EAX, EAX
		MOV 	AX,  [MEM_E801+2]
		SHL 	EAX, 16
		ADD 	EAX, SYS_16MEG_AREA_LIMIT
		XOR 	EDX, EDX

//Find max of E820 to set mapped space.
		MOV 	SI,  MEM_E820
@@25: 	MOV 	CL,  CMemE820.type[SI]
		TEST	CL,  CL
		JZ		@@35
		MOV 	EBX, CMemE820.base  [SI]
		MOV 	ECX, CMemE820.base+4[SI]
		ADD 	EBX, CMemE820.len   [SI]
		ADC 	ECX, CMemE820.len+4 [SI]
		SUB 	EBX, EAX
		SBB 	ECX, EDX
		JC		@@30
		MOV		EAX, CMemE820.base  [SI]
		MOV		EDX, CMemE820.base+4[SI]
		ADD		EAX, CMemE820.len   [SI]
		ADC		EDX, CMemE820.len+4 [SI]
@@30: 	ADD		SI,  sizeof(CMemE820)
		JMP		@@25

@@35: 	MOV		[MEM_PHYSICAL_SPACE],   EAX
		MOV		[MEM_PHYSICAL_SPACE+4], EDX

//Get PCI Bus Info
		MOV		U16 [SYS_PCI_BUSES], 256
		XOR		DX, DX
		MOV		AX, 0xB101
		INT		0x1A
		CMP		DX, 'PC'
		JNE		@@40
		MOV		CH, 0
		INC		CX
		MOV		U16 [SYS_PCI_BUSES], CX
@@40:
		CLI
//Enable A20
		IN		AL, 0x92
		OR		AL, 2
		OUT		0x92, AL

		POP		U32 [SYS_BOOT_BLK]
		POP		U32 [SYS_BOOT_SRC]	//See $LK,"BootHD",A="FF:::/Zenith/Boot/BootHD.CC,BOOT_SRC_HARDDRIVE"$, $LK,"BootDVD",A="FF:::/Zenith/Boot/BootDVD.CC,BOOT_SRC_DVD"$, & $LK,"BootRAM",A="FF:::/Zenith/Boot/BootRAM.CC,BOOT_SRC_RAM"$.

		CLD		
		XOR 	EAX, EAX
		MOV 	AX,  CS
		MOV 	DS,  AX
		MOV 	ES,  AX
		SHL 	EAX, 4

		MOV		U32 [MEM_BOOT_BASE], EAX

		MOV 	DX, CS
		SUB 	DX, sizeof(CBinFile) / 16
#assert !(sizeof(CBinFile) & 0xF)
		MOV 	GS, DX

		MOV		EDX, EAX
		ADD		EDX, U32 GS:[CBinFile.patch_table_offset]
		SUB		EDX, sizeof(CBinFile)
		MOV		U32 [SYS_BOOT_PATCH_TABLE_BASE], EDX

		ADD		U32 [GDT_BOOT_DS+2], EAX
		ADD		U32 [GDT_BOOT_CS+2], EAX
		ADD		EAX, I32 SYS_GDT
		MOV		U32 [SYS_GDT_PTR + CSysLimitBase.base], EAX
		LGDT	U32 [SYS_GDT_PTR]

		MOV		EAX, SYS_START_CR0
		MOV_CR0_EAX

/* The assembler doesn't support far jumps so
we hand code it.	16-bit code is not important
enough to fully implement in the assembler.

To complete the switch to 32-bit mode, we have to load
the code segment with a far jump.
*/
		DU8 		0x66, 0xEA; //JMP CGDT.boot_cs:CORE0_32BIT_INIT
		DU32		CORE0_32BIT_INIT;
		DU16		CGDT.boot_cs;
#assert $$ + 16 <= 0xFFFF
}
