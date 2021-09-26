
/**
 * u_short 
 * unsigned short int
*/





/**
 * struct sockaddr_in;
 * 我们把服务器的 IP 地址和端口号填入一个网际套接字地址结构（一个名为 name 的 sockaddr_in 结构变量）。
 * 使用 memset(&name, 0, sizeof(name)); 把整个结构清零。
 * 
 * 
 */



/**
 * socklen_t
 * 
 */


/**
 * pthread_t
 * 
 */

/**
 * int socket(int domain, int type, int protocol);
 * 
 * @brief       socket 翻译为中文是 插座、插槽的意思，而在网络编程中，其被翻译为 “套接字”。
 *              Linux 环境下，我们说“一切皆文件”。因此套接字也被视为一种文件描述符。
 * 
 * @param domain    用于指示协议族的名字，如 AF_INET 为 IPv4
 * @param type      用于指示类型，如基于流通信的 SOCK_STREAM 
 * @param protocol  用于指示对于这种 socket 的具体协议类型。一般情况下，使用前两个参数限定后，只会存在一种协议类型对应该情况。
 *                  这时，可以将 protocol 设置为 0。但是在某些情况下，会存在多个协议类型，这时就必须指定具体的协议类型。
 * 
 * @return 成功创建 socket 后，会返回一个文件描述符。失败时，该接口返回 -1。
*/


/**
 * int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen)
 *  
 * @brief 获取或者设置某个套接字关联的选项。选项可能存在于多层协议中，它们总会出现在最上面的套接字层。
 * 当操作套接字选项时，选项位于的层和选项的名称必须给出。为了操作套接字层的选项，应该讲层的值指定为 SOL_SOCKET。
 * 为了操作其他层的选项，控制选项的合适协议号必须给出。例如，为了表示一个选项由TCP 协议解析，层应该设置协议号 TCP 。
 * 
 * @param sock 将要被设置或者获取选项的套接字
 * 
 * @param level 选项所在的协议层
 * 
 * @param optname 需要访问的选项名
 * 
 * @param optval 对于 getsockopt()，指向返回选项值的缓冲。对于 setsockopt()，指向包含新选项值的缓冲。
 * 
 * @param optlen 对于 getsockopt()，作为入口参数时，选项值的最大长度。作为出口参数时，选项值的实际长度。
 * 对于 setsockopt() 现选项的长度。
 * 
 * @return 0 执行成功； 1 执行失败。
 * 
 * 参数详细扩展： 
 * sock 的几个值代表的意义：
 *  1） EBADF:      sock 不是有效的文件描述词
 *  2)  EFAULT:     optval 指向的内存并非有效的进程空间
 *  3)  EINVAL:     在调用 setsockopt() 时， optlen 无效
 *  4)  ENOPROTOOPT:指定的协议层不能识别选项
 *  5)  ENOTSOCK:   sock描述的不是套接字
 * 
 * level 指定控制套接字的层次，可以取三种值： 
 *  1） SOL_SOCKET： 通用套接字选项
 *  2） IPPROTO_OP： IP选项
 *  3） IPPROTO_TCP： TCP 选项
 * 
 * 
*/


/**
 * void *memset(void *s, int  c, unsigned long n);
 * 
 * @brief 将指针变量 s 所指向的前 n 字节的内存单元用一个 “整数” c 替换。
 *      c 是 int 型的指针变量，所以它可以为任何类型的数据进行初始化。
 * 
 *  memset() 的作用是在一段内存块中填充某个给定的值。因为它只能填充一个值，所以该函数的初始化为原始初始化，
 *  无法将变量初始化为程序中需要的数据。用 memset 初始化完之后，后面 程序中再想该内存空间中存放需要的数据。
 * 
 *  memset 一般使用 0 初始化内存单元，而且通常是给数组或结构体进行初始化。一般的变量 如 char、int、float等类型的
 *  变狼直接初始化即可，没有必要用 memset。
*/


