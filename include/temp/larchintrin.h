//===----------- larchintrin.h - LoongArch BASE intrinsics ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LoongArch Base intrinsics
//
//===----------------------------------------------------------------------===//
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#ifndef __LOONGARCH_BASE_H
#define __LOONGARCH_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct drdtime{
	unsigned long dvalue;
	unsigned long dtimeid;
} __drdtime_t;

typedef struct rdtime{
	unsigned int value;
	unsigned int timeid;
} __rdtime_t;

/* Assembly instruction format:          rd, csr_num */
/* Data types in instruction templates:  unsigned int, uimm14_32 */
#define __csrrd(/*uimm14_32*/ _1)	((unsigned int)__builtin_loongarch_csrrd(_1))

/* Assembly instruction format:          rd, csr_num */
/* Data types in instruction templates:  unsigned int, uimm14_32 */
#define __csrwr(/*unsigned int*/ _1, /*uimm14_32*/ _2)	((unsigned int)__builtin_loongarch_csrwr((unsigned int)(_1), (_2)))

/* Assembly instruction format:          rd, rj, csr_num */
/* Data types in instruction templates:  unsigned int, unsigned int, uimm14_32 */
#define __csrxchg(/*unsigned int*/ _1, /*unsigned int*/ _2, /*uimm14_32*/ _3) ((unsigned int)__builtin_loongarch_csrxchg((unsigned int)(_1), (unsigned int)(_2), (_3)))

/* Assembly instruction format:          rd, csr_num */
/* Data types in instruction templates:  unsigned long int, uimm14 */
#define __dcsrrd(/*uimm14*/ _1)	((unsigned long int)__builtin_loongarch_dcsrrd(_1))

/* Assembly instruction format:          rd, csr_num */
/* Data types in instruction templates:  unsigned long int, uimm14 */
#define __dcsrwr(/*unsigned long int*/ _1, /*uimm14*/ _2)	((unsigned long int)__builtin_loongarch_dcsrwr((unsigned long int)(_1), (_2)))

