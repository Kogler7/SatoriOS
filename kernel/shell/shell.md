[(104条消息) Linux命令之stat命令_恒悦sunsite的博客-CSDN博客_linux stat](https://blog.csdn.net/carefree2005/article/details/122454333)

stat命令用于显示文件的状态信息。stat命令的输出信息比ls命令的输出信息要更详细。stat命令可以查看的信息包括：

File：显示文件名
Size：显示文件大小
Blocks：文件使用的数据块总数
IO Block：IO块大小
regular file：文件类型（常规文件）
Device：设备编号
Inode：Inode号
Links：链接数
Access：文件的权限
Gid、Uid：文件所有权的Gid和Uid
access time：表示我们最后一次访问（仅仅是访问，没有改动）文件的时间
modify time：表示我们最后一次修改文件的时间
change time：表示我们最后一次对文件属性改变的时间，包括权限，大小，属性等等
Birth time : 文件创建时间，crtime，不过据查此属性linux已废弃，目前状态显示结果均为-
————————————————
版权声明：本文为CSDN博主「恒悦sunsite」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/carefree2005/article/details/122454333
