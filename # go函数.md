# go函数
## 声明
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
## 多返回值
```go
// 如果一个函数有多个返回值，那么这些返回值必须用 ( 和 ) 括起来
func rectProps(length, width float64)(float64, float64) {
    var area = length * width
    var perimeter = (length + width) * 2
    return area, perimeter
}
```
## 命名返回值
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
## 空白符
_ 在 Go 中被用作空白符，可以用作表示任何类型的任何值  

我们继续以 rectProps 函数为例，该函数计算的是面积和周长。假使我们只需要计算面积，而并不关心周长的计算结果，该怎么调用这个函数呢？这时，空白符 _ 就上场了
```go
func main() {  
    area, _ := rectProps(10.8, 5.6) // 返回值周长被丢弃
    fmt.Printf("Area %f ", area)
}
```

# TCP
假设一个客户端和服务器存在一个 TCP 连接，客户端开始执行关闭连接的操作，客户端先给服务器发送了一个 FIN 包以表示数据发送完毕，这会导致客户端的状态变成 FIN_WAIT1。  
由于 TCP 是全双工的，此时客户端还能接收服务器发过来的数据。

当服务器收到客户端发送的 FIN 包后发送一个 ACK 包以响应客户端的这个 FIN 包。此时服务器的状态变成 CLOSE_WAIT，客户端在收到服务器发送的 ACK 包后自己的状态变为 FIN_WAIT2。

一段时间后服务器向客户端发送一个 FIN 包，客户端收到服务器的 FIN 包并响应一个 ACK 包后进入 TIME_WAIT 状态，此时 TCP 连接完全断开。