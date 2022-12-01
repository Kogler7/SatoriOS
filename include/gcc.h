#ifndef _GCC_H_
#define _GCC_H_

#define nop() asm volatile("nop")

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define barrier() asm volatile("" :: \
                                   : "memory")

#define offsetof(type, member) ((size_t) & ((type *)0)->member)

#define container_of(ptr, type, member) (             \
    {                                                 \
        const typeof(((type *)0)->member) *p = (ptr); \
        (type *)((char *)p - offsetof(type, member)); \
    })

#endif /* !_GCC_H_ */