#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    /**
     * @brief 
     * step1 socket
     * step2 connect
     */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port        = htons(atoi(argv[2]));

    /**
     * @brief 
     * #include <sys/socket.h>
     * int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
     */
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    str_len = read(sock, message, sizeof(message) -1);
    if (str_len == -1) {
        error_handling("read() error!");
    }

    printf("Message from server: %s \n", message);
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// >>>>>>>注释内容>>>>>>
#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>>
/**
 * @brief 打开文件
 * 
 * @param path 打开的目标文件名及路径
 * @param flag 文件打开模式
 * @return int 成功返回文件描述符，失败返回-1
 */
int open(const char *path, int flag);


#include <unistd.h>
/**
 * @brief 关闭文件/套接字
 * 
 * @param fd 需要关闭的文件或套接字的文件描述符
 * @return int 成功返回0，失败返回-1
 */
int close(int fd);


#include <unistd.h>
/**
 * @brief 将数据写入文件
 * 
 * @param fd 数据传输对象的文件描述符
 * @param buf 保存要传输数据的缓冲地址值
 * @param nbytes 要传输数据的字节数
 * @return ssize_t 成功返回写入字节数，失败返回-1
 */
ssize_t write(int fd, const void *buf, size_t nbytes);


#include <unistd.h>
/**
 * @brief 读取文件中的数据
 * 
 * @param fd 数据接收对象的文件描述符
 * @param buf 要保存接收数据的缓冲地址值
 * @param nbytes 要接收数据的最大字节数
 * @return ssize_t 成功时返回接收的字节数 文件结尾返回0 失败返回-1
 */
ssize_t read(int fd, void *buf, size_t nbytes);


#include <sys/socket.h>
/**
 * @brief 创建套接字
 * 
 * @param domain 套接字中使用的协议族信息
 * @param type 套接字数据传输类型信息
 * @param protocol 计算机间通信中使用的协议信息
 * @return int 成功返回文件描述符，失败返回-1
 */
int socket(int domain, int type, int protocol);

int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
// <<<<<<注释内容<<<<<<<