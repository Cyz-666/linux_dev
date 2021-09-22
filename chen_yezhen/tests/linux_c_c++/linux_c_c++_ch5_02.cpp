/// 5.3 进程的创建

/**
 * 例1： 使用 fork 创建子进程
 * 
 * #include <unistd.h>
 * pid_t fork();
 * 
 * 输出： 
 * I am the parent process, my pid is 6585
 * fpid = 6586
 * result: 1
 * I am the child process, my pid is 6586
 * result: 1
 * 
 * 解释： 我们可以看到父进程和子进程的 PID 是不同的，说明是两个不同的进程。
 * 在语句 fpid = fork(); 之前，只有一个进程在执行这段代码，但是这条语句之后，
 * 就变成两个进程在执行了。这两个进程几乎完全相同，将要执行的代码都是下一条语句
 * if(pid < 0)。
 * 
 * 为什么两个进程的 pid 不同呢？ 这与fork 函数的特性有关。 fork 调用的一个奇妙
 * 之处在于它仅仅被调用以此，却能够返回两次。父进程 fork 返回的是子进程的 PID 
 * 我们可以看到父进程中的打印 "fpid = 6586" 和子进程中的打印 "I am the child process, my pid is 6586"
 * pid 都是 6586.另外 count 飞奔在父进程和子进程中执行了一次 count++，所以输出都是 count = 1.
 * 
 * 为什么 fork 不是control第一行 #include 处开始复制代码？
 * 这是因为 fork 是把进程当前的情况复制了一份，执行 fork 时，进程已经执行完了语句 int count = 0
 * fork 只复制下一次要执行的代码到新的进程。
 * 
 * 再次强调，在 fork 函数执行完毕后，如果新的进程创建成功，则出现两个进程，一个是子进程，一个是父进程。
 * 在子进程中 fork 函数返回 0，在父进程中，fork 只复制下一次要执行的代码到新的进程。
 *  
 * 
*/

// #include <unistd.h>
// #include <stdio.h>

// #include <iostream>
// using namespace std;

// int main()
// {
//     pid_t fpid;
//     int count = 0;
//     fpid = fork();
//     if(fpid < 0)
//     {
//         cout << "failed to fork." << endl;
//     }
//     else if(fpid == 0)
//     {
//         // 如果 fork 返回 0，则进入子进程
//         cout << "I am the child process, my pid is " << getpid() << endl;
//         count++;
//     }
//     else
//     {
//         // 如果 fork 返回值大于 0，则依旧在父进程中
//         cout << "I am the parent process, my pid is " << getpid() << endl;
//         cout << "fpid = " << fpid << endl;
//         count++;
//     }

//     cout << "result: " << count << endl;
//     getchar();
//     return 0;
// }


/**
 * 例2： 使用 execl 创建进程
 * 
*/
#include <unistd.h>

int main()
{
    execl("/bin/ls", "ls", "-al", "/home/cyz", NULL);
    return 0;
}