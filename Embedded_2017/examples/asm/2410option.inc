@===========================================
@ NAME: OPTION.A
@ DESC: Configuration options for .S files
@ HISTORY:
@ 02.28.2002: ver 1.0
@===========================================

@Start address of each stacks,
.EQU    _STACK_BASEADDRESS	, 0x33ff8000  
.EQU    _MMUTT_STARTADDRESS	, 0x33ff8000  
.EQU    _ISR_STARTADDRESS	, 0x33ffff00

@	GBLL 	PLL_ON_START  
@PLL_ON_START	SETL 	{TRUE}
.EQU PLL_ON_START, 1

@	GBLL	ENDIAN_CHANGE
@ENDIAN_CHANGE	SETL	{FALSE}

@		GBLA	ENTRY_BUS_WIDTH
@ENTRY_BUS_WIDTH	SETA	16	
.EQU ENTRY_BUS_WIDTH	,	16	


@BUSWIDTH = 16,32
@		GBLA    BUSWIDTH	@max. bus width for the GPIO configuration
@BUSWIDTH	SETA    32
.EQU BUSWIDTH, 32


@		GBLA	FCLK
@FCLK		SETA	50000000
.EQU FCLK , 50000000

    .IF	FCLK == 20000000	
.EQU M_MDIV	,	0x20	@Fin=12.0MHz Fout=30.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

    .IF	FCLK == 30000000	
.EQU M_MDIV	,	0x34	@Fin=12.0MHz Fout=30.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

    .IF	FCLK == 50000000	
.EQU M_MDIV	,	0x5c	@Fin=12.0MHz Fout=50.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

    .IF	FCLK == 60000000	
.EQU M_MDIV	,	0x70	@Fin=12.0MHz Fout=60.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

    .IF	FCLK == 70000000	
.EQU M_MDIV	,	0x84	@Fin=12.0MHz Fout=70.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

    .IF	FCLK == 75000000	
.EQU M_MDIV	,	0x8e	@Fin=12.0MHz Fout=75.0MHz
.EQU M_PDIV	,	0x4
.EQU M_SDIV	,	0x2
    .ENDIF

@	END
