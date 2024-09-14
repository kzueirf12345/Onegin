#include <string.h>

#include "text/text.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"
#include "utils/concole.h"

bool is_sorted(void* arr, size_t num, size_t size, int (*compare) (const void*, const void*));

int main()
{
    Text text = {};
    if (fill_text("./Onegin.txt", &text) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill text\n");
        return -1;
    }

    sort(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper);

    if (output_string_ptrs("./Onegin_sort.txt", text.string_ptrs, text.string_count) 
        != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output string_ptrs\n");
        return -1;
    }

    if (output_strings("./Onegin_sort.txt", text.data, text.size) 
        != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't output strings\n");
        return -1;
    }

    if (is_sorted(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper))
        printf("SORTED IS " GREEN_TEXT("CORRECT")   "!\n");
    else
        printf("SORTED IS " RED_TEXT  ("INCORRECT") "!\n");


    destroy_text(&text);

    return 0;
}

bool is_sorted(void* arr, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    for (size_t i = 1; i < num; ++i)
    {
        if (compare(*(void**)((char*)arr + (i - 1) * size), *(void**)((char*)arr + (i) * size)) > 0)
            return false;
    }
    return true;
}