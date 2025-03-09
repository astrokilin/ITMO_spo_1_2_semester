#ifndef SIZES_MAP_H
#define SIZES_MAP_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "general.h"
#include "maps_general.h"

#define __SIZE_DICT_MAX_MODE            0xFFFFFFFFFF
#define __SIZE_DICT_MAX_MODE_BITWIDTH   40

struct sizes_map_pair
{
    size_t val;
    size_t key;
};


struct __sizes_map_bucket
{
    uint64_t left_half; uint64_t right_half;
    struct sizes_map_pair place[3];
};

struct sizes_map
{
    struct __sizes_map_bucket *buckets;
    uint64_t cur_mode;
    uint32_t size;  
    uint32_t cap_size;
    uint16_t cap_ind;
};

inline static void
sizes_map_deinit(struct sizes_map *const self)
{
    free(self->buckets);
}

inline static void
sizes_map_reset(struct sizes_map *const self)
{
    self->size = 0;

    if (likely(self->cur_mode <= __SIZE_DICT_MAX_MODE))
    {
        self->cur_mode++;
        return;
    }

    // probably this will never happen at all so reseting the map is O(1)
    memset(self->buckets,
           0,
           self->cap_size * sizeof(struct __sizes_map_bucket));
    self->cur_mode = 0;
}

enum map_retcode
sizes_map_init(struct sizes_map*);

enum map_retcode
sizes_map_add(struct sizes_map*, struct sizes_map_pair);

enum sizes_map_get_first_retcode
{
    SIZES_MAP_NOT_FOUND,
    SIZES_MAP_FOUND
};

enum sizes_map_get_first_retcode
sizes_map_get_first(const struct sizes_map*, size_t, struct sizes_map_pair*);

#endif
