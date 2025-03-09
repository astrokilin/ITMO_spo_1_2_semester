#include <stdint.h>

#include "maps_general.h"
#include "sizes_map.h"

static const uint32_t map_prime_sizes[] = 
{
    31, 67, 137, 277, 557, 1117, 2237, 4481, 8969, 17957, 35923,
    71849, 143711, 287437, 574907, 1149817, 2299637, 4599277,
    9198557, 18397121, 36794267, 73588549, 147177103, 294354217,
    588708451, 1177416931, 2354833867, 4294967291
};

#define BUCKET_0_ENTRY_NOT_EMPTY_FLAG 0x20000000000
#define BUCKET_0_ENTRY_IS_GRAVE_FLAG  0x10000000000
#define BUCKET_1_ENTRY_NOT_EMPTY_FLAG 0x80000000000
#define BUCKET_1_ENTRY_IS_GRAVE_FLAG  0x40000000000
#define BUCKET_2_ENTRY_NOT_EMPTY_FLAG 0x200000000000
#define BUCKET_2_ENTRY_IS_GRAVE_FLAG  0x100000000000

inline static uint64_t
get_0_entry_mode(const uint64_t r_half)
{
    return r_half & __SIZE_DICT_MAX_MODE;
}

inline static uint64_t
get_1_entry_mode(const uint64_t l_half, const uint64_t r_half)
{
    return ((r_half >> __SIZE_DICT_MAX_MODE_BITWIDTH) | (l_half & 0xFFFF));
}

inline static uint64_t
get_2_entry_mode(const uint64_t l_half)
{
    return ((l_half >> 16) & __SIZE_DICT_MAX_MODE);
}

inline static char
entry_0_insert_available(
        const uint64_t r_half,
        const uint64_t l_half,
        const uint64_t mode)
{
    return (get_0_entry_mode(r_half) != mode
            || ((l_half & (BUCKET_0_ENTRY_NOT_EMPTY_FLAG | BUCKET_0_ENTRY_IS_GRAVE_FLAG))
            != BUCKET_0_ENTRY_NOT_EMPTY_FLAG));
}

inline static char
entry_1_insert_available(
        const uint64_t r_half,
        const uint64_t l_half,
        const uint64_t mode)
{
    return (get_1_entry_mode(l_half, r_half) != mode
            || ((l_half & (BUCKET_1_ENTRY_NOT_EMPTY_FLAG | BUCKET_1_ENTRY_IS_GRAVE_FLAG))
            != BUCKET_1_ENTRY_NOT_EMPTY_FLAG));
}

inline static char
entry_2_insert_available(
        const uint64_t l_half,
        const uint64_t mode)
{
    return (get_2_entry_mode(l_half) != mode
            || ((l_half & (BUCKET_0_ENTRY_NOT_EMPTY_FLAG | BUCKET_0_ENTRY_IS_GRAVE_FLAG))
            != BUCKET_0_ENTRY_NOT_EMPTY_FLAG));
}

enum bucket_insert_retval
{
    BUCKET_EXIST,
    BUCKET_INSERTED,
    BUCKET_FULL
};

