#include <string.h>

#include "text/text.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"


int main()
{
    // Text text = {};
    // if (fill_text("./Onegin.txt", &text) != ERROR_CODE_SUCCES)
    // {
    //     fprintf(stderr, "Can't fill text\n");
    //     return -1;
    // }

    // sort(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper);


    // if (output_string_ptrs("./Onegin_sort.txt", text.string_ptrs, text.string_count) != ERROR_CODE_SUCCES)
    // {
    //     fprintf(stderr, "Can't output strings\n");
    //     return -1;
    // }

    // destroy_text(&text);



    Text text = {};
    if (fill_text("./Onegin_short.txt", &text) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill text\n");
        return -1;
    }

    char** partition_element = NULL;
    partition(text.string_ptrs, text.string_ptrs + (text.string_count - 1), (void**)&partition_element,
              text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper);


    if (output_string_ptrs("./Onegin_short_sort.txt", text.string_ptrs, text.string_count) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output strings\n");
        return -1;
    }

    destroy_text(&text);
    return 0;
}