/* Assembly instruction format:          rd, rj, csr_num */
/* Data types in instruction templates:  unsigned long int, unsigned long int, uimm14 */
#define __dcsrxchg(/*unsigned long int*/ _1, /*unsigned long int*/ _2, /*uimm14*/ _3) ((unsigned long int)__builtin_loongarch_dcsrxchg((unsigned long int)(_1), (unsigned long int)(_2), (_3)))

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned char, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
unsigned char __iocsrrd_b(unsigned int _1)
{
	return (unsigned char)__builtin_loongarch_iocsrrd_b((unsigned int)_1);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned short, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
unsigned short __iocsrrd_h(unsigned int _1)
{
	return (unsigned short)__builtin_loongarch_iocsrrd_h((unsigned int)_1);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned int, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
unsigned int __iocsrrd_w(unsigned int _1)
{
	return (unsigned int)__builtin_loongarch_iocsrrd_w((unsigned int)_1);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates: unsigned long int, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
unsigned long int __iocsrrd_d(unsigned int _1)
{
	return (unsigned long int)__builtin_loongarch_iocsrrd_d((unsigned int)_1);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned char, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __iocsrwr_b(unsigned char _1, unsigned int _2)
{
	return (void)__builtin_loongarch_iocsrwr_b((unsigned char)_1, (unsigned int)_2);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned short, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __iocsrwr_h(unsigned short _1, unsigned int _2)
{
	return (void)__builtin_loongarch_iocsrwr_h((unsigned short)_1, (unsigned int)_2);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates:  unsigned int, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __iocsrwr_w(unsigned int _1, unsigned int _2)
{
	return (void)__builtin_loongarch_iocsrwr_w((unsigned int)_1, (unsigned int)_2);
}

/* Assembly instruction format:          rd, rj */
/* Data types in instruction templates: unsigned long int, unsigned int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __iocsrwr_d(unsigned long int _1, unsigned int _2)
{
	return (void)__builtin_loongarch_iocsrwr_d((unsigned long int)_1, (unsigned int)_2);
}

/* Assembly instruction format:          op, rj, si12 */
/* Data types in instruction templates: uimm5, unsigned int, simm12 */
#define __cacop(/*uimm5*/ _1, /*unsigned int*/ _2, /*simm12*/ _3) ((void)__builtin_loongarch_cacop((_1), (unsigned int)(_2), (_3)))

/* Assembly instruction format:          op, rj, si12 */
/* Data types in instruction templates: uimm5, unsigned long int, simm12 */
#define __dcacop(/*uimm5*/ _1, /*unsigned long int*/ _2, /*simm12*/ _3)	((void)__builtin_loongarch_dcacop((_1), (unsigned long int)(_2), (_3)))

#define __rdtime_d	__builtin_loongarch_rdtime_d
#define __rdtimel_w	__builtin_loongarch_rdtimel_w
#define __rdtimeh_w	__builtin_loongarch_rdtimeh_w

extern __inline __drdtime_t __attribute__((__gnu_inline__, __always_inline__, __artificial__))
__builtin_loongarch_rdtime_d (void)
{
  __drdtime_t drdtime;
  __asm__ volatile (
    "rdtime.d\t%[val],%[tid]\n\t"
    : [val]"=&r"(drdtime.dvalue),[tid]"=&r"(drdtime.dtimeid)
    :
  );
  return drdtime;
}

extern __inline __rdtime_t __attribute__((__gnu_inline__, __always_inline__, __artificial__))
__builtin_loongarch_rdtimeh_w (void)
{
  __rdtime_t rdtime;
  __asm__ volatile (
    "rdtimeh.w\t%[val],%[tid]\n\t"
    : [val]"=&r"(rdtime.value),[tid]"=&r"(rdtime.timeid)
    :
  );
  return rdtime;
}

extern __inline __rdtime_t __attribute__((__gnu_inline__, __always_inline__, __artificial__))
__builtin_loongarch_rdtimel_w (void)
{
  __rdtime_t rdtime;
  __asm__ volatile (
    "rdtimel.w\t%[val],%[tid]\n\t"
    : [val]"=&r"(rdtime.value),[tid]"=&r"(rdtime.timeid)
    :
  );
  return rdtime;
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, char, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crc_w_b_w(char _1, int _2)
{
	return (int)__builtin_loongarch_crc_w_b_w((char)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, short, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crc_w_h_w(short _1, int _2)
{
	return (int)__builtin_loongarch_crc_w_h_w((short)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, int, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crc_w_w_w(int _1, int _2)
{
	return (int)__builtin_loongarch_crc_w_w_w((int)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates: int, long int, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crc_w_d_w(long int _1, int _2)
{
	return (int)__builtin_loongarch_crc_w_d_w((long int)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, char, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crcc_w_b_w(char _1, int _2)
{
	return (int)__builtin_loongarch_crcc_w_b_w((char)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, short, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crcc_w_h_w(short _1, int _2)
{
	return (int)__builtin_loongarch_crcc_w_h_w((short)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates:  int, int, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crcc_w_w_w(int _1, int _2)
{
	return (int)__builtin_loongarch_crcc_w_w_w((int)_1, (int)_2);
}

/* Assembly instruction format:          rd, rj, rk */
/* Data types in instruction templates: int, long int, int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
int __crcc_w_d_w(long int _1, int _2)
{
	return (int)__builtin_loongarch_crcc_w_d_w((long int)_1, (int)_2);
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbclr()
{
	return (void)__builtin_loongarch_tlbclr();
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbflush()
{
	return (void)__builtin_loongarch_tlbflush();
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbfill()
{
	return (void)__builtin_loongarch_tlbfill();
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbrd()
{
	return (void)__builtin_loongarch_tlbrd();
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbwr()
{
	return (void)__builtin_loongarch_tlbwr();
}

extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __tlbsrch()
{
	return (void)__builtin_loongarch_tlbsrch();
}

/* Assembly instruction format:          code */
/* Data types in instruction templates:  uimm15 */
#define __syscall(/*uimm15*/ _1)	((void)__builtin_loongarch_syscall(_1))

/* Assembly instruction format:          code */
/* Data types in instruction templates:  uimm15 */
#define __break(/*uimm15*/ _1)	((void)__builtin_loongarch_break(_1))

/* Assembly instruction format:          hint */
/* Data types in instruction templates:  uimm15 */
#define __dbar(/*uimm15*/ _1)	((void)__builtin_loongarch_dbar(_1))

/* Assembly instruction format:          hint */
/* Data types in instruction templates:  uimm15 */
#define __ibar(/*uimm15*/ _1)	((void)__builtin_loongarch_ibar(_1))

/* Assembly instruction format:          rj, rk */
/* Data types in instruction templates:  long int, long int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __asrtle_d(long int _1, long int _2)
{
	return (void)__builtin_loongarch_asrtle_d((long int)_1, (long int)_2);
}

/* Assembly instruction format:          rj, rk */
/* Data types in instruction templates:  long int, long int */
extern __inline __attribute__((__gnu_inline__, __always_inline__, __artificial__))
void __asrtgt_d(long int _1, long int _2)
{
	return (void)__builtin_loongarch_asrtgt_d((long int)_1, (long int)_2);
}

#define __movfcsr2gr(uimm5) \
({ \
  unsigned int rd; \
  __asm__ volatile ( \
    "movfcsr2gr %0, $fcsr" #uimm5 \
    : "=&r"(rd) \
    : \
  ); rd; \
})

#define __movgr2fcsr(uimm5, rj) \
{ \
  __asm__ volatile ( \
    "movgr2fcsr $fcsr" #uimm5 ", %0" \
    : \
    : "r" (rj) \
  ); \
}

#ifdef __cplusplus
}
#endif
#endif /* __LOONGARCH_BASE_H */
