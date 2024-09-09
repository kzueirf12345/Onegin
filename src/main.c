#include <stdio.h>

#include "array/array.h"
#include "utils/utils.h"

int main()
{
    FILE* input = fopen("Onegin.txt", "r");
    if (!input)
    {
        fprintf(stderr, "Can't open file\n");
        return -1;
    }

    char array[MAX_STR_COUNT][MAX_STR_SIZE] = {};

    if (fill_array(input, (char ** const )array) != ERRORCODE_SUCCES)
    {
        fprintf(stderr, "Can't fill array\n");
        return -1;
    }

    if (fclose(input))
    {
        fprintf(stderr, "Can't close file\n");
        return -1;
    }
    return 0;
}