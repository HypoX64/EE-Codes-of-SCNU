@=========================================
@ NAME: 2410INIT.S
@ DESC: Start Code for JXARM9-2410
@       1. Exception vector table
@       2. Configure memory, ISR ,stacks
@	    3. Initialize C-variables
@       4. Interrupt Handle
@ HISTORY:
@ 2004.06.25:cooljet: ver 1.0
@=========================================

@=========================================
@ include files
@=========================================
	.INCLUDE "2410addr.inc"
	.INCLUDE "2410option.inc"
	.INCLUDE "2410memcfg.inc"

@=========================================
@ Pre-defined constants
@=========================================
.EQU    BIT_SELFREFRESH ,	(1<<22)

.EQU    USERMODE    , 	0x10
.EQU    FIQMODE     , 	0x11
.EQU    IRQMODE     , 	0x12
.EQU    SVCMODE     , 	0x13
.EQU    ABORTMODE   , 	0x17
.EQU    UNDEFMODE   , 	0x1b
.EQU    MODEMASK    , 	0x1f
.EQU    NOINT       , 	0xc0

@ The location of stacks
.EQU    SVCStack	,	(_STACK_BASEADDRESS-0x3800)	    @0x30ff4800 ~ 
.EQU    UserStack   ,	(_STACK_BASEADDRESS-0x2800) 	@0x30ff5800 ~
.EQU    UndefStack	,	(_STACK_BASEADDRESS-0x2400) 	@0x30ff5c00 ~
.EQU    AbortStack	,	(_STACK_BASEADDRESS-0x2000) 	@0x30ff6000 ~
.EQU    IRQStack    ,	(_STACK_BASEADDRESS-0x1000)	    @0x30ff7000 ~
.EQU    FIQStack	,	(_STACK_BASEADDRESS-0x0)	    @0x30ff8000 ~ 

@=========================================
@ MACROs
@=========================================
    .MACRO HANDLER HandleLabel
