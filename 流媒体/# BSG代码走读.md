# BSG代码走读

# go互斥锁和读写锁
    Q：为什么要加锁？
    A：Go语言中 sync 包里提供了互斥锁 Mutex 和读写锁 RWMutex 用于处理并发过程中可能出现同时两个或多个协程（或线程）读或写同一个变量的情况

    而锁的概念就是，当一个协程正在处理 a 时将 a 锁定，其它协程需要等待该协程处理完成并将 a 解锁后才能再进行操作，也就是说同时处理 a 的协程只能有一个。
- 多个线程在读相同的数据时
- 多个线程在写相同的数据时
- 同一个资源有读又有写

## 互斥锁 sync.Mutex
    互斥锁是一种常用的控制共享资源访问的方法，它能够保证同时只有一个 goroutine 可以访问到共享资源
```go
func (m *Mutex) Lock()
func (m *Mutex) Unlock()
```
## 读写锁 sync.RWMutex



# panic
    Go语言的类型系统会在编译时捕获很多错误，但有些错误只能在运行时检查，如数组访问越界、空指针引用等，这些运行时错误会引起宕机

    一般而言，当宕机发生时，程序会中断运行，并立即执行在该 goroutine（可以先理解成线程）中被延迟的函数（defer 机制），随后，程序崩溃并输出日志信息，日志信息包括 panic value 和函数调用的堆栈跟踪信息，panic value 通常是某种错误信息。

## 在宕机时触发延迟执行语句
    当 panic() 触发的宕机发生时，panic() 后面的代码将不会被运行，但是在 panic() 函数前面已经运行过的 defer 语句依然会在宕机发生时发生作用

```go
package main

import "fmt"
func main () {
    defer fmt.Println("宕机后要做的事情1")
    defer fmt.Println("宕机后要做的事情2")
    panic("宕机")
}
/*
    宕机后要做的事情2
    宕机后要做的事情1
    panic: 宕机

    goroutine 1 [running]:
    main.main()
        D:/code/main.go:8 +0xf8
    exit status 2

    宕机前，defer 语句会被优先执行，由于第 7 行的 defer 后执行，因此会在宕机前，这个 defer 会优先处理，随后才是第 6 行的 defer 对应的语句，这个特性可以用来在宕机发生前进行宕机信息处理。
*/
```

# 交换机镜像
https://blog.csdn.net/wsasy12345/article/details/83210444

# so库文件
## so介绍
    linux下的.so文件为共享库，相当于windows下的dll文件。在系统目录/usr/lib/下，我们可以看到很多应用程序库文件（常用的动态链接库和软件包的配置文件）

## 使用
    编译生成so库：编译时gcc后加-fPIC，这可以使gcc产生于位置无关的代码; 
    连接时，使用-shared，指示生成一个共享库文件; 
    共享库文件命名：lib-库命名.so


# OOM机制
    Linux内核有个机制叫OOM killer(Out Of Memory killer)，该机制会监控那些占用内存过大，尤其是瞬间占用内存很快的进程，然后防止内存耗尽而自动把该进程杀掉。内核检测到系统内存不足、挑选并杀掉某个进程的过程可以参考内核源代码linux/mm/oom_kill.c，当系统内存不足的时候，out_of_memory()被触发，然后调用select_bad_process()选择一个”bad”进程杀掉。如何判断和选择一个”bad进程呢？linux选择”bad”进程是通过调用oom_badness()，挑选的算法和想法都很简单很朴实：最bad的那个进程就是那个最占用内存的进程。
`grep "Out of memory" /var/log/messages`  
`egrep -i -r 'killed process' /var/log`

# Linux内存
    cat /proc/meminfo

# /proc/pid文件系统
|  目录名   | 功能说明  |
|----|----|
|mem    | 包含了进程在内存中的内容 |
|stat   | 包含了进程的状态信息 |
|limits | 存储了进程的软限制，硬限制等信息|

# 修改TCP缓冲区大小
## 查看TCP读缓冲区大小
    cat /proc/sys/net/ipv4/tcp_rmem
    4096	87380	6291456

    第一个值：4096	    
    给socket接收缓冲区分配的最小值min

    第二个值：87380 	  	默认值deafult
    默认值，接收缓冲区大小在系统负载不重的情况下可以增长到这个值

    第三个值：6291456 	最大值max
    是接收缓冲区最大值

    当我们修改TCP缓冲区大小时，最小不能小于4096，最大不能大于6291456
    修改的值需要在这个范围内

## 查看TCP使用的内存
    cat /proc/sys/net/ipv4/tcp_mem

# Go UDP模型
## UDP编程函数
1. 创建监听地址：   
    func ResolveUDPAddr(network, address string) (*UDPAddr, error) 
2. 创建用户通信的socket：   
    func ListenUDP(network string, laddr *UDPAddr) (*UDPConn, error) 
3. 接收udp数据：   
    func (c *UDPConn) ReadFromUDP(b []byte) (int, *UDPAddr, error) 
4. 写出数据到udp：   
    func (c *UDPConn) WriteToUDP(b []byte, addr *UDPAddr) (int, error)

## demo
```go
package main

import (
    "net"
    "fmt"
    "strings"
)

func main() {
//创建监听的地址，并且指定udp协议，返回一个UDP地址和一个错误信息
//我们使用127.0.0.1:6000是本机的回送地址作为师范，可以观察效果
    addr,err:=net.ResolveUDPAddr("udp","127.0.0.1:6666")
    //接收一下错误信息
    if err!=nil {
        fmt.Println("resolveudpaddr err", err)
        return
    }
    //创建用户通信的socket，需要用到上面监听函数的返回值，作为此函数的参数
    conn,err:=net.ListenUDP("udp",addr)
    if err!=nil {
        fmt.Println("listen err",err)
        return 
    }
    //延时调用关闭
    defer conn.Close()
    buf:=make([]byte,1024)
    for  {
    //接收udp数据，这里还是会返回一个udp地址，处理数据后发送给这个地址
        n,udpaddr,err:=conn.ReadFromUDP(buf)
        if n==0 {
            fmt.Printf("用户%s退出\n",conn.RemoteAddr().String())
            break
        }
        if err!=nil {
            fmt.Println("read err",err)
            return
        }
    /*写数据到udp地址，这里只是一个事例，大家可以做不同
    的数据处理后再发送，但注意只能接受字符切片类型作为函数参数*/
    _,err=conn.WriteToUDP((buf[:n]),udpaddr)
    if err!=nil{
    fmt.Println("writeudp err:",err)
    return
    }
    }
}
```


