/**
 * 文件的读取操作
 */
#include <stdio.h>
int main() {
	FILE *pfile;
	char sbuf[1024];
	pfile = fopen("test.txt", "r");
	fgets(sbuf, 1024, pfile);
	printf("%s", sbuf);
	fclose(pfile);
	return 0;
}