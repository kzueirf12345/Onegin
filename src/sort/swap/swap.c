#include <string.h>
#include <assert.h>

#include "swap.h"

static void swap_help(void** const elem1, void** const elem2, void* const temp, const size_t swapped_size);


void swap(void* elem1, void* elem2, size_t elem_size) 
{
    assert(elem1);
    assert(elem2);
    assert(elem_size);

    size_t swapped_size = 8;

    while (elem_size >= swapped_size)
    {
        uint64_t temp = 0;
        swap_help(&elem1, &elem2, &temp, swapped_size);
        elem_size -= swapped_size;
    }
    swapped_size >>= 1;


    if (elem_size >= swapped_size)
    {
        uint32_t* temp = 0;
        swap_help(&elem1, &elem2, &temp, swapped_size);
        elem_size -= swapped_size;
    }
    swapped_size >>= 1;

    if (elem_size >= swapped_size)
    {
        uint16_t* temp = 0;
        swap_help(&elem1, &elem2, &temp, swapped_size);
        elem_size -= swapped_size;
    }
    swapped_size >>= 1;

    if (elem_size >= swapped_size)
    {
        uint8_t* temp = 0;
        swap_help(&elem1, &elem2, &temp, swapped_size);
        elem_size -= swapped_size;
    }
}


static void swap_help(void** const elem1, void** const elem2, void* const temp, const size_t swapped_size)
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
