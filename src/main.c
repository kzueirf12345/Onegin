#include <string.h>

#include "text/text.h"
#include "mstrcmp/mstrcmp.h"
#include "sort/sort.h"
#include "output/output.h"


int main()
{
    Text text = {};
    if (fill_text("./Onegin.txt", &text) != ERROR_CODE_SUCCES)
    {
        fprintf(stderr, "Can't fill text\n");
        return -1;
    }

    sort(text.string_ptrs, text.string_count, sizeof(*text.string_ptrs), strcmp_alnum_wrapper);


    // for (size_t ind = 0; ind < text.string_count; ++ind)
    // {
    //     fputs(*(text.string_ptrs + ind), stderr);
    //     fputs("\n", stderr);
    // }


    // FILE* output = fopen("./Onegin_sort.txt", "wb");
    // if (!output)
    // {
    //     fprintf(stderr, "Can't open output file\n");
    //     return -1;
    // }

    // if (output_strings(output, strings) != ERROR_CODE_SUCCES)
    // {
    //     fprintf(stderr, "Can't output strings\n");
    //     return -1;
    // }
    
    // if (fclose(output))
    // {
    //     fprintf(stderr, "Can't close output file\n");
    //     return -1;
    // }

    destroy_text(&text);
    return 0;
}