/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.2                      */
/*     Description: StdTypes.h           */
/*****************************************/

#ifndef STDTYPES_H_
#define STDTYPES_H_

/* Unsigned Data Types */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

/* Signed Data Types */

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef char c8;

#define NULLPTR ((void*)0)
#define NULL ((char)0)

#define MAX_U8 ((u8)255)
#define MIN_U8 ((u8)0)

#define MAX_S8 ((u8)127)
#define MIN_S8 ((u8)-128)

#define ZERO_S8 ((s8)0)

#endif 