/*
**  @(#)delimiter.c
**
**  delimit - text file delimiter
**  -----------------------------
**
**  copyright (c) 1993-2021 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Delimiter field format
*/
static format_t df_format = NOT_APPLICABLE;

/*
** Delimiter field name
*/
static char df_name[_MAX_FIELD_NAME_SIZE + 1];

/*
** Delimiter field buffer size
*/
static size_t df_size = 0;

/*
** Delimiter field buffer
*/
static char df_buffer[_MAX_FIELD_SIZE + 1];

/*
** Delimiter field replacement (buffer)
*/
static char df_replace[_MAX_FIELD_SIZE + 1];

/*
** Delimiter error codes type
*/
typedef enum delimiter_error_codes_e {
        DE_CODE00 = 0,
        DE_CODE01,
        DE_CODE02,
        DE_CODE03,
} delimiter_error_codes_t;

/*
** Delimiter error messages structure and error messages table
*/
static struct delimiter_error_messages_s {
        delimiter_error_codes_t code;
        const char *message;
}
error_messages_tbl[] = {
        { DE_CODE00, "bad hexadecimal number or format: use 0x00 hexadecimal format" },
        { DE_CODE01, "no delimiter information" },
        { DE_CODE02, "invalid end of line sequence (or characters) at line:" },
        { DE_CODE03, "actual input line size not equal to format line size at line:" }
};

/*
** Local function prototypes
*/
static string_c_t AlphabeticOnly(delimit_specifications_t *, string_c_t, size_t);
static string_c_t AlphabeticNumericOnly(delimit_specifications_t *, string_c_t, size_t);
static string_c_t NumericOnly(delimit_specifications_t *, string_c_t, size_t);
static string_c_t ReplaceString(delimit_specifications_t *, string_c_t, size_t, string_c_t);
static string_c_t SpacesOnly(delimit_specifications_t *, string_c_t, size_t);
static string_c_t ZeroLength(delimit_specifications_t *, string_c_t, size_t);

/*
** Delimit open
*/
int DelimitOpen(delimit_specifications_t *ds, string_c_t input, string_c_t output, bool_c_t use_temporary) {
    ds->fields.count = 0;
    ds->fields.max_size = 0;
    ds->fields.max_record_size = 0;
    ds->replacements.character = _SPC;
    ds->replacements.number = '0';
    ds->input.io_state = IO_OK;
    ds->input.name = input;
    ds->input.fp = (FILE *)NULL;
    ds->input.buffer_size = _IO_BUFFER_SIZE;
    ds->output.io_state = IO_OK;
    ds->output.fp = (FILE *)NULL;
    ds->output.name = output;
    ds->output.buffer_size = _IO_BUFFER_SIZE;
    return (DelimitFileOpen(ds, use_temporary));
}

/*
** Delimit close
*/
void DelimitClose(delimit_specifications_t *ds) {
    DelimitFileClose(ds);
}

