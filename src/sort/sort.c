#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <sys/types.h>

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

    if (num > 2)
    {
        const ssize_t left_num = (ssize_t)((char*)partition_element - (char*)base) / (ssize_t)size;
        const ssize_t right_num = (ssize_t)num - left_num;

        if (left_num > 1)
            sort(base, (size_t)left_num, size, compare); // <
        if(right_num > 1)
            sort(partition_element, (size_t)right_num, size, compare); // >=
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

    assert                     ((char*)right > (char*)left);
    const size_t num = (size_t)((char*)right - (char*)left) / size + 1;

    if (num == 1)
        return;
    
    if (num == 2)
    {
        if (compare(*(void**)left, *(void**)right) > 0)
            swap(left, right, size);

        return;
    }

    const size_t pivot_offset = num >> 1;
    *partition_element = ((char*)left + pivot_offset * size);

    assert(         *partition_element);
    assert(*(void**)*partition_element);


    while (left != right)
    {
        while (left != right
               && compare(*(void**)left, *(void**)*partition_element) <= 0
               && left != *partition_element)
        {
            left = (char*)left + 1 * size;
            assert(left);
        }

        while (right != left
               && compare(*(void**)right, *(void**)*partition_element) >= 0
               && right != *partition_element)
        {
            right = (char*)right - 1 * size;
            assert(right);
        }

        if (left != right)
        {
            swap(left, right, size);

            if      (left  == *partition_element) *partition_element = right;
            else if (right == *partition_element) *partition_element = left;
        }

        assert(left);
        assert(right);
    }
}



bool is_sorted(void* base, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    for (size_t i = 1; i < num; ++i)
    {
        if (compare(*(void**)((char*)base + (i - 1) * size), *(void**)((char*)base + (i) * size)) > 0)
            return false;
    }
    return true;
}