/*
**  @(#)port.h
**
**  delimit - portable functions
**  ----------------------------
**
**  copyright (c) 1993-2024 Code Construct Systems (CCS)
*/
#ifndef __PORT_H
#define __PORT_H

/*
** Function prototypes
*/
extern int memcpy_p(void *, size_t, const void *, size_t);
extern int strcpy_p(string_c_t, size_t, const string_c_t, size_t);
extern int strcat_p(string_c_t, size_t, const string_c_t, size_t);
extern int strfmt_p(string_c_t, size_t, const string_c_t, ...);
extern int strtok_p(string_c_t *, string_c_t, const string_c_t, string_c_t *);
extern int strerror_p(string_c_t, size_t, int);
extern int time_p(time_t *);
extern int localtime_p(time_t *, struct tm *);
extern int fopen_p(FILE **, const string_c_t, const string_c_t);
extern int fclose_p(FILE *);
extern int basename_p(const string_c_t, string_c_t *);
extern int tmpfile_p(FILE **);

#endif /* __PORT_H */
