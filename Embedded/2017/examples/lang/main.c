/*
 * C语言演示程序
 */
extern int asse_add(int x, int y);
int embed_add(int x, int y);
void Main()
{
	int x, y;
	/*调用汇编函数asse_add*/
	x = asse_add(10, 20);
	y = embed_add(10, 20);
}

int embed_add(int x, int y)
{
	__asm__("add r0, r0, r1");
}
