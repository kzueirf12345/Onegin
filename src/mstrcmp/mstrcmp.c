#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mstrcmp.h"

static int strcmp_alnum(const char* first_str, const char* second_str);
static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr);


int strcmp_alnum_wrapper(const void* first_str, const void* second_str)
{
    assert(first_str);
    assert(second_str);

    return strcmp_alnum(first_str, second_str);
}


static int strcmp_alnum(const char* first_str, const char* second_str)
{
    assert(first_str);
    assert(second_str);


    for (; *first_str != '\0' && *second_str != '\0'; ++first_str, ++second_str)
    {
        skip_nalnum(&first_str, &second_str);

        if (*first_str == '\0' || *second_str == '\0')
            break;
        
        if (toupper(*first_str) != toupper(*second_str))
            return toupper(*first_str) < toupper(*second_str) ? -1 : 1;
    }

    if (toupper(*first_str) == toupper(*second_str)) return   0;
    if (*first_str == '\0')                          return   1;
    else                                             return  -1;
}

static void skip_nalnum(const char** const first_ptr_ptr, const char** const second_ptr_ptr) 
{
    assert(first_ptr_ptr);
    assert(second_ptr_ptr);
    assert(*first_ptr_ptr);
    assert(*second_ptr_ptr);

    while (**first_ptr_ptr != '\0' && !isalnum(**first_ptr_ptr))
        ++*first_ptr_ptr;

    while (**second_ptr_ptr != '\0' && !isalnum(**second_ptr_ptr))
        ++*second_ptr_ptr;
}



static int rstrcmp_alnum(const char* first_str, const char* second_str);
static void rskip_nalnum(const char* const first_str,  const char** const first_end_ptr, 
                         const char* const second_str, const char** const second_end_ptr);


int rstrcmp_alnum_wrapper(const void* first_str, const void* second_str)
{
    assert(first_str);
    assert(second_str);

    return rstrcmp_alnum(first_str, second_str);
}

static int rstrcmp_alnum(const char* first_str, const char* second_str)
{
    assert(first_str);
    assert(second_str);

    const char * first_end = strchr(first_str, '\0');
    const char * second_end = strchr(second_str, '\0');

    while (first_end != first_str && second_end != second_str)
    {
        --first_end;
        --second_end;

        rskip_nalnum(first_str, &first_end, second_str, &second_end);

        if (toupper(*first_end) != toupper(*second_end))
            return toupper(*first_end) < toupper(*second_end) ? -1 : 1;
            
        if (first_end == first_str || second_end == second_str)
            break;
    }

    if (toupper(*first_end) == toupper(*second_end)) return   0;
    if (first_end == first_str)                      return   1;
    else                                             return  -1;
}

static void rskip_nalnum(const char* const first_str,  const char** const first_end_ptr, 
                         const char* const second_str, const char** const second_end_ptr)
{
    assert(first_end_ptr);
    assert(second_end_ptr);
    assert(*first_end_ptr);
    assert(*second_end_ptr);
    assert(first_str);
    assert(second_str);

    while (*first_end_ptr != first_str && !isalnum(**first_end_ptr))
        --*first_end_ptr;

    while (*second_end_ptr != second_str && !isalnum(**second_end_ptr))
        --*second_end_ptr;
}