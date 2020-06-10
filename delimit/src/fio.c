/*
**  @(#)fio.c
**
**  delimit - file I/O functions for the text file delimiter
**  --------------------------------------------------------
**
**  copyright (c) 1993-2020 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Local function prototypes
*/
static int CheckFileModeType(const string_c_t);
static int OpenInput(delimit_specs_t *);
static int OpenOutput(delimit_specs_t *);
static int OpenOutputTemporaryFile(delimit_specs_t *);
static int OpenInputAsOutput(delimit_specs_t *);
static int CloseInput(delimit_specs_t *);
static int CloseOutput(delimit_specs_t *);

/*
** Open files for text file delimiter
*/
int DelimitFileOpen(delimit_specs_t *ds, bool_c_t use_temporary) {
    /*
    ** Open input file after checking file mode type
    */
    if (ds->input.name && strlen(ds->input.name) > 0) {
        if (CheckFileModeType(ds->input.name) != EXIT_SUCCESS) {
            return (EXIT_FAILURE);
        }
        if (OpenInput(ds) != EXIT_SUCCESS) {
            return (EXIT_FAILURE);
        }
    }

    /*
    ** Open output file or, if output file name is missing, open output temporary file
    */
    if (ds->output.name && strlen(ds->output.name) > 0) {
        if (OpenOutput(ds) != EXIT_SUCCESS) {
            return (EXIT_FAILURE);
        }
    }
    else {
        if (use_temporary) {
            if (OpenOutputTemporaryFile(ds) != EXIT_SUCCESS) {
                return (EXIT_FAILURE);
            }
        }
    }
    return (EXIT_SUCCESS);
}

/*
** Open input file as output for text file delimiter
*/
int DelimitFileOpenInputAsOutput(delimit_specs_t *ds) {
    return (OpenInputAsOutput(ds));
}

/*
** Read character from input file for text file delimiter
*/
int DelimitFileRead(delimit_specs_t *ds, int *c) {
    /*
    ** Read character from input file
    */
    *c = fgetc(ds->input.fp);

    /*
    ** Check if end of file
    */
    if (feof(ds->input.fp)) {
        ds->input.io_state = IO_EOF;
    }

    /*
    ** Check if read error
    */
    if (ferror(ds->input.fp)) {
        perror(ds->input.name);
        ds->input.io_state = IO_READ_ERROR;
        return (EXIT_FAILURE);
    }

    /*
    ** Increment input file counter if not end of file or read error
    */
    if (ds->input.io_state == IO_OK) {
        ds->input.counter++;
    }
    return (EXIT_SUCCESS);
}

/*
** Unread character to input file for text file delimiter
*/
int DelimitFileUnread(delimit_specs_t *ds, int c) {
    /*
    ** Unread character and decrement input file counter if not end of file or read error
    */
    if (ds->input.io_state == IO_OK) {
        ungetc(c, ds->input.fp);
        ds->input.counter--;
    }
    return (EXIT_SUCCESS);
}

/*
** Read a string from input file for text file delimiter
*/
int DelimitFileReadString(delimit_specs_t *ds, string_c_t s, size_t size) {
    /*
    ** Read string from input file
    */
    memset(s, 0, size + 1);
    fread(s, size, 1, ds->input.fp);

    /*
    ** Check if end of file
    */
    if (strlen(s) < 1 && feof(ds->input.fp)) {
        ds->input.io_state = IO_EOF;
        return (EXIT_SUCCESS);
    }

    /*
    ** Check if read error
    */
    if (ferror(ds->input.fp)) {
        perror(ds->input.name);
        ds->input.io_state = IO_READ_ERROR;
        return (EXIT_FAILURE);
    }

    /*
    ** Increment input file counter by string size if not end of file or read error
    */
    if (ds->input.io_state == IO_OK) {
        ds->input.counter = ds->input.counter + size;
    }
    return (EXIT_SUCCESS);
}

