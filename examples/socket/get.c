/**s
 * get请求远程内容
 */
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
char *getIp(char *host);
int main()
{
	char *ip;
	char host[] = "www.baidu.com";
	char Header[BUFSIZ];
	static char text[BUFSIZ];
	char * pGet = 0;
	char *pHost;
	char *url;
	FILE * pf;
	/** 循环请求的地址 */
	char myurl[] = "http://www.baidu.com";
	pHost = myurl;
	do {
		pHost++;
	} while (*pHost != '/');
	ip = (*getIp)(host);
	printf("%s\n", ip);
	/** 创建套接字 */
	int server_sock;
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	/** 绑定ip和端口 */
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;//使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr(ip);  //具体的IP地址
	serv_addr.sin_port = htons(80);  //端口
	connect(server_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	/** 声称请求header头 */
	strcat(Header, "GET /\r\n");
	//strcat(Header, GET);
	strcat(Header, "HTTP/1.1\r\n");
	strcat(Header, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
	strcat(Header, "Accept-Language:zh-CN,zh;q=0.8,en;q=0.6\r\n");
	strcat(Header, "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; InfoPath.2)\r\n");
	strcat(Header, "Host: ");
	strcat(Header, host);
	strcat(Header, "/r/nConnection: Keep-Alive\r\n");
	/** 发送get请求 */
	send(server_sock, Header, strlen(Header), 0);
	pf = fopen("1.txt", "w");
	while (recv(server_sock, text, BUFSIZ, 0) > 0) {
		//printf("%s", text);
		fputs(text, pf);
		memset(text, '\0', sizeof(text));
	}
	fclose(pf);
	//关闭套接字
	close(server_sock);
	return 0;
}



/**
* 获取下ip地址
* @param  host [description]
* @return      [description]
*/
char *getIp(char *host) {
	struct hostent *hent;
	int iplen = 16;
	char *ip = (char *)malloc(iplen + 1);
	memset(ip, 0, iplen + 1);
	if ((hent = gethostbyname(host)) == NULL) {
		perror("Can't get ip");
		exit(1);
	}
	if (inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL) {
		perror("Can't resolve host!\n");
		exit(1);
	}
	return ip;
}