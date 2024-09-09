#include <assert.h>

#include "array.h"

enum ErrorCode fill_array(FILE* input_file, char array[MAX_STR_COUNT][MAX_STR_SIZE])
{
    assert(input_file);
    assert(array);


    for (size_t str_num = 0; str_num < MAX_STR_COUNT && !feof(input_file) && !ferror(input_file);
         ++str_num)
    {
        if (!fgets((*array + str_num), MAX_STR_SIZE, input_file))
        {
            perror("Failure read into input file\n");
            return ERRORCODE_FAILURE;
        }
    }

    return ferror(input_file) ? ERRORCODE_FAILURE : ERRORCODE_SUCCES;
}
