#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "mstrcmp.h"


int mstrcmp(const char* const first_str, const char* const second_str, 
                           const bool is_test_mod)
{
    assert(first_str);
    assert(second_str);

    size_t first_index = 0;
    size_t second_index = 0;
    for (; first_str[first_index] != '\0' && second_str[second_index] != '\0';
         ++first_index, ++second_index)
    {
        if (!is_test_mod)
        {
            while (first_str[first_index] != '\0' && !isalnum(first_str[first_index]))
                ++first_index;

            while (second_str[second_index] != '\0' && !isalnum(second_str[second_index]))
                ++second_index;

            if (first_str[first_index] == '\0' || second_str[second_index] == '\0')
                break;
        }
        
        if (first_str[first_index] != second_str[second_index])
            return first_str[first_index] < second_str[second_index] ? -1 : 1;
    }

    return first_index == second_index
           ? 0
           : (first_str[first_index] == '\0' ? -1 : 1);
}
