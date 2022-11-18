#ifndef _SATORI_TYPES_H_
#define _SATORI_TYPES_H_

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

//未作详细检查
typedef signed char 		s8;
typedef unsigned char 		u8;
typedef unsigned char 		byte;

typedef signed short 		s16;
typedef unsigned short 		u16;
typedef unsigned short 		word;

typedef signed int 			s32;
typedef unsigned int 		u32;

typedef signed long long 	s64;
typedef unsigned long long 	u64;

typedef u64 				addr;

#endif /* !(__BIT_TYPES_DEFINED__) */

#endif /* !(_SATORI_TYPES_H_) */