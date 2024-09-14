#ifndef SRC_SORT_H
#define SRC_SORT_H

#include <stdbool.h>


void    sort  (void *base, size_t num, size_t size, int (*compare) (const void*, const void*));
bool is_sorted(void* base, size_t num, size_t size, int (*compare) (const void*, const void*));

#endif /*SRC_SORT_H*/