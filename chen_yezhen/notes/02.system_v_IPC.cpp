/**
 * 什么是 IPC？
 * IPC 指的是 inter-process communication，即进程间通信。
*/

/**
 * 什么是 System V IPC？
 *  System V IPC 指的是下面三种类型的通信方法： 
 *      System V 消息队列
 *      System V 信号量
 *      System V 共享内存
 *  这三种 IPC 机制的差别很大，之所以放在一起讨论，是因为这三种机制是一同被 开发出来的。
 * 之所以将他们称之为 System V，是因为 1983 年三者出现在主流的 System V Unix 系统上。
 * 
 * 消息队列 编程接口
 *  头文件：            #include <sys/msg.h>
 *  关联数据结构：      msqid_ds
 *  创建或打开对象：    msgget()
 *  关闭对象：          无
 *  控制操作：          msgctl()
 *  执行 IPC：          msgsnd() / msgrcv()
 * 
 * 信号量 编程接口
 *  头文件：            #include <sys/sem.h>
 *  关联数据结构：      semid_ds
 *  创建或打开对象：    semget()
 *  关闭对象：          无
 *  控制操作：          semctl()
 *  执行 IPC：          semop()
 * 
 * 共享内存 编程接口
 *  头文件：            #include <sys/shm.h>
 *  关联数据结构：      shmid_ds
 *  创建或打开对象：    shmget() + shmat()
 *  关闭对象：          无
 *  控制操作：          shmctl()
 *  执行 IPC：         访问共享内存区的内存数据
 * 
 *  从作用上看，三种通信机制各不相同，但是从涉及和实现的角度来看，还是有很多风格一致的地方。
 *  System V IPC 未遵循 “一切都是文件”的 Unix 哲学，而是采用标识符ID和键值来标识一个 System V IPC
 *  对象。每种 System V IPC 都有一个相关的 get 调用，该函数返回一个整型标识符ID，System V IPC 后续的函数
 *  操作都要作用在该标识符 ID 上。
 * 
 *  System V IPC 对象的作用范围是整个操作系统，内核没有维护引用技术。调用各种 get 函数返回的 ID 是
 *  操作系统范围内的标识符，对于任何进程，无论是否存在亲缘关系，只要有相应的权限，都可以通过操作 System V IPC
 *  对象来达到通信的目的。
 * 
 *  System V IPC 对象具有内核持久性。哪怕创建 System V IPC 对象的进程已经退出，哪怕有一段时间没有任何进程打开
 *  该 IPC 对象，只要不执行删除操作或系统重启，后面启动的进程仍然可以使用之前创建的 System V IPC 对象来通信。
 * 
 *  此外，我们也无法像操作文件一样来操作 System V IPC 对象。 System V IPC 对象在文件系统中没有实体文件
 *  与之关联。我们不能用文件相关的操作来访问它或修改它的属性。所以不得不提供专门的系统调用(如 msgctl、semop等)
 *  来操作这些对象。在 shell 中无法用 ls 查看存在的 IPC 对象，无法用 rm 将其删除，也无法用 chmod 来修改它们的
 *  访问权限
*/