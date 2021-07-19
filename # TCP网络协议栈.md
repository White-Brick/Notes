# TCP网络协议栈

## TCP/IP网络模型
    应用层
    传输层
    网络层（IP、ICMP、ARP、RARP）
    数据链路层

## 以太网帧格式
- Ethernet II格式的以太帧最大1518bytes，最小64bytes
- 根据以太帧第12字节来判断具体使用的以太帧格式

## IP报文格式

## TCP报文格式



# Socket编程
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


