#ifndef _SATORI_TYPES_H_
#define _SATORI_TYPES_H_
/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

//未作详细检查
typedef signed char 		s8;
typedef unsigned char 		u8;

typedef signed short 		s16;
typedef unsigned short 		u16;

typedef signed int 			s32;
typedef unsigned int 		u32;

typedef signed long long 	s64;
typedef unsigned long long 	u64;

typedef u8			u_int8_t;
typedef s8			int8_t;
typedef u16			u_int16_t;
typedef s16			int16_t;
typedef u32			u_int32_t;
typedef s32			int32_t;

#endif /* !(__BIT_TYPES_DEFINED__) */

#endif /* !(_SATORI_TYPES_H_) */