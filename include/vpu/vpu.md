CPU就是一个资源，无论是硬件的也好，虚拟的也罢，关键在于如何分配

只要是资源，就可以被虚拟化表示，由硬件完成的工作也可以用软件模拟

软件的一切对于开发者来说都是透明的，因而对于学习者来说更为友好

# 寄存器设计

[一口气看完45个寄存器 ——x86/x64架构 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/502718676)

# GDT与LDT

[GDT与LDT_billpig的博客-CSDN博客_gdt ldt](https://blog.csdn.net/billpig/article/details/5833980?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-5833980-blog-103324343.pc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-5833980-blog-103324343.pc_relevant_multi_platform_whitelistv3&utm_relevant_index=1)

保护模式下的段寄存器 由 16位的选择器 与 64位的段描述符寄存器 构成
段描述符寄存器： 存储段描述符
选择器：存储段描述符的索引

![1669988531181](image/vpu/1669988531181.png)

![1669989101316](image/vpu/1669989101316.png)

![1669991795388](image/vpu/1669991795388.png)

# 分段与分页

[深入解析分段与分页_happysnaker的博客-CSDN博客_分段和分页](https://blog.csdn.net/m0_51380306/article/details/120275714)

![1669997959290](image/vpu/1669997959290.png)

![1670000554685](image/vpu/1670000554685.png)

https://zhuanlan.zhihu.com/p/479968208

![1670118815418](image/vpu/1670118815418.png)![1670118939876](image/vpu/1670118939876.png)

[保护模式篇——段寄存器 - 寂静的羽夏 - 博客园 (cnblogs.com)](https://www.cnblogs.com/wingsummer/p/15310141.html)

# 门调用

[Linux中断技术、门描述符、IDT(中断描述符表)、异常控制技术总结归类_郑瀚Andrew的技术博客_51CTO博客](https://blog.51cto.com/u_15775105/5748062)

[idt是什么意思(IDT中国)-子辰百科 (dgthj.cn)](https://www.dgthj.cn/baike/893.html)
