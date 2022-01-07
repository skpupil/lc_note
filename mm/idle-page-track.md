一个bitmap文件，每一位代表着一个页的常用程度，用户态可以读取和设置这个文件。
推荐使用：工作集size探测
1、找到workload的每一页的pfn
2、写bitmap文件，设置为idle
3、等待内核，访存设置bitmap文件
4、读取bitmap文件，知道页的常用程度和工作集size
Idle Page Tracking设计目的是用户态使用的