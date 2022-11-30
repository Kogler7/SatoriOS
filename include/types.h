#ifndef _SATORI_TYPES_H_
#define _SATORI_TYPES_H_

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

typedef signed char 		s8;
typedef unsigned char 		u8;
typedef unsigned char 		byte;
typedef unsigned char 		sint;
typedef unsigned char 		bool;

typedef signed short 		s16;
typedef unsigned short 		u16;
typedef unsigned short 		word;

typedef signed int 			s32;
typedef unsigned int 		u32;

typedef signed long 	    s64;
typedef unsigned long 	    u64;

#define true        (bool)1
#define false       (bool)0
#define done        1
#define error       -1
#define null        0
#define nullstr     ""
#define nullptr     ((void *)0)

#define nop()       asm volatile("nop")

#endif /* !_SATORI_TYPES_H_ */