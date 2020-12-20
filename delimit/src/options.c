/*
**  @(#)options.c
**
**  delimit - command line options
**  ------------------------------
**
**  copyright (c) 1993-2021 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Local function prototypes
*/
static void GetOptionValues(int, string_c_t[], options_t *);
static void CheckOptionValues(options_t *);
static void SetDefaultOptions(options_t *);
static void StoreOptionArgument(int, string_c_t[], int, string_c_t, size_t);
static void StoreUniqueDelimiter(int, string_c_t[], int, options_t *);
static void DisplayUnknownOptionMessage(string_c_t);
static void DisplayVersion(int);
static void DisplayUsage(void);

/*
** Get command line options
*/
void GetOptions(int argc, string_c_t argv[], options_t *opts) {
    /*
    ** Set default options
    */
    SetDefaultOptions(opts);

    /*
    ** Display usage if no argument; otherwise get and check option values
    */
    if (argc == 1) {
        DisplayUsage();
    }
    else {
        GetOptionValues(argc, argv, opts);
        CheckOptionValues(opts);
    }
}

/*
** Get option values
*/
static void GetOptionValues(int argc, string_c_t argv[], options_t *opts) {
    int i;

    /*
    ** Process each command line option
    */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            StoreOptionArgument(argc, argv, ++i, opts->format, sizeof(opts->format) - 1);
        }
        else if (strcmp(argv[i], "-i") == 0) {
            StoreOptionArgument(argc, argv, ++i, opts->input, sizeof(opts->input) - 1);
        }
        else if (strcmp(argv[i], "-o") == 0) {
            StoreOptionArgument(argc, argv, ++i, opts->output, sizeof(opts->output) - 1);
        }
        else if (strcmp(argv[i], "-c") == 0) {
            opts->comma = TRUE;
        }
        else if (strcmp(argv[i], "-t") == 0) {
            opts->tab = TRUE;
        }
        else if (strcmp(argv[i], "-x") == 0) {
            opts->space = TRUE;
        }
        else if (strcmp(argv[i], "-s") == 0) {
            opts->single_quote = TRUE;
        }
        else if (strcmp(argv[i], "-d") == 0) {
            opts->double_quote = TRUE;
        }
        else if (strcmp(argv[i], "-u") == 0) {
            StoreUniqueDelimiter(argc, argv, ++i, opts);
        }
        else if (strcmp(argv[i], "-r") == 0) {
            opts->statistics = TRUE;
        }
        else if (strcmp(argv[i], "-w") == 0) {
            opts->overwrite = TRUE;
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion(argc);
        }
        else {
            DisplayUnknownOptionMessage(argv[i]);
        }
    }
}

/*
** Check option values
*/
static void CheckOptionValues(options_t *opts) {
    /*
    ** Check format file name option
    */
    if (strlen(opts->format) < 1) {
        printf("error-> format file name is missing\n");
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Check input file name option
    */
    if (strlen(opts->input) < 1) {
        printf("error-> input file name is missing\n");
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Check output file name option if overwrite option is false
    */
    if (strlen(opts->output) < 1) {
        if (opts->overwrite == FALSE) {
            printf("error-> output file name is missing\n");
            EXIT_APPLICATION(EXIT_FAILURE);
        }
    }
}

/*
** Set default options
*/
static void SetDefaultOptions(options_t *opts) {
    memset(opts->format, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(opts->input, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(opts->output, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(opts->unique_delimiter, 0, _MAX_UNIQUE_DELIMITER_SIZE + 1);
    opts->comma = FALSE;
    opts->tab = FALSE;
    opts->space = FALSE;
    opts->single_quote = FALSE;
    opts->double_quote = FALSE;
    opts->unique = FALSE;
    opts->statistics = FALSE;
    opts->overwrite = FALSE;
}

/*
** Store option argument
*/
static void StoreOptionArgument(int argc, string_c_t argv[], int i, string_c_t argument, size_t size) {
    if (argc < i || !argv[i]) {
        DisplayUsage();
    }
    assert(argv[i]);
    strcpy_p(argument, size, argv[i], size);
}

/*
** Store unique delimiter
*/
static void StoreUniqueDelimiter(int argc, string_c_t argv[], int i, options_t *opts) {
    if (argc < i || !argv[i]) {
        DisplayUsage();
    }
    if (opts->unique) {
        if (argv[i] && argv[0] != 0) {
            strcpy_p(opts->unique_delimiter, sizeof(opts->unique_delimiter), argv[i], strlen(argv[i]));
        }
    }
    else {
        opts->unique = TRUE;
        if (argv[i] && argv[0] != 0) {
            strcat_p(opts->unique_delimiter, sizeof(opts->unique_delimiter), argv[i], strlen(argv[i]));
        }
    }
}

/*
** Display unknown option message
*/
static void DisplayUnknownOptionMessage(string_c_t argument) {
    printf("error-> unknown option: %s\n", argument);
    EXIT_APPLICATION(EXIT_FAILURE);
}

/*
** Display version
*/
static void DisplayVersion(int argc) {
    printf("%s - delimit text file utility\n", _VERSION_PRODUCT);
    printf("%s\n\n", _VERSION_RELEASE);

    /*
    ** Exit application (if no other command line arguments)
    */
    if (argc == 2) {
        EXIT_APPLICATION(EXIT_SUCCESS);
    }
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _VERSION_PRODUCT);
    printf("where (options) include:\n");
    printf("  -f  [format file name]\n");
    printf("  -i  [input file name]\n");
    printf("  -o  [output file name]\n");
    printf("  -c  use comma field delimiter\n");
    printf("  -t  use tab field delimiter\n");
    printf("  -x  use space field delimiter\n");
    printf("  -s  use single quote delimiter\n");
    printf("  -d  use double quote delimiter\n");
    printf("  -u  [unique delimiter (0x00 hexadecimal number)]\n");
    printf("  -r  report statistics\n");
    printf("  -w  enable write over input file as output mode\n");
    printf("  -v  display version\n");

    /*
    ** Exit application
    */
    EXIT_APPLICATION(EXIT_SUCCESS);
}