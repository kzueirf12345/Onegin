#include <assert.h>

#include "output.h"

enum ErrorCode output_strings(FILE* file, char strings[MAX_STR_COUNT][MAX_STR_SIZE])
{
    assert(file);
    assert(strings);

    for (size_t string_ind = 0; string_ind < MAX_STR_COUNT; ++string_ind)
    {
        if (fputs(strings[string_ind], file) <= 0)
        {
            perror("Can't print string\n");
            return ERROR_CODE_FAILURE;
        }
    }

    return ERROR_CODE_SUCCES;
}