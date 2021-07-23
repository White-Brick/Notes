# DPDK
## 编译简单用例
设置DPDK源码路径

    export RTE_SDK=/path/to/rte_sdk
    export RTE_TARGET=x86_64-native-linuxapp-gcc

    export RTE_SDK=/home/dpdk/dpdk-stable-18.05.1

Build DPDK:

    cd $RTE_SDK
    make defconfig
    make

Build the sample applications:

    export RTE_TARGET=build
    make -C examples

    // 开启调试模式
    make DEBUG=1

    // 调整build输出
    make O=/tmp

## 运行用例
设置Hugepages

    查看大页内存
    cat /proc/meminfo | grep Huge
    设置大页内存
    echo '1024' > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
    大页挂载
    mkdir /mnt/huge
    mount -t hugetlbfs nodev /mnt/huge

加载VIFO驱动

    


