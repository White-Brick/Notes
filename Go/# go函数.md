# GO目录结构
- bin
存放编译后可执行的文件

- pkg
存放编译后的应用包

- src
存放应用源代码

## 常用命令
    go build hello
    在src目录或hello目录下执行go build hello，只在对应当前目录下生成文件
    
    go install hello
    在src目录或hello目录下执行go install hello，会把编译好的结果移动到 $GOPATH/bin

    go run hello
    在src目录或hello目录下执行go run hello，不生成任何文件只运行程序

    go fmt hello
    在src目录或hello目录下执行go fmt hello，格式化代码，将代码修改成标准格式


# 一、go函数
## 1、声明
```go
func functionname(parametername type) returntype {  
    // 函数体（具体实现的功能）
}
```
函数参数列表定义在`(`和`)`之间  
参数列表和返回值并非是必须的
```go
// example
func calculateBill(price int, no int) int {
    var totalPrice = price * no
    return totalPrice
}

// 如果有连续若干个参数，它们的类型一致，那么我们无须一一罗列，只需在最后一个参数后添加该类型
func calculateBill(price, no int) int {
    var totalPrice = price * no
    return totalPrice
}
```
## 2、多返回值
```go
// 如果一个函数有多个返回值，那么这些返回值必须用 ( 和 ) 括起来
func rectProps(length, width float64)(float64, float64) {
    var area = length * width
    var perimeter = (length + width) * 2
    return area, perimeter
}
```
## 3、命名返回值
从函数中可以返回一个命名值。一旦命名了返回值，可以认为这些值在函数第一行就被声明为变量了
```go
func rectProps(length, width float64)(area, perimeter float64) {
    // 不需要定义area和perimeter 直接进行赋值
    area = length * width
    perimeter = (length + width) * 2
    // 默认返回
    return
}
```
## 4、空白符
_ 在 Go 中被用作空白符，可以用作表示任何类型的任何值  

我们继续以 rectProps 函数为例，该函数计算的是面积和周长。假使我们只需要计算面积，而并不关心周长的计算结果，该怎么调用这个函数呢？这时，空白符 _ 就上场了
```go
func main() {  
    area, _ := rectProps(10.8, 5.6) // 返回值周长被丢弃
    fmt.Printf("Area %f ", area)
}
```

# 二、方法
Go中也有方法，它是一种特殊的函数，定义于struct之上(与struct关联、绑定)，被称为struct的receiver。
```go
type mytype struct {}

func (recv mytype) my_method(para) return_type {}
func (recv *mytype) my_method(para) return_type {}
```
这表示`my_method()`函数是绑定在mytype这个struct type上的，是与之关联的，是独属于mytype的。所以，此函数称为"方法"。所以，方法和字段一样，也是struct类型的一种属性。

# 三、Go Slice
**slice切片**，go数组的长度不可改变，Go 中提供了一种内置类型切片("动态数组")，与数组相比切片的**长度是不固定的，可以追加元素，在追加时可能使切片的容量增大**。

slice内部通过指针和相关属性引用数组片段实现。
```go
// 1.定义
var identifier []type

var slice1 []type = make([]type, len)
slice1 := make([]type, len)

// 2.初始化
s := []int{1, 2, 3}             // []表示是切片类型
s := arr[:]                     // 初始化切片a，是数组arr的引用
s := arr[startIndex:endIndex]   // 将 arr 中从下标 startIndex 到 endIndex-1 下的元素创建为一个新的切片
s := arr[startIndex:]           // 使用默认 endIndex 时将表示一直到arr的最后一个元素
s := arr[:endIndex]             // 使用默认 startIndex 时将表示从 arr 的第一个元素开始
s1 := s[startIndex:endIndex]    // 通过切片 s 初始化切片 s1
s := make([]int, len, cap)      // 通过内置函数 make() 初始化切片s，[]int 标识为其元素类型为 int 的切片

// 3.len() cap()
package main
import "fmt"
func main() {
   var numbers = make([]int,3,5)
   printSlice(numbers)
}
func printSlice(x []int){
   fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
// 输出：len=3 cap=5 slice=[0 0 0]
```

# 四、切片slice与数组
数组声明：[num]T  
切片声明：[]T  

PS:“值语义”与“引用语义”

    - 值语义：对象的拷贝与原对象无关
    - 引用语义：一个对象被系统标准的复制函数复制后，对象共享底层资源，只要一个改变另一个就会改变

    如何判断：
    判断该对象在发生拷贝时，是否需要重写operator =
    C++会为类提供默认的拷贝构造函数和重载函数，一般不需要自己重写，因为只要每个数据成员都为值语义，编译器就可以调用默认的成员（浅拷贝）



# 五、TCP
假设一个客户端和服务器存在一个 TCP 连接，客户端开始执行关闭连接的操作，客户端先给服务器发送了一个 FIN 包以表示数据发送完毕，这会导致客户端的状态变成 FIN_WAIT1。  
由于 TCP 是全双工的，此时客户端还能接收服务器发过来的数据。

当服务器收到客户端发送的 FIN 包后发送一个 ACK 包以响应客户端的这个 FIN 包。此时服务器的状态变成 CLOSE_WAIT，客户端在收到服务器发送的 ACK 包后自己的状态变为 FIN_WAIT2。

一段时间后服务器向客户端发送一个 FIN 包，客户端收到服务器的 FIN 包并响应一个 ACK 包后进入 TIME_WAIT 状态，此时 TCP 连接完全断开。