/*
 * 汇编语言编写实验
 * 该程序实现从源地址拷贝num个字数据即num*4个字节的内容到目的地址dst中
 */
.global _start
.text
.EQU    num, 20

/*
 * 程序入口地址，传递参数并设置堆栈
 */
_start:
        LDR     r0, =src         /*r0 = 源数据块地址*/
        LDR     r1, =dst         /*r1 = 目的数据块地址*/
        MOV     r2, #num         /*r2 = 拷贝字数量*/

        MOV     sp, #0x0c700000       /*建立栈指针(r13)*/

/*
 * 块拷贝：以32个字节（8个字）为单位进行拷贝
 * 使用指令：LDMIA, STMIA
 */
blockcopy:       
        MOVS    r3,r2, LSR #3    /*r3 = r2 / 8 = 2(num = 20)*/
        BEQ     copywords        /*少于8个字则跳转到copywords处理*/

        STMFD   sp!, {r4-r11}    /*保存工作寄存器*/
octcopy:
        LDMIA   r0!, {r4-r11}    /*从源地址取出8个字数据分别存放到r4 - r11中*/
        STMIA   r1!, {r4-r11}    /*将r4 - r11中的数据设置到目的数据块地址*/
        SUBS    r3, r3, #1       /*计数器累加*/
        BNE     octcopy          /*重复拷贝*/

        LDMFD   sp!, {r4-r11}    /*回复工作寄存器*/

/*
 * 字拷贝：以4个字节（1个字）为单位进行拷贝
 * 使用指令：LDR, STR
 */
copywords:
        ANDS    r2, r2, #7               /*最多拷贝7个，多余8个先使用blockcopy然后使用copywords拷贝*/
        BEQ     stop                     /*是否拷贝完毕，拷贝完毕则跳转到stop*/
wordcopy:
        LDR     r3, [r0], #4    /*从源地址取出1个字数据存放到r3中*/
        STR     r3, [r1], #4    /*将r3中的数据设置到目的数据地址*/
        SUBS    r2, r2, #1              /*计数器累加*/
        BNE     wordcopy                /*重复拷贝*/

stop:
        B       stop               /*死循环，程序结束*/

/*
 * 文字池：定义源地址数据以及目标地址
 */
.ltorg
src:
     .LONG     1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst:
     .LONG     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

.end


