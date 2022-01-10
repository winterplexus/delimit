/*
**  @(#)options.h
**
**  delimit - command line options
**  ------------------------------
**
**  copyright (c) 1993-2022 Code Construct Systems (CCS)
*/
#ifndef __OPTIONS_H
#define __OPTIONS_H

/*
** Define maximum unique delimiter string size
*/
#ifndef _MAX_UNIQUE_DELIMITER_SIZE
#define _MAX_UNIQUE_DELIMITER_SIZE 1024
#else
#error  _MAX_UNIQUE_DELIMITER_SIZE is defined in another include file
#endif

/*
** Command line options structure and type
*/
typedef struct options_s {
        char format[_MAX_FILE_NAME_SIZE + 1];
        char input[_MAX_FILE_NAME_SIZE + 1];
        char output[_MAX_FILE_NAME_SIZE + 1];
        char unique_delimiter[_MAX_UNIQUE_DELIMITER_SIZE + 1];
        bool_c_t comma;
        bool_c_t tab;
        bool_c_t space;
        bool_c_t single_quote;
        bool_c_t double_quote;
        bool_c_t unique;
        bool_c_t statistics;
        bool_c_t overwrite;
} options_t;

/*
** Function prototypes
*/
extern void GetOptions(int, string_c_t[], options_t *);

#endif /* __OPTIONS_H */