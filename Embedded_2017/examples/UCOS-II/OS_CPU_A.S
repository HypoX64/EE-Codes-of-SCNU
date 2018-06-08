@/*************************************************************************/
@/*                                                                       */
@/*     FILE                                        VERSION               */
@/*                                                                       */
@/*      os_cpu_a.s                              S3C2410X 1.00            */
@/*                                                                       */
@/* Project name: EB44B0(S3C44B0X) Main board                             */
@/* Description : Functions defined in this module                        */
@/*                                                                       */
@/*	                                                                      */
@/*	    void ARMDisableInt(void)	---    disable interrupts when in SVC */
@/*	    void ARMEnableInt(void)		---    enable interrupts when in SVC  */
@/*	    void OS_TASK_SWAP(void)		---    context switch                 */
@/*	    void OSStartHighRdy(void)	---    start highest priority task    */
@/*                                                                       */
@/* AUTHOR                                                                */
@/*                                                                       */
@/*      cooljet                                                          */
@/* DATE:                                                                 */
@/*      2003-06-07                                                       */
@/*                                                                       */
@/* HISTORY                                                               */
@/*                                                                       */
@/*         NAME            DATE                    REMARKS               */
@/*         cooljet    2003-06-06 13:10        Modify for PBI-2           */
@/*************************************************************************/

.EQU SwiV		,	0x08
.EQU IrqV		,	0x18
.EQU FiqV		,	0x1C
.EQU NoInt		,	0xc0

.EQU SVC32Mode	,	0x13
.EQU IRQ32Mode	,	0x12
.EQU FIQ32Mode	,	0x11

.EQU OSEnterSWI	,	0x00


@
@ These defines are use in the INT_IRQ processing for UART,
@ and Timer0 Interrupts
@
.EQU IRQ_TIMER1      , 12

@/*************************************************************************/
@/* External symbols we need the addresses of                             */
@/*************************************************************************/
	.EXTERN	OSTCBCur
addr_OSTCBCur :
	.LONG	OSTCBCur
	.EXTERN	OSTCBHighRdy
addr_OSTCBHighRdy :
	.LONG	OSTCBHighRdy
	.EXTERN	OSPrioCur
addr_OSPrioCur :
	.LONG	OSPrioCur
	.EXTERN	OSPrioHighRdy
addr_OSPrioHighRdy :
	.LONG	OSPrioHighRdy
   
	.EXTERN	need_to_swap_context
	.EXTERN	IrqStart
	.EXTERN	OSTimeTick
	.EXTERN	IrqFinish
	.EXTERN  irq_entry

	.EXTERN	OutDebug
	.EXTERN	BreakPoint
	
