#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "output.h"

enum ErrorCode output_strings(FILE** const output_file, char* const * const strings, 
                              const size_t strings_size)
{
    assert(output_file);
    assert(*output_file);
    assert(strings);
    assert(strings_size);

    if (fputs("==================STRINGS OUTPUT====================\n\n", *output_file) < 0)
    {
        perror("Can't puts header into output file");
        return ERROR_CODE_FAILURE;
    }

    for (size_t ind = 0; ind < strings_size; ++ind)
    {
        if (fputs(strings[ind], *output_file) < 0)
        {
            perror("Can't puts strings into output file");
            return ERROR_CODE_FAILURE;
        }
        if (fputs("\n", *output_file) < 0)
        {
            perror("Can't puts '\\n' into output file");
            return ERROR_CODE_FAILURE;
        }
    }

    return ERROR_CODE_SUCCESS;
}

enum ErrorCode output_text(FILE** const output_file, char* const text, const size_t text_size)
{
    assert(output_file);
    assert(*output_file);
    assert(text);
    assert(text_size);

    if (fputs("==================TEXT OUTPUT====================\n\n", *output_file) < 0)
    {
        perror("Can't puts header into output file");
        return ERROR_CODE_FAILURE;
    }

    for (const char* string_ptr = text;
         (size_t)(string_ptr - text) < text_size;
         string_ptr = strchr(string_ptr, '\0') + 1)
    {
        if (fputs(string_ptr, *output_file) < 0)
        {
            perror("Can't puts text into output file");
            return ERROR_CODE_FAILURE;
        }
        if (fputs("\n", *output_file) < 0)
        {
            perror("Can't puts '\\n' into output file");
            return ERROR_CODE_FAILURE;
        }
    }

    return ERROR_CODE_SUCCESS;
}
