#include <stdio.h>
#include <string.h>

#include "strings/strings.h"
#include "mstrcmp/mstrcmp.h"
#include "mstrcmp/test_mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"

int main(const int argc, const char* argv[])
{
    // char str1[] = "lol kek cheburek1234";
    // char str2[] = "kek lol orbidoll4312";
    // swap(str1, str2, sizeof(str1));
    // printf("first: %s\nsecond: %s\n", &str1[0], &str2[0]);

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


    sort(strings, MAX_STR_COUNT, MAX_STR_SIZE,
         (int(*)(const void* const, const void* const, const bool))strcmp_alnum); // TODO - wrapper


    if (argc > 1 && !strcmp(argv[1], "--test")) //TODO - preprocessing
    {
        if (test_mstrcmp(strings) != ERROR_CODE_SUCCES)
        {
            fprintf(stderr, "Can't test strcmp_alnum\n");
            return -1;
        }
    }


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