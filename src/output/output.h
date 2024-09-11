#ifndef SRC_OUTPUT_H
#define SRC_OUTPUT_H

#include <stdio.h>

#include "../utils/utils.h"

enum ErrorCode output_strings(FILE* file, char strings[MAX_STR_COUNT][MAX_STR_SIZE]);

#endif /*SRC_OUTPUT_H*/