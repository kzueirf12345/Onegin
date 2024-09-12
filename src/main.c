#include <stdio.h>
#include <string.h>

#include "strings/strings.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"

int main()
{
    FILE* input = fopen("./Onegin.txt", "rb");
    if (!input)
    {
        fprintf(stderr, "Can't open input file\n");
        return -1;
    }

    char strings[MAX_STR_COUNT][MAX_STR_SIZE] = {};

    if (fill_strings(input, strings) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill strings\n");
        return -1;
    }

    if (fclose(input))
    {
        fprintf(stderr, "Can't close input file\n");
        return -1;
    }


    sort(strings, MAX_STR_COUNT, MAX_STR_SIZE, strcmp_alnum_wrapper);


    FILE* output = fopen("./Onegin_sort.txt", "wb");
    if (!output)
    {
        fprintf(stderr, "Can't open output file\n");
        return -1;
    }

    if (output_strings(output, strings) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output strings\n");
        return -1;
    }
    
    if (fclose(output))
    {
        fprintf(stderr, "Can't close output file\n");
        return -1;
    }

    return 0;
}