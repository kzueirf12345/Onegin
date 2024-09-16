#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"


static enum ErrorCode fill_text_size                   (Text* const text, FILE** const input_file);
static enum ErrorCode fill_text_data                   (Text* const text, FILE** const input_file);
static enum ErrorCode fill_text_string_count_and_split (Text* const text);
static enum ErrorCode fill_text_string_ptrs            (Text* const text);


enum ErrorCode create_text(const char* const input_filename, Text* const text)
{
    assert(input_filename);
    assert(text);

    FILE* input_file = fopen(input_filename, "rb");
    if (!input_file)
    {
        perror("Can't fopen input file");
        return ERROR_CODE_FAILURE;
    }
    setbuf(input_file, NULL);


    const enum ErrorCode fill_text_size_errcode = fill_text_size(text, &input_file);
    if (fill_text_size_errcode != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't fill_text_size\n");
        return fill_text_size_errcode;
    }

    const enum ErrorCode fill_text_data_errcode = fill_text_data(text, &input_file);
    if (fill_text_data_errcode != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't fill_text_data\n");
        return fill_text_data_errcode;
    }


    if (fclose(input_file))
    {
        perror("Can't fclose input file");
        return ERROR_CODE_FAILURE;
    }
    input_file = NULL;


    const enum ErrorCode fill_text_string_count_errcode = fill_text_string_count_and_split(text);
    if (fill_text_string_count_errcode != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't fill_text_string_count_and_split\n");
        return fill_text_string_count_errcode;
    }

    const enum ErrorCode fill_text_string_ptrs_errcode = fill_text_string_ptrs(text);
    if (fill_text_string_ptrs_errcode != ERROR_CODE_SUCCESS)
    {
        fprintf(stderr, "Can't fill_text_string_ptrs\n");
        return fill_text_string_ptrs_errcode;
    }

    return ERROR_CODE_SUCCESS;
}

static enum ErrorCode fill_text_size(Text* const text, FILE** const input_file) 
{
    assert(text);
    assert(input_file);
    assert(*input_file);

    if (fseek(*input_file, 0, SEEK_END))
    {
        perror("Can't fseek to end input file");
        return ERROR_CODE_FAILURE;
    }

    long text_size = 0;
    if ((text_size = ftell(*input_file)) < 0)
    {
        perror("Can't ftell input_file");
        return ERROR_CODE_FAILURE;
    }
    text->text_size = (size_t)text_size + 1;


    if (fseek(*input_file, 0, SEEK_SET))
    {
        perror("Can't fseek to start input file");
        return ERROR_CODE_FAILURE;
    }

    return ERROR_CODE_SUCCESS;
}

enum ErrorCode fill_text_data(Text* const text, FILE** const input_file)
{
    assert(input_file);
    assert(*input_file);
    assert(text);
    assert(text->text_size);

    text->text = (char*)calloc(text->text_size, sizeof(*text->text));
    if (!text->text)
    {
        perror("Can't calloc memory for text->text");
        return ERROR_CODE_FAILURE;
    }

    if (fread(text->text, 1, text->text_size - 1, *input_file) != (text->text_size - 1))
    {
        perror("Can't fread into input file");
        return ERROR_CODE_FAILURE;
    }

    text->text[text->text_size - 1] = '\0';

    return ERROR_CODE_SUCCESS;
}

static enum ErrorCode fill_text_string_count_and_split (Text* const text)
{
    assert(text);
    assert(text->text_size);
    assert(text->text);

    text->string_size = 1;
    for (size_t ind = 0; ind < text->text_size; ++ind)
    {
        if (text->text[ind] == '\n')
        {
            text->text[ind] = '\0';
            ++text->string_size;
        }
    }

    return ERROR_CODE_SUCCESS;
}

static enum ErrorCode fill_text_string_ptrs(Text* const text)
{
    assert(text);
    assert(text->text_size);
    assert(text->text);
    assert(text->string_size);

    text->strings = (char**)calloc(text->string_size, sizeof(*text->strings));
    if (!text->strings)
    {
        perror("Can't calloc memory for strings");
        return ERROR_CODE_FAILURE;
    }

    *text->strings = text->text;
    assert(*text->strings);
    

    char** string_ptr = text->strings + 1;
    for (size_t string_ind = 1; string_ind < text->text_size; ++string_ind)
    {
        char* const string = text->text + string_ind;

        assert(string - 1);
        if  (*(string - 1) == '\0')
        {
            *string_ptr = string;
            ++string_ptr;
        }
    }

    return ERROR_CODE_SUCCESS;
}



void destroy_text(Text* text)
{
    assert(text);

    free(text->text);    text->text    = NULL;
    free(text->strings); text->strings = NULL;

    text->text_size   = 0;
    text->string_size = 0;
}