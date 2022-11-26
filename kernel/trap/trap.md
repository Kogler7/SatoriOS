[真象还原笔记：键盘驱动与环形输入缓冲区 - 简书 (jianshu.com)](https://www.jianshu.com/p/ff65a1ca6954)

[键盘——扫描码——ASCII码——显示器上的字符 (baidu.com)](https://baijiahao.baidu.com/s?id=1694086614934809141&wfr=spider&for=pc)

[(96条消息) linux 中断与异常---源码分析（三）_淡泊的猪的博客-CSDN博客](https://blog.csdn.net/whuzm08/article/details/80097186)

[(104条消息) x86构架之-Intel8042键盘控制器简介_rayylee的博客-CSDN博客](https://blog.csdn.net/hbuxiaofei/article/details/116274989)

i8042 Status Register

> Bit7: PARITY-EVEN(P_E): 从键盘获得的数据奇偶校验错误
> Bit6: RCV-TMOUT(R_T): 接收超时，置1
> Bit5: TRANS_TMOUT(T_T): 发送超时，置1
> Bit4: KYBD_INH(K_I): 为1，键盘没有被禁止。为0，键盘被禁止。
> Bit3: CMD_DATA(C_D): 为1，输入缓冲器中的内容为命令，为0，输入缓冲器中的内容为数据。
> Bit2: SYS_FLAG(S_F): 系统标志，加电启动置0，自检通过后置1
> Bit1: INPUT_BUF_FULL(I_B_F): 输入缓冲器满置1，i8042 取走后置0
> Bit0: OUT_BUF_FULL(O_B_F): 输出缓冲器满置1，CPU读取后置0

Control Register

> Bit7: 保留，应该为0
> Bit6: 将第二套扫描码翻译为第一套
> Bit5: 置1，禁止鼠标
> Bit4: 置1，禁止键盘
> Bit3: 置1，忽略状态寄存器中的 Bit4
> Bit2: 设置状态寄存器中的 Bit2
> Bit1: 置1，enable 鼠标中断
> Bit0: 置1，enable 键盘中断



驱动对键盘控制器发送命令是通过写端口64h实现的，共有12条命令，分别为

20h
准备读取8042芯片的Command Byte；其行为是将当前8042 Command Byte的内容放置于Output Register中，下一个从60H端口的读操作将会将其读取出来。

60h
准备写入8042芯片的Command Byte；下一个通过60h写入的字节将会被放入Command Byte。

A4h
测试一下键盘密码是否被设置；测试结果放置在Output Register，然后可以通过60h读取出来。测试结果可以有两种值：FAh=密码被设置；F1h=没有密码。

A5h
设置键盘密码。其结果被按照顺序通过60h端口一个一个被放置在Input Register中。密码的最后是一个空字节（内容为0）。

A6h
让密码生效。在发布这个命令之前，必须首先使用A5h命令设置密码。

AAh
自检。诊断结果放置在Output Register中，可以通过60h读取。55h=OK。

ADh
禁止键盘接口。Command Byte的bit-4被设置。当此命令被发布后，Keyboard将被禁止发送数据到Output Register。

AEh
打开键盘接口。Command Byte的bit-4被清除。当此命令被发布后，Keyboard将被允许发送数据到Output Register。

C0h
准备读取Input Port。Input Port的内容被放置于Output Register中，随后可以通过60h端口读取。

D0h
准备读取Outport端口。结果被放在Output Register中，随后通过60h端口读取出来。

D1h
准备写Output端口。随后通过60h端口写入的字节，会被放置在Output Port中。

D2h
准备写数据到Output Register中。随后通过60h写入到Input Register的字节会被放入到Output Register中，此功能被用来模拟来自于Keyboard发送的数据。如果中断被允许，则会触发一个中断。

[(104条消息) 通过对i8042 键盘控制器编程控制鼠标_Luwei的博客-CSDN博客](https://blog.csdn.net/snailhit/article/details/6684192?spm=1001.2101.3001.6650.7&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EESLANDING%7Edefault-7-6684192-blog-116274989.pc_relevant_landingrelevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EESLANDING%7Edefault-7-6684192-blog-116274989.pc_relevant_landingrelevant&utm_relevant_index=8)

[(104条消息) i8042与i8048键盘控制器芯片端口操作总结 _wzsy的博客-CSDN博客](https://blog.csdn.net/wzsy/article/details/6130651?spm=1001.2101.3001.6650.9&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-9-6130651-blog-6684192.pc_relevant_recovery_v2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-9-6130651-blog-6684192.pc_relevant_recovery_v2&utm_relevant_index=10)