@HandlerLabel:
	sub	sp,sp,#4        @decrement sp(to store jump address)
	stmfd	sp!,{r0}        @PUSH the work register to stack(lr does't push because it return to original address)
	ldr     r0,=\HandleLabel@load the address of HandleXXX to r0
	ldr     r0,[r0]         @load the contents(service routine start address) of HandleXXX
	str     r0,[sp,#4]      @store the contents(ISR) of HandleXXX to stack
	ldmfd   sp!,{r0,pc}     @POP the work register and pc(jump to ISR)
	.ENDM
	
@=========================================
@ EXTERNs
@=========================================
	.EXTERN  Image_RO_Limit  @ End of ROM code (=start of ROM data)
	.EXTERN  Image_RW_Base   @ Base of RAM to initialise
	.EXTERN  Image_ZI_Base   @ Base and limit of area
	.EXTERN  Image_ZI_Limit  @ to zero initialise
	
	.EXTERN  Main    @ The main entry of mon program 
	
@=========================================
@ Exception entry
@=========================================
    b	ResetHandler  
	b	HandlerUndef	@handler for Undefined mode
	b	HandlerSWI	    @handler for SWI interrupt
	b	HandlerPabort	@handler for PAbort
	b	HandlerDabort	@handler for DAbort
	b	.		        @reserved
	b	HandlerIRQ	    @handler for IRQ interrupt 
	b	HandlerFIQ	    @handler for FIQ interrupt

	.LTORG   
HandlerFIQ:      HANDLER HandleFIQ
HandlerIRQ:      HANDLER HandleIRQ
HandlerUndef:    HANDLER HandleUndef
HandlerSWI:      HANDLER HandleSWI
HandlerDabort:   HANDLER HandleDabort
HandlerPabort:   HANDLER HandlePabort

@===============================
@ IRQ Handle  
@===============================
IsrIRQ:  
	sub	sp,sp,#4           @reserved for PC
	stmfd	sp!,{r8-r9}   
	
	ldr	r9,=INTOFFSET
	ldr	r9,[r9]            @ Load the INTOFFSET register value to r9
	ldr	r8,=HandleEINT0    @ Load the ISR vector base address to r8
	add	r8,r8,r9,lsl #2    @ get the ISR vector r8 = r8 + r9 * 4
	ldr	r8,[r8]            @ Load the ISR address
	str	r8,[sp,#8]         @ store to sp, new PC
	ldmfd	sp!,{r8-r9,pc} @ jump to new PC, that is to ISR 

@===============================
@ ENTRY  
@===============================
ResetHandler:
	ldr	r0,=WTCON       @watch dog disable 
	ldr	r1,=0x0         
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff  @all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x3ff		@all sub interrupt disable
	str	r1,[r0]

/*
	[ {FALSE}
        @ rGPFDAT = (rGPFDAT & ~(0xf<<4)) | ((~data & 0xf)<<4)@    
        @ Led_Display
	ldr	r0,=GPFCON
	ldr	r1,=0x5500		
	str	r1,[r0]
	ldr	r0,=GPFDAT
	ldr	r1,=0x10
	str	r1,[r0]
	]
*/
	
	@To reduce PLL lock time, adjust the LOCKTIME register. 
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]
        
    .IFDEF PLL_ON_START
	@Configure MPLL
    ldr r0,=MPLLCON          
    ldr r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  @Fin=12MHz,Fout=50MHz
    str r1,[r0]
	.ENDIF
	
	@ Set memory control registers
   	ldr	r0,=SMRDATA
	ldr	r1,=BWSCON	@BWSCON Address
	add	r2, r0, #52	@End address of SMRDATA
0:       @
	ldr	r3, [r0], #4    
	str	r3, [r1], #4    
	cmp	r2, r0		
	bne	0b
		
    @Initialize stacks
	bl	InitStacks
	
  	@ Setup IRQ handler
	ldr	r0,=HandleIRQ       @This routine is needed
	ldr	r1,=IsrIRQ          @if there isn't 'subs pc,lr,#4' at 0x18, 0x1c
	str	r1,[r0]

	@ Copy and paste RW data/zero initialized data
	ldr	r0, =Image_RO_Limit @ Get pointer to ROM data
	ldr	r1, =Image_RW_Base  @ and RAM copy
	ldr	r3, =Image_ZI_Base  
	
	@ Zero init base => top of initialised data
	cmp	r0, r1      @ Check that they are different
	beq	2f
1:       
	cmp	r1, r3      @ Copy init data
	ldrcc	r2, [r0], #4    @--> LDRCC r2, [r0] + ADD r0, r0, #4         
	strcc	r2, [r1], #4    @--> STRCC r2, [r1] + ADD r1, r1, #4
	bcc	1b
2:       
	ldr	r1, =Image_ZI_Limit @ Top of zero init segment
	mov	r2, #0
3:       
	cmp	r3, r1      @ Zero init
	strcc	r2, [r3], #4
	bcc	3b		

   	bl	Main        @ Just to C Code Now......
   	b	.                       

@===================================================================================
@ Initializing stacks
@     Don't use DRAM,such as stmfd,ldmfd......
@     SVCstack is initialized before
@     Under toolkit ver 2.5, 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1'
@===================================================================================
InitStacks:
	mrs	r0,cpsr
	bic	r0,r0,#MODEMASK
	orr	r1,r0,#UNDEFMODE|NOINT
	msr	cpsr,r1			@UndefMode
	ldr	sp,=UndefStack
	
	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr,r1			@AbortMode
	ldr	sp,=AbortStack

	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr,r1			@IRQMode
	ldr	sp,=IRQStack
    
	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr,r1			@FIQMode
	ldr	sp,=FIQStack

	bic	r0,r0,#MODEMASK|NOINT
	orr	r1,r0,#SVCMODE
	msr	cpsr,r1			@SVCMode
	ldr	sp,=SVCStack
	
	mov	pc,lr   

	.LTORG	

@===================================================================
@ Memory configuration:
@     Memory configuration should be optimized for best performance 
@     The following parameter is not optimized.                     
@     Memory access cycle parameter strategy
@     1. The memory settings is  safe parameters even at HCLK=75Mhz.
@     2. SDRAM refresh period is for HCLK=75Mhz. 
@===================================================================
SMRDATA:
    .LONG (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
    .LONG ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   @GCS0
    .LONG ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   @GCS1 
    .LONG ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))   @GCS2
    .LONG ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))   @GCS3
    .LONG ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))   @GCS4
    .LONG ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))   @GCS5
    .LONG ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    @GCS6
    .LONG ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))    @GCS7
    .LONG ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+REFCNT)       

    .LONG 0xb2            @SCLK power saving mode, ARM core burst enable , BANKSIZE 128M/128M - 11/29/2002

    .LONG 0x30            @MRSR6 CL=3clk
    .LONG 0x30            @MRSR7

