#include <stdio.h>
#include <string.h>

#include "strings/strings.h"
#include "mstrcmp/test_mstrcmp.h"
#include "sort/sort.h"

int main(const int argc, const char* argv[])
{
    // char str1[] = "lol kek cheburek1234";
    // char str2[] = "kek lol orbidoll4312";
    // swap(str1, str2, sizeof(str1));
    // printf("first: %s\nsecond: %s\n", &str1[0], &str2[0]);

    FILE* input = fopen("./Onegin.txt", "rb");
    if (!input)
    {
        fprintf(stderr, "Can't open file\n");
        return -1;
    }

    char strings[MAX_STR_COUNT][MAX_STR_SIZE] = {};

    if (fill_strings(input, strings) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill strings\n");
        return -1;
    }

    // for (size_t i = 0; i < MAX_STR_COUNT; ++i)
    // {
    //     fprintf(stderr, "/%s|\n", strings[i]);
    // }

    if (argc > 1 && !strcmp(argv[1], "--test"))
    {
        if (test_mstrcmp(strings) != ERROR_CODE_SUCCES)
        {
            fprintf(stderr, "Can't test mstrcmp\n");
            return -1;
        }
    }

    if (fclose(input))
    {
        fprintf(stderr, "Can't close file\n");
        return -1;
    }
    return 0;
}