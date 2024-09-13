#include <string.h>
#include <assert.h>

#include "swap.h"

void swap_help(void** const elem1, void** const elem2, void* const temp, const size_t swapped_size);


void swap(void* elem1, void* elem2, size_t elem_size) 
{
    assert(elem1);
    assert(elem2);


    while (elem_size >= 8)
    {
        uint64_t temp = 0;
        swap_help(&elem1, &elem2, &temp, 8);
        elem_size -= 8;
    }


    if (elem_size >= 4)
    {
        uint32_t* temp = (uint32_t*)elem1;
        swap_help(&elem1, &elem2, &temp, 4);
        elem_size -= 4;
    }

    if (elem_size >= 2)
    {
        uint16_t* temp = (uint16_t*)elem1;
        swap_help(&elem1, &elem2, &temp, 2);
        elem_size -= 2;
    }

    if (elem_size >= 1)
    {
        uint8_t* temp = (uint8_t*)elem1;
        swap_help(&elem1, &elem2, &temp, 1);
        elem_size -= 1;
    }
}


void swap_help(void** const elem1, void** const elem2, void* const temp, const size_t swapped_size)
{
    assert(elem1);
    assert(elem2);
    assert(*elem1);
    assert(*elem2);
    assert(temp);

    memcpy(temp, *elem1, swapped_size);
          memcpy(*elem1, *elem2, swapped_size);
                  memcpy(*elem2, temp, swapped_size);
    
    *elem1 = (char*)(*elem1) + swapped_size;
    *elem2 = (char*)(*elem2) + swapped_size;
}
