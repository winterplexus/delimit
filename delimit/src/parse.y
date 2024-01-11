/*
**  @(#)parse.y
**
**  delimit - parser for the commands interpreter
**  ---------------------------------------------
**
**  copyright (c) 1993-2024 Code Construct Systems (CCS)
*/
%{

#include "delimit.h"

/*
** Local function prototypes
*/
static void StoreFormat(delimit_specifications_t *, size_t, format_t, string_c_t);
static void StoreFormatReplaceString(delimit_specifications_t *, size_t, string_c_t , string_c_t);

/*
** Pointer to text file delimiter specifications
*/
static delimit_specifications_t *dsp;

%}

%union {
       string_c_t string;
       size_t number;
}

%token <string> T_STRING
%token <number> T_NUMBER

%token T_DASH
%token T_ALPHABETIC
%token T_ALPHANUMERIC
%token T_NULL
%token T_NUMERIC
%token T_PRINTABLE
%token T_REMOVE
%token T_SPACES
%token T_TERM
%token T_UNKNOWN

%type  <string> lstring
%type  <number> lnumber

%start session

%%

session:
    |
    commands
    ;
commands
    : command
    | commands command
    ;
lstring
    : T_STRING
      { $$ = $1; }
    ;
lnumber
    : T_NUMBER
      { $$ = $1; }
    ;
command
    : T_TERM
    ;
command
    : lnumber T_DASH T_DASH
      { StoreFormat(dsp, $1, NO_ACTION, (string_c_t )NULL); }
    ;
command
    : lnumber T_DASH lstring
      { StoreFormat(dsp, $1, NO_ACTION, $3); }
    ;
command
    : lnumber T_ALPHABETIC T_DASH
      { StoreFormat(dsp, $1, ALPHABETIC, (string_c_t )NULL); }
    ;
command
    : lnumber T_ALPHABETIC lstring
      { StoreFormat(dsp, $1, ALPHABETIC, $3); }
    ;
command
    : lnumber T_ALPHANUMERIC T_DASH
      { StoreFormat(dsp, $1, ALPHANUMERIC, (string_c_t )NULL); }
    ;
command
    : lnumber T_ALPHANUMERIC lstring
      { StoreFormat(dsp, $1, ALPHANUMERIC, $3); }
    ;
command
    : lnumber T_NULL T_DASH
      { StoreFormat(dsp, $1, ZERO_LENGTH, (string_c_t )NULL); }
    ;
command
    : lnumber T_NULL lstring
      { StoreFormat(dsp, $1, ZERO_LENGTH, $3); }
    ;
command
    : lnumber T_PRINTABLE T_DASH
      { StoreFormat(dsp, $1, PRINTABLE, (string_c_t )NULL); }
    ;
command
    : lnumber T_PRINTABLE lstring
      { StoreFormat(dsp, $1, PRINTABLE, $3); }
    ;
command
    : lnumber T_NUMERIC T_DASH
      { StoreFormat(dsp, $1, NUMERIC, (string_c_t )NULL); }
    ;
command
    : lnumber T_NUMERIC lstring
      { StoreFormat(dsp, $1, NUMERIC, $3); }
    ;
command
    : lnumber T_REMOVE T_DASH
      { StoreFormat(dsp, $1, REMOVE_STRING, (string_c_t )NULL); }
    ;
command
    : lnumber T_REMOVE lstring
      { StoreFormat(dsp, $1, REMOVE_STRING, $3); }
    ;
command
    : lnumber T_SPACES T_DASH
      { StoreFormat(dsp, $1, SPACES, (string_c_t )NULL); }
    ;
command
    : lnumber T_SPACES lstring
      { StoreFormat(dsp, $1, SPACES, $3); }
    ;
command
    : lnumber lstring T_DASH
      { StoreFormatReplaceString(dsp, $1, $2, (string_c_t )NULL); }
    ;
command
    : lnumber lstring lstring
      { StoreFormatReplaceString(dsp, $1, $2, $3); }
    ;

