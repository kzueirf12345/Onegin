#ifndef SRC_MSTRCMP_H
#define SRC_MSTRCMP_H

#include <stdbool.h>

// enum MstrcmpResult
// {
//     MSTRCMP_RESULT_LESS  = -1,
//     MSTRCMP_RESULT_EQUAL = 0,
//     MSTRCMP_RESULT_GREAT = 1
// };

int strcmp_alnum(const char* const first_str, const char* const second_str, 
                           const bool is_test_mod);

#endif /*SRC_MSTRCMP_H*/