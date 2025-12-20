/*
**  @(#)delimit.h
**
**  delimit - delimit text file utility
**  -----------------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
*/
#ifndef __DELIMIT_H
#define __DELIMIT_H

/*
** Standard C header files
*/
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#ifdef _POSIX_ENVIRONMENT
#include <unistd.h>
#endif

#ifdef _WINDOWS_ENVIRONMENT
#include <io.h>
#include <process.h>
#include <share.h>
#endif

/*
** Local modules header files
*/
#include "common.h"
#include "delimiter.h"
#include "dct.h"
#include "fio.h"
#include "interp.h"
#include "options.h"
#include "platform.h"
#include "port.h"
#include "util.h"
#include "version.h"

/*
** Unwind buffer stack pointer
*/
extern jmp_buf unwind_buffer_sp;

/*
** Define exit application macro (unwind stack to last setjmp)
*/
#ifndef EXIT_APPLICATION
#define EXIT_APPLICATION(_code) longjmp(unwind_buffer_sp, _code)
#else
#error  EXIT_APPLICATION is defined in another include file
#endif

/*
** Windows environment functions
*/
#ifdef _WINDOWS_ENVIRONMENT
#define strdup _strdup
#endif

#endif /* __DELIMIT_H */