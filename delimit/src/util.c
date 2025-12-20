/*
**  @(#)util.c
**
**  delimit - utility functions for the text file delimiter
**  -------------------------------------------------------
**
**  copyright (c) 1993-2025 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Memory allocate
*/
void *MemoryAllocate(const long size) {
    void *address;

    /*
    ** Allocate heap memory
    */
    address = (void *)malloc(size);
    if (address == NULL) {
        printf("error-> memory allocation failed (%d)\n", errno);
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    **  Fill allocated heap memory with nulls.
    */
    memset(address, 0, size);

    /*
    ** Print debug heap memory allocation parameters
    */
#ifdef _DEBUG_MEMORY
#ifdef _FORMAT_P_SPECIFIER
    printf("%p: MEMORY DEBUG: MemoryAllocate(%ld)\n", address, size);
#else
    printf("%x: MEMORY DEBUG: MemoryAllocate(%ld)\n", address, size);
#endif
#endif

    /*
    ** Return allocated heap memory address
    */
    return (address);
}

/*
** Free memory
*/
void MemoryFree(void *address) {
    /*
    ** Print debug heap memory free parameters
    */
#ifdef _DEBUG_MEMORY
#ifdef _FORMAT_P_SPECIFIER
    printf("%p: MEMORY DEBUG: MemoryFree(address)\n", address);
#else
    printf("%x: MEMORY DEBUG: MemoryFree(address)\n", address);
#endif
#endif

    /*
    ** Free heap memory if address is not null
    */
    if (address) {
        free(address);
    }
}

/*
** File copy
*/
void FileCopy(FILE *ifp, FILE *ofp) {
    unsigned char *buffer;
    char message[BUFSIZ];
    size_t count = 0;

    /*
    ** Allocate memory for I/O buffer
    */
    buffer = (unsigned char *)MemoryAllocate(_IO_BUFFER_SIZE);
    if (buffer == NULL) {
        return;
    }

    /*
    ** Process input file until end of file
    */
    while (!feof(ifp)) {
        /*
        ** Read a block of data from input file into I/O buffer
        */
        count = fread(buffer, sizeof(char), _IO_BUFFER_SIZE, ifp);
        if (ferror(ifp)) {
            strerror_p(message, sizeof(message), errno);
            printf("error-> unable to read from input file: %*s\n", BUFSIZ, message);
            break;
        }

        /*
        ** Write a block of data to output file from I/O buffer
        */
        fwrite(buffer, sizeof(char), count, ofp);
        fflush(ofp);
        if (ferror(ofp)) {
            strerror_p(message, sizeof(message), errno);
            printf("error-> unable to write to output file: %*s\n", BUFSIZ, message);
            break;
        }
    }

    /*
    ** Free I/O buffer allocated memory
    */
    MemoryFree((string_c_t)buffer);
}