@=========================================
@ Exception vector table
@=========================================
.EQU HandleReset, 	    _ISR_STARTADDRESS        @   4 
.EQU HandleUndef, 	    _ISR_STARTADDRESS + 0x4  @   4
.EQU HandleSWI, 	    _ISR_STARTADDRESS + 0x8  @   4
.EQU HandlePabort, 	    _ISR_STARTADDRESS + 0xc  @   4
.EQU HandleDabort, 	    _ISR_STARTADDRESS + 0x10 @   4
.EQU HandleReserved, 	_ISR_STARTADDRESS + 0x14 @   4
.EQU HandleIRQ, 	    _ISR_STARTADDRESS + 0x18 @   4
.EQU HandleFIQ, 	    _ISR_STARTADDRESS + 0x1c @   4

@=========================================
@ Interrupt vector table
@=========================================
.EQU HandleEINT0, 	    _ISR_STARTADDRESS + 0x20 @   4
.EQU HandleEINT1, 	    _ISR_STARTADDRESS + 0x24 @   4
.EQU HandleEINT2, 	    _ISR_STARTADDRESS + 0x28 @   4
.EQU HandleEINT3, 	    _ISR_STARTADDRESS + 0x2c @   4
.EQU HandleEINT4_7,  	_ISR_STARTADDRESS + 0x30 @   4
.EQU HandleEINT8_23, 	_ISR_STARTADDRESS + 0x34 @   4
.EQU HandleRSV6,     	_ISR_STARTADDRESS + 0x38 @   4
.EQU HandleBATFLT, 	    _ISR_STARTADDRESS + 0x3c @   4
.EQU HandleTICK, 	    _ISR_STARTADDRESS + 0x40 @   4
.EQU HandleWDT, 	    _ISR_STARTADDRESS + 0x44 @   4
.EQU HandleTIMER0, 	    _ISR_STARTADDRESS + 0x48 @   4
.EQU HandleTIMER1, 	    _ISR_STARTADDRESS + 0x4c @   4
.EQU HandleTIMER2, 	    _ISR_STARTADDRESS + 0x50 @   4
.EQU HandleTIMER3, 	    _ISR_STARTADDRESS + 0x54 @   4
.EQU HandleTIMER4, 	    _ISR_STARTADDRESS + 0x58 @   4
.EQU HandleUART2, 	    _ISR_STARTADDRESS + 0x5c @   4
.EQU HandleLCD, 	    _ISR_STARTADDRESS + 0x60 @   4
.EQU HandleDMA0, 	    _ISR_STARTADDRESS + 0x64 @   4
.EQU HandleDMA1, 	    _ISR_STARTADDRESS + 0x68 @   4
.EQU HandleDMA2, 	    _ISR_STARTADDRESS + 0x6c @   4
.EQU HandleDMA3, 	    _ISR_STARTADDRESS + 0x70 @   4
.EQU HandleMMC, 	    _ISR_STARTADDRESS + 0x74 @   4
.EQU HandleSPI0, 	    _ISR_STARTADDRESS + 0x78 @   4
.EQU HandleUART1, 	    _ISR_STARTADDRESS + 0x7c @   4
.EQU HandleRSV24, 	    _ISR_STARTADDRESS + 0x80 @   4
.EQU HandleUSBD,     	_ISR_STARTADDRESS + 0x84 @   4
.EQU HandleUSBH,     	_ISR_STARTADDRESS + 0x88 @   4
.EQU HandleIIC,     	_ISR_STARTADDRESS + 0x8c @   4 
.EQU HandleUART0,     	_ISR_STARTADDRESS + 0x90 @   4
.EQU HandleSPI1, 	    _ISR_STARTADDRESS + 0x94 @   4
.EQU HandleRTC, 	    _ISR_STARTADDRESS + 0x98 @   4
.EQU HandleADC, 	    _ISR_STARTADDRESS + 0x9c @   4

        .END
