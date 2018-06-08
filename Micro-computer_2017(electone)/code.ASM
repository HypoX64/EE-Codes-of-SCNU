;=======================================================
; 文件名: Hypo.asm
; 功能描述: 按键0-6为音符键，按下后会有对应的音调响起,
;           按键弹起后音符终止。
;           按键12，13，14可以选择低音，中音，高音区。
;           按下按键15后开始播放之前按下的音符（不超过16个）
;           数码管0显示音符，数码管2显示音区
;=======================================================

IOY3			EQU 06C0H

MY8254_COUNT0	EQU IOY3+00H   ;8254计数器0端口地址
MY8254_COUNT1	EQU IOY3+02H   ;8254计数器1端口地址
MY8254_COUNT2	EQU IOY3+04H   ;8254计数器2端口地址
MY8254_MODE		EQU IOY3+06H   ;8254控制寄存器端口地址
MY8255_A    EQU  0600H         ;8255A端口地址
MY8255_B    EQU  0602H		   ;8255B端口地址
MY8255_C    EQU  0604H         ;8255C端口地址
MY8255_CON	EQU  0606H         ;8255控制端口地址

SSTACK	SEGMENT STACK          ;定义堆栈段
		DW 256 DUP(?)
SSTACK	ENDS		

DATA  	SEGMENT
DTABLE	DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H;数码管的段选数据
		DB 7FH,6FH,77H,7CH,39H,5EH,79H,71H
		
FREQ_LIST1  DW  248,278,312,330,371,416,467       ;低音频率表
FREQ_LIST2  DW  495,556,624,661,742,833,935   	  ;中音频率表
FREQ_LIST3  DW  990,1112,1248,1322,1484,1665,1869 ;高音频率表
REC_DATA   DW 000,000,000,000,000,000,000,000     ;录音储存段
		   DW 000,000,000,000,000,000,000,000
SB         DB 00H,00H                             ;过渡段
REC_TIME   DB 00H,00H,00H,00H,00H,00H,00H,00H     ;时间储存段
		   DB 00H,00H,00H,00H,00H,00H,00H,00H
SAVE_SI    DW ?   ;录音储存地址储存
SI_FREQ    DW ?   ;频率表地址储存
SAVE_SI_TIME DW ? ;时间储存表地址储存
SAVE_TIME DB 01H  ;时间技术储存
CHOOSE_FLAG DW 01H;频率表选择标志位

DATA  	ENDS

CODE 	SEGMENT
      	ASSUME CS:CODE,DS:DATA  ;初始化数据段、代码段
START:  MOV AX,DATA
		MOV DS,AX
		
		MOV DX,MY8254_MODE          ;初始化8254工作方式
		MOV AL,36H                  ;定时器0、方式3
		OUT DX,AL
		
		MOV SI,OFFSET REC_DATA     ;装入录音表初始地址
		MOV SAVE_SI,SI
		MOV CL,0EH
CLEAN_REC:                         ;录音表清零
		MOV AX,0000H
		MOV [SI],AX
		ADD SI,2
		LOOP CLEAN_REC
		
		
		MOV SI,OFFSET REC_TIME     ;装入时间表起始地址
		MOV SAVE_SI_TIME,SI
		
		MOV SI,OFFSET FREQ_LIST1     ;装入频率表默认起始地址
		MOV SI_FREQ,SI	
		
 		MOV SI,3000H
		MOV AL,00H
		MOV [SI],AL				;清显示缓冲
		MOV [SI+1],AL
		MOV [SI+2],AL
		MOV [SI+3],AL
		MOV [SI+4],AL
		MOV [SI+5],AL
		MOV DI,3005H
        MOV DX,MY8255_CON		;写8255控制字
        MOV AL,81H
		OUT DX,AL
BEGIN:  CALL DIS				;调用显示子程序
		CALL DIS_FREQ           ;调用音区显示子程序
		CALL CLEAR				;清屏
		CALL CCSCAN				;键盘扫描
		JNZ INK1
		JMP BEGIN
INK1:   CALL DIS
        CALL DALLY
        CALL DALLY
        CALL CLEAR
		CALL CCSCAN
		JNZ INK2				;有键按下，转到INK2
		JMP BEGIN
