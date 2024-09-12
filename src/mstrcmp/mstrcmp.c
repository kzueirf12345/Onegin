#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "mstrcmp.h"


static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr);


int strcmp_alnum(const char* const first_str, const char* const second_str, 
                           const bool is_test_mod)
{
    assert(first_str);
    assert(second_str);

    const char* first_ptr = first_str;
    const char* second_ptr = second_str;
    for (; *first_ptr != '\0' && *second_ptr != '\0'; ++first_ptr, ++second_ptr)
    {
        if (!is_test_mod)
        {
            skip_nalnum(&first_ptr, &second_ptr);

            if (*first_ptr == '\0' || *second_ptr == '\0')
                break;
        }
        
        if (*first_ptr != *second_ptr)
            return *first_ptr < *second_ptr ? -1 : 1;
    }

    if (*first_ptr == *second_ptr) return  0;
    if (*first_ptr == '\0')        return -1;
    else                           return  1;
}


static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr) 
{
    while (**first_ptr_ptr != '\0' && !isalnum(**first_ptr_ptr))
        ++*first_ptr_ptr;

    while (**second_ptr_ptr != '\0' && !isalnum(**second_ptr_ptr))
        ++*second_ptr_ptr;
}
