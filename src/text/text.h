#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include <stdio.h>

#include "../utils/utils.h"

typedef struct Text
{
    char * data;
    size_t size;
    size_t string_count;
    char ** string_ptrs;
} Text;

enum ErrorCode fill_text(const char* const input_filename, Text* const text);
void destroy_text(Text* text);

#endif /*SRC_INPUT_H*/