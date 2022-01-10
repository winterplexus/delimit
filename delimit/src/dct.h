/*
**  @(#)dct.h
**
**  delimit - file fields dictionary for the text file delimiter
**  ------------------------------------------------------------
**
**  copyright (c) 1993-2022 Code Construct Systems (CCS)
*/
#ifndef __DCT_H
#define __DCT_H

/*
** Data dictionary entry status type
*/
typedef enum dictionary_entry_status_e {
        ENTRY_FOUND = 0,
        ENTRY_NOT_FOUND,
        ENTRY_IS_LAST,
        ENTRY_EOF
} dictionary_entry_status_t;

/*
** Data dictionary structure and type
*/
typedef struct dictionary_s {
        size_t size;
        format_t format;
        string_c_t replace;
        string_c_t name;
        struct dictionary_s *next;
} dictionary_t;

/*
** Function prototypes
*/
extern int StoreDictionaryEntry(const size_t, format_t, string_c_t, string_c_t);
extern dictionary_entry_status_t SetStartDictionaryEntry(void);
extern dictionary_entry_status_t GetStartDictionaryEntry(size_t *, format_t *, string_c_t, size_t, string_c_t, size_t);
extern dictionary_entry_status_t GetNextDictionaryEntry(size_t *, format_t *, string_c_t, size_t, string_c_t, size_t);
extern void PrintDictionary(void);
extern void FreeDictionary(void);

#endif /* __DCT_H */