#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mstrcmp.h"

static int strcmp_alnum(const char* first_str, const char* second_str);
static void skip_nalnum(const char** const string_ptr); 


int strcmp_alnum_wrapper(const void* first_str, const void* second_str)
{
    assert(first_str);
    assert(second_str);

    return strcmp_alnum(*(char* const*)first_str, *(char* const*)second_str);
}


static int strcmp_alnum(const char* first_str, const char* second_str)
{
    assert(first_str);
    assert(second_str);

    for (; *first_str != '\0' && *second_str != '\0'; ++first_str, ++second_str)
    {
        skip_nalnum(&first_str);
        skip_nalnum(&second_str);

        if (*first_str == '\0' || *second_str == '\0')
            break;
        
        if (toupper(*first_str) != toupper(*second_str))
            return toupper(*first_str) < toupper(*second_str) ? -1 : 1;
    }

    if (toupper(*first_str) == toupper(*second_str)) return   0;
    else if (*first_str == '\0')                     return   1;
    else                                             return  -1;
}

static void skip_nalnum(const char** const string_ptr)
{
    assert(string_ptr);
    assert(*string_ptr);

    while (**string_ptr != '\0' && !isalnum(**string_ptr))
        ++*string_ptr;
}



static int r_strcmp_alnum(const char* first_str, const char* second_str);
static void r_skip_nalnum(const char* const string,  const char** const string_end_ptr);


int r_strcmp_alnum_wrapper(const void* first_str, const void* second_str)
{
    assert(first_str);
    assert(second_str);

    return r_strcmp_alnum(*(char* const *)first_str, *(char* const *)second_str);
}

static int r_strcmp_alnum(const char* first_str, const char* second_str)
{
    assert(first_str);
    assert(second_str);

    const char * first_end = strchr(first_str, '\0');
    const char * second_end = strchr(second_str, '\0');

    while (first_end != first_str && second_end != second_str)
    {
        --first_end;
        --second_end;

        r_skip_nalnum(first_str, &first_end);
        r_skip_nalnum(second_str, &second_end);

        if (toupper(*first_end) != toupper(*second_end))
            return toupper(*first_end) < toupper(*second_end) ? -1 : 1;
            
        if (first_end == first_str || second_end == second_str)
            break;
    }

    if (toupper(*first_end) == toupper(*second_end)) return   0;
    else if (first_end == first_str)                 return   1;
    else                                             return  -1;
}

static void r_skip_nalnum(const char* const string,  const char** const string_end_ptr)
{
    assert(string);
    assert(string_end_ptr);
    assert(*string_end_ptr);

    while (*string_end_ptr != string && !isalnum(**string_end_ptr))
        --*string_end_ptr;
}