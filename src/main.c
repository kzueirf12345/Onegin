#include <string.h>
#include <stdlib.h>

#include "text/text.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"
#include "utils/concole.h"


enum ErrorCode output_two_sorts_and_default_text(FILE** const output_file, Text* const text,
                                                 int (*first_compare ) (const void*, const void*),
                                                 int (*second_compare) (const void*, const void*));


int main()
{
    Text text = {};
    if (create_text("./Onegin.txt", &text) != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't fill text\n");
        return EXIT_FAILURE;
    }


    FILE* output_file = fopen("./Onegin_sort.txt", "wb");
    if (!output_file)
    {
        perror("Can't open output file");
        return EXIT_FAILURE;
    }

    if (output_two_sorts_and_default_text(&output_file, &text, strcmp_alnum_wrapper, r_strcmp_alnum_wrapper)
        != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't sort or output text\n");
        return EXIT_FAILURE;
    }

    if (fclose(output_file))
    {
        perror("Can't close output file");
        return EXIT_FAILURE;
    }
    output_file = NULL;


    destroy_text(&text);

    return 0;
}


enum ErrorCode output_two_sorts_and_default_text(FILE ** const output_file, Text* const text,
                                                 int (*first_compare)  (const void*, const void*),
                                                 int (*second_compare) (const void*, const void*))
{
    sort(text->strings, text->string_size, sizeof(*text->strings), first_compare);
    
    #ifdef TEST_MODE
    if (is_sorted(text->strings, text->string_size, sizeof(*text->strings), first_compare))
        printf("SORTED IS " GREEN_TEXT("CORRECT")   "!\n");
    else
        printf("SORTED IS " RED_TEXT  ("INCORRECT") "!\n");
    #endif /*TEST_MODE*/

    if (output_strings(output_file, text->strings, text->string_size) != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't output strings\n");
        return ERROR_CODE_FAILURE;
    }


    sort(text->strings, text->string_size, sizeof(*text->strings), second_compare);

    #ifdef TEST_MODE
    if (is_sorted(text->strings, text->string_size, sizeof(*text->strings), second_compare))
        printf("SORTED IS " GREEN_TEXT("CORRECT")   "!\n");
    else
        printf("SORTED IS " RED_TEXT  ("INCORRECT") "!\n");
    #endif /*TEST_MODE*/
 
    if (output_strings(output_file, text->strings, text->string_size) != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't output string_ptrs\n");
        return ERROR_CODE_FAILURE;
    }


    if (output_text(output_file, text->text, text->text_size) != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't output strings\n");
        return ERROR_CODE_FAILURE;
    }

    return ERROR_CODE_SUCCESS;
}