#include <string.h>
#include <stdint.h>

#include "general.h"
#include "maps_general.h"
#include "string_map.h"

default_retcode
string_map_builder_add(
        struct string_map_builder *const self,
        const char *const str,
        const size_t strlen)
{
    size_t ind;
    size_t desired_size;
    size_t padding;
    char *dest;

    ind = self->strings.size;
    padding = sizeof(size_t) - (strlen % sizeof(size_t));
    desired_size = sizeof(size_t) + strlen + padding;

    if (chunk_extend_to_fit(&self->strings, desired_size) == ERROR)
        return ERROR;

    self->strings.size += desired_size;

    dest = self->strings.start + ind;
    *((size_t*)dest) = strlen;
    dest += sizeof(size_t);
    memcpy(dest, str, strlen);
    memset(dest + strlen, 0, padding);

    return SUCCESS;
}

