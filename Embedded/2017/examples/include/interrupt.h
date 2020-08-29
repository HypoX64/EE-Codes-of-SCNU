#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define IRQ_MAX   32
#define IRQ_MIN    1

void Isr_Init(void);
void Irq_Request(int irq_no, void* irq_routine);
void Irq_Enable(int irq_no);
void Irq_Disable(int irq_no);

#endif

