
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

#define MAXLINE 2048
#define	LISTENQ		1024

using namespace std;
int main(int argc, char **argv)
{
    int listenfd, connfd = -1;
    struct sockaddr_in servaddr;
    u_short port = 4000;
    char buff[MAXLINE];
    time_t ticks;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        cout << "on socket() error occur. " << endl;
        return -1;
    }
    memset(&servaddr, 0, sizeof(sockaddr_in));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port); // daytim eserver
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {
        cout << "on bind() error occur. " << endl;
        return -1;
    }

    if(listen(listenfd, LISTENQ) == -1)
    {
        cout << "on listen() error occur. " << endl;
        return -1;
    }

    cout << "server started..." << endl;
    for( ; ; )
    {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
        cout << "write one: " << buff << endl; 
    }
}