/*
** Delimit file
*/
int DelimitFile(delimit_specifications_t *ds) {
#ifdef _WINDOWS_ENVIRONMENT
    size_t size = 2;
#else
    size_t size = 1;
#endif
    bool_c_t f_field = TRUE;

    /*
    ** Set start dictionary entry
    */
    if (SetStartDictionaryEntry() == ENTRY_EOF) {
        printf("error-> %s\n", error_messages_tbl[DE_CODE01].message);
        return (EXIT_FAILURE);
    }

    /*
    ** Process input and output files while input file is not end of file or read error (and for output file, write error)
    */
    while (ds->input.io_state == IO_OK && ds->output.io_state == IO_OK) {
        /*
        ** Get next dictionary entry
        */
        if (GetNextDictionaryEntry(&df_size, &df_format, df_replace, sizeof(df_replace), df_name, sizeof(df_name)) == ENTRY_EOF) {
            /*
            ** Read string from input file (end of file sequence)
            */
            if (DelimitFileReadString(ds, df_buffer, size) != EXIT_SUCCESS) {
                break;
            }

            /*
            ** Set field delimiter flag
            */
            f_field = TRUE;

            /*
            ** Increment input and output file line counts
            */
            ds->input.line_count++;
            ds->output.line_count = ds->input.line_count;

            /*
            ** Check if end of line sequence (characters) are valid
            */
            if (strlen(df_buffer) < size) {
                printf("error-> %s %ld\n", error_messages_tbl[DE_CODE02].message, ds->input.line_count);
                break;
            }
#ifdef _WINDOWS_ENVIRONMENT
            if (!(df_buffer[0] == _CARRIAGE_RETURN && df_buffer[1] == _LINE_FEED)) {
#else
            if (!(df_buffer[0] == _LINE_FEED)) {
#endif
                printf("error-> %s %ld\n", error_messages_tbl[DE_CODE03].message, ds->input.line_count);
                break;
            }

            /*
            ** Exit if unable to write string (end of file sequence) to output file
            */
            if (DelimitFileWriteString(ds, df_buffer) != EXIT_SUCCESS) {
                return (EXIT_FAILURE);
            }

            /*
            ** Set and get start dictionary entry
            */
            SetStartDictionaryEntry();
            if (GetStartDictionaryEntry(&df_size, &df_format, df_replace, sizeof(df_replace), df_name, sizeof(df_name)) == ENTRY_EOF) {
                return (EXIT_FAILURE);
            }
        }

        /*
        ** Read next string from input file
        */
        if (DelimitFileReadString(ds, df_buffer, df_size) != EXIT_SUCCESS) {
            break;
        }
        if (ds->input.io_state != IO_OK) {
            break;
        }
        if (df_format == REMOVE_STRING) {
            continue;
        }

        /*
        ** Write field delimiter if required
        */
        if (f_field) {
            f_field = FALSE;
        }
        else {
            if (DelimitWriteFieldDelimiter(ds) != EXIT_SUCCESS) {
                return (EXIT_FAILURE);
            }
        }

        /*
        ** Write field quote
        */
        if (DelimitWriteFieldQuote(ds) != EXIT_SUCCESS) {
            return (EXIT_FAILURE);
        }

        /*
        ** Format field based on format type
        */
        switch (df_format) {
            case ALPHABETIC:
                 AlphabeticOnly(ds, df_buffer, df_size);
                 break;
            case ALPHANUMERIC:
                 AlphabeticNumericOnly(ds, df_buffer, df_size);
                 break;
            case NOT_APPLICABLE:
                 break;
            case NUMERIC:
                 NumericOnly(ds, df_buffer, df_size);
                 break;
            case REPLACE_STRING:
                 ReplaceString(ds, df_buffer, df_size, df_replace);
                 break;
            case SPACES:
                 SpacesOnly(ds, df_buffer, df_size);
                 break;
            case ZERO_LENGTH:
                 ZeroLength(ds, df_buffer, df_size);
                 break;
            default:
                 break;
        }

        /*
        ** Write field string
        */
        if (strlen(df_buffer) > 0) {
            if (DelimitFileWriteString(ds, df_buffer) != EXIT_SUCCESS) {
                return (EXIT_FAILURE);
            }
        }

        /*
        ** Write field quote
        */
        if (DelimitWriteFieldQuote(ds) != EXIT_SUCCESS) {
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

/*
** Delimit add field count
*/
void DelimitAddFieldCount(delimit_specifications_t *ds) {
    ds->fields.count++;
}

/*
** Delimit add field maximum size
*/
void DelimitAddFieldMaxSize(delimit_specifications_t *ds, size_t size) {
    if (size) {
        ds->fields.max_size = ds->fields.max_size + size;
    }
}

/*
** Delimit add field maximum record size
*/
void DelimitAddFieldMaxRecordSize(delimit_specifications_t *ds, size_t size) {
    if (size) {
        ds->fields.max_record_size = ds->fields.max_record_size + size;
    }
}

/*
** Delimit set comma
*/
void DelimitSetComma(delimit_specifications_t *ds, bool_c_t b) {
    ds->delimiters.comma = b;
}

/*
** Delimit set tab
*/
void DelimitSetTab(delimit_specifications_t *ds, bool_c_t b) {
    ds->delimiters.tab = b;
}

/*
** Delimit set space
*/
void DelimitSetSpace(delimit_specifications_t *ds, bool_c_t b) {
    ds->delimiters.space = b;
}

/*
** Delimit set single
*/
void DelimitSetSingle(delimit_specifications_t *ds, bool_c_t b) {
    ds->delimiters.single_quote = b;
}

/*
** Delimit set double
*/
void DelimitSetDouble(delimit_specifications_t *ds, bool_c_t b) {
    ds->delimiters.double_quote = b;
}

/*
** Delimit set unique
*/
int DelimitSetUnique(delimit_specifications_t *ds, bool_c_t b, string_c_t value) {
    unsigned long number;

    /*
    ** Exit if no unique value
    */
    if (!value || strlen(value) < 1) {
        return (EXIT_SUCCESS);
    }

    /*
    ** Check and convert unique value into a number
    */
    if (strlen(value) > 3 && (value[1] == 'x' || value[1] == 'X')) {
        number = strtoul(value, NULL, 16);
        if (number != 0) {
            ds->delimiters.unique = b;
            ds->delimiters.unique_chr = (char)number;
            return (EXIT_SUCCESS);
        }
    }

    /*
    ** Unique value is a bad hexadecimal number
    */
    printf("error-> %s\n", error_messages_tbl[DE_CODE00].message);
    return (EXIT_FAILURE);
}

/*
** Alphabetic only
*/
static string_c_t AlphabeticOnly(delimit_specifications_t *ds, string_c_t s, size_t size) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        if (*s == '\0') {
            *s = ds->replacements.character;
        }
        if (!isalpha((int)*s)) {
            *s = ds->replacements.character;
        }
        s++;
    }
    return (sp);
}

/*
** Alphanumeric only
*/
static string_c_t AlphabeticNumericOnly(delimit_specifications_t *ds, string_c_t s, size_t size) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        if (*s == '\0') {
            *s = ds->replacements.character;
        }
        if (!isalnum((int)*s)) {
            *s = ds->replacements.character;
        }
        s++;
    }
    return (sp);
}

/*
** Numeric only
*/
static string_c_t NumericOnly(delimit_specifications_t *ds, string_c_t s, size_t size) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        if (*s == '\0') {
            *s = ds->replacements.number;
        }
        if (!isdigit((int)*s)) {
            *s = ds->replacements.number;
        }
        s++;
    }
    return (sp);
}

/*
** Zero length
*/
static string_c_t ZeroLength(delimit_specifications_t *ds, string_c_t s, size_t size) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        *s = '\0';
        s++;
    }
    return (sp);
}

/*
** Spaces only
*/
static string_c_t SpacesOnly(delimit_specifications_t *ds, string_c_t s, size_t size) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        if (*s == '\0') {
            *s = _SPC;
        }
        if (!isspace((int)*s)) {
            *s = _SPC;
        }
        s++;
    }
    return (sp);
}

/*
** Replace string
*/
static string_c_t ReplaceString(delimit_specifications_t *ds, string_c_t s, size_t size, string_c_t r) {
    string_c_t sp = s;
    size_t i = 0;

    for (i = 0; i < size; i++) {
        *s = r[i];
        s++;
    }
    return (sp);
}
