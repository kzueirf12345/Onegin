#include <assert.h>
#include <string.h>

#include "swap.h"


static void memcpy_for_swap(void** const elem1, void** const elem2, void* const temp,
                            const size_t swapped_size);


void swap(void* elem1, void* elem2, size_t elem_size) 
{
    assert(elem1);
    assert(elem2);
    assert(elem_size);

    while (elem_size >= sizeof(uint64_t))
    {
        uint64_t temp = 0;
        memcpy_for_swap(&elem1, &elem2, &temp, sizeof(uint64_t));
        elem_size -= sizeof(uint64_t);
    }


    if (elem_size & sizeof(uint32_t))
    {
        uint32_t temp = 0;
        memcpy_for_swap(&elem1, &elem2, &temp, sizeof(uint32_t));
    }

    if (elem_size & sizeof(uint16_t))
    {
        uint16_t temp = 0;
        memcpy_for_swap(&elem1, &elem2, &temp, sizeof(uint16_t));
    }

    if (elem_size & sizeof(uint8_t))
    {
        uint8_t temp = 0;
        memcpy_for_swap(&elem1, &elem2, &temp, sizeof(uint8_t));
    }
}


static void memcpy_for_swap(void** const elem1, void** const elem2, void* const temp,
                            const size_t swapped_size)
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
