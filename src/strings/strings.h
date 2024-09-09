#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include <stdio.h>

#include "../utils/utils.h"

enum ErrorCode fill_strings(FILE* input_file, char strings[MAX_STR_COUNT][MAX_STR_SIZE]);

#endif /*SRC_INPUT_H*/