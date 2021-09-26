/**
 * 可用的文件 I/O 函数包括 -- 打开文件、读文件、写文件等等。
 * 大多数 UNIX 文件 I/O 只需要用到 5 个函数： open / read / write / lseek / close
 * 这里所说明的函数都是不带缓存的 I/O(unbuffered I/O)。
 * 
 * 问题1： 什么事文件描述符？
 *  对于内核而言，所有打开文件都由文件描述符引用。文件描述符是一个非负整数。当打开一个现存文件
 * 或创建一个新文件时，内核向进程返回一个文件描述符。当然、读写一个文件时，用 open 或 create 
 * 返回的文件描述符标识该文件，将其作为参数传送给 read 或 write。
 *  按照惯例，UNIX shell 使文件描述符 0 与进程的标准输入相结合，文件描述符 1 与标准输出相结合，
 * 文件描述符 2 与标准出错输出相结合。这是 UNIX shell以及很多应用程序使用的惯例，而与内核无关。
 *  文件描述符的范围是 0 ~ OPEN_MAX。早期上限为 19，现在基本都将其增加到 63。
*/

/**
 * #include <fcntl.h>
 * int open(const char *path, int oflag, ... /. mode_t mode ./);
 * int openat(int fd, const char *path, int oflag, ... /. mode_t mode ./);
 * 
 * @brief 调用 open 或 openat 函数可以打开或创建一个文件      
 *      最后一个参数写为 ... ISO C用这种方法表明余下的参数的数量及其类型是可变的。对于 open 函数
 *      而言，仅当创建新文件时才使用最后这个参数（稍后将对此进行说明）。在函数原型中将此参数放置在注释
 *      中。
 * @param path 要打开或创建文件的名字
 * 
 * @param oflag 用来 说明此函数的多个选项，用下列一个或多个常亮进行 “或” 运算构成 oflag 参数
 *              （这些常量在头文件 <fcntl.h> 中定义）。
 *              O_RDONLY        只读打开
 *              O_WRONLY        只写打开
 *              O_WDWR          读、写打开
 *              O_EXEC          只执行打开
 *              O_SEARCH        只搜索打开（应用于目录）
 *              O_APPEND        每次写时都追加到文件的尾端。
 *              O_CLOEXEC       把 FD_CLOEXEC 常量设置为文件描述符标识。
 * 
 * @return 若成功，返回文件描述符，若出错，返回 -1。
*/