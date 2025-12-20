/*
**  @(#)interp.h
**
**  delimit - commands interpreter
**  ------------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
*/
#ifndef __INTERP_H
#define __INTERP_H

/*
** Lexical scanner standard input file pointer
*/
extern FILE *yyin;

/*
** Source line number counter
*/
extern int yylineno;

/*
** Function prototypes
*/
extern int yylex(void);
extern int yyparse(void);
extern int yyparseinit(delimit_specifications_t *);
extern int yylex_destroy(void);

#endif /* __INTERP_H */