@/*************************************************************************/
@/*                                                                       */
@/* FUNCTION                                                              */
@/*                                                                       */
@/*      TickHandler                                                      */
@/*                                                                       */
@/* DESCRIPTION                                                           */
@/*                                                                       */
@/*      This function will be called when every tick is expired          */
@/*                                                                       */
@/*             -    	Call	IrqStart                                  */
@/*             -       Call	OSTimeTick                           	  */
@/*             -       Call 	IrqFinish                                 */
@/*             -       Context switching when necessaryly                */
@/*                                                                       */
@/* AUTHOR                                                                */
@/*                                                                       */
@/*      @                                                     */
@/* DATE:                                                                 */
@/*      2003-06-05                                                       */
@/* CALLED BY                                                             */
@/*                                                                       */
@/*                                                                       */
@/* CALLS                                                                 */
@/*                                                                       */
@/*      none                                                             */
@/*                                                                       */
@/* INPUTS                                                                */
@/*                                                                       */
@/*      None                                                             */
@/*                                                                       */
@/* OUTPUTS                                                               */
@/*                                                                       */
@/*      None                                                             */
@/*                                                                       */
@/* HISTORY                                                               */
@/*                                                                       */
@/*         NAME            DATE                    REMARKS               */
@/*                                                                       */
@/*                                                                       */
@/*************************************************************************/
@VOID    TickHandler(void)
@{
	.GLOBAL	OSTickISR
OSTickISR :
/*
        stmfd sp!,{r0-r3,r12,lr}

		mov r0, #IRQ_TIMER1
		BL Irq_Clear

        bl OSIntEnter
        bl OSTimeTick
        bl OSIntExit

        ldr r0,=need_to_swap_context
        ldr r1,[r0]
        cmp r1,#1
        beq _IntCtxSw

        ldmfd sp!,{r0-r3,r12,lr}
        subs pc,lr,#4


_IntCtxSw:
        mov r1,#0
        str r1,[r0]

        ldmfd sp!,{r0-r3,r12,lr}
        stmfd sp!,{r0-r3}
        mov r1,sp
        add sp,sp,#16
        sub r2,lr,#4

        mrs r3,spsr
        orr r0,r3,#NOINT
        msr spsr_c,r0

        ldr r0,=.+8
        movs pc,r0

        stmfd sp!,{r2}              @ push old task's pc
        stmfd sp!,{r4-r12,lr}       @ push old task's lr,r12-r4
        mov r4,r1                   @ Special optimised code below
        mov r5,r3
        ldmfd r4!,{r0-r3}
        stmfd sp!,{r0-r3}           @ push old task's r3-r0
        stmfd sp!,{r5}              @ push old task's psr
        mrs r4,spsr
        stmfd sp!,{r4}              @ push old task's spsr
        
        @ OSPrioCur = OSPrioHighRdy
        ldr r4,=OSPrioCur
        ldr r5,=OSPrioHighRdy
        ldrb r5,[r5]
        strb r5,[r4]
        
        @ Get current task TCB address
        ldr r4,=OSTCBCur
        ldr r5,[r4]
        str sp,[r5]                 @ store sp in preempted tasks's TCB

        bl OSTaskSwHook             @ call Task Switch Hook

        @ Get highest priority task TCB address
        ldr r6,=OSTCBHighRdy
        ldr r6,[r6]
        ldr sp,[r6]                 @ get new task's stack pointer

        @ OSTCBCur = OSTCBHighRdy
        str r6,[r4]                 @ set new current task TCB address

        ldmfd sp!,{r4}              @ pop new task's spsr
        msr SPSR_cxsf,r4
        ldmfd sp!,{r4}              @ pop new task's psr
        msr CPSR_cxsf,r4

        ldmfd sp!,{r0-r12,lr,pc}    @ pop new task's r0-r12,lr & pc
*/
    STMFD    sp!,{r0-r12,lr}

	@End of interrupt
	@(Clear pending bit of INTPEND that don't accessed it.)
	@	rI_ISPC= BIT_TIMER0;
	mov r0, #IRQ_TIMER1
	BL Irq_Clear

	BL	IrqStart
	
	BL	OSTimeTick

	BL	IrqFinish

	
	LDR		r0, =need_to_swap_context
	LDR		r2, [r0]
	CMP		r2, #1
	LDREQ	pc, =_CON_SW


_NOT_CON_SW :
	@not context switching
	LDMFD    sp!,{r0-r12, lr}
	SUBS	pc, lr, #4


_CON_SW:
	@set need_to_swap_context is '0'
	MOV		r1, #0
	STR		r1, [r0]


	@now context switching
	LDMFD    sp!,{r0-r12,lr}
	SUB		lr, lr, #4

	STR				lr, SAVED_LR

	@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	@Change Supervisor mode
	@!!!r12 register don't preserved. (r12 that PC of task)

    MRS             lr, SPSR
	AND				lr, lr, #0xFFFFFFE0
	ORR				lr, lr, #0x13
    MSR             CPSR_cxsf, lr


	@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	@Now  Supervisor mode
	@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	STR		r12, [sp, #-8]	@ saved r12
	LDR		r12, SAVED_LR
	STMFD	sp!, {r12}		@ r12 that PC of task
	SUB		sp, sp, #4		@ inclease stack point
	LDMFD	sp!, {r12}		@ restore r12
	STMFD	sp!, {lr}		@ save lr
	STMFD	sp!, {r0-r12}	@ save register file and ret address
	MRS		r4, CPSR
	STMFD	sp!, {r4}		@ save current PSR
	MRS		r4, SPSR		@ YYY+
	STMFD	sp!, {r4}		@ YYY+ save SPSR

	@ OSPrioCur = OSPrioHighRdy
	LDR	r4, addr_OSPrioCur
	LDR	r5, addr_OSPrioHighRdy
	LDRB	r6, [r5]
	STRB	r6, [r4]
	
	@ Get current task TCB address
	LDR	r4, addr_OSTCBCur
	LDR	r5, [r4]
	STR	sp, [r5]		@ store sp in preempted tasks's TCB

	@ Get highest priority task TCB address
	LDR	r6, addr_OSTCBHighRdy
	LDR	r6, [r6]
	LDR	sp, [r6]		@ get new task's stack pointer

	@ OSTCBCur = OSTCBHighRdy
	STR	r6, [r4]		@ set new current task TCB address

	LDMFD	sp!, {r4}		@ YYY+
	MSR	SPSR_cxsf, r4		@ YYY+
	LDMFD	sp!, {r4}		@ YYY+
	MSR	CPSR_cxsf, r4		@ YYY+
	LDMFD	sp!, {r0-r12, lr, pc}	@ YYY+

SAVED_LR:
	.LONG  0

@	void OS_TASK_SW(void)
@	
@	Perform a context switch.
@
@	On entry, OSTCBCur and OSPrioCur hold the current TCB and priority
@	and OSTCBHighRdy and OSPrioHighRdy contain the same for the task
@	to be switched to.
@
@	The following code assumes that the virtual memory is directly
@	mapped into  physical memory. If this is not true, the cache must 
@	be flushed at context switch to avoid address aliasing.
	.GLOBAL	OS_TASK_SW
OS_TASK_SW:
	STMFD	sp!, {lr}		@ save pc
	STMFD	sp!, {lr}		@ save lr
	STMFD	sp!, {r0-r12}	@ save register file and ret address
	MRS	r4, CPSR
	STMFD	sp!, {r4}		@ save current PSR
	MRS	r4, SPSR		@ YYY+
	STMFD	sp!, {r4}		@ YYY+ save SPSR

	@ OSPrioCur = OSPrioHighRdy
	LDR	r4, addr_OSPrioCur
	LDR	r5, addr_OSPrioHighRdy
	LDRB	r6, [r5]
	STRB	r6, [r4]
	
	@ Get current task TCB address
	LDR	r4, addr_OSTCBCur
	LDR	r5, [r4]
	STR	sp, [r5]		@ store sp in preempted tasks's TCB

	@ Get highest priority task TCB address
	LDR	r6, addr_OSTCBHighRdy
	LDR	r6, [r6]
	LDR	sp, [r6]		@ get new task's stack pointer

	@ OSTCBCur = OSTCBHighRdy
	STR	r6, [r4]		@ set new current task TCB address

	LDMFD	sp!, {r4}		@ YYY+
	MSR	SPSR_cxsf, r4		@ YYY+
	LDMFD	sp!, {r4}		@ YYY+
	MSR	CPSR_cxsf, r4		@ YYY+
	LDMFD	sp!, {r0-r12, lr, pc}	@ YYY+

@	void OSStartHighRdy(void)
@	
@	Start the task with the highest priority@
@
	.GLOBAL	OSStartHighRdy
OSStartHighRdy:
	LDR	r4, addr_OSTCBCur	@ Get current task TCB address
	LDR	r5, addr_OSTCBHighRdy	@ Get highest priority task TCB address

	LDR	r5, [r5]		@ get stack pointer
	LDR	sp, [r5]		@ switch to the new stack

	STR	r5, [r4]		@ set new current task TCB address

	LDMFD	sp!, {r4}		@ YYY
	MSR	SPSR_cxsf, r4
	LDMFD	sp!, {r4}		@ get new state from top of the stack
	MSR	CPSR_cxsf, r4		@ CPSR should be SVC32Mode
	LDMFD	sp!, {r0-r12, lr, pc }	@ start the new task

	.END
