# SatoriOS


- -Wall means that all warnings are enabled
- -O2 means that the compiler will optimize the code
- -g3 means that the compiler will generate debugging information
- -march=loongarch64 means that the compiler will generate code for LoongArch64
- -mabi=lp64s means that the compiler will generate code for LP64S ABI
- -ffreestanding means that the compiler will not assume that the code is part of a larger program
- 开启后GCC就知道正在编译内核，因此禁用C标准库里的大部分库，并针对裸机环境进行调整。
- 而不使用此选项，gcc就会针对运行在操作系统上的应用编译。
- -fno-common means that the compiler will not allow uninitialized global variables
- -nostdlib means that the compiler will not use the standard C library
- -I means that the compiler will search for header files in the specified directory
- -fno-stack-protector means that the compiler will not generate stack protection code
- -fno-pie means that the compiler will not generate position-independent code
- -no-pie means that the compiler will not generate position-independent code
- -Wall -O0 -g3是常规的警告信息、优化级别和调试级别选项，可以根据需要修改
- -march=loongarch64 -mabi=lp64s是指定相应的目标架构和ABI(lp64s表示64位、不带浮点支持的LA ABI)
- -ffreestanding选项是告诉编译器不要假设有标准库存在，程序也不一定从main()函数开始，它隐含了-fno-builtin，编译器不会自动识别一些内置的函数(如memcpy)
- -fnostdlib，不链接一些系统启动文件和库(如/crt*.o/libc/libgcc等)
- -fno-common，告诉编译器不要把未初始化的全局变量放到一个common block，而是放到BSS中
- -I. 允许编译器在当前目标找头文件
- -fno-stack-protector，不要自动生成栈保护（检测栈是否溢出等的代码）
- -fno-pie -no-pie，不要生成位置无关的可执行代码。内核的位置一般不会动，这个选项可能提升性能。但如果你的内核需要支持位置无关以提高安全性，则不用这些选项。