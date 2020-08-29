@=====================================================================
@ File Name : 2410slib.s
@ Function  : S3C2410  (Assembly)
@ Program   : Shin, On Pil (SOP)
@ Date      : March 20, 2002
@ Version   : 0.0
@ History
@   1.0 : Programming start (February 26,2002) -> SOP
@=====================================================================

@Interrupt, FIQ/IRQ disable
.EQU NOINT  , 0xc0    @ 1100 0000  

@Check if tasm.exe(armasm -16 ...@ADS 1.0) is used.
@.EQU THUMBCODE ,  TRUE

   .MACRO     MOV_PC_LR
     .IFDEF THUMBCODE
       bx lr
     .ELSE
       mov pc,lr
     .ENDIF
   .ENDM

@==========================================================================
@ int SET_IF(void);
@     Des: Set the I, F bit of CPSR, that is disable all IRQ, FIQ
@          This function works only if the processor is in previliged mode.
@     Return: The return value is current CPSR.
@==========================================================================
	.GLOBAL	SET_IF
SET_IF:
   mrs r0,cpsr
   mov r1,r0
   orr r1,r1,#NOINT
   msr cpsr_cxsf,r1		
   MOV_PC_LR

@==========================================================================
@ void WR_IF(int cpsrValue);
@     Des: Write the CPSR
@          This function works only if the processor is in previliged mode.
@     Return: NULL
@==========================================================================
   .GLOBAL WR_IF
WR_IF:	
    @This function works only if the processor is in previliged mode.
   msr cpsr_cxsf,r0		
   MOV_PC_LR


@==========================================================================
@ void CLR_IF(void);
@     Des: Clear the I, F bit of CPSR, that is enable all IRQ, FIQ
@          This function works only if the processor is in previliged mode.
@     Return: NULL
@==========================================================================
   .GLOBAL  CLR_IF
CLR_IF:
   mrs r0,cpsr
   bic r0,r0,#NOINT
   msr cpsr_cxsf,r0		
   MOV_PC_LR

@====================================
@ MMU Cache/TLB/etc on/off functions
@====================================
.EQU R1_I	,	(1<<12)
.EQU R1_C	,	(1<<2)
.EQU R1_A	,	(1<<1)
.EQU R1_M    ,	(1)
.EQU R1_iA	,	(1<<31)
.EQU R1_nF   ,	(1<<30)

@======================================
@ void MMU_EnableICache(void)
@     Des: Enable the instruction cache
@     Return: NULL
@======================================
   .GLOBAL MMU_EnableICache
MMU_EnableICache:
   mrc p15,0,r0,c1,c0,0
   orr r0,r0,#R1_I
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_DisableICache(void)
@     Des: Disable the instruction cache
@     Return: NULL
@======================================
   .GLOBAL MMU_DisableICache
MMU_DisableICache:
   mrc p15,0,r0,c1,c0,0
   bic r0,r0,#R1_I
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_EnableDCache(void)
@     Des: Enable the data cache
@     Return: NULL
@======================================
   .GLOBAL MMU_EnableDCache
MMU_EnableDCache:
   mrc p15,0,r0,c1,c0,0
   orr r0,r0,#R1_C
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_DisableDCache(void)
@     Des: Disable the data cache
@     Return: NULL
@======================================
   .GLOBAL MMU_DisableDCache
MMU_DisableDCache:
   mrc p15,0,r0,c1,c0,0
   bic r0,r0,#R1_C
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_EnableAlignFault(void)
@     Des: Enable the align fault
@     Return: NULL
@======================================
   .GLOBAL MMU_EnableAlignFault 
MMU_EnableAlignFault:
   mrc p15,0,r0,c1,c0,0
   orr r0,r0,#R1_A
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_DisableAlignFault(void)
@     Des: Disable the align fault
@     Return: NULL
@======================================
   .GLOBAL MMU_DisableAlignFault
MMU_DisableAlignFault:
   mrc p15,0,r0,c1,c0,0
   bic r0,r0,#R1_A
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_EnableMMU(void)
@     Des: Enable MMU
@     Return: NULL
@======================================
   .GLOBAL MMU_EnableMMU
MMU_EnableMMU:
   mrc p15,0,r0,c1,c0,0
   orr r0,r0,#R1_M
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_DisableMMU(void)
@     Des: Disable MMU
@     Return: NULL
@======================================
   .GLOBAL MMU_DisableMMU
MMU_DisableMMU:
   mrc p15,0,r0,c1,c0,0
   bic r0,r0,#R1_M
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_SetFastBusMode(void)
@     Des: Set fast bus mode
@          FCLK:HCLK= 1:1
@     Return: NULL
@======================================
  .GLOBAL MMU_SetFastBusMode
MMU_SetFastBusMode:
   mrc p15,0,r0,c1,c0,0
   bic r0,r0,#R1_iA|R1_nF
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_SetAsyncBusMode(void) 
@     Des: Set async bus mode
@          FCLK:HCLK= 1:2
@     Return: NULL
@======================================
   .GLOBAL MMU_SetAsyncBusMode
MMU_SetAsyncBusMode:
   mrc p15,0,r0,c1,c0,0
   orr r0,r0,#R1_nF|R1_iA
   mcr p15,0,r0,c1,c0,0
   MOV_PC_LR

@======================================
@ void MMU_SetTTBase(int base) 
@     Des: Set TTBase
@     Return: NULL
@======================================
   .GLOBAL MMU_SetTTBase
MMU_SetTTBase:
   @ro=TTBase
   mcr p15,0,r0,c2,c0,0
   MOV_PC_LR

@======================================
@ void MMU_SetDomain(int domain)
@     Des: Set domain
@     Return: NULL
@======================================
   .GLOBAL MMU_SetDomain
