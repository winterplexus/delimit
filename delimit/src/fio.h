/*
**  @(#)fio.h
**
**  delimit - file I/O functions for the text file delimiter
**  --------------------------------------------------------
**
**  copyright (c) 1993-2024 Code Construct Systems (CCS)
*/
#ifndef __FIO_H
#define __FIO_H

/*
** Function prototypes
*/
extern int DelimitFileOpen(delimit_specifications_t *, bool_c_t);
extern int DelimitFileOpenInputAsOutput(delimit_specifications_t *);
extern int DelimitWriteFieldDelimiter(delimit_specifications_t *);
extern int DelimitWriteFieldQuote(delimit_specifications_t *);
extern int DelimitFileRead(delimit_specifications_t *, int *);
extern int DelimitFileUnread(delimit_specifications_t *, int);
extern int DelimitFileReadString(delimit_specifications_t *, string_c_t, size_t);
extern int DelimitFileWrite(delimit_specifications_t *, int);
extern int DelimitFileWriteString(delimit_specifications_t *, string_c_t);
extern int DelimitFileClose(delimit_specifications_t *);
extern int DelimitFileCloseInput(delimit_specifications_t *);
extern int DelimitFileCloseOutput(delimit_specifications_t *);

#endif /* __FIO_H */