%%

/*
** Parse error codes type
*/
typedef enum parse_error_codes_e {
        ER_CODE_00 = 0,
        ER_CODE_01,
        ER_CODE_02,
        ER_CODE_03,
        ER_CODE_04,
        ER_CODE_05,
        ER_CODE_06
} parse_error_codes_t;

/*
** Parse error message structure and parse error messages table
*/
static struct parse_error_messages_s {
        parse_error_codes_t code;
        char *message;
}
parse_error_messages_tbl[] = {
        { ER_CODE_00, "field size cannot be negative" },
        { ER_CODE_01, "field size is too small" },
        { ER_CODE_02, "field size is too large" },
        { ER_CODE_03, "field replacement string is too small" },
        { ER_CODE_04, "field replacement string is too large" },
        { ER_CODE_05, "field name is too small" },
        { ER_CODE_06, "field name is too large" }
};

/*
** Parser initialization
*/
int yyparseinit(delimit_specifications_t *ds) {
    dsp = ds;
}

/*
** Display error messages
*/
int yyerror(const string_c_t message) {
    printf("error-> format file (%d): %s\n", yylineno, message);
    EXIT_APPLICATION(EXIT_FAILURE);
}

/*
** Store format
*/
static void StoreFormat(delimit_specifications_t *ds, size_t size, format_t format, string_c_t name) {
    string_c_t replace = "";

    if (size < 0) {
        yyerror(parse_error_messages_tbl[ER_CODE_00].message);
    }
    if (size < 1) {
        yyerror(parse_error_messages_tbl[ER_CODE_01].message);
    }
    if (size > _MAX_FIELD_SIZE) {
        yyerror(parse_error_messages_tbl[ER_CODE_02].message);
    }
    if (name == NULL) {
        strcpy_p(name, strlen(name), "", sizeof(""));
    }
    else {
        if (strlen(name) < 1) {
            yyerror(parse_error_messages_tbl[ER_CODE_05].message);
        }
        if (strlen(name) > _MAX_FIELD_NAME_SIZE) {
            yyerror(parse_error_messages_tbl[ER_CODE_06].message);
        }
    }

    /*
    ** Store dictionary entry
    */
    if (StoreDictionaryEntry(size, format, replace, name) != EXIT_SUCCESS) {
        EXIT_APPLICATION(EXIT_FAILURE);
    }
}

/*
** Store format with replacement string
*/
static void StoreFormatReplaceString(delimit_specifications_t *ds, size_t size, string_c_t replace, string_c_t name) {
    format_t format = REPLACE_STRING;

    if (size < 0) {
        yyerror(parse_error_messages_tbl[ER_CODE_00].message);
    }
    if (size < 1) {
        yyerror(parse_error_messages_tbl[ER_CODE_01].message);
    }
    if (size > _MAX_FIELD_SIZE) {
        yyerror(parse_error_messages_tbl[ER_CODE_02].message);
    }
    if (replace == NULL) {
        strcpy_p(replace, strlen(replace), "", sizeof(""));
    }
    if (strlen(replace) < 1 || strlen(replace) < size) {
        yyerror(parse_error_messages_tbl[ER_CODE_03].message);
    }
    if (strlen(replace) > _MAX_FIELD_NAME_SIZE || strlen(replace) > size) {
        yyerror(parse_error_messages_tbl[ER_CODE_04].message);
    }
    if (name == NULL) {
        strcpy_p(name, strlen(name), "", sizeof(""));
    }
    else {
        if (strlen(name) < 1) {
            yyerror(parse_error_messages_tbl[ER_CODE_05].message);
        }
        if (strlen(name) > _MAX_FIELD_NAME_SIZE) {
            yyerror(parse_error_messages_tbl[ER_CODE_06].message);
        }
    }

    /*
    ** Store dictionary entry
    */
    if (StoreDictionaryEntry(size, format, replace, name) != EXIT_SUCCESS) {
        EXIT_APPLICATION(EXIT_FAILURE);
    }
}
