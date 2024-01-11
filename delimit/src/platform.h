/*
**  @(#)platform.h
**
**  delimit - platform dependencies
**  -------------------------------
**
**  copyright (c) 1993-2024 Code Construct Systems (CCS)
*/
#ifndef __PLATFORM_H
#define __PLATFORM_H

/*
** Check if system default values are defined in another include file
*/
#ifdef  _IO_BUFFER_SIZE
#error  _IO_BUFFER_SIZE is defined in another include file
#endif

/*
** Define system default values (platform dependent)
*/
#ifdef  _ARCH_32
#define _IO_BUFFER_SIZE 2048  /* 32-bit */
#endif
#ifdef  _ARCH_64
#define _IO_BUFFER_SIZE 32768 /* 64-bit */
#endif

#endif /* __PLATFORM_H */
