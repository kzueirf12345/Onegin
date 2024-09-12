#ifndef SRC_MSTRCMP_H
#define SRC_MSTRCMP_H

#include <stdbool.h>

int strcmp_alnum(const char* const first_str, const char* const second_str, const bool is_test_mod);

int strcmp_alnum_wrapper(const void* const first_str, const void* const second_str);


#endif /*SRC_MSTRCMP_H*/