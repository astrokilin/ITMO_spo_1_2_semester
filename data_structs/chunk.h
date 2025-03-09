#ifndef CHUNK_H
#define CHUNK_H

#include <stdlib.h>
#include <string.h>

#include "general.h"

struct extendable_chunk
{
    size_t size;
    size_t __capacity;
    char *start;
};

inline static void
chunk_deinit(struct extendable_chunk *const self)
{
    free(self->start);
}

inline static void
chunk_deinit_shallow(struct extendable_chunk *const self)
{
    self->start = 0;
}

inline static default_retcode
chunk_init(struct extendable_chunk *const self, const size_t N)
{ 
    char *start;

    if (unlikely(!(start = (char*) malloc(N))))
        return ERROR;

    self->size = 0;
    self->__capacity = N;
    self->start = start;
    return SUCCESS;
}

inline static default_retcode
chunk_init_deepcopy(
        struct extendable_chunk *const self,
        const struct extendable_chunk *const other)
{
    char *start;

    if (unlikely(!(start = (char*) malloc(other->__capacity))))
        return ERROR;

    memcpy(start, other->start, other->size);
    self->size = other->size;
    self->__capacity = other->__capacity;
    self->start = start;
    return SUCCESS;
}

inline static default_retcode
chunk_slim_down(struct extendable_chunk *const self)
{
    char *new_chunk;
    size_t size;

    size = self->size;
    // zero size would cause realloc to behave like free
    // but this function should leave chunk valid
    // so just make the chunk very small
    if (size == 0)
        size = 16;

    new_chunk = (char*) realloc(self->start, size);

    if (unlikely(!new_chunk))
        return ERROR;

    self->__capacity = size;
    self->start = new_chunk;
    return SUCCESS;
}

inline static default_retcode
chunk_extend_to_fit(struct extendable_chunk *const self, const size_t l)
{
    char *new_chunk;
    size_t capacity;
    size_t new_size;

    new_size = self->size + l;
    capacity = self->__capacity;

    if (new_size > capacity)
    {
        capacity = capacity << (LOG2(new_size / capacity) + 1);

        new_chunk = (char*) realloc(self->start, capacity);

        if (unlikely(new_chunk == NULL))
            return ERROR;

        self->start = new_chunk;
        self->__capacity = capacity;
    }

    return SUCCESS; 
}

inline static default_retcode
chunk_append_from(struct extendable_chunk *const self, const void *buf, const size_t len)
{
    if (chunk_extend_to_fit(self, len) == ERROR)
        return ERROR;

    memcpy(self->start + self->size, (char*) buf, len);
    self->size += len;
    return SUCCESS; 
}

#define DEFINE_TYPED_CHUNK_LIST(T_NAME, TYPE)                           \
                                                                        \
inline static default_retcode                                           \
T_NAME ##_append(struct extendable_chunk *self, const TYPE t)           \
{                                                                       \
    if (chunk_extend_to_fit(self, sizeof(t)) == ERROR)                  \
        return ERROR;                                                   \
                                                                        \
    *((TYPE*)(&(self->start[self->size]))) = t;                         \
    self->size += sizeof(TYPE);                                         \
    return SUCCESS;                                                     \
}                                                                       \
                                                                        \
inline static TYPE                                                      \
T_NAME ##_pop(struct extendable_chunk *self)                            \
{                                                                       \
    return *((TYPE*)(self->start + (self->size -= sizeof(TYPE))));      \
}                                                                       \
                                                                        \
inline static void                                                      \
T_NAME ##_truncate(struct extendable_chunk *self, const size_t N)       \
{                                                                       \
    self->size -= N * sizeof(TYPE);                                     \
}                                                                       \

#endif
