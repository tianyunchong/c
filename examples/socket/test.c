#include <stdio.h>
#include <string.h>
#include "get.c"
int main() {
	char html[BUFSIZ * 1000];
	char myurl[] = "http://www.baidu.com";
	getHtml(myurl, html);
	printf("%s\n", html);
	return 0;
}