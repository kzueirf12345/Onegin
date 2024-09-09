#include <assert.h>

#include "strings.h"

enum ErrorCode fill_strings(FILE* input_file, char strings[MAX_STR_COUNT][MAX_STR_SIZE])
{
    assert(input_file);
    assert(strings);


    for (size_t str_num = 0; str_num < MAX_STR_COUNT && !feof(input_file) && !ferror(input_file);
         ++str_num)
    {
        if (!fgets(strings[str_num], MAX_STR_SIZE, input_file))
        {
            perror("Failure read into input file\n");
            return ERROR_CODE_FAILURE;
        }
    }

    return ferror(input_file) ? ERROR_CODE_FAILURE : ERROR_CODE_SUCCES;
}