inline static enum bucket_insert_retval
bucket_insert(
        struct __sizes_map_bucket *const b,
        const struct sizes_map_pair p,
        const uint64_t mode)
{
    uint64_t l_half;
    uint64_t r_half;

    l_half = b->left_half;
    r_half = b->right_half;

    if (entry_0_insert_available(l_half, r_half, mode))
    {
        r_half &= 0xFFFFFF0000000000;        
        r_half |= mode;
        l_half &= !BUCKET_0_ENTRY_IS_GRAVE_FLAG;
        l_half |= BUCKET_0_ENTRY_NOT_EMPTY_FLAG;

        b->left_half = l_half;
        b->right_half = r_half;
        b->place[0] = p;
        return BUCKET_INSERTED;
    }
    else if (b->place[0].key == p.key && b->place[0].val == p.val)
    {
        return BUCKET_EXIST;
    }

    if (entry_1_insert_available(l_half, r_half, mode))
    {
        r_half &= 0x000000FFFFFFFFFF;        
        r_half |= mode << __SIZE_DICT_MAX_MODE_BITWIDTH;
        l_half &= 0xFFFFFFFFFFFF0000 & !BUCKET_1_ENTRY_IS_GRAVE_FLAG;
        r_half |= mode >> (__SIZE_DICT_MAX_MODE_BITWIDTH + 8);
        l_half |= BUCKET_1_ENTRY_NOT_EMPTY_FLAG;

        b->left_half = l_half;
        b->right_half = r_half;
        b->place[1] = p;
        return BUCKET_INSERTED;
    }
    else if (b->place[1].key == p.key && b->place[1].val == p.val)
    {
        return BUCKET_EXIST;
    }

    if (entry_2_insert_available(l_half, mode))
    {
        l_half &= 0xFF0000000000FFFF & !BUCKET_2_ENTRY_IS_GRAVE_FLAG;
        r_half |= mode << 16;
        l_half |= BUCKET_2_ENTRY_NOT_EMPTY_FLAG;

        b->left_half = l_half;
        b->right_half = r_half;
        b->place[2] = p;
        return BUCKET_INSERTED;
    }
    else if (b->place[2].key == p.key && b->place[2].val == p.val)
    {
        return BUCKET_EXIST;
    }

    return BUCKET_FULL;
}
 
enum bucket_search_retval
{
    BUCKET_NOT_FOUND,
    BUCKET_FOUND,
    BUCKET_SEARCH_END
};
 
inline static enum bucket_search_retval
bucket_search(
        const struct __sizes_map_bucket *const b,
        const size_t key,
        const uint64_t mode,
        struct sizes_map_pair *const p)
{
    const uint64_t l_half = b->left_half;
    const uint64_t r_half = b->right_half;

    if (get_0_entry_mode(r_half) == mode && (l_half & BUCKET_0_ENTRY_NOT_EMPTY_FLAG))
    {
        if (!(l_half & BUCKET_0_ENTRY_IS_GRAVE_FLAG) && b->place[0].key == key)
        {
            *p = b->place[0];
            return BUCKET_FOUND;
        }
    }
    else
    {
        return BUCKET_SEARCH_END;
    }

    if (get_1_entry_mode(l_half, r_half) == mode
        && (l_half & BUCKET_1_ENTRY_NOT_EMPTY_FLAG))
    {
        if (!(l_half & BUCKET_1_ENTRY_IS_GRAVE_FLAG) && b->place[1].key == key)
        {
            *p = b->place[1];
            return BUCKET_FOUND;
        }
    }
    else
    {
        return BUCKET_SEARCH_END;
    }

    if (get_2_entry_mode(l_half) == mode && (l_half & BUCKET_1_ENTRY_NOT_EMPTY_FLAG))
    {
        if (!(l_half & BUCKET_2_ENTRY_IS_GRAVE_FLAG) && b->place[2].key == key)
        {
            *p = b->place[2];
            return BUCKET_FOUND;
        }
    }
    else
    {
        return BUCKET_SEARCH_END;
    }

    return BUCKET_NOT_FOUND;
}


inline static enum map_retcode
bucket_arr_insert(
        struct __sizes_map_bucket *const arr,
        const uint32_t cap,
        const struct sizes_map_pair p,
        const unsigned char mode)
{
    const uint32_t start_ind = p.key % cap;

    switch (bucket_insert(&arr[start_ind], p, mode))
    {
        case BUCKET_EXIST:
            return MAP_ELEMENT_EXISTS;

        case BUCKET_INSERTED:
            return MAP_SUCCESS;

        case BUCKET_FULL:
            break;
    }

    for (size_t i = start_ind + 1; i < cap; i++)
    {
        switch (bucket_insert(&arr[i], p, mode))
        {
            case BUCKET_EXIST:
                return MAP_ELEMENT_EXISTS;

            case BUCKET_INSERTED:
                return MAP_SUCCESS;

            case BUCKET_FULL:
                continue;
        }
   }

    // we rotated around the table

    for (size_t i = 0; i < start_ind; i++)
    {
        switch (bucket_insert(&arr[i], p, mode))
        {
            case BUCKET_EXIST:
                return MAP_ELEMENT_EXISTS;

            case BUCKET_INSERTED:
                return MAP_SUCCESS;

            case BUCKET_FULL:
                continue;
        }
   }

    return MAP_FULL;
}

