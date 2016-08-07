/**
 * 使用get的方式请求网址
 *
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    int sock;
    /** 建立socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    /** 套接字ip和端口绑定 */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));//每个字节用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(sock, 20);
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    //接收客户端请求
    int clnt_sock = accept(sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //向客户端发送数据
    char str[] = "hello worold";
    write(clnt_sock, str , sizeof(str));
    //关闭套接字
    close(clnt_sock);
    close(sock);
    return 1;
}