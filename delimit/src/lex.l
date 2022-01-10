/*
**  @(#)lex.l
**
**  delimit - lexical scanner for the commands interpreter
**  ------------------------------------------------------
**
**  copyright (c) 1993-2022 Code Construct Systems (CCS)
*/
%option noyywrap

%{

#include "delimit.h"
#include "parse.h"

/*
** Local function prototypes
*/
static void yywarning(const char *);
static void yycomment(void);
static void yystring(void);
static void yynumber(void);

/*
** Source file line number counter
*/
#ifdef YY_LINE_NUMBER
int yylineno = 1;
#endif

%}

ws              [ \t]+
eol             [\r\n]+
comment         #.*
string          \"[^\"\n]*[\"\n]
number          [0-9]+

%%

{ws}            ;
{eol}           { yylineno++; }
{comment}       { yycomment(); }
{string}        { yystring(); return (T_STRING); }
{number}        { yynumber(); return (T_NUMBER); }
-               { return (T_DASH); }
alphabetic      { return (T_ALPHABETIC); }
alphanumeric    { return (T_ALPHANUMERIC); }
null            { return (T_NULL); }
numeric         { return (T_NUMERIC); }
printable       { return (T_PRINTABLE); }
remove          { return (T_REMOVE); }
spaces          { return (T_SPACES); }
.               { return (T_UNKNOWN); }

%%

#include <stdlib.h>

/*
** Process warnings
*/
static void yywarning(const char *message) {
    printf("warning-> format file (%d): %s\n", yylineno, message);
}

/*
** Process comments
*/
static void yycomment(void) {
    char c;

    while ((c = input()) != '\n' && c != 0) {
        ;
    }
    yylineno++;
}

/*
** Process strings
*/
static void yystring(void) {
    yylval.string = strdup(yytext + 1);
    if (yylval.string[yyleng - 2] != '\"') {
        yywarning("unterminated character string(\")");
    }
    else {
        yylval.string[yyleng - 2] = '\0';
    }
}

/*
** Process numbers
*/
static void yynumber(void) {
    size_t l;

    if ((strlen(yytext) < 2)  && (yytext[0] == '0')) {
        yylval.number = (long)0;
    }
    if ((l = atoi(yytext)) == 0) {
        yywarning("invalid unsigned integer");
    }
    yylval.number = l;
}
