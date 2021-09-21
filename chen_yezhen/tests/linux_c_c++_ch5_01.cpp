/// 5.2 进程的描述


#include <iostream>

using namespace std;

/**
 *  例1： 测试 pid_t 类型的长度
 */
// int main(int argc, char *argv[])
// {
//     pid_t pid;
//     /// 4
//     cout << sizeof(pid_t) << endl;
//     return 0;
// }

/**
 * 例2： 获取当前进程的 ID
 * ps -ef | grep prog_name 可以在控制台验证输出结果
 * 
 * 在 Linux 系统的 /var/run 目录下，一般会看到很多的 *.pid 文件，而且往往新安装的程序在运行后也会在
 * /var/run 目录下产生自己的 pid 文件。它的主要作用是防止进程启动多个副本。只有获得相应 PID 文件写入
 * 权限的进程才能正常启动，并把自身的 PID 写入该文件中。
 * 
*/
// #include <unistd.h>
// int main(int argc, char *argv[])
// {
//     pid_t pid = getpid();
//     cout << "pid = " << pid << endl;
//     getchar();
//     return 0;
// }



/**
 * 例3： 通过 PID 文件判断进程是否运行
 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static char* starter_pid_file_default = "/var/run/test.pid";

static bool check_pid(char *pid_file)
{
    struct stat stb;
    FILE *pidfile;

    if(stat(pid_file, &stb))
    {
        pidfile = fopen(pid_file, "r");
        if(pidfile)
        {
            char buf[64];
            pid_t pid = 0;
            memset(buf, 0, sizeof(buf));
            if(fread(buf, 1, sizeof(buf), pidfile))
            {
                buf[sizeof(buf) - 1] = '\0';
                pid = atoi(buf);
            }
            fclose(pidfile);
            if(pid && kill(pid, 0) == 0)
            {
                // such a process is running 
                return 1;
            }
        }
        printf("removing pidfile '%s', process not running \n", pid_file);
        unlink(pid_file);
    }
    return 0;
}

int main()
{
    FILE *fd = fopen(starter_pid_file_default, "w");

    if(fd)
    {
        fprintf(fd, "%u\n", getpid());
        fclose(fd);
    }

    if(check_pid(starter_pid_file_default))
    {
        printf("test is already running (%s exists)", starter_pid_file_default);
    }
    else
    {
        printf("teset is NOT runnint (%s NOT exists)", starter_pid_file_default);
    }
    unlink(starter_pid_file_default);
    getchar();
    return 0;
}

