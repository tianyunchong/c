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
#include <errno.h>
char *getIp(char *host);
void GetHost(char * src, char * web, char * file, int * port);
int getHtml(char myurl[], char html[]);


int getHtml(char myurl[], char html[])
{
	char *ip;
	static char text[BUFSIZ];
	int portnumber, nbytes;
	char host_addr[256];
	char host_file[1024];
	char request[1024];
	/** 循环请求的地址 */
	GetHost(myurl, host_addr, host_file, &portnumber);/*分析网址、端口、文件名等*/
	ip = (*getIp)(host_addr);
	/** 创建套接字 */
	int server_sock;
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	/** 绑定ip和端口 */
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;//使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr(ip);  //具体的IP地址
	serv_addr.sin_port = htons(80);  //端口
	connect(server_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	sprintf(request, "GET /%s HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\n\
Host: %s:%d\r\nConnection: Close\r\n\r\n", host_file, host_addr, portnumber);
	/*发送http请求request*/
	int send, totalsend;
	send = 0; totalsend = 0;
	nbytes = strlen(request);
	while (totalsend < nbytes) {
		send = write(server_sock, request + totalsend, nbytes - totalsend);
		if (send == -1)  {
			printf("send error!%s\n", strerror(errno));
			return 0;
		}
		totalsend += send;
	}
	/** 发送get请求 */
	while (recv(server_sock, text, BUFSIZ, 0) > 0) {
		strcat(html, text);
		memset(text, 0, sizeof(text));
	}
	//关闭套接字
	close(server_sock);
	return 1;
}


/**************************************************************
功能：从字符串src中分析出网站地址和端口，并得到用户要下载的文件
***************************************************************/
void GetHost(char * src, char * web, char * file, int * port)  {
	char * pA;
	char * pB;
	memset(web, 0, sizeof(*web));
	memset(file, 0, sizeof(*file));
	*port = 0;
	if (!(*src))   {
		return;
	}
	pA = src;
	if (!strncmp(pA, "http://", strlen("http://"))) {
		pA = src + strlen("http://");
	} else if (!strncmp(pA, "https://", strlen("https://"))) {
		pA = src + strlen("https://");
	}
	pB = strchr(pA, '/');
	if (pB)  {
		memcpy(web, pA, strlen(pA) - strlen(pB));
		if (pB + 1)  {
			memcpy(file, pB + 1, strlen(pB) - 1);
			file[strlen(pB) - 1] = 0;
		}
	}	else  {
		memcpy(web, pA, strlen(pA));
	}
	if (pB) {
		web[strlen(pA) - strlen(pB)] = 0;
	}	else {
		web[strlen(pA)] = 0;
	}
	pA = strchr(web, ':');
	if (pA) {
		*port = atoi(pA + 1);
	}	else {
		*port = 80;
	}
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