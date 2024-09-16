#ifndef SRC_OUTPUT_H
#define SRC_OUTPUT_H

#include <stdio.h>

#include "../utils/utils.h"


enum ErrorCode output_strings(FILE** const output_file, char* const * const strings, 
                              const size_t strings_size);

enum ErrorCode output_text(FILE** const output_file, char* const text, const size_t text_size);

#endif /*SRC_OUTPUT_H*/