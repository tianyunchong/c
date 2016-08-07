/**
 * 使用get的方式请求网址
 *
 */
#include <stdio.h>
#include <sys/socket.h>
int main() {
	char * host;
	int sock;
	host = "http://www.baidu.com";
	/** 建立socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	printf("%d\n", sock);
	return 1;
}