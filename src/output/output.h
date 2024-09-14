#ifndef SRC_OUTPUT_H
#define SRC_OUTPUT_H

#include <stdio.h>

#include "../utils/utils.h"


enum ErrorCode output_string_ptrs(const char* const output_filename, char* const * const strings, 
                                  const size_t strings_size);

enum ErrorCode output_strings(const char* const output_filename, char* const strings,
                              const size_t strings_size);

#endif /*SRC_OUTPUT_H*/