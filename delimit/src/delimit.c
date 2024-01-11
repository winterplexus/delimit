/*
**  @(#)delimit.c
**
**  delimit - delimit text file utility
**  -----------------------------------
**
**  copyright (c) 1993-2024 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Unwind buffer stack pointer
*/
jmp_buf unwind_buffer_sp;

/*
** Local function prototypes
*/
static void ProcessFiles(options_t *, delimit_specifications_t *);
static void OpenFiles(options_t *, delimit_specifications_t *);
static void ParseFormatFile(delimit_specifications_t *);
static void SetDelimiters(options_t *, delimit_specifications_t *);
static void CloseFiles(delimit_specifications_t *);
static void FreeLexicalBuffers(void);
static void OverWriteInputFile(options_t *, delimit_specifications_t *);
static void SetSystemSignals(void);
static void InterruptHandler(int);
static void DisplayTotals(options_t *, delimit_specifications_t *);

/*
** Delimit text file utility driver
*/
int main(int argc, string_c_t argv[]) {
    options_t opts;
    delimit_specifications_t ds;

    /*
    ** Set system signals and if stack was unwound then close files, free lexical buffers and exit
    */
    SetSystemSignals();
    if (setjmp(unwind_buffer_sp) != 0) {
        CloseFiles(&ds);
        FreeLexicalBuffers();
        return (EXIT_FAILURE);
    }

    /*
    ** Get options
    */
    GetOptions(argc, argv, &opts);

    /*
    ** Process input and output files
    */
    ProcessFiles(&opts, &ds);
}

/*
** Process files
*/
static void ProcessFiles(options_t *opts, delimit_specifications_t *ds) {
    /*
    ** Set defaults
    */
    DelimitSetDefaults(ds, opts->input, opts->output);

    /*
    ** Open files
    */
    OpenFiles(opts, ds);

    /*
    ** Parse format file
    */
    ParseFormatFile(ds);

    /*
    ** Set delimiters
    */
    SetDelimiters(opts, ds);

    /*
    ** Delimit file
    */
    DelimitFile(ds);

    /*
    ** Over-write input file
    */
    OverWriteInputFile(opts, ds);

    /*
    ** Display totals
    */
    DisplayTotals(opts, ds);

    /*
    ** Free dictionary
    */
    FreeDictionary();

    /*
    ** Close files
    */
    CloseFiles(ds);
}

/*
** Open files
*/
static void OpenFiles(options_t *opts, delimit_specifications_t *ds) {
    /*
    ** Open input and output files and if over-write option is true, open input file with both read and write capability
    */
    if (DelimitOpen(ds, opts->overwrite) != EXIT_SUCCESS) {
        DelimitClose(ds);
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Open format file for parser and if open failed then print error messsage and exit
    */
    fopen_p(&yyin, opts->format, (string_c_t)_F_RO);
    if (yyin == NULL) {
        printf("error-> unable to open format file: %s (%d)\n", opts->format, errno);
        EXIT_APPLICATION(EXIT_FAILURE);
    }
}

/*
** Parse format file
*/
static void ParseFormatFile(delimit_specifications_t *ds) {
    /*
    ** Parser initialization
    */
    yyparseinit(ds);

    /*
    ** Parse format file and if the parse failed then close files and exit
    */
    if (yyparse()) {
        CloseFiles(ds);
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Print dictionary if required
    */
#ifdef _DEBUG_DICTIONARY
    PrintDictionary();
#endif
}

/*
** Set delimiters
*/
static void SetDelimiters(options_t *opts, delimit_specifications_t *ds) {
    /*
    ** Set unique character delimiter and if set operation failed then close files and exit
    */
    if (DelimitSetUnique(ds, opts->unique, opts->unique_delimiter) != EXIT_SUCCESS) {
        DelimitClose(ds);
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Set other delimiters
    */
    DelimitSetComma(ds, opts->comma);
    DelimitSetTab(ds, opts->tab);
    DelimitSetSpace(ds, opts->space);
    DelimitSetSingle(ds, opts->single_quote);
    DelimitSetDouble(ds, opts->double_quote);
}

/*
** Close files
*/
static void CloseFiles(delimit_specifications_t *ds) {
    /*
    ** Flush and close delimiter file
    */
    fflush(yyin);
    fclose_p(yyin);

    /*
    ** Close input and output files
    */
    DelimitFileClose(ds);
}

/*
** Free lexical buffers
*/
static void FreeLexicalBuffers(void) {
    /*
    ** Free lexical scanner buffers
    */
#ifdef _FREE_LEXICAL_BUFFERS
    yylex_destroy();
#endif
}

/*
** Over-write input file
*/
static void OverWriteInputFile(options_t *opts, delimit_specifications_t *ds) {
    if (opts->overwrite) {
        /*
        ** Close input and output temporary files
        */
        DelimitFileCloseInput(ds);
        if (DelimitFileOpenInputAsOutput(ds) != EXIT_SUCCESS) {
            return;
        }

        /*
        ** Rewind output file and write output file over input file
        */
        rewind(ds->output.fp);
        FileCopy(ds->output.fp, ds->input.fp);
    }
}

/*
** Set system signals
*/
static void SetSystemSignals(void) {
    signal(SIGINT, InterruptHandler);
    signal(SIGTERM, InterruptHandler);
}

/*
** Interrupt handler
*/
static void InterruptHandler(int signal_number) {
    printf("signal detected (%d)!\n", signal_number);

    /*
    ** Exit application
    */
    EXIT_APPLICATION(EXIT_SUCCESS);
}

/*
** Display totals
*/
static void DisplayTotals(options_t *opts, delimit_specifications_t *ds) {
    if (opts->statistics) {
        printf("statistics\n");
        printf("----------\n");
        printf("input file  ->  ");
        printf("total lines: %ld\t", ds->input.line_count);
        printf("total count: %ld\n", ds->input.counter);
        printf("output file ->  ");
        printf("total lines: %ld\t", ds->output.line_count);
        printf("total count: %ld\n", ds->output.counter);
    }
}