// 在成功创建套接字后，该套接字仅仅是一个文件描述符，并没有任何地址与之关联。使用该 socket 发送数据包时，由于该 socket 
// 没有任何 IP 地址，内核会根据策略自动选择一个地址。但是某些情况下，我们需要手工指定 socket 使用哪个 IP 地址进行发送。
// 这时，就需要使用 bind 系统调用了。
/**
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * 
 * @brief 能够将套接字文件描述符、端口号和 ip 绑定一起。
 *  注意：绑定的一定时自己的 IP 和端口号，不是对方的；比如对于 TCP 服务器来说绑定的就是服务器自己的 IP 和端口号。
 * 
 * @param sockfd    表示 socket 函数创建的通信文件描述符
 * @param addr      表示绑定到套接字的地址
 * @param addrlen   表示所指定的结构体变量的大小
 * 
 * @return      0 成功； -1 失败。
 * 
 * Linux 环境编程从应用到内核 PAGE 810。
 * 
 * 为什么要使用 struct sockaddr *类型的地址？
 *  因为 Linux 的套接字是针对多种协议族的，而每个协议族都可以有不同的地址类型。所以 Linux 套接字关于地址的系统调用
 *  统一使用了一个公共结构体，并要求调用者将实际地址参数进行强制类型转换，以此来避免编译警告。
 * 
 *  因为每个协议族的地址类型各不相同，所以需要通过参数 addrlen 来告诉内核这个地址的实际大小。
 * 
 * 注意：struct sockaddr 数据类型会在 socket 涉及地址的所有接口中出现。这是因为套接字接口要支持所有的协议族，
 * 所以涉及地址的地方都是用了一个统一的地址结构 struct sockaddr。
*/

//
// struct sockaddr{
//     sa_family_t sa_family;
//     char        sa_data[14];
// };
/**
 * 
*/

/**
 * int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * 
 * @brief   客户端链接函数， connect 的用途是使用指定的套接字去连接指定的地址。对于面向连接的协议（套接字类型为 SOCK_STREAM），
 *          connect 只能成功一次（当然要如此，因为真正的连接已经建立了）。如果重复调用 connect，会返回 -1 表示失败，同时错误码为
 *          EISCONN。而对于飞面向连接的协议（套接字类型为 SOCK_DGRAM），则可以执行多次 connect（因为这时的 connect 仅仅是设置了
 *          默认的目的地址）。
 *          
 *          对于 TCP 来说 connect 实际上是要真正的进行三次握手，所以其默认是一个阻塞操作。name是否可以写一个非阻塞的 TCP connect 代码呢？
 *          这时一个合格的网络开发工程师的基本功，具体的实现可以参看 UNPv1 的实现。更重要的是要理解其原理，这样才能在需要的时候，信手捏来。
 * 
 * @param sockfd    套接字描述符
 * @param addr      要连接的地址
 * @param addrlen   要连接的地址长度
 * 
 * @return 0 表示成功， -1 表示失败。
*/

/**
 * int listen(int sockfd, int backlog);
 * 
 * @brief   服务器端使用 listen 来监听端口
 * 
 * @param sockfd    成功创建的 TCP 套接字
 * @param backlog   定义 TCP 未处理连接的队列长度。该队列虽然已经完成了三次握手，但服务器端还没有执行 accept 的
 *                  连接。APUE 中说， backlog 只是一个提示，具体的数值实际上是由系统来决定的。
 * 
 * @return  0 表示成功； -1 表示失败。
*/

/**
 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 * 
 * @brief accept 用于从指定套接字的连接队列中去除第一个连接，并返回一个新的套接字用于于客户端进行通信。
 * 
 * @param sockfd    处于监听状态的套接字
 * @param addr      用于保存对端的地址信息
 * @param addrlen   是一个输入输出值。调用者将其初始化为 addr 缓存的大小，accept 返回时，会将其设置为 addr 的大小。
 * 
 * @return 若执行成功，则返回一个非负的文件描述符； 若失败则返回 -1。
 * 
 * 注意： 若不关心对端地址信息，则可以将 addr 和 addrlen 设置为 NULL。
 * 
*/

/**
 * printf 和 sprintf 的区别？
 * sprintf 函数打印到字符串中，而 printf 函数打印输出到屏幕上。
 * sprintf 函数在我们完成其他数据类型转换成字符串类型的操作中应用广泛。
 * 
 * sprintf函数包含在 <stdio.h> 的头文件中。
 * 
 * sprintf 函数的格式： 
 * int sprintf(char *buffer, const char *format [, argument, ...]);
 * 除了前两个参数固定外，可选参数可以是任意个。buffer 是字符数组名；format 是格式化字符串。
 * 只要在 printf 中可以使用的格式化字符串，在 sprintf 中都可以是使用。其中的格式化字符串是
 * 此函数的精华。
 * sprintf 函数打印到字符串中（可用于完成其他数据类型转换成字符串和字符串拼接）
*/

