/**
 * 自动登录入口
 * http://blog.csdn.net/yangguo_2011/article/details/14106223
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int create_tcp_socket();
char *get_ip(char *hosts);
char *build_get_query(char *host, char *page);
void usage();
#define HOST "www.baidu.com"
#define PAGE "/"
#define PORT 80
#define USERAGENT "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.114 Safari/537.36"
#define ACCEPTLANGUAGE "zh-CN,zh;q=0.8,en;q=0.6,en-US;q=0.4,en-GB;q=0.2"
#define ACCEPTENCODING "gzip,deflate,sdch"
int main(int argc, char *argv[]) {
	struct sockaddr_in *remote;
	int sock;
	int tmpres;
	char *ip;
	char *get;
	char buf[BUFSIZ + 1];
	char *host;
	char *page;
	if (argc == 1) {
		printf("%s\n", "you should give the first param host, if not , we will use www.baidu.com!");
		host = HOST;
	} else {
		host = argv[1];
	}
	/** 接受传递的参数 */
	page = argc > 2 ? argv[2] : PAGE;
	fprintf(stdout, "page:%s,hostName:%s\n", page, host);
	sock = create_tcp_socket();
	ip = (*get_ip)(host);
	remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in*));
	remote->sin_family = AF_INET;
	tmpres = inet_pton(AF_INET, ip, (void *)(&(remote->sin_addr.s_addr)));
	if (tmpres < 0) {
		perror("Can't set remote->sin_addr.s_addr");
		exit(1);
	} else if (tmpres == 0) {
		fprintf(stderr, "%s is not a valid IP address\n", ip);
		exit(1);
	}
	remote->sin_port = htons(PORT);
	if (connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0) {
		perror("Could not connect!\n");
		exit(1);
	}
	/** get请求 */
	get = build_get_query(host, page);
	fprintf(stdout, "<start>\n%s\n<end>\n", get);
	int sent = 0;
	while (sent < strlen(get)) {
		tmpres = send(sock, get + sent, strlen(get) - sent, 0);
		if (tmpres == -1) {
			perror("Can't send query!");
			exit(1);
		}
		sent += tmpres;
	}
	memset(buf, 0, sizeof(buf));


}

void usage() {
	fprintf(stderr, "USAGE:main host [page]\n\thost:the website hostname. ex:www.baidu.com\n\tpage:the page to retrieve. ex:index.html,default:/\n");
}
/**
 * 创建tcp socket
 * @return [description]
 */
int create_tcp_socket() {
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Can't create TCP socket!\n");
		exit(1);
	}
	return sock;
}

/**
 * 获取下ip地址
 * @param  host [description]
 * @return      [description]
 */
char *get_ip(char *host) {
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

char *build_get_query(char *host, char *page) {
	char *query;
	char *getpage = page;
	char *tpl = "GET %s HTTP/1.1\r\nHost:%s\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nUser-Agent:%s\r\nAccept-Language:%s\r\n\r\n"; //Accept-Encoding:%s\r\n
	query = (char *)malloc(strlen(host) + strlen(getpage) + strlen(USERAGENT) + strlen(tpl) + strlen(ACCEPTLANGUAGE) - 5); //+strlen(ACCEPTENCODING)
	sprintf(query, tpl, getpage, host, USERAGENT, ACCEPTLANGUAGE); //ACCEPTENCODING
	return query;
}