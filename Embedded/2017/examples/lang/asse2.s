/*
 * ������Ա�дʵ��
 * �ó�����ʾC���Ժͻ�����Ե��໥���÷���
 */
.global _start
.global asse_add

.text
.EQU    num, 20

/*
 * ������ڵ�ַ�����ݲ��������ö�ջ
 */
_start:
        MOV     sp, #0x33000000       /*����ջָ��(r13)*/
		B       Main                  /*��ת��C���Գ���*/

/*
 * int asse_add(int x, int y);
 */
asse_add:
		ADD     r0, r0, r1            /*r0 = r0 + r1*/
		MOV     pc, lr                /*��������*/
.end

