/**
 * unp 测试程序1： UNP 1.2节； 一个简单的时间获取客户程序
 * 本例是 TCP 当前时间查询客户程序的一个实现。该客户与其服务器建立一个 TCP 连接后，服务器以
 * 直观可读格式简单地送回当前时间和日期。
*/


#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
  
#include <iostream>
using namespace std;

#define MAXLINE 2048

int  
main(int argc, char **argv)  
{  
    int                 sockfd, n;  
    char                recvline[MAXLINE + 1];  
    struct sockaddr_in  servaddr;  

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {
        cout << "on socket() error occur. " << endl;
        return -1;   
    } 
  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port   = htons(4000);    /* daytime server */  

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)  
    {
        cout << "on connect() error occur. " << endl;
        return -1;   
    }
  
    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {  
        recvline[n] = 0;    /* null terminate */  
        if (fputs(recvline, stdout) == EOF)  
        {
            cout << "on socket() error occur. " << endl;
            return -1;   
        }
    }  
    if (n < 0)  
    {
        cout << "read error occur. " << endl;
        return -1;   
    }
  
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