#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    char filename[100] = {0};
    printf("input file name");
    scanf("%s", filename);
    //gets(filename);
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("error");
        exit(0);
    }
    //创建套接字

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));                 //每个字节都用0填充
    serv_addr.sin_family = AF_INET;                           //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("192.168.123.140"); //具体的IP地址
    serv_addr.sin_port = htons(1234);                         //端口

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //连接

    char buffer[1024] = {0};
    int nCount;
    while ((nCount = read(sock, buffer, 1024)) > 0) //不断数据
    {
        fwrite(buffer, nCount, 1, fp); //不断写入到fp里
    }
    puts("file transfer success");

    fclose(fp);
    close(sock);

    return 0;
}
