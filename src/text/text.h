#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include <stdio.h>

#include "../utils/utils.h"


typedef struct Text
{
    char*  text;
    size_t text_size;
    size_t string_size;
    char** strings;
} Text;


enum ErrorCode create_text(const char* const input_filename, Text* const text);
void destroy_text(Text* text);


#endif /*SRC_INPUT_H*/