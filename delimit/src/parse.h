#define T_STRING 257
#define T_NUMBER 258
#define T_DASH 259
#define T_ALPHABETIC 260
#define T_ALPHANUMERIC 261
#define T_NULL 262
#define T_NUMERIC 263
#define T_PRINTABLE 264
#define T_REMOVE 265
#define T_SPACES 266
#define T_TERM 267
#define T_UNKNOWN 268
typedef union {
       string_c_t string;
       size_t number;
} YYSTYPE;
extern YYSTYPE yylval;
