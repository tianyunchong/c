#include <stdio.h>
#include <string.h>
int main() {
	char *pHost = 0;
	char myurl[] = "http://www.baidu.com";
	char host[BUFSIZ];
	int i;
	for (i = 0, pHost = myurl; *pHost != '/' && *pHost != '\0'; pHost++, i++) {
		host[i] = *pHost;
	}
	printf("%s\n", host);
}