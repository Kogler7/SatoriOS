来源于GCC交叉编译的库

/opt/cross-tools/target/usr/lib64/clang/11.0.0/include/larchintrin.h


添加了一行代码

```C
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
```

用于关闭一些警告信息
