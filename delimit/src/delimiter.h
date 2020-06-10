/*
**  @(#)delimiter.h
**
**  delimit - text file delimiter
**  -----------------------------
**
**  copyright (c) 1993-2020 Code Construct Systems (CCS)
*/
#ifndef __DELIMITER_H
#define __DELIMITER_H

/*
** Define maximum field size and field name size
*/
#ifndef _MAX_FIELD_SIZE
#define _MAX_FIELD_SIZE 1024
#else
#error  _MAX_FIELD_SIZE is defined in another include file
#endif
#ifndef _MAX_FIELD_NAME_SIZE
#define _MAX_FIELD_NAME_SIZE 64
#else
#error  _MAX_FIELD_NAME_SIZE is defined in another include file
#endif

/*
** Check if print control characters are defined in another include file
*/
#ifdef  _TAB
#error  _TAB is defined in another include file
#endif
#ifdef  _SP
#error  _SP is defined in another include file
#endif
#ifdef  _LINE_FEED
#error  _LINE_FEED is defined in another include file
#endif
#ifdef  _CARRIAGE_RETURN
#error  _CARRIAGE_RETURN is defined in another include file
#endif

/*
** Define print control characters
*/
#define _TAB 0x09
#define _SP 0x20
#define _LINE_FEED 0x0a
#define _CARRIAGE_RETURN 0x0d

/*
** Check if special character strings and field separatorsare defined in another include file
*/
#ifdef  _SINGLE_QUOTE
#error  _SINGLE_QUOTE is defined in another include file
#endif
#ifdef  _DOUBLE_QUOTE
#error  _DOUBLE_QUOTE is defined in another include file
#endif
#ifdef  _TAB_SEPARATOR
#error  _TAB_SEPARATOR is defined in another include file
#endif
#ifdef  _SP_SEPARATOR
#error  _SP_SEPARATOR is defined in another include file
#endif
#ifdef  _COMMA_SEPARATOR
#error  _COMMA_SEPARATOR is defined in another include file
#endif
#ifdef  _DECIMAL_POINT
#error  _DECIMAL_POINT is defined in another include file
#endif

/*
** Define special character strings and field separators
*/
#define _SINGLE_QUOTE "\'"
#define _DOUBLE_QUOTE "\""
#define _DECIMAL_POINT '.'
#define _TAB_SEPARATOR "\t"
#define _SP_SEPARATOR " "
#define _COMMA_SEPARATOR ","

/*
** Filter format type
*/
typedef enum format_e {
        ALPHABETIC = 0,
        ALPHANUMERIC,
        NOT_APPLICABLE,
        NUMERIC,
        REMOVE_STRING,
        REPLACE_STRING,
        SPACES,
        ZERO_LENGTH
} format_t;

/*
** File I/O state type
*/
typedef enum io_state_e {
        IO_WRITE_ERROR = -2,
        IO_READ_ERROR = -1,
        IO_EOF = 0,
        IO_OK = 1,
        IO_UNKNOWN = 2
} io_state_t;

/*
** Field parameters structure and type
*/
typedef struct d_fields_s {
        size_t count;
        size_t max_size;
        size_t max_record_size;
} d_fields_t;

/*
** Delimiters structure and type
*/
typedef struct d_delimiters_s {
        char unique_chr;
        bool_c_t unique;
        bool_c_t tab;
        bool_c_t space;
        bool_c_t comma;
        bool_c_t double_quote;
        bool_c_t single_quote;
} d_delimiters_t;

/*
** Replacements structure and type
*/
typedef struct d_replacements_s {
        char character;
        int number;
} d_replacements_t;

/*
** File stream structure and type
*/
typedef struct d_file_stream_s {
        string_c_t name;
        FILE *fp;
        bool_c_t opened;
        io_state_t io_state;
        size_t buffer_size;
        long counter;
        long line_count;
} d_file_stream_t;

/*
** Text file delimiter specifications structure and type
*/
typedef struct delimit_specs_s {
        d_fields_t fields;
        d_delimiters_t delimiters;
        d_replacements_t replacements;
        d_file_stream_t input;
        d_file_stream_t output;
} delimit_specs_t;

/*
** Function prototypes
*/
extern int DelimitOpen(delimit_specs_t *, string_c_t, string_c_t, bool_c_t);
extern int DelimitSetUnique(delimit_specs_t *, bool_c_t, string_c_t);
extern int DelimitFile(delimit_specs_t *);
extern void DelimitClose(delimit_specs_t *);
extern void DelimitAddFieldCount(delimit_specs_t *);
extern void DelimitAddFieldMaxSize(delimit_specs_t *, size_t);
extern void DelimitAddFieldMaxRecordSize(delimit_specs_t *, size_t);
extern void DelimitSetTab(delimit_specs_t *, bool_c_t);
extern void DelimitSetComma(delimit_specs_t *, bool_c_t);
extern void DelimitSetSpace(delimit_specs_t *, bool_c_t);
extern void DelimitSetDouble(delimit_specs_t *, bool_c_t);
extern void DelimitSetSingle(delimit_specs_t *, bool_c_t);

#endif /* __DELIMITER_H */
