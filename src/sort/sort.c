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
    assert(num);
    assert(size);

    for (size_t nsort_size = num; nsort_size > 1; --nsort_size)
    {
        for (size_t str_ind = 1; str_ind < nsort_size; ++str_ind)
        {
            if (compare(*(void**)((char*)base + (str_ind - 1) * size),
                        *(void**)((char*)base + (str_ind    ) * size)) > 0)
            {
                swap(((char*)base + (str_ind - 1) * size),
                     ((char*)base + (str_ind    ) * size),
                     size);
            }
        }
    }
}

void partition(void* left, void* right, void** const partition_element, size_t num, size_t size,
               int (*compare) (const void*, const void*))
{
    assert(left);
    assert(right);
    assert(compare);
    assert(num);
    assert(size);
    assert(partition_element);


    if (left == right)
        return;
    
    if ((void*)((char*)left + 1 * size) == right)
    {
        if (compare(*(void**)left, *(void**)right) > 0)
        {
            swap(left, right, size);
        }
    }


    const uintptr_t partition_offset= ((uintptr_t)((char*)right - (char*)left) / sizeof(char*)) >> 1;
    *partition_element = (void*)((char*)left + partition_offset * sizeof(char*));

    assert(*partition_element);
    assert((left <= *partition_element) && (*partition_element <= right));
    // fprintf(stderr, "left: %s\npartition_element: %s\n\n", *(char**)left, *(char**)*partition_element);


    while (left != right)
    {
        while (left != right && compare(*(void**)left, *(void**)*partition_element) < 0)
        {
            left = (void*)((char*)left + 1 * size);
            assert(left);
        }

        // fprintf(stderr, "left: %s\npartition_element: %s\nright: %s \n",
        //                 *(char**)left, *(char**)*partition_element, *(char**)right);
        
        while (right != left && compare(*(void**)right, *(void**)*partition_element) > 0)
        {
            right = (void*)((char*)right - 1 * size);
            assert(right);
        }

        swap(left, right, size);
        assert(left);
        assert(right);
    }
}
