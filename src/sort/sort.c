#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "sort.h"
#include "swap/swap.h"
#include "../output/output.h"


static void partition(void* left, void* right, void** const partition_element, size_t num,
                      int (*compare) (const void*, const void*));


void sort(void* base, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    assert(base);
    assert(compare);
    assert(num);
    assert(size);


    void* partition_element = NULL;
    partition(base, ((char*)base + (num - 1) * size), &partition_element, size, compare);
    // fprintf(stderr, "%s\n", *(char**)partition_element);

    if (num > 2)
    {
        const size_t left_num = (size_t)((char*)partition_element - (char*)base) / size;
        const size_t right_num = num - left_num;

        assert(left_num > 0);
        assert(right_num > 0);

        sort(base, left_num, size, compare); // <
        sort(partition_element, right_num, size, compare); // >=
    }  
}


static void partition(void* left, void* right, void** const partition_element, size_t size,
                      int (*compare) (const void*, const void*))
{
    assert(left);
    assert(right);
    assert(compare);
    assert(size);
    assert(partition_element);

    const size_t num = (size_t)((char*)right - (char*)left) / size + 1;

    if (num == 1)
        return;
    
    if (num == 2)
    {
        if (compare(*(void**)left, *(void**)right) > 0)
        {
            swap(left, right, size);
        }
        return;
    }

    const size_t pivot_offset = num >> 1;
    const void* const pivot = *(void**)((char*)left + pivot_offset * size);
    assert(pivot);

    int cnt = 0;
    while (left != right)
    {
        // if (200 < cnt  && cnt < 230)
        // {
        //     fprintf(stderr, "left: %s\nright: %s\n", *(char**)left, *(char**)right);
        // }
        // else if (cnt > 230){
        //     return;
        // }
        ++cnt;
        while (left != right && compare(*(void**)left, pivot) < 0)
        {
            left = (void*)((char*)left + 1 * size);
            assert(left);
        }

        while (right != left && compare(*(void**)right, pivot) > 0)
        {
            right = (void*)((char*)right - 1 * size);
            assert(right);
        }

        if (left != right)
        {
            swap(left, right, size);

            left = (void*)((char*)left + 1 * size);
            assert(left);

            if (left != right)
            {
                right = (void*)((char*)right - 1 * size);
                assert(right);
            }
        }
        assert(left);
        assert(right);
    }

    *partition_element = left;
    assert(*partition_element);
}