;===============蜂鸣器关闭子程序==================
SILENT:
		MOV DX,MY8254_MODE          ;初始化8254工作方式
		MOV AL,36H                  ;定时器0、方式3
		OUT DX,AL
		RET
		
;===============远程跳转过渡=================	
PLAY2_JUMP:     JMP PLAY2
CHOOSE_JUMP1:   JMP CHOOSE1

CHOOSE_JUMP2:   JMP CHOOSE2

CHOOSE_JUMP3:   JMP CHOOSE3

;========================================
;确定按下键的位置
;========================================
INK2:   MOV CH,0FEH
		MOV CL,00H

COLUM:  MOV AL,CH
        MOV DX,MY8255_A 
		OUT DX,AL
        MOV DX,MY8255_C 
		IN AL,DX

L1:     TEST AL,01H         ;is L1?
        JNZ L2              ;如果不是的话跳转到L2

        MOV AL,00H          ;L1
		JMP KCODE

L2:     TEST AL,02H         ;is L2?
        JNZ L3

        MOV AL,04H          ;L2
        JMP KCODE

L3:     TEST AL,04H         ;is L3?
        JNZ L4

        MOV AL,08H          ;L3
		JMP KCODE

L4:     TEST AL,08H         ;is L4?
        JNZ NEXT

        MOV AL,0CH          ;L4
		
;=================================
;确认按键的值
;=================================
KCODE:  ADD AL,CL
		CALL PUTBUF
		PUSH AX
		;=========================
		;键值存在AX中
        ;========================
        CMP AX,12      ;选择音区1
        JZ CHOOSE_JUMP1
        
        CMP AX,13      ;选择音区2
        JZ CHOOSE_JUMP2
        
        CMP AX,14      ;选择音区3
        JZ CHOOSE_JUMP3
        
        CMP AX,15      ;播放录制的音乐
        JZ PLAY2_JUMP  ;jump to play2
        
        POP AX
		PUSH AX
		
		CALL PLAY  ; 播放音符
		
		POP AX
		PUSH AX
        
;=====================
;松手检测
;=====================		
KON:    CALL DIS  
        CALL DIS_FREQ
		CALL CLEAR
		CALL CNT_TIME ;按键没有弹起，执行时间计数
		POP AX
		PUSH AX
		CALL CCSCAN
		JNZ KON   ;判断是否弹起，如果没有弹起，继续检测。
		
		;按键弹起后：
		CALL SILENT ;蜂鸣器静音
		
		MOV SI,SAVE_SI_TIME  
		MOV AL,SAVE_TIME
		MOV [SI],AX  ;按下的时间进入时间表
		INC SAVE_SI_TIME;时间表地址+1
		MOV SAVE_TIME,00H;时间计数清零
			
		INC SAVE_SI ;录音表地址+1
		INC SAVE_SI
		
		POP AX

NEXT:   INC CL
		MOV AL,CH
		TEST AL,08H
		JZ KERR
		ROL AL,1
		MOV CH,AL
		JMP COLUM
KERR:   JMP BEGIN

CNT_TIME:              ;时间计数
		CALL DALLY3
		INC SAVE_TIME
		RET
		
;========================================
;键盘扫描子程序，有按键按下，返回1
;========================================
CCSCAN: MOV AL,00H
        MOV DX,MY8255_A  
		OUT DX,AL
        MOV DX,MY8255_C 
        IN  AL,DX
		NOT AL
        AND AL,0FH
		RET
;========================================
;清屏子程序
;========================================
CLEAR:  MOV DX,MY8255_B 
        MOV AL,00H
        OUT DX,AL
		RET
;========================================
;显示子程序
;========================================
DIS:    PUSH AX
		MOV SI,3000H;数码管地址
		MOV DL,0FEH ;数码管位选
		MOV AL,DL
AGAIN:  PUSH DX
        MOV DX,MY8255_A 
        OUT DX,AL   ;数码管位选输出
        MOV AL,[SI]
        MOV BX,OFFSET DTABLE
		AND AX,00FFH
		ADD BX,AX   ;得到数码管段选数据
		MOV AL,[BX]
        MOV DX,MY8255_B 
		OUT DX,AL   ;数码管段选输出
		CALL DALLY
        POP DX
        MOV AL,DL
		MOV DL,AL
		JMP OUT1
