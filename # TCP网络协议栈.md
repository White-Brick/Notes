# TCP网络协议栈

## TCP/IP网络模型
    - 应用层
    - 传输层
    - 网络层（IP、ICMP、ARP、RARP）
    - 数据链路层

## 以太网帧格式
- Ethernet II格式的以太帧最大1518bytes，最小64bytes
- 根据以太帧第12字节来判断具体使用的以太帧格式

## IP报文格式
// Todo:

## TCP报文格式
// Todo:



# tcp的半连接队列syns queue和全连接队列accept queue
## ss工具
- 列出处于time-wait状态的tcp连接  
`ss -tan state time-wait`  

- 列出访问http或者https服务时处于time-wait状态的tcp连接  
`ss -tan state time-wait'dport = :http or dport = :https'`

# 三次握手
                                                (LISTEN)
    (SYN_SENT)   ---[SYN seq = x]           -->
                 <--[SYN seq = y, ACK = x+1]--- (SYN_RCVD)
    (ESTABLISHED)---[ACK = y+1]             -->
                                                (ESTABLISHED)

    write()      ---[seq = x+1, ACK = y+1]  -->
                 <--[ACK = x+2]             -->read()

    (FIN_WAIT_1) ---[FIN seq = x+2, ACK=y+1]-->
                 <--[ACK = x+3]             --- (CLOSE_WAIT)
    (FIN_WAIT_2)
                 <--[FIN seq = y+1]         ---
    (TIME_WAIT)

## 三次握手中丢包如何处理
### 1. A发送给B的SYN中途被丢
    三次握手过程中，第一个SYN包中途被丢，没有达到B，A会周期性超时重传，直到收到B的确认，即B发送过来的SYN+ACK包


### 2. B发送给A的SYN+ACK中途被丢
    B会周期性超时重传，直到收到A的确认


### 3. A发送给B的确认ACK中途被丢
    A发送完ACK（握手过程中的第三个包），A的状态随即变成Established状态，而B显然认为TCP为active状态

    a. 假定此时双方都没有发送数据，B在没有收到ACK的情况下，会周期性超时重传，直到收到A的确认，在收到A的ACK后，TCP连接也为Established状态，双向可以收发包
    b. 假定A在发送ACK后，不知晓B未收到，开始进行数据传送，B收到来自A的Data+ACK，便自然切换到Established状态，并接收A的Data
    c. 假定B有数据发送，数据却发送不出去，会一直周期性超时重传SYN+ACK，直到收到A的确认才可以发送数据


# 四次挥手
// Todo:

# Socket编程
## 1、网络中的进程之间如何通信？
本地的进程间通信（IPC）总结如下：
- 消息传递（管道、FIFO、消息队列）
- 同步（互斥量、条件变量、读写锁、信号量、文件和写记录锁）
- 共享内存（匿名的和具名的）

Q：如何标识唯一一个网络中的进程？  
本地可以通过**进程PID**来唯一标识一个进程，在网络中，由TCP/IP协议族通过**网络层的ip地址**可以唯一标识网络中的主机，通过**传输层的协议+端口**可以唯一标识主机中的应用程序（进程）。通过三元组：ip、协议、端口就可以标识网络中的进程了。

## 2、什么是socket？
网络中进程通信是通过socket来实现的。“一切皆文件”，可以用open->read/write->close的模式进行操作。socket即是一种特殊的文件。

## 3、socket基本操作
### 3.1、socket()
```C
int socket(int domain, int type, int protocol);
```
socket()函数对应普通文件的打开操作。普通文件的打开返回一个文件描述符，socket()返回socket描述符（socket descriptor），它唯一标识一个socket，作为参数，通过它来进行一些读写操作。

类似于fopen()传入不同参数，打开不同的文件。创建socket的时候，也可以指定不同的参数创建不同的socket描述符，socket函数的三个参数分别为：
- domain：即协议域，又称为协议族（family）。常用的协议族有，**AF_INET**、AF_INET6、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、AF_UNIX决定了要用一个绝对路径名作为地址。

- type：指定socket类型。常用的socket类型有，**SOCK_STREAM、SOCK_DGRAM**、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等。

- protocol：常用的协议有，**IPPROTO_TCP、IPPTOTO_UDP**、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。

PS：当我们调用socket创建一个socket时，返回的socket描述字它存在于协议族（address family，AF_XXX）空间中，但没有一个具体的地址。如果想要给它赋值一个地址，就必须调用bind()函数，否则就当调用connect()、listen()时系统会自动随机分配一个端口。

### 3.2、bind()
正如上面所说bind()函数把一个地址族中的特定地址赋给socket。例如对应AF_INET、AF_INET6就是把一个ipv4或ipv6地址和端口号组合赋给socket。
```C
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
函数的三个参数分别为：
- sockfd：它是通过socket()函数创建，唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。

- addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同，如ipv4对应的是： 
```C
// ipv4 
struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* address in network byte order */
};

// ipv6 
struct sockaddr_in6 { 
    sa_family_t     sin6_family;   /* AF_INET6 */ 
    in_port_t       sin6_port;     /* port number */ 
    uint32_t        sin6_flowinfo; /* IPv6 flow information */ 
    struct in6_addr sin6_addr;     /* IPv6 address */ 
    uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */ 
};

struct in6_addr { 
    unsigned char   s6_addr[16];   /* IPv6 address */ 
};

// Unix域 
#define UNIX_PATH_MAX    108

struct sockaddr_un { 
    sa_family_t sun_family;               /* AF_UNIX */ 
    char        sun_path[UNIX_PATH_MAX];  /* pathname */ 
};
```
- addrlen：对应地址长度。

PS：通常服务器在启动的时候都会绑定一个众所周知的地址（如ip地址+端口号），用于提供服务，客户就可以通过它来接连服务器；而客户端就不用指定，有系统自动分配一个端口号和自身的ip地址组合。这就是为什么通常服务器端在listen之前会调用bind()，而客户端就不会调用，而是在connect()时由系统随机生成一个。
> 补充：网络字节序与主机字节序  
> // Todo；

## Socket编程实例
```C
int main() {

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed.\n");
        exit(0);
    }
    else {
        printf("socket successfully created.\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htol(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bindingn newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed.\n");
        exit(0);
    }
    else {
        printf("Socket successfully binded.\n");
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("listen failed.\n");
        exit(0);
    }
    else {
        printf("Listening..\n");
    }
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0) {
        printf("accept failed.\n");
        exit(0);
    }
    else {
        printf("sever accept the client.\n");
    }

    func(connfd);

    close(sockfd);
}

void func(int sockfd) {
    char buff[MAX];
    int n; 
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        // read the msg from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buff which contains the client contents
        printf("From client: %s\t To Client: ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server msg in the buffer
        while ((buf[n++] = getchar()) != '\n');
        // send the buffer to client
        write(sockfd, buff, sizeof(buff));
        if (strncmp ("exit", buff, 4) == 0) {
            printf("Server exit.\n");
            break;
        }
    }
}

```