/**
 * int snprintf(char *str, size_t size, const char *format, ...);
 * 
 * @brief 由于 sprintf 不能检查目标字符串的长度，可能造成众多的安全问题，所以会推荐使用 snprintf
 * 
 * @param str 将格式化后的字符串写入的目标位置
 * @param size 要写入的字符最大数组，如果超过 size 会被截断。
 * @param format snprintf 设将可变参数(...) 按照 format 格式化成字符串，并将字符串复制到 str 中
 * 
 * @return  如果格式化后的字符串长度小于等于 size， 则会把字符串全部复制到 str 中，并给其后添加一个字符串结束符 '\0'
 *          
 *          如果格式化后的字符串长度大于 size， 超过 size 的部分会被截断，只将其中的 (size - 1)个字符复制到 str 中，
 *          并给其后添加一个字符串结束符 '\0'，
 *      
 *          返回值为与写入的字符串长度。
*/


/**
 * #include <sys/stat.h>   
 * #include <unistd.h>
 * 
 * int stat(const char *file_name, struct stat *buf); 
 * 
 * @brief stat函数用来将参数 file_name 所指的文件状态，复制到参数 buf 所指的结构中。
 * 
 * @param file_name 表示文件的路径
 * @param buf       表示声明的结构体
 * @return 0 执行成功； -1 执行失败； 错误代码存于 errno 中。
 * 错误码： 
 * ENOENT   参数 file_name 指定的文件不存在
 * ENOTDIR  路径中的目录存在但却非真正的目录
 * ELOOP    欲打开的文件有过多符号连接问题，上限为 16 符号连接。
 * EFAULT   参数 buf 为无效指针，指向无法存在的内存空间。
 * EACCESS  存取文件时被拒绝
 * ENOMEM   核心内存不足
 * ENAMETOOLONG 参数 file_name 的路径名称太长
 * 
*/

/**
 * 数据发送系统调用接口
 * #include <sys/types.h>
 * #include <sys/socket.h>
 * 
 * ssize_t send(int sockfd, const void *buf, size_t len, int flags);
 * ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, 
 *                  const struct sockaddr *dest_addr, socklen_t addrlen);
 * ssize_t snedmsg(int sockfd, const struct msghdr *msg, int flags);
 * 
 * @brief send 只能用于处理已连接状态的套接字（无论 TCP 还是 UDP 都可以进行连接）。
 *  sendto 可以在调用时，指定目的地址。这样的话，如果套接字已经是连接状态，那么目的地址 dest_addr
 *  与地址长度就应该为 NULL 和 0，不然就可能会返回错误。
 *  sendmsg 比较特殊，无论是要发送的数据还是目的地址，都保存在 msg 中。其中 msg.msg_name 和 msg.msg_len
 *  用于指明目的地址，而msg.msg_iov 则用于保存要发送的数据。这三个系统调用都支持设置指示标志位 flags。
 * 
 * @note 说明： 稍微现代些的系统调用，一般都会拥有或保留一个指示标志参数。通过标志位 flags，可以
 *  从容地为系统调用增加新功能，同时兼容老版本。
 *  由于 socket 同时还是文件描述符，所以为文件提供的写操作（如 write() ）也可以被socket 套接字直接调用。
 * 
*/

/**
 * #include <sys/types.h>
 * #include <sys/socket.h>
 * 
 * ssize_t recv(int sockfd, void *buf, size_t len, int flags);
 * ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, 
 *                  struct sockaddr *src_addr, socklen_t *addrlen);
 * ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
 * 
 * @brief 与 send 类似， recv一般也是面向连接的套接字。原因在于对于非面向连接的套接字来说，若使用
 *  recv 接受数据，通过该接口将不能获得发送端的地址，也就是说不知道这个数据是谁发过来的。所以，如果
 *  使用者不关心发送端信息，或者该信息可以从数据中获得，那么 recv 接口同样也可以用于非面向连接的套接字。
 *      再来看 recvfrom，它会通过额外的参数 src_addr 和 addrlen，来获得发送方的地址，其中需要注意的值 addrlen，
 *  它既是输入值又是输出值。
 *      最后是 recvmsg，它与 sendmsg 一样，把接收到的数据和地址都保存在了 msg 中。
 *  其中 msg.msg_name 和 msg.msg_len 用于保存接收端地址，而 msg.msg_iov 用于保存接收到的数据。
 *      这三个系统调用与对应的发送接口一样，都支持设置标志位 flags -- 都是比较现代的接口涉及方法。
 * 
*/