static enum map_retcode
rehash(struct sizes_map *self)
{
    uint32_t i;
    uint64_t mode;
    uint32_t old_cap;
    uint32_t new_cap;
    struct __sizes_map_bucket *arr;
    struct __sizes_map_bucket *new_arr;
    uint64_t l_half;
    uint64_t r_half;
 
    if (self->cap_ind == sizeof(map_prime_sizes) / sizeof(uint32_t) - 1)
        return MAP_SUCCESS;

    i = self->cap_ind;
    old_cap = map_prime_sizes[i];
    new_cap = map_prime_sizes[i + 1];
    arr = self->buckets;
    mode = self->cur_mode;

    new_arr = (struct __sizes_map_bucket*) calloc(
            new_cap, sizeof(struct __sizes_map_bucket));

    if (unlikely(!new_arr))
        return MAP_MEM_ERROR;

    for (i = 0; i < old_cap; i++)
    {
        l_half = arr[i].left_half;
        r_half = arr[i].right_half;

        if (!entry_0_insert_available(l_half, r_half, mode))
            bucket_arr_insert(new_arr, new_cap, arr[i].place[0], 0);

        if (!entry_1_insert_available(l_half, r_half, mode))
            bucket_arr_insert(new_arr, new_cap, arr[i].place[1], 0);

        if (!entry_2_insert_available(l_half, mode))
            bucket_arr_insert(new_arr, new_cap, arr[i].place[2], 0);
    }

    free(arr);
    self->cur_mode = 0;
    self->buckets = new_arr;
    self->cap_ind++;
    self->cap_size = new_cap;
    return MAP_SUCCESS;
}



enum map_retcode
sizes_map_init(struct sizes_map *self)
{
    struct __sizes_map_bucket *p;

    p = (struct __sizes_map_bucket*) calloc(
            (self->cap_size = map_prime_sizes[0]),
            sizeof(struct __sizes_map_bucket));

    if (!p)
        return MAP_MEM_ERROR;

    self->buckets = p;
    self->cur_mode = 0;
    self->cap_ind = 0;
    self->size = 0;
    return MAP_SUCCESS;
}

enum map_retcode
sizes_map_add(
        struct sizes_map *const self,
        const struct sizes_map_pair p)
{
    enum map_retcode res;

    if ((self->size / 9 == self->cap_size / 4) && rehash(self) == MAP_MEM_ERROR)
        return MAP_MEM_ERROR;

    res = bucket_arr_insert(
            self->buckets,
            self->cap_size,
            p,
            self->cur_mode);

    if (res == MAP_SUCCESS)
        self->size++;

    return res;
}

enum sizes_map_get_first_retcode
sizes_map_get_first(
        const struct sizes_map *const self,
        const size_t key,
        struct sizes_map_pair *const p)
{
    const uint64_t mode = self->cur_mode;
    const struct __sizes_map_bucket *arr = self->buckets;
    const uint32_t start_ind = key % self->cap_size;
    const uint32_t cap = self->cap_size;
 
    switch (bucket_search(&arr[start_ind], key, mode, p))
    {
        case BUCKET_FOUND:
            return SIZES_MAP_FOUND;

        case BUCKET_NOT_FOUND:
            break;

        case BUCKET_SEARCH_END:
            return SIZES_MAP_NOT_FOUND;
    }

    for (size_t i = start_ind + 1; i < cap; i++)
    { 
        switch (bucket_search(&arr[start_ind], key, mode, p))
        {
            case BUCKET_FOUND:
                return SIZES_MAP_FOUND;

            case BUCKET_NOT_FOUND:
                continue;

            case BUCKET_SEARCH_END:
                return SIZES_MAP_NOT_FOUND;
        }
    }

    // we rotated around the table

    for (size_t i = 0; i < start_ind; i++)
    {
        switch (bucket_search(&arr[start_ind], key, mode, p))
        {
            case BUCKET_FOUND:
                return SIZES_MAP_FOUND;

            case BUCKET_NOT_FOUND:
                continue;

            case BUCKET_SEARCH_END:
                return SIZES_MAP_NOT_FOUND;
        }
   }

    return SIZES_MAP_NOT_FOUND; 
}
