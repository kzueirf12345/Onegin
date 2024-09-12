#ifndef SRC_SORT_H
#define SRC_SORT_H

#include <stdbool.h>

#include "../utils/utils.h"


void sort(void *base, size_t num, size_t size, int (*compare) (const void* const, const void* const));


#endif /*SRC_SORT_H*/