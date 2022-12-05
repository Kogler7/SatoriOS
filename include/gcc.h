#ifndef _GCC_H_
#define _GCC_H_

#define nop() asm volatile("nop")
#define die()  \
    while (1)  \
    {          \
        nop(); \
    }

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

#define array_size(x) (sizeof(x) / sizeof((x)[0]))

#define attr_packed __attribute__((packed))
#define attr_aligned(x) __attribute__((aligned(x)))

#define attr_weak __attribute__((weak))
#define attr_naked __attribute__((naked))

#define attr_unused __attribute__((unused))
#define attr_used __attribute__((used))
#define attr_const __attribute__((const))
#define attr_pure __attribute__((pure))
#define attr_noreturn __attribute__((noreturn))

#endif /* !_GCC_H_ */