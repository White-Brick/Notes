# iptables
NAT+防火墙工具
## 原理

## 操作链
- I 插入
- A 追加
- R 替换
- D 删除
- L 显示

举例：   

    iptables -t filter -A FORWARD -s 10.1.1.11 -d 202.1.1.1 -j ACCEPT 

    上面的命令意思为：追加一个规则至filter表中的FORWARD链尾，允许（-j ACCEPT）源地址为10.1.1.11目的地址为202.1.1.1的数据包通过。
    其中-t后面跟的是表名，在-A后面跟Chain名，后面的小写的-s为源地址，-d为目的地址，-j为处理方向。

    在iptables中，默认的表名就是filter，所以这里可以省略-t filter直接写成:
    iptables -A FORWARD -s 10.1.1.11 -d 202.1.1.1 -j ACCEPT

## 匹配参数
- -s 匹配源地址
- -d 匹配目的地址
- -p 匹配协议
- -i 匹配入接口
- -o 匹配出接口
- --sport/--dport 匹配源端口/目的端口 
- -j 跳转包的方向

## 实例分析一：NAT路由器
LAN口：10.1.1.254/24 eth0  
WAN口：60.1.1.1/24   eth1  
效果：实现内网中的节点10.1.1.0/24可控地访问Internet  

    1. 首先将LAN的节点pc的网关指向10.1.1.254。
    2. 确定你的linux的ip配置无误，可以正确的ping通内外的地址。同时用route命令查看linux的本地路由表，确认指定了可用的ISP提供的默认网关。
    3. 使用sysctl net.ipv4.ip_forward=1打开linux的转发功能。
    4. iptables -P FORWARD DROP，将FORWARD链的策略Policy设置为DROP，这样做的目的是做到对内网ip的控制，你允许哪一个访问internet就可以增加一个规则，不在规则中的ip将无法访问internet。
    5. iptables -A FORWARD -m state --state ESTABLISHED, RELATED -j ACCEPT，这条规则规定允许任何地址到任何地址的确认包和关联包（已经建立tcp连接的包以及该连接相关的包）通过，否则你只允许lan IP访问没有用
    6. iptables -t nat -A POSTROUTING -s 10.1.1.0/24 -j SNAT --to 60.1.1.1（SNAT在POSTROUTING链上做），这条规则做了一个SNAT，也就是源地址转换，将来自10.1.1.0/24的地址转换为60.1.1.1
    7. 添加允许的ip至FORWARD链，例如，ptables -A FORWARD -s 10.1.1.0/24 -p tcp --dport http -j ACCEPT只允许他们访问80端口

## 实例分析二：端口转发/映射
LAN口：10.1.1.254/24 eth0  
WAN口：60.1.1.1/24   eth1  
LAN内web server: 10.1.1.1:80  
LAN内ftp server: 10.1.1.2:21  
效果：实现内网中的节点10.1.1.0/24可控地访问Internet  

    1. 同样确认你的linux的各项配置正常，能够访问内外网。
    2. iptables -P FORWARD DROP，
       iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT
       配置策略，加入确认包和关联包允许通过
    3. iptables -t nat -A PREROUTING -d 60.1.1.1 -p tcp --dport 80 -j DNAT --to 10.1.1.1:80（DNAT在PREROUTING链上做），把访问60.1.1.1:80的数据包转发到Lan内web server
    重点详见：链接


### 补充：NAT与NPAT，端口映射
- NAT：网络地址转换方法
- PAT（NAPT）：增加了端口的概念，每个私网IP对应同一个公网IP的不同端口号，这样子就能实现多个私网IP共用一个公网IP
- 端口转发/映射：Port-Forwarding，NAT的一种，外网主机的IP地址的端口映射到内部网络中的机器上，以提供相应的服务。作为服务器，服务器的程序会监听特定的端口，用客户上门。那么我们就需要把这个特定端口永久分给服务器，保证客户通过这个地址和端口就能找到服务器。这就是端口映射。

## REDIRECT重定向
REDIRECT是DNAT的特殊情况是重定向，也就是所谓的Redirection。
# netfilter
三表
- filter 防火墙功能
- nat 地址转换和端口转发
- mangle 自定义

filter操作链Chain
- INPUT 入
- FORWARD 转发
- OUTPUT 出

nat操作链
- PREROUTING
- POSTROUTING
- OUTPUT  


参考：  
https://blog.csdn.net/qq_33611327/article/details/79385940

# ebtables