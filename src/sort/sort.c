#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "sort.h"
#include "swap/swap.h"


void sort(void* base, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    assert(base);
    assert(compare);

    for (size_t nsort_size = num; nsort_size > 1; --nsort_size)
    {
        for (size_t str_ind = 1; str_ind < nsort_size; ++str_ind)
        {
            if (compare(*(char**)((char*)base + (str_ind - 1) * size),
                        *(char**)((char*)base + (str_ind    ) * size)) > 0)
            {
                swap(((char*)base + (str_ind - 1) * size),
                     ((char*)base + (str_ind    ) * size),
                     size);
            }
        }
    }
}