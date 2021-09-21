/**
 * unp 测试程序1： UNP 1.2节； 一个简单的时间获取客户程序
 * 本例是 TCP 当前时间查询客户程序的一个实现。该客户与其服务器建立一个 TCP 连接后，服务器以
 * 直观可读格式简单地送回当前时间和日期。
*/

#include    "unp.h"  
  
int  
main(int argc, char **argv)  
{  
    int                 sockfd, n;  
    char                recvline[MAXLINE + 1];  
    struct sockaddr_in  servaddr;  
  
    if (argc != 2)  
        err_quit("usage: a.out <IPaddress>");  
  
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
        err_sys("socket error");  
  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port   = htons(13);    /* daytime server */  
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)  
        err_quit("inet_pton error for %s", argv[1]);  
  
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)  
        err_sys("connect error");  
  
    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {  
        recvline[n] = 0;    /* null terminate */  
        if (fputs(recvline, stdout) == EOF)  
            err_sys("fputs error");  
    }  
    if (n < 0)  
        err_sys("read error");  
  
    exit(0);  
}

/**
 * 代码解读
 * 包含自己编写的名为 unp.h 的头文件，该头文件包含大部分网络程序都需要的许多系统头文件，并定义了各种
 * 常值。
 * 
 * socket 函数创建一个网际(AF_INET)字节流(SOCK_STREAM)套接字，它是TCP套接字的花哨名字。该函数返回一个
 * 小整数描述符，以后的所有函数调用（如随后的 connect 和 read） 就用该描述符来标识这个套接字。
*/