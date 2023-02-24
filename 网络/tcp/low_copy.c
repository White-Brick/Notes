#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// 程序输入 源文件 目的文件 ./low_copy data.txt copy.txt

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    int fd_src;
    int fd_dst;

    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage : %s <src_file> <dst_file> \n", argv[0]);
        exit(1);
   }

    fd_dst = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC);
    if (fd_dst == -1) {
        error_handling("open() fd_dst error!");
    }

    fd_src = open(argv[1], O_RDONLY);
    if (fd_dst == -1) {
        error_handling("open() fd_src error!");
    }

    memset(buf, 0, sizeof(buf));
    if (read(fd_src, buf, sizeof(buf)) == -1) {
        error_handling("read() error!"); 
    }
    printf("Get data : %s\n", buf);

    if (write(fd_dst, buf, sizeof(buf)) == -1) {
        error_handling("write() error!");
    }

    close(fd_src);
    close(fd_dst);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