MMU_SetDomain:
   @ro=domain
   mcr p15,0,r0,c3,c0,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateIDCache(void)
@======================================
   .GLOBAL MMU_InvalidateIDCache
MMU_InvalidateIDCache:
   mcr p15,0,r0,c7,c7,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateICache(void)
@======================================
   .GLOBAL MMU_InvalidateICache
MMU_InvalidateICache:
   mcr p15,0,r0,c7,c5,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateICacheMVA(U32 mva)
@======================================
   .GLOBAL MMU_InvalidateICacheMVA
MMU_InvalidateICacheMVA:	
   @r0=mva
   mcr p15,0,r0,c7,c5,1
   MOV_PC_LR
	
@======================================
@ void MMU_PrefetchICacheMVA(U32 mva)
@======================================
   .GLOBAL MMU_PrefetchICacheMVA
MMU_PrefetchICacheMVA:
   @r0=mva
   mcr p15,0,r0,c7,c13,1
   MOV_PC_LR

@======================================
@ void MMU_InvalidateDCache(void)
@======================================
   .GLOBAL MMU_InvalidateDCache
MMU_InvalidateDCache:
   mcr p15,0,r0,c7,c6,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateDCacheMVA(U32 mva)
@======================================
   .GLOBAL MMU_InvalidateDCacheMVA
MMU_InvalidateDCacheMVA:
   @r0=mva
   mcr p15,0,r0,c7,c6,1
   MOV_PC_LR

@======================================
@ void MMU_CleanDCacheMVA(U32 mva)
@======================================
   .GLOBAL MMU_CleanDCacheMVA
MMU_CleanDCacheMVA:
   @r0=mva
   mcr p15,0,r0,c7,c10,1
   MOV_PC_LR

@======================================
@ void MMU_CleanInvalidateDCacheMVA(U32 mva)
@======================================
   .GLOBAL MMU_CleanInvalidateDCacheMVA
MMU_CleanInvalidateDCacheMVA:
   @r0=mva
   mcr p15,0,r0,c7,c14,1
   MOV_PC_LR

@======================================
@ void MMU_CleanDCacheIndex(U32 index)
@======================================
   .GLOBAL MMU_CleanDCacheIndex
MMU_CleanDCacheIndex:
   @r0=index 
   mcr p15,0,r0,c7,c10,2
   MOV_PC_LR

@======================================
@ void MMU_CleanInvalidateDCacheIndex(U32 index)	
@======================================
   .GLOBAL MMU_CleanInvalidateDCacheIndex
MMU_CleanInvalidateDCacheIndex:	
   @r0=index
   mcr p15,0,r0,c7,c14,2
   MOV_PC_LR

@======================================
@ void MMU_WaitForInterrupt(void)
@======================================
   .GLOBAL MMU_WaitForInterrupt 
MMU_WaitForInterrupt:	
   mcr p15,0,r0,c7,c0,4
   MOV_PC_LR

@======================================
@ void MMU_InvalidateTLB(void)
@======================================
   .GLOBAL MMU_InvalidateTLB
MMU_InvalidateTLB:	
   mcr p15,0,r0,c8,c7,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateITLB(void)
@======================================
   .GLOBAL MMU_InvalidateITLB
MMU_InvalidateITLB:	
   mcr p15,0,r0,c8,c5,0
   MOV_PC_LR

@======================================
@ void MMU_InvalidateITLBMVA(U32 mva)
@======================================
   .GLOBAL MMU_InvalidateITLBMVA
MMU_InvalidateITLBMVA:
   @ro=mva
   mcr p15,0,r0,c8,c5,1
   MOV_PC_LR

@======================================
@ void MMU_InvalidateDTLB(void)
@======================================
	.GLOBAL MMU_InvalidateDTLB
MMU_InvalidateDTLB:
	mcr p15,0,r0,c8,c6,0
	MOV_PC_LR

@======================================
@ void MMU_InvalidateDTLBMVA(U32 mva)
@======================================
	.GLOBAL MMU_InvalidateDTLBMVA 
MMU_InvalidateDTLBMVA:
	@r0=mva
	mcr p15,0,r0,c8,c6,1
	MOV_PC_LR

@======================================
@ void MMU_SetDCacheLockdownBase(U32 base)
@======================================
   .GLOBAL MMU_SetDCacheLockdownBase 
MMU_SetDCacheLockdownBase:
   @r0= victim & lockdown base
   mcr p15,0,r0,c9,c0,0
   MOV_PC_LR
	
@======================================
@ void MMU_SetICacheLockdownBase(U32 base)
@======================================
   .GLOBAL MMU_SetICacheLockdownBase
MMU_SetICacheLockdownBase:
   @r0= victim & lockdown base
   mcr p15,0,r0,c9,c0,1
   MOV_PC_LR

@======================================
@ void MMU_SetDTLBLockdown(U32 baseVictim)
@======================================
   .GLOBAL MMU_SetDTLBLockdown
MMU_SetDTLBLockdown:
   @r0= baseVictim
   mcr p15,0,r0,c10,c0,0
   MOV_PC_LR
	
@======================================
@ void MMU_SetITLBLockdown(U32 baseVictim)
@======================================
   .GLOBAL MMU_SetITLBLockdown
MMU_SetITLBLockdown:
   @r0= baseVictim
   mcr p15,0,r0,c10,c0,1
   MOV_PC_LR

@======================================
@ void MMU_SetProcessId(U32 pid)
@======================================
   .GLOBAL MMU_SetProcessId
MMU_SetProcessId:	
   @r0= pid
   mcr p15,0,r0,c13,c0,0
   MOV_PC_LR
	
   .END
   
