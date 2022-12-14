#include "types.h"

#ifndef _SATORI_SYSCALL_H_
#define _SATORI_SYSCALL_H_

#define SYSCALL_NUM_MAX 64

#define SYSCALL_EXIT 0
#define SYSCALL_FORK 1
#define SYSCALL_GETPID 19
#define SYSCALL_WAITPID 6

#define SYSCALL_READ 2
#define SYSCALL_WRITE 3
#define SYSCALL_OPEN 4
#define SYSCALL_CLOSE 5


#define SYSCALL_CREAT 7
#define SYSCALL_LINK 8
#define SYSCALL_UNLINK 9
#define SYSCALL_EXECVE 10
#define SYSCALL_CHDIR 11
#define SYSCALL_TIME 12
#define SYSCALL_MKNOD 13
#define SYSCALL_CHMOD 14
#define SYSCALL_CHOWN 15
#define SYSCALL_BRK 16
#define SYSCALL_LSEEK 18

#define SYSCALL_STAT 17

#define SYSCALL_RTX_GETW 26
#define SYSCALL_RTX_DELW 27
#define SYSCALL_RTX_GOTO 20
#define SYSCALL_RTX_PUTC 21
#define SYSCALL_RTX_PUTS 22
#define SYSCALL_RTX_CLS 25

#define SYSCALL_KBD_GETC 23
#define SYSCALL_KBD_GETS 24

typedef void (*syscall_t)(void);

extern syscall_t syscall_table[SYSCALL_MAX];

void syscall_entry(int idx, u32* args);

#endif /* !_SATORI_SYSCALL_H_ */