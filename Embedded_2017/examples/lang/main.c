/*
 * C������ʾ����
 */
extern int asse_add(int x, int y);
int embed_add(int x, int y);
void Main()
{
	int x, y;
	/*���û�ຯ��asse_add*/
	x = asse_add(10, 20);
	y = embed_add(10, 20);
}

int embed_add(int x, int y)
{
	__asm__("add r0, r0, r1");
}