/*
** Write character to output file for text file delimiter
*/
int DelimitFileWrite(delimit_specs_t *ds, int c) {
    /*
    ** Write character to output file
    */
    fputc(c, ds->output.fp);
    fflush(ds->output.fp);

    /*
    ** Increment output file counter if not write error
    */
    if (!ferror(ds->output.fp)) {
        ds->output.counter++;
    }
    else {
        perror(ds->output.name);
        ds->output.io_state = IO_WRITE_ERROR;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/*
** Write a string to output file for text file delimiter
*/
int DelimitFileWriteString(delimit_specs_t *ds, string_c_t s) {
    /*
    ** Write string to output file
    */
    fwrite(s, sizeof(char), strlen(s), ds->output.fp);
    fflush(ds->output.fp);

    /*
    ** Increment output file counter by string size if not write error
    */
    if (!ferror(ds->output.fp)) {
        ds->output.counter++;
    }
    else {
        perror(ds->output.name);
        ds->output.io_state = IO_WRITE_ERROR;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/*
** Close files for text file delimiter
*/
int DelimitFileClose(delimit_specs_t *ds) {
    CloseInput(ds);
    CloseOutput(ds);
    return (EXIT_SUCCESS);
}

/*
** Close input file for text file delimiter
*/
int DelimitFileCloseInput(delimit_specs_t *ds) {
    return (CloseInput(ds));
}

/*
** Close output file for text file delimiter
*/
int DelimitFileCloseOutput(delimit_specs_t *ds) {
    return (CloseOutput(ds));
}

/*
** Check file mode type
*/
static int CheckFileModeType(const string_c_t filename) {
    struct stat st;
    int status = EXIT_FAILURE;

    /*
    ** Get file status
    */
    if (stat(filename, &st) < 0) {
        perror(filename);
        return (EXIT_FAILURE);
    }

    /*
    ** Check file mode type
    */
    switch (st.st_mode & S_IFMT) {
        case S_IFREG:
             status = EXIT_SUCCESS;
             break;
        default:
             printf("error-> unusable file type (not a regular file)\n");
             break;
    }

    /*
    ** Return status of file mode type
    */
    return (status);
}

/*
** Open input file
*/
static int OpenInput(delimit_specs_t *ds) {
    /*
    ** Set input file entry fields to default values
    */
    ds->input.io_state = IO_OK;
    ds->input.fp = NULL;
    ds->input.opened = FALSE;
    ds->input.counter = 0;
    ds->input.line_count = ds->input.counter;

    /*
    ** Open input file
    */
    if (ds->input.name && strlen(ds->input.name) > 0) {
        fopen_p(&ds->input.fp, ds->input.name, (string_c_t)_F_RO_BIN);
        if (ds->input.fp == NULL) {
            perror(ds->input.name);
            return (EXIT_FAILURE);
        }
        ds->input.opened = TRUE;
    }
    return (EXIT_SUCCESS);
}

/*
** Open output file
*/
static int OpenOutput(delimit_specs_t *ds) {
    /*
    ** Set output file entry fields to default values
    */
    ds->output.io_state = IO_OK;
    ds->output.fp = NULL;
    ds->output.opened = FALSE;
    ds->output.counter = 0;
    ds->output.line_count = ds->output.counter;

    /*
    ** Open output file
    */
    if (ds->output.name && strlen(ds->output.name) > 0) {
        fopen_p(&ds->output.fp, ds->output.name, (string_c_t)_F_RW_BIN);
        if (ds->output.fp == NULL) {
            perror(ds->output.name);
            return (EXIT_FAILURE);
        }
        ds->output.opened = TRUE;
    }
    return (EXIT_SUCCESS);
}

/*
** Open output temporary file
*/
static int OpenOutputTemporaryFile(delimit_specs_t *ds) {
    /*
    ** Set output temporary file entry fields to default values
    */
    ds->output.io_state = IO_OK;
    ds->output.fp = NULL;
    ds->output.opened = FALSE;
    ds->output.counter = 0;
    ds->output.line_count = ds->output.counter;

    /*
    ** Create and open output temporary file
    */
    tmpfile_p(&ds->output.fp);
    if (ds->output.fp == NULL) {
        perror("unable to create and open temporary file");
        return (EXIT_FAILURE);
    }
    ds->input.opened = TRUE;
    return (EXIT_SUCCESS);
}

/*
** Open input file as output file
*/
static int OpenInputAsOutput(delimit_specs_t *ds) {
    /*
    ** Set input file entry fields to default values
    */
    ds->input.io_state = IO_OK;
    ds->input.fp = NULL;
    ds->input.opened = FALSE;

    /*
    ** Open input file with both read and write capability
    */
    if (ds->input.name && strlen(ds->input.name) > 0) {
        fopen_p(&ds->input.fp, ds->input.name, (string_c_t)_F_RW_BIN);
        if (ds->input.fp == NULL) {
            perror(ds->input.name);
            return (EXIT_FAILURE);
        }
    }
    ds->input.opened = TRUE;
    return (EXIT_SUCCESS);
}

/*
** Close input file
*/
static int CloseInput(delimit_specs_t *ds) {
    if (ds->input.opened == TRUE) {
        return (fclose_p(ds->input.fp));
    }
    return (EXIT_SUCCESS);
}

/*
** Close output file
*/
static int CloseOutput(delimit_specs_t *ds) {
    if (ds->output.opened == TRUE) {
        return (fclose_p(ds->output.fp));
    }
    return (EXIT_SUCCESS);
}
