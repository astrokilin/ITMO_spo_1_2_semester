#ifndef STRING_MAP_H
#define STRING_MAP_H

#include <stdlib.h>
#include <stdint.h>

#include <data_structs/chunk.h>
#include "maps_general.h"

#define STRING_MAP_STR_BY_OFFSET(str_start, str_ind) \
    ((char*)((str_start) + (str_ind) + sizeof(size_t)))
#define STRING_MAP_STRLEN_BY_OFFSET(str_start, str_ind) \
    (*((size_t*)((str_start) + (str_ind))))
// read only map
struct string_map
{
    char *data;
    size_t data_size;
};

inline static void
string_map_deinit(struct string_map *const self)
{
    free(self->data);
}

inline static size_t
string_map_get_str_len(const struct string_map *const self, const size_t ind)
{
    return *((size_t*)(self->data + ind));
}

// full length including padded zeroes
inline static size_t
string_map_get_str_len_full(const struct string_map *const self, const size_t ind)
{
    size_t res; 

    res = *((size_t*)(self->data + ind));
    return res + (sizeof(size_t) - (res % sizeof(size_t))) % sizeof(size_t);
}

inline static char*
string_map_get_str_ptr(const struct string_map *const self, const size_t ind)
{
    return self->data + ind + sizeof(size_t);
}

//--------------------------------- string_map_builder -----------------------------------

struct string_map_builder
{
    #define __STRING_MAP_BUILDER_PREALLOC_BYTES 512
    struct extendable_chunk strings;
};

inline static default_retcode
string_map_builder_init(struct string_map_builder *const self, const size_t start_offset)
{
    if (chunk_init(&self->strings, __STRING_MAP_BUILDER_PREALLOC_BYTES) == ERROR)
        return ERROR;

    self->strings.size = start_offset;
    return SUCCESS;
}

inline static void
string_map_builder_deinit(struct string_map_builder *const self)
{
    chunk_deinit(&self->strings);
}

default_retcode
string_map_builder_add(struct string_map_builder*, const char*, size_t);

inline static default_retcode
string_map_builder_start_adding(
        struct string_map_builder *const self,
        const size_t max_size_required,
        char **const dest)
{
    if (chunk_extend_to_fit(&self->strings,
                            max_size_required
                            + max_size_required % sizeof(size_t)
                            + sizeof(size_t)) == ERROR)
        return ERROR;

    *dest = self->strings.start + self->strings.size + sizeof(size_t);
    return SUCCESS;
}

inline static void
string_map_builder_finish_adding(
        struct string_map_builder *const self,
        size_t size_used)
{
    char *data = self->strings.start + self->strings.size;
    *((size_t*)data) = size_used;
    size_used += size_used % sizeof(size_t);
    memset(data + sizeof(size_t) + size_used, 0, size_used);
    self->strings.size += size_used;
}


inline static default_retcode
string_map_builder_finish(
        struct string_map_builder *const self, 
        struct string_map *const res)
{ 
    if (chunk_slim_down(&self->strings) == ERROR)
        return ERROR;

    res->data = self->strings.start;
    res->data_size = self->strings.size;
    return SUCCESS;
}

#endif
