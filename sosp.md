# HeMem: Scalable Tiered Memory Management for Big Data Applications and Real NVM

[论文](https://dl.acm.org/doi/10.1145/3477132.3483550)

&emsp;&emsp;HeMem: NVM(产品：Intel’s Optane DC persistent memory)用作内存，在和DRAM形成的多层内存操作系统中，实现动态管理内存，不需要trace access bit，不需要刷掉TLB，用户态实现，无需修改OS，对应用透明。<br/>


<div style="text-align:center">
<img src="../pics/paper/SOSP21-HeMem/dram-nvm-scalability.png" width="60%" width="60%"/></div>
<br/>
<div style="text-align:center">
<img src="../pics/paper/SOSP21-HeMem/scan-overhead.png" width="60%" width="60%"/></div>
<br/>

### 实验测试得出：<br/>
&emsp;&emsp;相比于DRAM，optane写是很慢的，带宽是很小的。<br/>
&emsp;&emsp;随机访问4K以下是很慢的，这种应该放在DRAM。<br/>
&emsp;&emsp;在不影响应用性能的前提下，完全可以利用optane的剩余带宽来进行页面的迁移。<br/>
&emsp;&emsp;放入NVM后，内存容量大幅度增加，更多的页和更多级的页表，传统的trace技术，扫描页表中的access位和dirty位，还要刷出TLB（如果命中TLB，无法改变页表中的flags），开销过大。<br/>
&emsp;&emsp;不对称的NVM读写带宽。写的多的数据结构尽可能驻留DRAM。
### optane 有多种分层内存访问方式：<br/>
&emsp;&emsp;内存模式memory mode (MM)：对应用透明，没有明确的机制取探测冷热数据。DRAM用作NVM的cache。粒度是cache line(64B)。涉及复杂的缓存一致性问题，并且缓存回写影响性能。<br/>
<div style="text-align:center">
<img src="../pics/paper/SOSP21-HeMem/memory-mode.png" width="60%" width="60%" /></div>
<br/>

&emsp;&emsp;app-direct (AP) mode中的kmemedax：NVM对OS来说，是一个独立分割的NUMA node。使用内核已经存在的NUMA内存管理机制，实现更简单，不需要回写。对于上层程序来说，多层内存管理系统有单独的线程异步执行。页被周期性的发生迁移。粒度是页。内存策略的管理和做迁移决定之前的统计工作，可能比较复杂。和MM相比，数据只在一个地方。内存的管理在一个单独的线程上执行，长时间运行的迁移会推迟扫描和统计工作的进行。并且，扫描和统计开销大。<br/>
<div style="text-align:center">
<img src="../pics/paper/SOSP21-HeMem/NUMA-memory-mode.png" width="60%" width="60%">
</div>
<br/>

&emsp;&emsp;文件系统：对应用程序可见的字节或块访问的设备。应用程序来做map文件到内存的工作，而不是OS，灵活性更大。<br/>


### HeMem系统设计
&emsp;&emsp;它拦截OS的内存管理系统调用，比如mmap 和 madvise。为了在用户态处理page fault，新的内存映射的虚拟地址空间被注册到了user-faultfd。这样，OS遇到page fault，直接交给hemem 线程。<br/>
<br/>
<div style="text-align:center">
<img src="../pics/paper/SOSP21-HeMem/hemem.png" width="60%" width="60%"/>
</div>


<br/>
&emsp;&emsp;内存频繁程度的测量统计方案：HeMem使用performance counter设置CPU event来跟踪内存访问的次数（可以区分读和写、DRAM访问和NVM访问）。每间隔若干次访问，CPU触发事件，将当前访问的目标地址写入一块预留的缓冲区。HeMem维护一个异步线程收集缓冲区上的信息，记录每一个数据块的近期被访问次数，然后归入冷热队列。采样频率和冷热阈值是根据实验经验决定固定的数值。维护每个页面的计数器来冷却热页面的access计数，热页随时间变冷。<br/><br/>


&emsp;&emsp;分配：使用DAX方式挂载DRAM和NVM到内核中。进行内存allocation。在用户态的库中进行多层内存的管理，有效且低开销的维护应用的运行时内存使用信息。比如，拦截mmap系统调用，付出函数调用的开销，获得应用程序内存空间的信息。<br/>


&emsp;&emsp;迁移：数据迁移策略根据上述信息标记待迁移的数据块，采用批处理的方式进行迁移。迁移时加写保护标记，根据实验，迁移时应用写的概率极小可忽略。并设置了迁移的最大量上限。并且优化了DMA来做迁移。迁移模块基于DMA。如果没用DMA，那就由迁移策略触发线程进行成批的迁移。<br/>

&emsp;&emsp;page fault：因为hemem管理了内存分配，知道内存空间地址，也就容易处理page fault。fault 是缺页则分配，是写保护则等待。<br/>

### 细节：
&emsp;&emsp;DRAM预留一定区域，保证分配首先在DRAM上完成。短暂存活和都在DRAM上，小页面交给OS管理。标记写的多的页面，迁移到DRAM时候，给高优先级。<br/>

&emsp;&emsp;应用范围：在访问内存频繁的任务存在时，再开启另一个任务，内存总量超越了DRAM。并且，这样的应用不使用内核的内存管理特性。<br/>

&emsp;&emsp;hemem是用户态的应用程序粒度的多层内存管理，不涉及OS页的管理。因为静态不增长，在选择要迁移到数据，要有所取舍。内核和应用的一些数据结构（如缓冲区，队列和堆栈）驻留在DRAM。不管.text段。实验没有涉及硬盘swap。<br/>

&emsp;&emsp;在开机时，预先在开机时通过DAX分配一定空间的内存给多层内存管理系统。如果将来linux将NVM以NUMA的方式整合进匿名内存管理系统，需要通过使用NUMA子系统，改变预分配的方式。 <br/>

&emsp;&emsp;支持共享内存。<br/>

&emsp;&emsp;按照单个CPU socket的内存池进行管理内存，而不是全局内存。这对大数据应用够用了。
<br/>

### 实现：
&emsp;&emsp;linux5.1 上打两个userfaultfd的patch（未进入主线，在原来缺页异常的基础上，支持了写保护异常）。配置optane为App-Direct mode，并挂载为DAX设备。
在单个socket上跑的测试，在单个NUMA node的上实验（NUMA的影响超出论文范围）。<br/>
&emsp;&emsp;HeMem将GAP图处理测试用例的运行时间减少了50%，将TPC-C在Silo数据库上的吞吐量提高了13%，将键值存储在性能隔离下的尾延迟降低了16%，并减少了10倍的NVM磨损。<br/>

[perf event](https://www.brendangregg.com/perf.html#Events)