OUT1:   POP AX
		RET
		
;====== 延时子程序 ======		
DALLY:  PUSH CX
        MOV CX,0006H
T1:     MOV AX,009FH
T2:     DEC AX
		JNZ T2
		LOOP T1
		POP CX
		RET
;========================================
;存键盘值到相应位的缓冲中
;========================================
PUTBUF: 
		MOV [SI],AL
		CMP DI,3005H
		JNZ GOBACK
GOBACK: RET


CHOOSE1:
		MOV SI,OFFSET FREQ_LIST1     ;装入频率表1起始地址
		MOV SI_FREQ,SI
		MOV CHOOSE_FLAG,01H		
		JMP BEGIN
CHOOSE2:
		MOV SI,OFFSET FREQ_LIST2     ;装入频率表2起始地址
		MOV SI_FREQ,SI
		MOV CHOOSE_FLAG,02H			
		JMP BEGIN
CHOOSE3:
		MOV SI,OFFSET FREQ_LIST3     ;装入频率表3起始地址
		MOV SI_FREQ,SI
		MOV CHOOSE_FLAG,03H			
		JMP BEGIN
		
;==========================
;音区数码管显示
;==========================
DIS_FREQ:
	    PUSH AX
		MOV SI,3003H
		MOV DL,0FBH
		MOV AL,DL
AGAIN1:  PUSH DX
        MOV DX,MY8255_A 
        OUT DX,AL
        MOV AL,[SI]
        MOV BX,OFFSET DTABLE
		AND AX,00FFH
		ADD BX,CHOOSE_FLAG
		MOV AL,[BX]
        MOV DX,MY8255_B 
		OUT DX,AL
		CALL DALLY
        POP DX
        MOV AL,DL
		MOV DL,AL
		JMP OUT2
OUT2:   POP AX
		RET
	
PLAY:   
		MOV SI,SI_FREQ              ;装入频率表起始地址
		ADD SI,AX
		ADD SI,AX
		MOV DX,0FH                  ;输入时钟为1MHz，1M = 0F4240H  
		MOV AX,4240H                
		DIV WORD PTR [SI] ;取出频率值计算计数初值，0F4240H / 输出频率  
		
		MOV SI,SAVE_SI    ;将计数初值存入录音音符段
		MOV [SI],AX
		
		
		MOV DX,MY8254_COUNT0     ;蜂鸣器播放音符
		OUT DX,AL                   
		MOV AL,AH
		OUT DX,AL
			
		RET
		
PLAY2:  
		MOV SI,OFFSET REC_DATA    ;装入录音表计数初值起始地址
		MOV DI,OFFSET REC_TIME     ;装入录音时间表起始地址
PLAY2_1:
        MOV AX,[SI]
		MOV DX,MY8254_COUNT0
		OUT DX,AL                   ;装入计数初值并播放
		MOV AL,AH
		OUT DX,AL
		
		MOV DL,[DI]                 ;取出演奏相对时间，调用延时子程序 
		CALL DALLY2
		
		ADD SI,2
		INC DI
		CALL SILENT					;停止播放0.1秒
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		CALL DALLY3
		
		CMP WORD PTR [SI],0         ;判断是否到曲末？
		JE  XXX                     ;如果来到曲末跳转到开始
		JMP PLAY2_1					;否则继续播放下一个音符
		
XXX:    JMP START ;远程跳转过渡

DALLY2	PROC                        ;延时子程序2
D0:		MOV CX,0015H
D1:		MOV AX,00F0H
D2:		DEC AX
		JNZ D2 
		LOOP D1
		DEC DL
		JNZ D0
		RET
DALLY2	ENDP

DALLY3	PROC                        ;延时子程序3
D00:	MOV CX,0010H
D11:	MOV AX,00F0H
D22:	DEC AX
		JNZ D22
		LOOP D11
		RET
DALLY3	ENDP

CODE	ENDS
		END START
