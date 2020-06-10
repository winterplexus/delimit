/*
**  @(#)fio.h
**
**  delimit - file I/O functions for the text file delimiter
**  --------------------------------------------------------
**
**  copyright (c) 1993-2020 Code Construct Systems (CCS)
*/
#ifndef __FIO_H
#define __FIO_H

/*
** Function prototypes
*/
extern int DelimitFileOpen(delimit_specs_t *, bool_c_t);
extern int DelimitFileOpenInputAsOutput(delimit_specs_t *);
extern int DelimitFileRead(delimit_specs_t *, int *);
extern int DelimitFileUnread(delimit_specs_t *, int);
extern int DelimitFileReadString(delimit_specs_t *, string_c_t, size_t);
extern int DelimitFileWrite(delimit_specs_t *, int);
extern int DelimitFileWriteString(delimit_specs_t *, string_c_t);
extern int DelimitFileClose(delimit_specs_t *);
extern int DelimitFileCloseInput(delimit_specs_t *);
extern int DelimitFileCloseOutput(delimit_specs_t *);

#endif /* __FIO_H */
