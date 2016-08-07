/**
 * 客户端代码请求
 */
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	//创建套接字
	int cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	//向服务端发起请求
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;//使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	serv_addr.sin_port = htons(1234);  //端口
	connect(cli_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	/** 读取服务器返回的数据 */
	char buffer[40];
	read(cli_sock, buffer, sizeof(buffer) - 1);
	printf("%s\n", buffer);
	//关闭套接字
	close(cli_sock);
	return 1;
}