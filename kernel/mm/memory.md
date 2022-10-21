# 实现思路

- TLB配置


## 设计思路

- 采用离散的存储管理方式
- 采用四级分页结构，每页大小4KB
- 利用位示图描述物理块信息
- 设计页表数据结构
- 启动MMU，设置TLB
- 研究内存管理算法

## 工作流程

	a.系统初始化代码会在内存中生成页表，然后把页表地址设置给MMU对应寄存器，使MMU知道页表在物理内存中的什么位置，以便在需要时进行查找。之后通过专用指令启动MMU，以此为分界，之后程序中所有内存地址都变成虚地址，MMU硬件开始自动完成查表和虚实地址转换。
	b.OS初始化后期，创建第一个用户进程，这个过程中也需要创建页表，把其地址赋给进程结构体中某指针成员变量。即每个进程都要有独立的页表。
	c.用户创建新进程时，子进程拷贝一份父进程的页表，之后随着程序运行，页表内容逐渐更新变化。


# 参考资料

- 早期内存分配管理

[【linux 内存管理】memblock算法简单梳理_bigDxin的博客-CSDN博客](https://blog.csdn.net/zhangwenxinzck/article/details/105307799?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-105307799-blog-124286916.pc_relevant_aa_2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-105307799-blog-124286916.pc_relevant_aa_2&utm_relevant_index=5)

[(91条消息) 内核杂谈——页表项存放的是物理地址还是虚拟地址？_LuckY_chh的博客-CSDN博客_create_pgd_mapping](https://blog.csdn.net/m0_37797953/article/details/113650688?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-3-113650688-blog-101612855.t0_edu_mix&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-3-113650688-blog-101612855.t0_edu_mix&utm_relevant_index=4)

[(91条消息) Linux内存管理之MMU的过程_布道师Peter的博客-CSDN博客_linux mmu](https://blog.csdn.net/melody157398/article/details/106846311)

[(91条消息) 【Linux】Linux的虚拟内存详解（MMU、页表结构）__kerneler的博客-CSDN博客](https://blog.csdn.net/qq_38350702/article/details/109508057?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-5-109508057-blog-127061728.pc_relevant_3mothn_strategy_and_data_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~Rate-5-109508057-blog-127061728.pc_relevant_3mothn_strategy_and_data_recovery&utm_relevant_index=10)

[(91条消息) 硬件篇之MMU_ipmux的博客-CSDN博客_mmu](https://blog.csdn.net/ipmux/article/details/19167605)

[(91条消息) 深度学习arm MMU一篇就够了_代码改变世界ctw的博客-CSDN博客_smmu granule](https://blog.csdn.net/weixin_42135087/article/details/123573475?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2~default~CTRLIST~Rate-1-123573475-blog-19167605.pc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2~default~CTRLIST~Rate-1-123573475-blog-19167605.pc_relevant_multi_platform_whitelistv3&utm_relevant_index=1)

# 信息记录

## MEM_MAP

```c
loongson_mem_map->count = 15

0 type:1;   start:0x00200000;    size:0x0ee00000;

1 type:2;   start:0x0f000000;    size:0x01000000;

2 type:1;   start:0x00000000;    size:0x10000000; //256MB

3 type:1;   start:0x90000000;    size:0xf0000000; //3840MB 3.75GB

4 type:1;   start:0x00000000;    size:0x10000000;

5 type:1;   start:0x90010000;    size:0x6e6c0000;

6 type:1;   start:0xfe6e0000;    size:0x00010000; //FE6F

7 type:1;   start:0xfe700000;    size:0x00190000; //FE89

8 type:1;   start:0xfef10000;    size:0x01080000;

9 type:1;   start:0xfffe0000;    size:0x80020000; //18000

10 type:1;   start:0x100d0000;    size:0x00001000; //FFF9

11 type:2;   start:0xfe6f0000;    size:0x00010000; //FE70

12 type:2;   start:0xfe890000;    size:0x002c0000; //FEB5

13 type:2;   start:0xfeb60000;    size:0x003b0000; //FEF1

14 type:2;   start:0xfff90000;    size:0x00050000; //FFFE
```
