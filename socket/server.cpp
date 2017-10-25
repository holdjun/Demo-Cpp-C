#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    FILE *fp = fopen("./example.cpp", "rb");
    if (fp == NULL)
    {
        printf("error");
        exit(0);
    }
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); //每个字节都用0填充
    serv_addr.sin_family = AF_INET;           //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY;   //具体的IP地址 = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(1234);         //端口
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buffer[1024] = {0};

    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    int nCount;
    while ((nCount = fread(buffer, 1, 1024, fp)) > 0) //不断写入文件
    {
        write(clnt_sock, buffer, 1024);
    }

    shutdown(clnt_sock, SHUT_WR);
    fclose(fp);

    close(clnt_sock);
    close(serv_sock);

    return 0;
}
