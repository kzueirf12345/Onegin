#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "test_mstrcmp.h"
#include "mstrcmp.h"
#include "../utils/concole.h"

#define START_TESTING_LINE "========START TESTING======="
#define END_TESTING_LINE   "=========END TESTING========"

int sign(const int num);


enum ErrorCode test_mstrcmp(const char strings[MAX_STR_COUNT][MAX_STR_SIZE])
{
    assert(strings);

    printf("\n" START_TESTING_LINE "\n\n");

    for (size_t first_index = 0; first_index < MAX_STR_COUNT; ++first_index)
    {
        assert(strings[first_index]);

        for (size_t second_index = 0; second_index < MAX_STR_COUNT; ++second_index)
        {
            assert(strings[second_index]);

            if (printf("Test case №%-5zu", first_index*MAX_STR_COUNT + second_index) <= 0)
            {
                perror("Can't print test case header\n");
                return ERROR_CODE_FAILURE;
            }

            int result_strcmp = strcmp(strings[first_index], strings[second_index]);
            int result_mstrcmp = (int)mstrcmp(strings[first_index], strings[second_index], true);
            int sign_strcmp = sign(result_strcmp);
            int sign_mstrcmp = sign(result_mstrcmp);

            const char* const answer = (sign_strcmp == sign_mstrcmp 
                                        ? GREEN_TEXT("CORRECT")
                                        : RED_TEXT("INCORRECT"));

            if (printf("%s\n", answer) <= 0)
            {
                perror("Can't print test case answer\n");
                return ERROR_CODE_FAILURE;
            }

            if (!strcmp(answer, RED_TEXT("INCORRECT")))
            {
                if (printf("strcmp answer:  %d\n"
                           "mstrcmp answer: %d\n"
                           "first string:  /%s\\\n"
                           "second string: /%s\\\n",
                           sign_strcmp, sign_mstrcmp,
                           strings[first_index], strings[second_index]) <= 0)
                {
                    perror("Can't print test case incorrect string\n");
                    return ERROR_CODE_FAILURE;  
                }
            }
        }
    }

    printf("\n" END_TESTING_LINE "\n");

    return ERROR_CODE_SUCCES;
}

int sign(const int num)
{
    return num == 0 ? num : num / abs(num);
}
