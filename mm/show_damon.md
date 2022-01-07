#! https://zhuanlan.zhihu.com/p/446677951
# DAMON: Linux内存数据访问监控框架

DAMON（Data Access MONitor）是linux kernel的内存数据访问监控框架。在5.15进入了主线。<br/>

DAMON可以做虚拟内存和物理内存的访问监控，监控的结果是数据的访问频繁程度，可以通过回调函数（比如利用MADV），做很多内存优化的操作，包括冷内存的swap out和将热页组织为大页等。<br/>

虚拟内存监控和物理内存监控都是通过检查PTE的accessed bit来做访问监控的。虚拟内存监控，是直接访问目标虚拟地址空间的页表即可。物理内存则是，访问每个映射到目标物理地址空间的页表。检查和重置accessed bit可能对内存的回收和idle page track机制造成干扰，damon使用PG_idle 和 PG_young page 标志来避免。 <br/>

监控原理：

### 1、基于region的采样

把一个完整的监控区域划分为小的region，<br/>

假设同一个region的页，访问频率是相同的。基于这个假设，damon只需要检查任意一个PTE的accessed bit，就可以确定一个region的访问频率。<br/>

监控精度和开销是一对tradeoff。<br/>

监控精度和开销主要通过设置采样间隔和结果聚合间隔来控制。<br/>

每个采样间隔（sampling interval），damon会检查一次region的访问情况。<br/>

每个聚合间隔（aggregation interval），damon汇总所有采样间隔结果。<br/>

为了防止随着监控区域的增大，开销会无限制的增大，damon采样的region数目是有最大最小值的（ minimum number of regions, and maximum number of regions）。<br/>

### 2、自适应的region调整<br/>

随着系统的运行，不同数据的访问频繁模式是动态变化的，就需要自适应的调整region，包括分割和合并region。<br/>

合并的是，那些聚合统计后，发现访问频繁模式差距小的region。<br/>

保证region数目不超过上限的前提下，在每次聚合统计清理标记时候，尝试分割一个region成两个到三个。<br/>

### 3、基于VMA的虚拟地址监控

我们知道，虚拟地址空间大部分是没有映射的，监控这些ummap的区域完全是浪费。因此，damon应该自适应的去除这些umap区域。

基于这个原因，初始化的时候，damon利用VMA划分了三个大的region：堆、栈、mmap。不去监控两个大的gap（1、heap和mmap上界之间。2、mmap下界和stack之间。）<br/>

为了应对程序运行过程中，动态的内存地址map和unmap。damon在每个regions update interval之后重新初始化。<br/>

进程虚拟地址空间：
```
    <heap>
    <BIG UNMAPPED REGION 1>
    <uppermost mmap()-ed region>
    (small mmap()-ed regions and munmap()-ed regions)
    <lowermost mmap()-ed region>
    <BIG UNMAPPED REGION 2>
    <stack>
```






[kernel doc](https://docs.kernel.org/vm/damon/index.html)

https://linuxplumbersconf.org/event/11/contributions/984/attachments/870/1670/daos_ksummit_2021.pdf

https://sjp38.github.io/post/damon/

https://lwn.net/Articles/863191/

https://github.com/sjp38/linux/releases/tag/damon/patches/v34

https://blog.csdn.net/zqh1630/article/details/109954910

https://lore.kernel.org/linux-mm/20210520075629.4332-1-sj38.park@gmail.com/