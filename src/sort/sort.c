#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "sort.h"


void swap(void* elem1, void* elem2, size_t elem_size);

// static int num1 = 0;

void sort(void *base, size_t num, size_t size,
          int (*compare) (const void* const, const void* const, const bool))
{
    assert(base);
    assert(compare);

    for (size_t nsort_size = num; nsort_size > 1; --nsort_size)
    {
        for (size_t str_ind = 1; str_ind < nsort_size; ++str_ind)
        {
                // num1++;
                // fprintf(stderr, "%d. elem1 = %s, elem2 = %s\n", num1, 
                //                 (const char*)((char*)base + (str_ind - 1) * size),
                //                 (const char*)(((char*)base + (str_ind) * size)));
            if (compare(((char*)base + (str_ind - 1) * size),
                        ((char*)base + (str_ind) * size),
                        false) > 0)
            {
                swap(((char*)base + (str_ind - 1) * size),
                     ((char*)base + (str_ind) * size),
                     size);
            }
        }
    }
}


//TODO - memcpy

void swap(void* elem1, void* elem2, size_t elem_size) 
{
    assert(elem1);
    assert(elem2);


    //TODO - func for memcpy and >>
    while (elem_size >= 8)
    {
        uint64_t temp = 0;
        memcpy(&temp, elem1, 8);
               memcpy(elem1, elem2, 8);
                      memcpy(elem2, &temp, 8);
        elem1 = (char*)elem1 + 8;
        elem2 = (char*)elem2 + 8;
        elem_size -= 8;
    }

    if (elem_size >= 4)
    {
        uint32_t* temp = (uint32_t*)elem1;
        memcpy(&temp, elem1, 4);
               memcpy(elem1, elem2, 4);
                      memcpy(elem2, &temp, 4);
        elem1 = (char*)elem1 + 4;
        elem2 = (char*)elem2 + 4;
        elem_size -= 4;
    }

    if (elem_size >= 2)
    {
        uint16_t* temp = (uint16_t*)elem1;
        memcpy(&temp, elem1, 2);
               memcpy(elem1, elem2, 2);
                      memcpy(elem2, &temp, 2);
        elem1 = (char*)elem1 + 2;
        elem2 = (char*)elem2 + 2;
        elem_size -= 2;
    }

    if (elem_size >= 1)
    {
        uint8_t* temp = (uint8_t*)elem1;
        memcpy(&temp, elem1, 1);
               memcpy(elem1, elem2, 1);
                      memcpy(elem2, &temp, 1);
        elem1 = (char*)elem1 + 1;
        elem2 = (char*)elem2 + 1;
        elem_size -= 1;
    }
}

#undef SWAP_HELP