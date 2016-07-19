//
// Created by zyh on 16/7/19.
//

#include <stdio.h>
int main() {
//	int abb = 12;
//	printf("%d", abb);
	//----------------------
	/* 无符号类型输出 */
//	unsigned aaa = 112;
//	printf("this is %u", aaa);
	//------------------------
	/* 浮点数,双精度浮点数 */
//	float a = 1.55f;
//	double b = 1.47;
//	printf("%f\n%lf", a, b);
	//-------------------------
	/* 输出对齐 */
	int a1=20, a2=345, a3=700, a4=22;
	int b1=56720, b2=9999, b3=20098, b4=2;
	int c1=233, c2=205, c3=1, c4=6666;
	int d1=34, d2=0, d3=23, d4=23006783;
	printf("%-9d %-9d %-9d %-9d\n", a1, a2, a3, a4);
	printf("%-9d %-9d %-9d %-9d\n", b1, b2, b3, b4);
	printf("%-9d %-9d %-9d %-9d\n", c1, c2, c3, c4);
	printf("%-9d %-9d %-9d %-9d\n", d1, d2, d3, d4);
	return 0;
}