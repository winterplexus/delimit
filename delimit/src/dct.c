/*
**  @(#)dct.c
**
**  delimit - file fields dictionary for the text file delimiter
**  ------------------------------------------------------------
**
**  copyright (c) 1993-2022 Code Construct Systems (CCS)
*/
#include "delimit.h"

/*
** Single linked list dictionary nodes
*/
static dictionary_t *dictionary_node_start = (dictionary_t *)NULL;
static dictionary_t *dictionary_node_end = (dictionary_t *)NULL;
static dictionary_t *dictionary_node = (dictionary_t *)NULL;

/*
** Store dictionary entry
*/
int StoreDictionaryEntry(const size_t size, format_t format, string_c_t replace, string_c_t name) {
    dictionary_t *node;

    /*
    ** Set parameters to empty string if parameters are null
    */
    if (!replace) {
        replace = (string_c_t)"";
    }
    if (!name) {
        name = (string_c_t)"";
    }

    /*
    ** Allocate memory for dictionary node and node entry string fields
    */
    node = (dictionary_t *)MemoryAllocate(sizeof(dictionary_t));
    if (node == (dictionary_t *)NULL) {
        return (EXIT_FAILURE);
    }
    node->replace = (string_c_t)MemoryAllocate((long)strlen(replace) + 1);
    if (node->replace == (string_c_t)NULL) {
        return (EXIT_FAILURE);
    }
    node->name = (string_c_t)MemoryAllocate((long)strlen(name) + 1);
    if (node->name == (string_c_t)NULL) {
        return (EXIT_FAILURE);
    }

    /*
    ** Set pointer to next dictionary node to null and copy parameters to associated node entry fields
    */
    node->next = (dictionary_t *)NULL;
    node->size = size;
    node->format = format;

    /*
    ** Copy string parameters to associated node entry string fields
    */
    strcpy_p(node->replace, strlen(replace) + 1, replace, strlen(replace));
    strcpy_p(node->name, strlen(name) + 1, name, strlen(name));

    /*
    ** Link dictionary node to end node if end node is not null; otherwise set dictionary node as the end node
    */
    if (dictionary_node_end) {
        dictionary_node_end->next = node;
        dictionary_node_end = node;
    }
    else {
        dictionary_node_start = node;
        dictionary_node_end = dictionary_node_start;
    }
    return (EXIT_SUCCESS);
}

/*
** Set dictionary node to start node if start node is not null
*/
dictionary_entry_status_t SetStartDictionaryEntry(void) {
    if (dictionary_node_start) {
        dictionary_node = dictionary_node_start;
        return (ENTRY_FOUND);
    }
    else {
        return (ENTRY_EOF);
    }
}

/*
** Get start dictionary entry
*/
dictionary_entry_status_t GetStartDictionaryEntry(size_t *size, format_t *format, string_c_t replace, size_t replace_size, string_c_t name, size_t name_size) {
    dictionary_t *node;

    /*
    ** Exit if dictionary start node is null
    */
    if (!dictionary_node_start) {
        return (ENTRY_EOF);
    }

    /*
    ** Set parameters to empty string if parameters are null
    */
    if (!replace) {
        replace = (string_c_t)"";
    }
    if (!name) {
        name = (string_c_t)"";
    }

    /*
    ** Set dictionary node to start node
    */
    node = dictionary_node_start;

    /*
    ** Set dictionary current node to dictionary node's next node pointer
    */
    dictionary_node = node->next;

    /*
    ** Set parameters with associated node entry fields
    */
    *size = node->size;
    *format = node->format;

    /*
    ** Set string parameters with associated node entry string fields
    */
    strcpy_p(replace, replace_size, node->replace, strlen(node->replace));
    strcpy_p(name, name_size, node->name, strlen(node->name));

    /*
    ** Return dictionary entry status
    */
    if (!dictionary_node) {
        return (ENTRY_IS_LAST);
    }
    else {
        return (ENTRY_FOUND);
    }
}

/*
** Get next dictionary entry
*/
dictionary_entry_status_t GetNextDictionaryEntry(size_t *size, format_t *format, string_c_t replace, size_t replace_size, string_c_t name, size_t name_size) {
    dictionary_t *node;

    /*
    ** Exit if current node is null
    */
    if (!dictionary_node) {
        return (ENTRY_EOF);
    }

    /*
    ** Set parameters to empty string if parameters are null
    */
    if (!replace) {
        replace = (string_c_t)"";
    }
    if (!name) {
        name = (string_c_t)"";
    }

    /*
    ** Set dictionary node to current node.
    */
    node = dictionary_node;

    /*
    ** Set current node to dictionary node's next node pointer
    */
    dictionary_node = node->next;

    /*
    ** Set parameters with associated node entry fields
    */
    *size = node->size;
    *format = node->format;

    /*
    ** Set string parameters with associated node entry string fields
    */
    strcpy_p(replace, replace_size, node->replace, strlen(node->replace));
    strcpy_p(name, name_size, node->name, strlen(node->name));

    /*
    ** Return dictionary entry status
    */
    return (ENTRY_FOUND);
}

/*
** Print dictionary
*/
void PrintDictionary(void) {
    dictionary_t *node, *tmp = NULL;

    /*
    ** Print entry fields for each dictionary node in the linked list
    */
    for (node = dictionary_node_start; node; node = tmp) {
        tmp = node->next;
        printf("dictionary-> size: %4zu format: %d name: %64s\n", node->size, node->format, node->name);
    }
}

/*
** Free dictionary
*/
void FreeDictionary(void) {
    dictionary_t *node, *tmp = NULL;

    /*
    ** Free allocated memory for each node's entry string fields and the dictionary node itself in the linked list
    */
    for (node = dictionary_node_start; node; node = tmp) {
        tmp = node->next;
        MemoryFree((string_c_t)node->replace);
        MemoryFree((string_c_t)node->name);
        MemoryFree((dictionary_t *)node);
    }

    /*
    ** Set start and end nodes to null
    */
    dictionary_node_start = (dictionary_t *)NULL;
    dictionary_node_end = (dictionary_t *)NULL;
}