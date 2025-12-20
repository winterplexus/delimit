/*
**  @(#)util.h
**
**  delimit - utility functions for the text file delimiter
**  -------------------------------------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
*/
#ifndef __UTIL_H
#define __UTIL_H

/*
** Function prototypes
*/
extern void *MemoryAllocate(const long);
extern void MemoryFree(void *);
extern void FileCopy(FILE *, FILE *);

#endif /* __UTIL_H */