#include "sys/syscall.h"
#include "io/kinfo.h"

#define syscall_error(fmt, ...) pr_error(SYSCALL, fmt, ##__VA_ARGS__)

syscall_t syscall_table[SYSCALL_NUM_MAX] = {
    [SYSCALL_EXIT]      = nullptr,
    [SYSCALL_FORK]      = nullptr,
    [SYSCALL_READ]      = nullptr,
    [SYSCALL_WRITE]     = nullptr,
    [SYSCALL_OPEN]      = nullptr,
    [SYSCALL_CLOSE]     = nullptr,
    [SYSCALL_WAITPID]   = nullptr,
    [SYSCALL_CREAT]     = nullptr,
    [SYSCALL_LINK]      = nullptr,
    [SYSCALL_UNLINK]    = nullptr,
    [SYSCALL_EXECVE]    = nullptr,
    [SYSCALL_CHDIR]     = nullptr,
    [SYSCALL_TIME]      = nullptr,
    [SYSCALL_MKNOD]     = nullptr,
    [SYSCALL_CHMOD]     = nullptr,
    [SYSCALL_LSEEK]     = nullptr,
    [SYSCALL_GETPID]    = nullptr,
}

void syscall_entry(int idx, u32* args)
{
    if (idx < 0 || idx >= SYSCALL_NUM_MAX) {
        syscall_error("Invalid syscall index: %d", idx);
    }
    syscall_t syscall = syscall_table[idx];
    if (syscall == nullptr) {
        syscall_error("Unimplemented syscall: %d", idx);
    }
    syscall(args);
}