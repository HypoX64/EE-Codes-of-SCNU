/*
 * 汇编语言编写实验
 * 该程序演示C语言和汇编语言的相互调用方法
 */
.global _start
.global asse_add

.text
.EQU    num, 20

/*
 * 程序入口地址，传递参数并设置堆栈
 */
_start:
        MOV     sp, #0x0c700000       /*建立栈指针(r13)*/
		B       Main                  /*跳转到C语言程序*/

/*
 * int asse_add(int x, int y);
 */
asse_add:
		ADD     r0, r0, r1            /*r0 = r0 + r1*/
		MOV     pc, lr                /*函数返回*/
.end

