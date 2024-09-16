#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <sys/types.h>

#include "sort.h"
#include "swap/swap.h"
#include "../output/output.h"

//          rofls
static void partition(void* left, void* right, void** const partition_element, size_t num,
                      int (*compare) (const void*, const void*));


void sort(void* base, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    assert(base);
    assert(num);
    assert(size);
    assert(compare);

    void* partition_element = NULL;
    partition(base, ((char*)base + (num - 1) * size), &partition_element, size, compare);

    if (num > 2)
    {
        assert(partition_element >= base);
        const size_t left_num = (size_t)((char*)partition_element - (char*)base) / size;

        assert(num >= left_num);
        const size_t right_num = num - left_num;

        if (left_num > 1)
            sort(base, left_num, size, compare); // <

        if(right_num > 1)
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

    assert(right > left);
    const size_t num = (size_t)((char*)right - (char*)left) / size + 1;

    if (num == 1)
        return;
    
    if (num == 2)
    {
        if (compare(left, right) > 0)
            swap(left, right, size);

        return;
    }

    const size_t pivot_offset = num >> 1;
    *partition_element = ((char*)left + pivot_offset * size);

    assert(*partition_element);


    while (left != right)
    {
        while (left != right
               && compare(left, *partition_element) <= 0
               && left != *partition_element)
        {
            left = (char*)left + 1 * size;
        }

        while (right != left
               && compare(right, *partition_element) >= 0
               && right != *partition_element)
        {
            right = (char*)right - 1 * size;
        }

        if (left != right)
        {
            swap(left, right, size);

            if      (left  == *partition_element) *partition_element = right;
            else if (right == *partition_element) *partition_element = left;
        }
    }
}



bool is_sorted(void* base, size_t num, size_t size, int (*compare) (const void*, const void*))
{
    assert(base);
    assert(num);
    assert(size);
    assert(compare);

    for (size_t i = 1; i < num; ++i)
    {
        if (compare(((char*)base + (i - 1) * size), ((char*)base + (i) * size)) > 0)
            return false;
    }
    return true;
}