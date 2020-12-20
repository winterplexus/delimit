/*
**  @(#)common.h
**
**  delimit - common definitions
**  ----------------------------
**
**  copyright (c) 1993-2021 Code Construct Systems (CCS)
*/
#ifndef __COMMON_H
#define __COMMON_H

/*
** Check if file stream I/O options are defined in another include file
*/
#ifdef  _F_RO
#error  _F_RO is defined in another include file
#endif
#ifdef  _F_RO_BIN
#error  _F_RO_BIN is defined in another include file
#endif
#ifdef  _F_RW_BIN
#error  _F_RW_BIN is defined in another include file
#endif
#ifdef  _F_AP
#error  _F_AP is defined in another include file
#endif
#ifdef  _F_AP_BIN
#error  _F_AP_BIN is defined in another include file
#endif

/*
** Define file stream I/O options
*/
#define _F_RO "r"
#define _F_RO_BIN "rb+"
#define _F_RW_BIN "wb+"
#define _F_AP "a+"
#define _F_AP_BIN "ab+"

/*
** Define maximum file name size
*/
#ifndef _MAX_FILE_NAME_SIZE
#define _MAX_FILE_NAME_SIZE 255
#else
#error  _MAX_FILE_NAME_SIZE is defined in another include file
#endif

/*
** Define maximum message size
*/
#ifndef _MAX_MESSAGE_SIZE
#define _MAX_MESSAGE_SIZE 80
#else
#error  _MAX_MESSAGE_SIZE is defined in another include file
#endif

/*
** Define empty string
*/
#ifndef _EMPTY_STRING
#define _EMPTY_STRING ""
#else
#error  _EMPTY_STRING is defined in another include file
#endif

/*
** Undefine TRUE and FALSE if defined in another include file
*/
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

/*
** Check if data type is defined in another include file
*/
#ifdef bool_c_t
#error bool_c_t is defined in another include file
#endif

/*
** Define Boolean data type
*/
typedef enum boolean_t {
        FALSE = 0, TRUE = 1
} bool_c_t;

/*
** Check if data type is defined in another include file
*/
#ifdef string_c_t
#error string_c_t is defined in another include file
#endif

/*
** Define custom string (null-terminated character array) data type
*/
typedef char *string_c_t;

#endif /* __COMMON_H */