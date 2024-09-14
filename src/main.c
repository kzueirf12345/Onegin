#include <string.h>

#include "text/text.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"
#include "utils/concole.h"

int main()
{
    Text text = {};
    if (fill_text("./Onegin.txt", &text) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill text\n");
        return EXIT_FAILURE;
    }

    // NOTE - start-end sort

           sort  (text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper);
    if (is_sorted(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper))
        printf("SORTED IS " GREEN_TEXT("CORRECT")   "!\n");
    else
        printf("SORTED IS " RED_TEXT  ("INCORRECT") "!\n");

    if (output_string_ptrs("./Onegin_sort.txt", text.string_ptrs, text.string_count) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output string_ptrs\n");
        return EXIT_FAILURE;
    }

    // NOTE - end-start sort

           sort  (text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), rstrcmp_alnum_wrapper);
    if (is_sorted(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), rstrcmp_alnum_wrapper))
        printf("SORTED IS " GREEN_TEXT("CORRECT")   "!\n");
    else
        printf("SORTED IS " RED_TEXT  ("INCORRECT") "!\n");

    if (output_string_ptrs("./Onegin_sort.txt", text.string_ptrs, text.string_count) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output string_ptrs\n");
        return EXIT_FAILURE;
    }

    // NOTE - not sort

    if (output_strings("./Onegin_sort.txt", text.data, text.size) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output strings\n");
        return EXIT_FAILURE;
    }


    destroy_text(&text);

    return 0;
}