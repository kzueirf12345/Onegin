#include <assert.h>

#include "output.h"

enum ErrorCode output_string_ptrs(const char* const output_filename, char* const * const strings, 
                                  const size_t strings_size)
{
    assert(output_filename);
    assert(strings);
    assert(strings_size);

    FILE* output_file = fopen(output_filename, "ab");
    if (!output_file)
    {
        perror("Can't open output file");
        return -1;
    }

    for (size_t ind = 0; ind < strings_size; ++ind)
    {
        if (fputs(strings[ind], output_file) < 0)
        {
            perror("Can't puts strings into output file");
            return ERROR_CODE_FAILURE;
        }
        if (fputs("\n", output_file) < 0)
        {
            perror("Can't puts '\\n' into output file");
            return ERROR_CODE_FAILURE;
        }
    }

    if (fclose(output_file))
    {
        perror("Can't close output file");
        return ERROR_CODE_FAILURE;
    }
    output_file = NULL;

    return ERROR_CODE_SUCCES;
}