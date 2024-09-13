#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "mstrcmp.h"


static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr);


int strcmp_alnum(const char* first_str, const char* second_str)
{
    assert(first_str);
    assert(second_str);

    // fprintf(stderr, "first: %s\nsecond: %s \n\n", first_str, second_str);

    for (; *first_str != '\0' && *second_str != '\0'; ++first_str, ++second_str)
    {
        skip_nalnum(&first_str, &second_str);
        
        if (*first_str != *second_str)
            return *first_str < *second_str ? -1 : 1;
    }

    if (*first_str == *second_str) return  0;
    if (*first_str == '\0')        return -1;
    else                           return  1;
}



int strcmp_alnum_wrapper(const void* first_str, const void* second_str)
{
    return strcmp_alnum(first_str, second_str);
}


static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr) 
{
    while (**first_ptr_ptr != '\0' && !isalnum(**first_ptr_ptr))
        ++*first_ptr_ptr;

    while (**second_ptr_ptr != '\0' && !isalnum(**second_ptr_ptr))
        ++*second_ptr_ptr;
}
