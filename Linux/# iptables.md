# iptables
 pkts bytes target     prot opt in     out     source               destination
44682 2681K RETURN     icmp --  *      *       0.0.0.0/0            0.0.0.0/0            icmptype 8 limit: avg 1/sec burst 1

icmptype 8 limit: avg 1/sec burst 1

# 速率限制limit
`--limit`: Specifies the rate at what tokens get refilled into the bucket. 4/hour means 4 tokens per hour (1 token every 15 minutes).  
`--limit-burst`: Specifies the maximum amount of tokens that can be filled in the bucket. (This is also the amount of tokens the bucket starts out with).

# 删除iptables规则
```shell
iptables -L -n --line-number # 查看每个规则chain的序列号
iptables -D INPUT 3 # 删除INPUT的第三条已添加规则，这里3代表第几行规则
```

# iptables操作命令
查看iptables防火墙状态：`service iptables status`
开启防火墙：`service iptables stop`
停止防火墙：`service iptables stop`

# 简介
