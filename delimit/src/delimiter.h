/*
**  @(#)delimiter.h
**
**  delimiter - text file delimiter
**  -------------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
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
#define _MAX_FIELD_NAME_SIZE 128
#else
#error  _MAX_FIELD_NAME_SIZE is defined in another include file
#endif

/*
** Check if print control characters are defined in another include file
*/
#ifdef  _TAB
#error  _TAB is defined in another include file
#endif
#ifdef  _LINE_FEED
#error  _LINE_FEED is defined in another include file
#endif
#ifdef  _CARRIAGE_RETURN
#error  _CARRIAGE_RETURN is defined in another include file
#endif
#ifdef  _SPC
#error  _SPC is defined in another include file
#endif

/*
** Define print control characters
*/
#define _TAB 0x09
#define _LINE_FEED 0x0a
#define _CARRIAGE_RETURN 0x0d
#define _SPC 0x20

/*
** Check if special character strings and field separatorsare defined in another include file
*/
#ifdef  _COMMA_SEPARATOR
#error  _COMMA_SEPARATOR is defined in another include file
#endif
#ifdef  _TAB_SEPARATOR
#error  _TAB_SEPARATOR is defined in another include file
#endif
#ifdef  _SPC_SEPARATOR
#error  _SPC_SEPARATOR is defined in another include file
#endif
#ifdef  _SINGLE_QUOTE_SEPARATOR
#error  _SINGLE_QUOTE_SEPARATOR is defined in another include file
#endif
#ifdef  _DOUBLE_QUOTE_SEPARATOR
#error  _DOUBLE_QUOTE_SEPARATOR is defined in another include file
#endif
#ifdef  _DECIMAL_POINT
#error  _DECIMAL_POINT is defined in another include file
#endif

/*
** Define special character strings and field separators
*/
#define _COMMA_SEPARATOR ","
#define _TAB_SEPARATOR "\t"
#define _SPC_SEPARATOR " "
#define _SINGLE_QUOTE_SEPARATOR "\'"
#define _DOUBLE_QUOTE_SEPARATOR "\""
#define _DECIMAL_POINT '.'

/*
** Filter format type
*/
typedef enum format_e {
        NO_ACTION,
        ALPHABETIC,
        ALPHANUMERIC,
        NUMERIC,
        PRINTABLE,
        SPACES,
        REMOVE_STRING,
        REPLACE_STRING,
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
        bool_c_t comma;
        bool_c_t tab;
        bool_c_t space;
        bool_c_t single_quote;
        bool_c_t double_quote;
        bool_c_t unique;
        char unique_chr;
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
typedef struct delimit_specifications_s {
        d_fields_t fields;
        d_delimiters_t delimiters;
        d_replacements_t replacements;
        d_file_stream_t input;
        d_file_stream_t output;
} delimit_specifications_t;

/*
** Function prototypes
*/
extern int DelimitOpen(delimit_specifications_t *, bool_c_t);
extern int DelimitClose(delimit_specifications_t *);
extern int DelimitFile(delimit_specifications_t *);
extern int DelimitAddFieldCount(delimit_specifications_t *);
extern int DelimitAddFieldMaxSize(delimit_specifications_t *, size_t);
extern int DelimitAddFieldMaxRecordSize(delimit_specifications_t *, size_t);
extern int DelimitSetComma(delimit_specifications_t *, bool_c_t);
extern int DelimitSetTab(delimit_specifications_t *, bool_c_t);
extern int DelimitSetSpace(delimit_specifications_t *, bool_c_t);
extern int DelimitSetSingle(delimit_specifications_t *, bool_c_t);
extern int DelimitSetDouble(delimit_specifications_t *, bool_c_t);
extern int DelimitSetUnique(delimit_specifications_t *, bool_c_t, string_c_t);
extern int DelimitSetDefaults(delimit_specifications_t *, string_c_t input, string_c_t output);

#endif /* __DELIMITER_H */