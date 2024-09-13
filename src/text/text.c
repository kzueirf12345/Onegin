#include <assert.h>
#include <stdio.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "text.h"

static enum ErrorCode fill_text_size         (Text* const text, const char* const filename);
static enum ErrorCode fill_text_data         (Text* const text, const int file_handle);
static enum ErrorCode fill_text_string_count (Text* const text);
static enum ErrorCode fill_text_string_ptrs  (Text* const text);


enum ErrorCode fill_text(const char* const input_filename, Text* const text)
{
    assert(input_filename);
    assert(text);


    int input_file_handle = 0;

#ifdef __linux__

    if ((input_file_handle = open(input_filename, O_RDONLY)) < 0)
    {
        perror("Can't open input file");
        return ERROR_CODE_FAILURE;
    }

#else /*__linux__*/

    if ((input_handle = open(input_filename, O_RDONLY | O_BINARY)) < 0)
    {
        perror("Can't open input file");
        return ERROR_CODE_FAILURE;
    }

#endif /*__linux__*/

    const enum ErrorCode fill_text_size_code = fill_text_size(text, input_filename);
    if (fill_text_size_code != ERROR_CODE_SUCCES)
    {
        return fill_text_size_code;
    }

    const enum ErrorCode fill_text_data_code = fill_text_data(text, input_file_handle);
    if (fill_text_data_code != ERROR_CODE_SUCCES)
    {
        return fill_text_data_code;
    }

    if (close(input_file_handle))
    {
        perror("Can't close input file");
        return ERROR_CODE_FAILURE;
    }

    const enum ErrorCode fill_text_string_count_code = fill_text_string_count(text);
    if (fill_text_string_count_code != ERROR_CODE_SUCCES)
    {
        return fill_text_string_count_code;
    }
    // fprintf(stderr, "string_count: %zu\n", text->string_count);

    const enum ErrorCode fill_text_string_ptrs_code = fill_text_string_ptrs(text);
    if (fill_text_string_ptrs_code != ERROR_CODE_SUCCES)
    {
        return fill_text_string_ptrs_code;
    }

    return ERROR_CODE_SUCCES;
}

static enum ErrorCode fill_text_size(Text* const text, const char* const filename) 
{
    assert(text);
    assert(filename);

    struct stat stat_data = {};
    if (stat(filename, &stat_data) || !S_ISREG(stat_data.st_mode))
    {
        perror("Can't handle stat");
        return ERROR_CODE_FAILURE;
    }

    if (stat_data.st_size < 0)
    {
        return ERROR_CODE_FAILURE;
    }
    text->size = (size_t)(stat_data.st_size + 1);

    return ERROR_CODE_SUCCES;
}

enum ErrorCode fill_text_data(Text* const text, const int file_handle)
{
    assert(text);
    assert(text->size);

    text->data = (char*)calloc(text->size, sizeof(*text->data));
    if (!text->data)
    {
        perror("Can't calloc memory for text->data");
        return ERROR_CODE_FAILURE;
    }

    if (read(file_handle, text->data, text->size) != (ssize_t)(text->size - 1))
    {
        perror("Can't read into input file");
        return ERROR_CODE_FAILURE;
    }

    text->data[text->size-1] = '\0';

    return ERROR_CODE_SUCCES;
}

static enum ErrorCode fill_text_string_count (Text* const text)
{
    assert(text);
    assert(text->size);
    assert(text->data);


    text->string_count = 1;
    for (size_t ind = 0; ind < text->size; ++ind)
    {
        if (text->data[ind] == '\n')
        {
            text->data[ind] = '\0'; // REVIEW - Как сделать лучше? Просто тут неявно
            ++text->string_count;
        }
    }

    return ERROR_CODE_SUCCES;
}

static enum ErrorCode fill_text_string_ptrs(Text* const text)
{
    assert(text);
    assert(text->size);
    assert(text->data);
    assert(text->string_count);


    text->string_ptrs = (char**)calloc(text->string_count, sizeof(*text->string_ptrs));
    if (!text->string_ptrs)
    {
        perror("Can't calloc memory for string_ptrs");
        return ERROR_CODE_FAILURE;
    }

    *text->string_ptrs = text->data;
    assert(*text->string_ptrs);


    char** string_ptr_ptr = text->string_ptrs + 1;
    assert(string_ptr_ptr);
    for (size_t string_ind = 1; string_ind < text->size; ++string_ind)
    {
        char* const string_ptr = text->data + string_ind;
        assert(string_ptr);

        // fprintf(stderr, "string_ptr p - %p  data - %s\n", string_ptr, string_ptr);
        if (*(string_ptr - 1) == '\0')
        {
            // fprintf(stderr, "%s\n", string_ptr);
            *string_ptr_ptr = string_ptr;
            assert(*string_ptr_ptr);
            string_ptr_ptr++;
        }
    }

    return ERROR_CODE_SUCCES;
}



void destroy_text(Text* text)
{
    assert(text);

    if (text->data)
    {
        free(text->data); text->data = NULL;
    }
    if (text->string_ptrs)
    {
        free(text->string_ptrs); text->string_ptrs = NULL;
    }
    text->size = 0;
    text->string_count = 0;
}