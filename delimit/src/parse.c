#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 10 "parse.y"

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

#line 26 "parse.y"
typedef union {
       string_c_t string;
       size_t number;
} YYSTYPE;
#line 32 "y.tab.c"
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
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    3,    3,    1,    2,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,
};
short yylen[] = {                                         2,
    0,    1,    1,    2,    1,    1,    1,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,
};
short yydefred[] = {                                      0,
    6,    7,    0,    0,    0,    3,    5,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    4,    8,    9,   10,
   11,   12,   13,   14,   15,   18,   19,   16,   17,   20,
   21,   22,   23,   24,   25,
};
short yydgoto[] = {                                       3,
   16,    4,    5,    6,
};
short yysindex[] = {                                   -248,
    0,    0,    0, -257, -248,    0,    0, -246, -245, -242,
 -241, -228, -227, -224, -223, -220,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
short yyrindex[] = {                                      1,
    0,    0,    0,    0,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   12,    0,    0,   35,
};
#define YYTABLESIZE 40
short yytable[] = {                                       7,
    1,    8,    9,   10,   11,   12,   13,   14,   15,    1,
    7,    7,   18,   20,    7,    7,   22,   24,    2,   19,
   21,   23,   25,   27,   29,   31,   33,   35,    7,    7,
   26,   28,    7,    7,   30,   32,    7,    2,   34,   17,
};
short yycheck[] = {                                     257,
    0,  259,  260,  261,  262,  263,  264,  265,  266,  258,
  257,  257,  259,  259,  257,  257,  259,  259,  267,    8,
    9,   10,   11,   12,   13,   14,   15,   16,  257,  257,
  259,  259,  257,  257,  259,  259,  257,    0,  259,    5,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 268
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_STRING","T_NUMBER","T_DASH",
"T_ALPHABETIC","T_ALPHANUMERIC","T_NULL","T_NUMERIC","T_PRINTABLE","T_REMOVE",
"T_SPACES","T_TERM","T_UNKNOWN",
};
char *yyrule[] = {
"$accept : session",
"session :",
"session : commands",
"commands : command",
"commands : commands command",
"lstring : T_STRING",
"lnumber : T_NUMBER",
"command : T_TERM",
"command : lnumber T_DASH T_DASH",
"command : lnumber T_DASH lstring",
"command : lnumber T_ALPHABETIC T_DASH",
"command : lnumber T_ALPHABETIC lstring",
"command : lnumber T_ALPHANUMERIC T_DASH",
"command : lnumber T_ALPHANUMERIC lstring",
"command : lnumber T_NULL T_DASH",
"command : lnumber T_NULL lstring",
"command : lnumber T_PRINTABLE T_DASH",
"command : lnumber T_PRINTABLE lstring",
"command : lnumber T_NUMERIC T_DASH",
"command : lnumber T_NUMERIC lstring",
"command : lnumber T_REMOVE T_DASH",
"command : lnumber T_REMOVE lstring",
"command : lnumber T_SPACES T_DASH",
"command : lnumber T_SPACES lstring",
"command : lnumber lstring T_DASH",
"command : lnumber lstring lstring",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 145 "parse.y"

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
#line 286 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 5:
#line 62 "parse.y"
{ yyval.string = yyvsp[0].string; }
break;
case 6:
#line 66 "parse.y"
{ yyval.number = yyvsp[0].number; }
break;
case 8:
#line 73 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, NO_ACTION, (string_c_t )NULL); }
break;
case 9:
#line 77 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, NO_ACTION, yyvsp[0].string); }
break;
case 10:
#line 81 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ALPHABETIC, (string_c_t )NULL); }
break;
case 11:
#line 85 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ALPHABETIC, yyvsp[0].string); }
break;
case 12:
#line 89 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ALPHANUMERIC, (string_c_t )NULL); }
break;
case 13:
#line 93 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ALPHANUMERIC, yyvsp[0].string); }
break;
case 14:
#line 97 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ZERO_LENGTH, (string_c_t )NULL); }
break;
case 15:
#line 101 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, ZERO_LENGTH, yyvsp[0].string); }
break;
case 16:
#line 105 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, PRINTABLE, (string_c_t )NULL); }
break;
case 17:
#line 109 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, PRINTABLE, yyvsp[0].string); }
break;
case 18:
#line 113 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, NUMERIC, (string_c_t )NULL); }
break;
case 19:
#line 117 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, NUMERIC, yyvsp[0].string); }
break;
case 20:
#line 121 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, REMOVE_STRING, (string_c_t )NULL); }
break;
case 21:
#line 125 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, REMOVE_STRING, yyvsp[0].string); }
break;
case 22:
#line 129 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, SPACES, (string_c_t )NULL); }
break;
case 23:
#line 133 "parse.y"
{ StoreFormat(dsp, yyvsp[-2].number, SPACES, yyvsp[0].string); }
break;
case 24:
#line 137 "parse.y"
{ StoreFormatReplaceString(dsp, yyvsp[-2].number, yyvsp[-1].string, (string_c_t )NULL); }
break;
case 25:
#line 141 "parse.y"
{ StoreFormatReplaceString(dsp, yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].string); }
break;
#line 507 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
