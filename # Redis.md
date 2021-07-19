# Redis
## 简介
    Redis属于高性能的key-value数据库，全称Remote Dictionary Server远程数据服务器。

## 场景
    Redis交换数据非常快，在服务器中常用来存储一些需要频繁调取的数据，节省内存开销，也极大的提升了速度。将一些热点数据存储到Redis中，要用的时候，直接从内存取，极大的提高了速度和节约了服务器的开销。

## 数据类型
    支持string（字符串），hash（哈希），list（列表），set（集合）及zset(sorted set：有序集合)

## 服务命令
```redis
redis-cli // 启动redis客户端
redis-cli -h host -p port -a password   // 远程服务器启动redis-cli
```

## 持久化
- 快照（RDB）
- 仅附加文件（AOF）