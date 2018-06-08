@************************************************ 
@ NAME    : MEMCFG.A
@ DESC	  : Memory bank configuration file
@ Revision: 02.28.2002 ver 1.0
@************************************************

@Memory Area
@GCS6 16bit(16MB) SDRAM(0x0c000000-0x0cffffff)
@GCS7 16bit(16MB) SDRAM(0x0d000000-0x0dffffff)
@          or
@GCS6 32bit(32MB) SDRAM(0x0c000000-0x0dffffff)

 
@BWSCON
.EQU    DW8		,	(0x0)
.EQU    DW16		,	(0x1)
.EQU    DW32		,	(0x2)
.EQU    WAIT		,	(0x1<<2)
.EQU    UBLB		,	(0x1<<3)

@	ASSERT :DEF:BUSWIDTH
.IF BUSWIDTH==16
.EQU    B1_BWSCON	, (DW16)
.EQU    B2_BWSCON	, (DW8)
.EQU    B3_BWSCON	, (DW8)
.EQU    B4_BWSCON	, (DW8)
.EQU    B5_BWSCON	, (DW8)
.EQU    B6_BWSCON	, (DW8)
.EQU    B7_BWSCON	, (DW8)
.ELSE    @BUSWIDTH=32
.EQU    B1_BWSCON	, (DW32)
.EQU    B2_BWSCON	, (DW8)
.EQU    B3_BWSCON	, (DW8)
.EQU    B4_BWSCON	, (DW8)
.EQU    B5_BWSCON	, (DW8)
.EQU    B6_BWSCON	, (DW32)
.EQU    B7_BWSCON	, (DW32)
.ENDIF

@BANK0CON 

.EQU    B0_Tacs		,	0x0	@0clk
.EQU    B0_Tcos		,	0x0	@0clk
.EQU    B0_Tacc		,	0x7	@14clk
.EQU    B0_Tcoh		,	0x0	@0clk
.EQU    B0_Tah		,	0x0	@0clk
.EQU    B0_Tacp		,	0x0	
.EQU    B0_PMC		,	0x0	@normal

@BANK1CON
.EQU    B1_Tacs		,	0x0	@0clk
.EQU    B1_Tcos		,	0x0	@0clk
.EQU    B1_Tacc		,	0x7	@14clk
.EQU    B1_Tcoh		,	0x0	@0clk
.EQU    B1_Tah		,	0x0	@0clk
.EQU    B1_Tacp		,	0x0	
.EQU    B1_PMC		,	0x0	@normal

@Bank 2 parameter
.EQU    B2_Tacs		,	0x0	@0clk
.EQU    B2_Tcos		,	0x0	@0clk
.EQU    B2_Tacc		,	0x7	@14clk
.EQU    B2_Tcoh		,	0x0	@0clk
.EQU    B2_Tah		,	0x0	@0clk
.EQU    B2_Tacp		,	0x0	
.EQU    B2_PMC		,	0x0	@normal

/*
@Bank 3 parameter
.EQU    B3_Tacs	,	0x0	@0clk
.EQU    B3_Tcos	,	0x0	@0clk
.EQU    B3_Tacc	,	0x7	@14clk
.EQU   B3_Tcoh ,   0x0	@0clk
.EQU   B3_Tah	,	0x0	@0clk
.EQU   B3_Tacp	,	0x0	
.EQU    B3_PMC	,	0x0	@normal
*/
@Bank 3 parameter
.EQU    B3_Tacs	,	0x0	@0clk
.EQU    B3_Tcos	,	0x3	@0clk
.EQU    B3_Tacc	,	0x7	@14clk
.EQU    B3_Tcoh ,   0x1	@0clk
.EQU    B3_Tah	,	0x0	@0clk
.EQU    B3_Tacp	,	0x3	
.EQU    B3_PMC	,	0x0	@normal

@Bank 4 parameter
.EQU    B4_Tacs		,	0x0	@0clk
.EQU    B4_Tcos		,	0x0	@0clk
.EQU    B4_Tacc		,	0x7	@14clk
.EQU    B4_Tcoh		,	0x0	@0clk
.EQU    B4_Tah		,	0x0	@0clk
.EQU    B4_Tacp		,	0x0	
.EQU    B4_PMC		,	0x0	@normal

@Bank 5 parameter
.EQU    B5_Tacs		,	0x0	@0clk
.EQU    B5_Tcos		,	0x0	@0clk
.EQU    B5_Tacc		,	0x7	@14clk
.EQU    B5_Tcoh		,	0x0	@0clk
.EQU    B5_Tah		,	0x0	@0clk
.EQU    B5_Tacp		,	0x0	
.EQU    B5_PMC		,	0x0	@normal

@Bank 6 parameter
.EQU    B6_MT		,	0x3	@SDRAM
@B6_Trcd		,	0x0	@2clk
.EQU    B6_Trcd		,	0x1	@3clk
.EQU    B6_SCAN		,	0x1	@9bit

@Bank 7 parameter
.EQU    B7_MT		,	0x3	@SDRAM
@.EQU    B7_Trcd		,	0x0	@2clk
.EQU    B7_Trcd		,	0x1	@3clk
.EQU    B7_SCAN		,	0x1	@9bit

@REFRESH parameter
.EQU    REFEN		,	0x1	@Refresh enable
.EQU    TREFMD		,	0x0	@CBR(CAS before RAS)/Auto refresh
.EQU    Trp		,	0x0	@2clk
.EQU    Trc		,	0x3	@7clk
		
.EQU    Tchr		,	0x2	@3clk
.EQU    REFCNT		,	1113	@period=15.6us, HCLK=60Mhz, (2048+1-15.6*60)

