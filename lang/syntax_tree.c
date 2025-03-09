#include <stdio.h>

#include "syntax_tree.h"

#define NODE_TYPE_LEAF            0
#define NODE_TYPE_1_CHILD         1
#define NODE_TYPE_2_CHILD         2
#define NODE_TYPE_3_CHILD         3
#define NODE_TYPE_N_CHILD         4
#define NODE_TYPE_PAR_LEAF        5
#define NODE_TYPE_PAR_1_CHILD     6
#define NODE_TYPE_PAR_2_CHILD     7
#define NODE_TYPE_PAR_N_CHILD     8

static const unsigned char
NODE_TYPE_MAP[] =
{
    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_SOURCE

    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_FUNC_DEF
    NODE_TYPE_PAR_N_CHILD,    // SYNTAX_TREE_FUNC_UNTYPED_SIGN
    NODE_TYPE_PAR_N_CHILD,    // SYNTAX_TREE_FUNC_TYPED_SIGN
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_FUNC_UNTYPED_ARG
    NODE_TYPE_PAR_1_CHILD,    // SYNTAX_TREE_FUNC_TYPED_ARG

    NODE_TYPE_PAR_1_CHILD,    // SYNTAX_TREE_STATEMENT_DEFINE
    NODE_TYPE_PAR_2_CHILD,    // SYNTAX_TREE_STATEMENT_DEFINEASSIGN
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_STATEMENT_IF
    NODE_TYPE_3_CHILD,        // SYNTAX_TREE_STATEMENT_IF_ELSE
    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_STATEMENT_WHILE
    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_STATEMENT_UNTIL
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_STATEMENT_REPEAT_WHILE
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_STATEMENT_REPEAT_UNTIL
    NODE_TYPE_LEAF,           // SYNTAX_TREE_STATEMENT_BREAK
    NODE_TYPE_1_CHILD,        // SYNTAX_TREE_STATEMENT_EXP
    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_STATEMENT_BLOCK
    NODE_TYPE_LEAF,           // SYNTAX_TREE_STATEMENT_RETURN
    NODE_TYPE_1_CHILD,        // SYNTAX_TREE_STATEMENT_RETURN_EXP

    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_ASSIGN
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_PLUS
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_MINUS
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_MUL
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_DIV
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_AND
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_OR
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_EQUAL
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_LESS
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_GREATER
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL

    NODE_TYPE_1_CHILD,        // SYNTAX_TREE_EXPR_UNOP_MINUS
    NODE_TYPE_1_CHILD,        // SYNTAX_TREE_EXPR_UNOP_NOT

    NODE_TYPE_N_CHILD,        // SYNTAX_TREE_EXPR_CALL
    NODE_TYPE_3_CHILD,        // SYNTAX_TREE_EXPR_RANGE
    NODE_TYPE_2_CHILD,        // SYNTAX_TREE_EXPR_INDEX

    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_PLACE
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_LITERAL_BOOL
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_LITERAL_CHAR
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_LITERAL_NUM
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_LITERAL_NUM_128
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_EXPR_LITERAL_STR

    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_BOOL
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_BYTE
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_SHORT
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_USHORT
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_INT
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_UINT
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_LONG
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_ULONG
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_HUGE
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_CHAR
    NODE_TYPE_LEAF,           // SYNTAX_TREE_TYPEREF_BUILTIN_STRING
    NODE_TYPE_PAR_LEAF,       // SYNTAX_TREE_TYPEREF_CUSTOM
    NODE_TYPE_PAR_1_CHILD     // SYNTAX_TREE_TYPEREF_ARRAY
};

struct ast_node_location*
ast_node_get_location(const union ast_node_ptr node)
{
    char *node_b;

    node_b = node.unknown;

    switch (NODE_TYPE_MAP[node.header->type])
    {
        case NODE_TYPE_LEAF:
            node_b += sizeof(struct ast_node_leaf);
            break;

        case NODE_TYPE_1_CHILD:
            node_b += sizeof(struct ast_node_1_child);
            break;

        case NODE_TYPE_2_CHILD:
            node_b += sizeof(struct ast_node_2_child);
            break;

        case NODE_TYPE_3_CHILD:
            node_b += sizeof(struct ast_node_3_child);
            break;

        case NODE_TYPE_N_CHILD:
            node_b += sizeof(struct __ast_node_children_header)
                      + AST_NODE_N_CHILD_NUM(node) * sizeof(size_t);
            break;
        
        case NODE_TYPE_PAR_LEAF:
            node_b += sizeof(struct ast_par_node_leaf);
            break;

        case NODE_TYPE_PAR_1_CHILD:
            node_b += sizeof(struct ast_par_node_1_child);
            break;

        case NODE_TYPE_PAR_2_CHILD:
            node_b += sizeof(struct ast_par_node_2_child);
            break;

        case NODE_TYPE_PAR_N_CHILD:
            node_b += sizeof(struct __ast_par_node_children_header)
                      + AST_PAR_NODE_N_CHILD_NUM(node) * sizeof(size_t);
            break;
    }

    return (struct ast_node_location*) node_b;
}

DEFINE_TYPED_CHUNK_LIST(long_stack, size_t)

inline static default_retcode
syntax_tree_add_obj(
        struct extendable_chunk *const self,
        const void *obj,
        const size_t obj_byte_size)
{
    if (chunk_append_from(self, obj, obj_byte_size) == ERROR)
        return ERROR;

    return SUCCESS;
}

inline static default_retcode
syntax_tree_add_comp_obj(
        struct extendable_chunk *const self,
        const void *const obj_half_1,
        const size_t obj_half_1_byte_size,
        const void *const obj_half_2,
        const size_t obj_half_2_byte_size)
{
    if (chunk_append_from(self, obj_half_1, obj_half_1_byte_size) == ERROR)
        return ERROR;
 
    if (chunk_append_from(self, obj_half_2, obj_half_2_byte_size) == ERROR)
        return ERROR;

    return SUCCESS;
}

inline static void
syntax_tree_remove_top_node_subtree(
        struct extendable_chunk *const self,
        size_t cur_node_ind)
{
    union ast_node_ptr node;

    char *const nodes_base = self->start;

    while (1)
    {
        node.unknown = nodes_base + cur_node_ind; 

        switch (NODE_TYPE_MAP[node.header->type])
        {
            case NODE_TYPE_LEAF:
            case NODE_TYPE_PAR_LEAF:
                self->size = cur_node_ind;
                return;

            case NODE_TYPE_1_CHILD:
                cur_node_ind = AST_NODE_1_CHILD(node);
                break;

            case NODE_TYPE_2_CHILD:
                cur_node_ind = AST_NODE_1_CHILD(node);
                break;

            case NODE_TYPE_3_CHILD:
                cur_node_ind = AST_NODE_1_CHILD(node);
                break;

            case NODE_TYPE_N_CHILD:
                cur_node_ind = AST_NODE_N_CHILD_ARR(node)[0];
                break;

            case NODE_TYPE_PAR_1_CHILD:
                cur_node_ind = AST_PAR_NODE_1_CHILD(node);
                break;

            case NODE_TYPE_PAR_2_CHILD:
                cur_node_ind = AST_PAR_NODE_1_CHILD(node);
                break;

            case NODE_TYPE_PAR_N_CHILD:
                cur_node_ind = AST_PAR_NODE_N_CHILD_ARR(node)[0];
                break;
        }
    }
}

inline static default_retcode
syntax_tree_add_pos(
        struct extendable_chunk *const self,
        const int line_num,
        const int columnt_num)
{
    int *pos_place;

    if (chunk_extend_to_fit(self, 2 * sizeof(int)) == ERROR)
        return ERROR;

    pos_place = (int*)(self->start + self->size);
    self->size += 2 * sizeof(int);
    pos_place[0] = line_num;
    pos_place[1] = columnt_num;

    return SUCCESS;
}

//--------------------------- resources addition subroutines -----------------------------

static const uint32_t map_prime_sizes[] = 
{
    31, 67, 137, 277, 557, 1117, 2237, 4481, 8969, 17957, 35923,
    71849, 143711, 287437, 574907, 1149817, 2299637, 4599277,
    9198557, 18397121, 36794267, 73588549, 147177103, 294354217,
    588708451, 1177416931, 2354833867, 4294967291
};

static inline uint32_t
str_djb2_hash(const char *str, size_t len)
{
    uint32_t hash = 5381;

    while (len--)
        hash = ((hash << 5) + hash) + *str++;

    return hash;
}

static inline uint32_t
num_djb2_hash(const uint64_t num)
{
    uint32_t hash = 5381;

    hash = ((hash << 5) + hash) + ((uint32_t)num);
    hash = ((hash << 5) + hash) + ((uint32_t)(num >> 32));
    return hash;
}

static inline uint32_t
big_num_djb2_hash(const uint128_t num)
{
    uint64_t half = uint128_to_i64(num);
    uint32_t hash = 5381;

    hash = ((hash << 5) + hash) + ((uint32_t)half);
    hash = ((hash << 5) + hash) + ((uint32_t)(half >> 32));
    half = uint128_high_half(num);
    hash = ((hash << 5) + hash) + ((uint32_t)half);
    hash = ((hash << 5) + hash) + ((uint32_t)(half >> 32));
    return hash;
}


enum uint128_from_string_retcode
{
    UINT128_T_FROM_STRING_SUCCESS,
    UINT128_T_FROM_STRING_OVERFLOW
};

inline static enum uint128_from_string_retcode
uint128_from_string(const char *str, size_t string_len, uint128_t *place)
{
    size_t string_len_rem;
    size_t string_len_main;
    char overflowed;
    uint128_t res = uint128_from_i64(0);
    uint64_t res_part = 0;
    char ovf = 0;

    if (str[0] != '0')
    {
        string_len_rem = string_len % 19;
        string_len_main = string_len / 19;

        while (string_len_rem--)
            res_part = res_part * 10 + (*str++ & 15);

        res = uint128_add_i64(res, res_part);

        while (string_len_main--)
        {
            res_part = (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);
            res_part = res_part * 10 + (*str++ & 15);

            res = uint128_mul_i64_overflow(res, 0x8AC7230489E80000, &overflowed);
            ovf |= overflowed;

            res = uint128_add_i64_overflow(res, res_part, &overflowed);
            ovf |= overflowed;

            res_part = 0;
        }

        *place = res;

        if (ovf)
        {
            res = uint128_from_i64(uint128_to_i64(res));
            return UINT128_T_FROM_STRING_OVERFLOW;
        }

        return UINT128_T_FROM_STRING_SUCCESS;
    }

    switch (str[1])
    {
        case 'x':
        case 'X':
            str += 2;
            string_len -= 2;
            //TODO: add support for hex constants
            break;

        case 'b':
        case 'B':
            str += 2;
            string_len -= 2;
            //TODO: add support for hex constants
            break;
    }

    return UINT128_T_FROM_STRING_SUCCESS;
}

inline static default_retcode
uint64_chunk_append(struct extendable_chunk *const self, const uint64_t x)
{
    if (chunk_extend_to_fit(self, sizeof(uint64_t)) == ERROR)
        return ERROR;

    *(uint64_t*)(self->start + self->size) = x;
    self->size += sizeof(uint64_t);
    return SUCCESS;
}

inline static default_retcode
uint128_chunk_append(struct extendable_chunk *const self, const uint128_t x)
{
    if (chunk_extend_to_fit(self, sizeof(uint128_t)) == ERROR)
        return ERROR;

    *(uint128_t*)(self->start + self->size) = x;
    self->size += sizeof(uint128_t);
    return SUCCESS;
}

inline static default_retcode
hash_map_init(struct __ast_builder_hash_tbl *const map)
{
    struct __ast_builder_hash_entry *p;

    p = (struct __ast_builder_hash_entry*)
        calloc(map_prime_sizes[1], sizeof(struct __ast_builder_hash_entry));

    if (!p)
        return ERROR;

    map->entries = p; 
    map->cap_ind = 1;
    map->size = 0;
    return SUCCESS;
}

inline static void
hash_map_deinit(struct __ast_builder_hash_tbl *const map)
{
    free(map->entries);
}

inline static void
hash_map_insert(
        struct __ast_builder_hash_tbl *const map,
        const uint32_t ind,
        const struct __ast_builder_hash_entry entr)
{
    map->size++;
    map->entries[ind] = entr;
}

static default_retcode
rehash(struct __ast_builder_hash_tbl *self)
{
    size_t i;
    uint32_t ind;
    uint32_t old_cap;
    uint32_t new_cap;
    struct __ast_builder_hash_entry *arr;
    struct __ast_builder_hash_entry *new_arr;
    struct __ast_builder_hash_entry tmp_entry;

    if (self->cap_ind == sizeof(map_prime_sizes) / sizeof(uint32_t) - 1)
        return SUCCESS;

    new_cap = map_prime_sizes[self->cap_ind + 1];
    old_cap = map_prime_sizes[self->cap_ind];
    arr = self->entries;

    new_arr = (struct __ast_builder_hash_entry*)
              calloc(new_cap, sizeof(struct __ast_builder_hash_entry));

    if (!new_arr)
        return ERROR;

    for (i = 0; i < old_cap; i++)
    {
        if ((tmp_entry.str_ind = arr[i].str_ind))
        {
            tmp_entry.hash = arr[i].hash;
            new_arr[tmp_entry.hash % new_cap] = tmp_entry;
            break;
        }
    }

OUTER_CYCLE:
    for (i++; i < old_cap; i++)
    {
        if ((tmp_entry.str_ind = arr[i].str_ind))
        {
            tmp_entry.hash = arr[i].hash;
            ind = tmp_entry.hash % new_cap;

            if (!new_arr[ind].str_ind)
            {
                new_arr[ind] = tmp_entry;
                goto OUTER_CYCLE;
            }

            for (size_t j = ind + 1; j < new_cap; j++)
            {
                if (!new_arr[j].str_ind)
                {
                    new_arr[j] = tmp_entry;
                    goto OUTER_CYCLE;
                }
            }

            for (size_t j = 0; j <= ind; j++)
            {
                if (!new_arr[j].str_ind)
                {
                    new_arr[j] = tmp_entry;
                    goto OUTER_CYCLE;
                }
            }
        }
    }

    free(arr);
    self->entries = new_arr;
    self->cap_ind++;
    return SUCCESS;
}

inline static default_retcode
hash_map_check_rehash(struct __ast_builder_hash_tbl *const map)
{
    if ((map->size / 3 >= map_prime_sizes[map->cap_ind] / 4) && rehash(map) == ERROR)
        return ERROR;
    
    return SUCCESS;
}

//------------------------------ ast builder public funcs --------------------------------

#define AST_NODE_PREALLOC_BYTES               8096
#define AST_BUILDER_STACK_NODE_NUM_PREALLOC   32
#define AST_BUILDER_CHUNK_64_PRALLOC_BYTES    512 // should be >= 8
#define AST_BUILDER_CHUNK_128_PRALLOC_BYTES   128 // should be >= 16
default_retcode
ast_builder_init(struct ast_builder *self)
{
    if (chunk_init(&self->tree, AST_NODE_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_0;

    if (chunk_init(&self->nodes_stack,
                   AST_BUILDER_STACK_NODE_NUM_PREALLOC * sizeof(size_t))
        == ERROR)
        goto ERROR_EXIT_1;

    if (string_map_builder_init(&self->string_builder, sizeof(size_t)) == ERROR)
        goto ERROR_EXIT_2;

    if (chunk_init(&self->uint64_chunk, AST_BUILDER_CHUNK_64_PRALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_3;

    self->uint64_chunk.size = sizeof(uint64_t);

    if (chunk_init(&self->uint128_chunk, AST_BUILDER_CHUNK_128_PRALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_4;

    // ensure 16 byte alligment
    self->uint128_chunk.size = ((uintptr_t)self->uint128_chunk.start) % 16 + 16;

    if (hash_map_init(&self->uint64_map) == ERROR)
        goto ERROR_EXIT_5;

    if (hash_map_init(&self->uint128_map) == ERROR)
        goto ERROR_EXIT_6;

    if (hash_map_init(&self->strings_map) == ERROR)
        goto ERROR_EXIT_7;

    return SUCCESS;

ERROR_EXIT_7:
    hash_map_deinit(&self->uint128_map);
ERROR_EXIT_6:
    hash_map_deinit(&self->uint64_map);
ERROR_EXIT_5:
    chunk_deinit(&self->uint128_chunk);
ERROR_EXIT_4:
    chunk_deinit(&self->uint64_chunk);
ERROR_EXIT_3:
    string_map_builder_deinit(&self->string_builder);
ERROR_EXIT_2:
    chunk_deinit(&self->nodes_stack);
ERROR_EXIT_1:
    chunk_deinit(&self->tree);
ERROR_EXIT_0: 
    return ERROR;
}

void
ast_builder_deinit(struct ast_builder *const self)
{
    hash_map_deinit(&self->uint128_map);
    hash_map_deinit(&self->uint64_map);
    chunk_deinit(&self->uint128_chunk);
    chunk_deinit(&self->uint64_chunk);
    string_map_builder_deinit(&self->string_builder);
    chunk_deinit(&self->nodes_stack);
    chunk_deinit(&self->tree);
}

default_retcode
ast_builder_finish(struct ast_builder *const self, struct syntax_tree *const tree)
{
    if (chunk_slim_down(&self->tree) == ERROR)
        return ERROR;

    if (chunk_slim_down(&self->uint64_chunk) == ERROR)
        return ERROR;

    if (chunk_slim_down(&self->uint128_chunk) == ERROR)
        return ERROR;

    if (string_map_builder_finish(&self->string_builder, &tree->strings) == ERROR)
        return ERROR;

    tree->tree = self->tree.start;
    tree->numbers = self->uint64_chunk.start;
    tree->big_numbers = self->uint128_chunk.start;
     // at the end stack contains only one entry
    tree->top_ind = *((size_t*) self->nodes_stack.start);

    chunk_deinit(&self->nodes_stack);
    hash_map_deinit(&self->uint128_map);
    hash_map_deinit(&self->uint64_map);
    return SUCCESS;
}


enum ast_builder_add_res_num_retcode
ast_builder_add_res_num(
        struct ast_builder *const self,
        const char *const str,
        const size_t strlen,
        size_t *const result_ind)
{
    size_t hash_ind; 
    size_t cur_cap;
    char  *cur_chunk_base;
    size_t cur_str;
    struct __ast_builder_hash_entry entr;
    struct __ast_builder_hash_entry *arr;
    struct __ast_builder_hash_tbl *map;
    uint128_t res = uint128_from_i64(0);
    uint64_t half;

    if (uint128_from_string(str, strlen, &res) == UINT128_T_FROM_STRING_OVERFLOW
        || uint128_high_half(res) == 0)
    {
        half = uint128_to_i64(res);
        map = &self->uint64_map; 

        if (hash_map_check_rehash(map) == ERROR)
            return AST_BUILDER_ADD_RES_NUM_ERROR;

        cur_cap = map_prime_sizes[map->cap_ind];
        entr.hash = num_djb2_hash(uint128_to_i64(res));
        hash_ind = entr.hash % cur_cap;

        cur_chunk_base = self->uint64_chunk.start;
        entr.str_ind = self->uint64_chunk.size;
        arr = map->entries;

        if (!(cur_str = arr[hash_ind].str_ind))
        {
            if (uint64_chunk_append(&self->uint64_chunk, half) == ERROR)
                return AST_BUILDER_ADD_RES_NUM_ERROR;

            hash_map_insert(map, hash_ind, entr);
            *result_ind = entr.str_ind;
            return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
        }
        else if (arr[hash_ind].hash == entr.hash
                 && half == *(uint64_t*)(cur_chunk_base + cur_str))
        {
            *result_ind = cur_str;
            return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
        }

        for (size_t i = hash_ind + 1; i < cur_cap; i++)
        {
            if (!(cur_str = arr[i].str_ind))
            {
                if (uint64_chunk_append(&self->uint64_chunk, half) == ERROR)
                    return AST_BUILDER_ADD_RES_NUM_ERROR;

                hash_map_insert(map, i, entr);
                *result_ind = entr.str_ind;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
            }
            else if (arr[i].hash == entr.hash
                     && half == *(uint64_t*)(cur_chunk_base + cur_str))
            {
                *result_ind = cur_str;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
            }
        }

        for (size_t i = 0; i < hash_ind; i++)
        {
            if (!(cur_str = arr[i].str_ind))
            {
                if (uint64_chunk_append(&self->uint64_chunk, half) == ERROR)
                    return AST_BUILDER_ADD_RES_NUM_ERROR;

                hash_map_insert(map, i, entr);
                *result_ind = entr.str_ind;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
            }
            else if (arr[i].hash == entr.hash
                     && half == *(uint64_t*)(cur_chunk_base + cur_str))
            {
                *result_ind = cur_str;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL;
            }
        }
    }
    else
    {
        map = &self->uint128_map; 

        if (hash_map_check_rehash(map) == ERROR)
            return AST_BUILDER_ADD_RES_NUM_ERROR;

        cur_cap = map_prime_sizes[map->cap_ind];
        entr.hash = big_num_djb2_hash(res);
        hash_ind = entr.hash % cur_cap;

        cur_chunk_base = self->uint128_chunk.start;
        entr.str_ind = self->uint128_chunk.size;
        arr = map->entries;

        if (!(cur_str = arr[hash_ind].str_ind))
        {
            if (uint128_chunk_append(&self->uint128_chunk, res) == ERROR)
                return AST_BUILDER_ADD_RES_NUM_ERROR;

            hash_map_insert(map, hash_ind, entr);
            *result_ind = entr.str_ind;
            return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
        }
        else if (arr[hash_ind].hash == entr.hash
                 && uint128_cmp(res, *(uint128_t*)(cur_chunk_base + cur_str)))
        {
            *result_ind = cur_str;
            return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
        }

        for (size_t i = hash_ind + 1; i < cur_cap; i++)
        {
            if (!(cur_str = arr[i].str_ind))
            {
                if (uint128_chunk_append(&self->uint128_chunk, res) == ERROR)
                    return AST_BUILDER_ADD_RES_NUM_ERROR;

                hash_map_insert(map, i, entr);
                *result_ind = entr.str_ind;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
            }
            else if (arr[i].hash == entr.hash
                     && uint128_cmp(res, *(uint128_t*)(cur_chunk_base + cur_str)))
            {
                *result_ind = cur_str;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
            }
        }

        for (size_t i = 0; i < hash_ind; i++)
        {
            if (!(cur_str = arr[i].str_ind))
            {
                if (uint128_chunk_append(&self->uint128_chunk, res) == ERROR)
                    return AST_BUILDER_ADD_RES_NUM_ERROR;

                hash_map_insert(map, i, entr);
                *result_ind = entr.str_ind;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
            }
            else if (arr[i].hash == entr.hash
                     && uint128_cmp(res, *(uint128_t*)(cur_chunk_base + cur_str)))
            {
                *result_ind = cur_str;
                return AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG;
            }
        }
    }

    return AST_BUILDER_ADD_RES_NUM_NO_SPACE;
}

default_retcode
ast_builder_res_num_reinsert_128_as_64(
        struct ast_builder *const self,
        const size_t ind,
        size_t *const new_ind)
{
    uint64_t val = uint128_to_i64(*(uint128_t*)(self->uint128_chunk.start + ind));  
    *new_ind = self->uint64_chunk.size;
    return uint64_chunk_append(&self->uint64_chunk, val);
}


enum ast_builder_add_res_str_retcode
ast_builder_add_res_str(
        struct ast_builder *const self,
        const char *const str,
        const size_t strlen,
        size_t *const result_ind)
{
    size_t hash_ind; 
    size_t cur_cap;
    char  *cur_str_base;
    size_t cur_str;
    struct __ast_builder_hash_entry entr;
    struct __ast_builder_hash_entry *arr;
    struct __ast_builder_hash_tbl *map;

    map = &self->strings_map;

    if (hash_map_check_rehash(map) == ERROR)
        return AST_BUILDER_ADD_RES_STR_ERROR;

    cur_cap = map_prime_sizes[map->cap_ind];
    entr.hash = str_djb2_hash(str, strlen);
    hash_ind = entr.hash % cur_cap;

    entr.str_ind = self->string_builder.strings.size;
    cur_str_base = self->string_builder.strings.start;
    arr = map->entries;

    if (!(cur_str = arr[hash_ind].str_ind))
    {
        if (string_map_builder_add(&self->string_builder, str, strlen) == ERROR)
            return AST_BUILDER_ADD_RES_STR_ERROR;

        hash_map_insert(map, hash_ind, entr);
        *result_ind = entr.str_ind;
        return AST_BUILDER_ADD_RES_STR_SUCCESS;
    }
    else if (arr[hash_ind].hash == entr.hash && !strcmp(str, cur_str_base + cur_str))
    {
        *result_ind = cur_str;
        return AST_BUILDER_ADD_RES_STR_SUCCESS;
    }

    for (size_t i = hash_ind + 1; i < cur_cap; i++)
    {
        if (!(cur_str = arr[i].str_ind))
        {
            if (string_map_builder_add(&self->string_builder, str, strlen) == ERROR)
                return AST_BUILDER_ADD_RES_STR_ERROR;

            hash_map_insert(map, hash_ind, entr);
            *result_ind = entr.str_ind;
            return AST_BUILDER_ADD_RES_STR_SUCCESS;
        }
        else if (arr[i].hash == entr.hash && !strcmp(str, cur_str_base + cur_str))
        {
            *result_ind = cur_str;
            return AST_BUILDER_ADD_RES_STR_SUCCESS;
        }
    }

    for (size_t i = 0; i < hash_ind; i++)
    {
        if (!(cur_str = arr[i].str_ind))
        {
            if (string_map_builder_add(&self->string_builder, str, strlen) == ERROR)
                return AST_BUILDER_ADD_RES_STR_ERROR;

            *result_ind = entr.str_ind;
            hash_map_insert(map, hash_ind, entr);
            return AST_BUILDER_ADD_RES_STR_SUCCESS;
        }
        else if (arr[i].hash == entr.hash && !strcmp(str, cur_str_base + cur_str))
        {
            *result_ind = cur_str;
            return AST_BUILDER_ADD_RES_STR_SUCCESS;
        }
    }

    return AST_BUILDER_ADD_RES_STR_NO_SPACE;
}


void
ast_builder_remove_node(struct ast_builder *self)
{
    syntax_tree_remove_top_node_subtree(&self->tree, long_stack_pop(&self->nodes_stack));
}

default_retcode
ast_builder_save_node_pos(
        struct ast_builder *const self,
        const int line_num,
        const int columnt_num)
{
    return syntax_tree_add_pos(&self->tree, line_num, columnt_num);
}

default_retcode
ast_builder_new_node_leaf(
        struct ast_builder *const self,
        const unsigned char t)
{
    size_t this_node_ind;
    struct ast_node_leaf res;
    struct extendable_chunk *ast;

    ast = &self->tree;
    this_node_ind = ast->size;

    res.header.type = t;

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_node_leaf)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_node_1_child(
        struct ast_builder *const self,
        const unsigned char t)
{
    size_t this_node_ind;
    struct ast_node_1_child res;
    struct extendable_chunk *ast;

    ast = &self->tree;
    this_node_ind = ast->size;

    res.header.type = t;
    res.child_1 = long_stack_pop(&self->nodes_stack);

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_node_1_child)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_node_2_child(
        struct ast_builder *const self,
        const unsigned char t)
{
    size_t this_node_ind;
    struct extendable_chunk *stack;
    struct ast_node_2_child res;
    struct extendable_chunk *ast;
    size_t *child_ind_arr;

    ast = &self->tree;
    this_node_ind = ast->size;
    stack = &self->nodes_stack;
    long_stack_truncate(stack, 2);
    child_ind_arr = (size_t*) (stack->start + stack->size);

    res.parent_struct.header.type = t;
    res.parent_struct.child_1 = child_ind_arr[0];
    res.child_2 = child_ind_arr[1];

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_node_2_child)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_node_3_child(
        struct ast_builder *const self,
        const unsigned char t)
{
    size_t this_node_ind;
    struct ast_node_3_child res;
    struct extendable_chunk *stack;
    struct extendable_chunk *ast;
    size_t *child_ind_arr;

    ast = &self->tree;
    this_node_ind = ast->size;
    stack = &self->nodes_stack;
    long_stack_truncate(stack, 3);
    child_ind_arr = (size_t*) (stack->start + stack->size);

    res.parent_struct.parent_struct.header.type = t;
    res.parent_struct.parent_struct.child_1 = child_ind_arr[0];
    res.parent_struct.child_2 = child_ind_arr[1];
    res.child_3 = child_ind_arr[2];

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_node_3_child)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_node_N_child(
        struct ast_builder *const self,
        const unsigned char t,
        const size_t N)
{
    size_t this_node_ind;
    struct __ast_node_children_header res;
    struct extendable_chunk *stack;
    struct extendable_chunk *ast;;
    size_t children_size;

    ast = &self->tree;
    this_node_ind = ast->size;
    stack = &self->nodes_stack;

    res.header.type = t;
    res.num = N;

    long_stack_truncate(stack, N);
    children_size = sizeof(size_t) * N;

    if (syntax_tree_add_comp_obj(ast,
                                &res,
                                sizeof(struct __ast_node_children_header),
                                stack->start + stack->size,
                                children_size) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_par_node_leaf(
        struct ast_builder *self,
        const unsigned char t,
        const union ast_node_param p)
{
    size_t this_node_ind;
    struct ast_par_node_leaf res;
    struct extendable_chunk *ast;

    ast = &self->tree;
    this_node_ind = ast->size;

    res.header.header.type = t;
    res.header.parameter = p;

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_par_node_leaf)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_par_node_1_child(
        struct ast_builder *self,
        const unsigned char t,
        const union ast_node_param p)
{
    size_t this_node_ind;
    struct ast_par_node_1_child res;
    struct extendable_chunk *ast;

    ast = &self->tree;
    this_node_ind = ast->size;

    res.header.header.type = t;
    res.header.parameter = p;
    res.child_1 = long_stack_pop(&self->nodes_stack);

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_par_node_1_child)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_par_node_2_child(
        struct ast_builder *self,
        const unsigned char t,
        const union ast_node_param p)
{
    size_t this_node_ind;
    struct ast_par_node_2_child res;
    struct extendable_chunk *stack;
    struct extendable_chunk *ast;
    size_t *child_ind_arr;

    ast = &self->tree;
    this_node_ind = ast->size;
    stack = &self->nodes_stack;
    long_stack_truncate(stack, 2);
    child_ind_arr = (size_t*) (stack->start + stack->size);

    res.parent_struct.header.header.type = t;
    res.parent_struct.header.parameter = p;
    res.parent_struct.child_1 = child_ind_arr[0];
    res.child_2 = child_ind_arr[1];

    if (syntax_tree_add_obj(ast, &res, sizeof(struct ast_par_node_2_child)) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

default_retcode
ast_builder_new_par_node_N_child(
        struct ast_builder *self,
        const unsigned char t,
        const union ast_node_param p,
        const size_t N)
{
    size_t this_node_ind;
    struct __ast_par_node_children_header res;
    struct extendable_chunk *stack;
    struct extendable_chunk *ast;
    size_t children_size;

    ast = &self->tree;
    this_node_ind = ast->size;
    stack = &self->nodes_stack;

    res.header.header.type = t;
    res.header.parameter = p;
    res.num = N;

    long_stack_truncate(stack, N);
    children_size = sizeof(size_t) * N;

    if (syntax_tree_add_comp_obj(ast,
                                &res,
                                sizeof(struct __ast_par_node_children_header),
                                stack->start + stack->size,
                                children_size) == ERROR)
        return ERROR;

    return long_stack_append(&self->nodes_stack, this_node_ind);
}

//------------------------------- ast to dot file stuff ----------------------------------

struct dot_file_builder
{
    #define __DOT_FILE_CONTENTS_STRING_PREALLOC 128
    struct extendable_chunk nodes_decl_string;
    struct extendable_chunk nodes_conn_string;
    struct syntax_tree tree;
};

#define NODE_TYPE_TO_STR_MAX_SIZE 24 // size of longest string from this table
static const char*
node_type_t_to_str_map[] = {
    "source",                 // SYNTAX_TREE_SOURCE

    "func def",               // SYNTAX_TREE_FUNC_DEF
    "func sign untyped",      // SYNTAX_TREE_FUNC_UNTYPED_SIGN
    "func sign typed",        // SYNTAX_TREE_FUNC_TYPED_SIGN
    "func arg untyped",       // SYNTAX_TREE_FUNC_UNTYPED_ARG
    "func arg typed",         // SYNTAX_TREE_FUNC_TYPED_ARG

    "variable define",        // SYNTAX_TREE_STATEMENT_DEFINE
    "variable define assign", // SYNTAX_TREE_STATEMENT_DEFINEASSIGN
    "if",                     // SYNTAX_TREE_STATEMENT_IF
    "if else",                // SYNTAX_TREE_STATEMENT_IF_ELSE
    "while",                  // SYNTAX_TREE_STATEMENT_WHILE
    "until",                  // SYNTAX_TREE_STATEMENT_UNTIL
    "repeat while",           // SYNTAX_TREE_STATEMENT_REPEAT_WHILE
    "repeat until",           // SYNTAX_TREE_STATEMENT_REPEAT_UNTIL
    "break",                  // SYNTAX_TREE_STATEMENT_BREAK
    "expression",             // SYNTAX_TREE_STATEMENT_EXP
    "block",                  // SYNTAX_TREE_STATEMENT_BLOCK
    "return",                 // SYNTAX_TREE_STATEMENT_RETURN
    "return expression",      // SYNTAX_TREE_STATEMENT_RETURN_EXP

    "=",                      // SYNTAX_TREE_EXPR_BINOP_ASSIGN
    "+",                      // SYNTAX_TREE_EXPR_BINOP_PLUS
    "-",                      // SYNTAX_TREE_EXPR_BINOP_MINUS
    "*",                      // SYNTAX_TREE_EXPR_BINOP_MUL
    "/",                      // SYNTAX_TREE_EXPR_BINOP_DIV
    "and",                    // SYNTAX_TREE_EXPR_BINOP_AND
    "or",                     // SYNTAX_TREE_EXPR_BINOP_OR
    "==",                     // SYNTAX_TREE_EXPR_BINOP_EQUAL
    "!=",                     // SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL
    "<",                      // SYNTAX_TREE_EXPR_BINOP_LESS
    "<=",                     // SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL
    ">",                      // SYNTAX_TREE_EXPR_BINOP_GREATER
    ">=",                     // SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL

    "-",                      // SYNTAX_TREE_EXPR_UNOP_MINUS
    "not",                    // SYNTAX_TREE_EXPR_UNOP_NOT

    "call",                   // SYNTAX_TREE_EXPR_CALL
    "range",                  // SYNTAX_TREE_EXPR_RANGE
    "index",                  // SYNTAX_TREE_EXPR_INDEX

    "place",                  // SYNTAX_TREE_EXPR_PLACE
    "bool",                   // SYNTAX_TREE_EXPR_LITERAL_BOOL
    "char",                   // SYNTAX_TREE_EXPR_LITERAL_CHAR
    "numeral",                // SYNTAX_TREE_EXPR_LITERAL_NUM
    "128 bit numeral",        // SYNTAX_TREE_EXPR_LITERAL_NUM_128
    "literal",                // SYNTAX_TREE_EXPR_LITERAL_STR

    "typeref boolean",        // SYNTAX_TREE_TYPEREF_BUILTIN_BOOL
    "typeref byte",           // SYNTAX_TREE_TYPEREF_BUILTIN_BYTE
    "typeref unsigned byte",  // SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE
    "typeref short",          // SYNTAX_TREE_TYPEREF_BUILTIN_SHORT
    "typeref unsigned short", // SYNTAX_TREE_TYPEREF_BUILTIN_USHORT
    "typeref int",            // SYNTAX_TREE_TYPEREF_BUILTIN_INT
    "typeref unsigned int",   // SYNTAX_TREE_TYPEREF_BUILTIN_UINT
    "typeref long",           // SYNTAX_TREE_TYPEREF_BUILTIN_LONG
    "typeref unsigned long",  // SYNTAX_TREE_TYPEREF_BUILTIN_ULONG
    "typeref i128",           // SYNTAX_TREE_TYPEREF_BUILTIN_HUGE
    "typeref u128",           // SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE
    "typeref char",           // SYNTAX_TREE_TYPEREF_BUILTIN_CHAR
    "typeref string",         // SYNTAX_TREE_TYPEREF_BUILTIN_STRING
    "typeref custom type",    // SYNTAX_TREE_TYPEREF_CUSTOM
    "typeref array type"      // SYNTAX_TREE_TYPEREF_ARRAY
};

// max len of %ld is 20 digits => max len of node_entry is 20 + 14 bytes
#define NODE_ENTRY_PREFIX_SIZE 10
static const char node_entry_prefix[] = "\t%ld\t[label=\"%s";

#define NODE_ENTRY_POSTFIX_SIZE 4
static const char node_entry_postfix[] = "\"];\n";

#define NODE_ENTRY_PAR_STR_SIZE 2
static const char node_entry_par_str[] = "\\n%s";
#define NODE_ENTRY_PAR_NUM_SIZE 22
static const char node_entry_par_num[] = "\\n%ld";
#define NODE_ENTRY_PAR_NUM_BIG_SIZE 41
static const char node_entry_par_num_big[] = "\\n(%018lx %018lx)";

#define LOC_ENTRY_STR_MAX_LEN 31
static const char node_entry_loc[] = "\\npos: (%d, %d)";


#define PRINT_PAR_NOPE          0
#define PRINT_PAR_STR           1
#define PRINT_PAR_NUM           2
#define PRINT_PAR_NUM_BIG       3
#define PRINT_PAR_PAR           4
static const unsigned char
node_print_par_guide[] =
{
    PRINT_PAR_NOPE,      // SYNTAX_TREE_SOURCE

    PRINT_PAR_NOPE,      // SYNTAX_TREE_FUNC_DEF
    PRINT_PAR_STR,       // SYNTAX_TREE_FUNC_UNTYPED_SIGN
    PRINT_PAR_STR,       // SYNTAX_TREE_FUNC_TYPED_SIGN
    PRINT_PAR_STR,       // SYNTAX_TREE_FUNC_UNTYPED_ARG
    PRINT_PAR_STR,       // SYNTAX_TREE_FUNC_TYPED_ARG

    PRINT_PAR_STR,       // SYNTAX_TREE_STATEMENT_DEFINE
    PRINT_PAR_STR,       // SYNTAX_TREE_STATEMENT_DEFINEASSIGN
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_IF
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_IF_ELSE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_WHILE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_UNTIL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_REPEAT_WHILE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_REPEAT_UNTIL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_BREAK
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_EXP
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_BLOCK
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_RETURN
    PRINT_PAR_NOPE,      // SYNTAX_TREE_STATEMENT_RETURN_EXP

    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_ASSIGN
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_PLUS
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_MINUS
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_MUL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_DIV
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_AND
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_OR
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_EQUAL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_LESS
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_GREATER
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL

    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_UNOP_MINUS
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_UNOP_NOT

    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_CALL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_RANGE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_EXPR_INDEX

    PRINT_PAR_STR,       // SYNTAX_TREE_EXPR_PLACE
    PRINT_PAR_PAR,       // SYNTAX_TREE_EXPR_LITERAL_BOOL
    PRINT_PAR_PAR,       // SYNTAX_TREE_EXPR_LITERAL_CHAR
    PRINT_PAR_NUM,       // SYNTAX_TREE_EXPR_LITERAL_NUM
    PRINT_PAR_NUM_BIG,   // SYNTAX_TREE_EXPR_LITERAL_NUM_128
    PRINT_PAR_STR,       // SYNTAX_TREE_EXPR_LITERAL_STR

    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_BOOL
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_BYTE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_SHORT
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_USHORT
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_INT
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_UINT
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_LONG
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_ULONG
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_HUGE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_CHAR
    PRINT_PAR_NOPE,      // SYNTAX_TREE_TYPEREF_BUILTIN_STRING
    PRINT_PAR_STR,       // SYNTAX_TREE_TYPEREF_CUSTOM
    PRINT_PAR_NUM        // SYNTAX_TREE_TYPEREF_ARRAY
};

static const unsigned char
node_has_location_guide[] =
{
    0,       // SYNTAX_TREE_SOURCE

    0,       // SYNTAX_TREE_FUNC_DEF
    0,       // SYNTAX_TREE_FUNC_UNTYPED_SIGN
    0,       // SYNTAX_TREE_FUNC_TYPED_SIGN
    0,       // SYNTAX_TREE_FUNC_UNTYPED_ARG
    0,       // SYNTAX_TREE_FUNC_TYPED_ARG

    1,       // SYNTAX_TREE_STATEMENT_DEFINE
    1,       // SYNTAX_TREE_STATEMENT_DEFINEASSIGN
    1,       // SYNTAX_TREE_STATEMENT_IF
    1,       // SYNTAX_TREE_STATEMENT_IF_ELSE
    1,       // SYNTAX_TREE_STATEMENT_WHILE
    1,       // SYNTAX_TREE_STATEMENT_UNTIL
    1,       // SYNTAX_TREE_STATEMENT_REPEAT_WHILE
    1,       // SYNTAX_TREE_STATEMENT_REPEAT_UNTIL
    1,       // SYNTAX_TREE_STATEMENT_BREAK
    1,       // SYNTAX_TREE_STATEMENT_EXP
    1,       // SYNTAX_TREE_STATEMENT_BLOCK
    1,       // SYNTAX_TREE_STATEMENT_RETURN
    1,       // SYNTAX_TREE_STATEMENT_RETURN_EXP

    0,       // SYNTAX_TREE_EXPR_BINOP_ASSIGN
    0,       // SYNTAX_TREE_EXPR_BINOP_PLUS
    0,       // SYNTAX_TREE_EXPR_BINOP_MINUS
    0,       // SYNTAX_TREE_EXPR_BINOP_MUL
    0,       // SYNTAX_TREE_EXPR_BINOP_DIV
    0,       // SYNTAX_TREE_EXPR_BINOP_AND
    0,       // SYNTAX_TREE_EXPR_BINOP_OR
    0,       // SYNTAX_TREE_EXPR_BINOP_EQUAL
    0,       // SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL
    0,       // SYNTAX_TREE_EXPR_BINOP_LESS
    0,       // SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL
    0,       // SYNTAX_TREE_EXPR_BINOP_GREATER
    0,       // SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL

    0,       // SYNTAX_TREE_EXPR_UNOP_MINUS
    0,       // SYNTAX_TREE_EXPR_UNOP_NOT

    0,       // SYNTAX_TREE_EXPR_CALL
    0,       // SYNTAX_TREE_EXPR_RANGE
    0,       // SYNTAX_TREE_EXPR_INDEX

    0,       // SYNTAX_TREE_EXPR_PLACE
    0,       // SYNTAX_TREE_EXPR_LITERAL_BOOL
    0,       // SYNTAX_TREE_EXPR_LITERAL_CHAR
    0,       // SYNTAX_TREE_EXPR_LITERAL_NUM
    0,       // SYNTAX_TREE_EXPR_LITERAL_NUM_128
    0,       // SYNTAX_TREE_EXPR_LITERAL_STR

    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_BOOL
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_BYTE
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_SHORT
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_USHORT
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_INT
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_UINT
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_LONG
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_ULONG
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_HUGE
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_CHAR
    0,       // SYNTAX_TREE_TYPEREF_BUILTIN_STRING
    1,       // SYNTAX_TREE_TYPEREF_CUSTOM
    0        // SYNTAX_TREE_TYPEREF_ARRAY
};

inline static default_retcode
dot_file_builder_create_entry(
        struct dot_file_builder *self,
        char* nodes_base,
        const size_t node_ind)
{
    union ast_node_ptr node;
    struct extendable_chunk *text;
    struct ast_node_location *node_loc;
    unsigned char node_type;
    size_t node_par;
    uint128_t big;
    size_t str_max_size;
    int real_size;

    node.unknown = nodes_base + node_ind;
    node_type = node.header->type;
    text = &self->nodes_decl_string;

    // print node name
    str_max_size = NODE_ENTRY_PREFIX_SIZE
                   + NODE_ENTRY_POSTFIX_SIZE
                   + NODE_TYPE_TO_STR_MAX_SIZE
                   + 1;

    if (chunk_extend_to_fit(text, str_max_size) == ERROR)
        return ERROR;

    real_size = sprintf(text->start + text->size,
                        node_entry_prefix,
                        node_ind,
                        node_type_t_to_str_map[node_type]);

    if (real_size < 0)
        return ERROR;

    text->size += real_size;

    // print node parameter

    switch (node_print_par_guide[node_type])
    {
        case PRINT_PAR_NOPE:
            break;

        case PRINT_PAR_STR:
            node_par = AST_PAR_NODE_PARAMETER(node).ind;
            str_max_size = string_map_get_str_len(&self->tree.strings, node_par)
                           + NODE_ENTRY_PAR_STR_SIZE;

            if (chunk_extend_to_fit(text, str_max_size) == ERROR)
                return ERROR;

            real_size = sprintf(text->start + text->size,
                                node_entry_par_str,
                                string_map_get_str_ptr(&self->tree.strings, node_par));

            if (real_size < 0)
                return ERROR;

            text->size += real_size;
            break;

        case PRINT_PAR_NUM:
            node_par = AST_PAR_NODE_PARAMETER(node).ind;
            str_max_size = NODE_ENTRY_PAR_NUM_SIZE;

            if (chunk_extend_to_fit(text, str_max_size) == ERROR)
                return ERROR;

            real_size = sprintf(text->start + text->size,
                                node_entry_par_num,
                                syntax_tree_get_num(&self->tree, node_par));

            if (real_size < 0)
                return ERROR;

            text->size += real_size;
            break;

        case PRINT_PAR_NUM_BIG:
            node_par = AST_PAR_NODE_PARAMETER(node).ind;
            str_max_size = NODE_ENTRY_PAR_NUM_BIG_SIZE;
            big = syntax_tree_get_num_big(&self->tree, node_par);

            if (chunk_extend_to_fit(text, str_max_size) == ERROR)
                return ERROR;

            real_size = sprintf(text->start + text->size,
                                node_entry_par_num_big,
                                uint128_high_half(big),
                                uint128_to_i64(big));

            if (real_size < 0)
                return ERROR;

            text->size += real_size;
            break;

        case PRINT_PAR_PAR:
            node_par = AST_PAR_NODE_PARAMETER(node).ind;
            str_max_size = NODE_ENTRY_PAR_NUM_SIZE;

            if (chunk_extend_to_fit(text, str_max_size) == ERROR)
                return ERROR;

            real_size = sprintf(text->start + text->size,
                                node_entry_par_num,
                                node_par);

            if (real_size < 0)
                return ERROR;

            text->size += real_size;
            break;
    }

    // print node location

    if (node_has_location_guide[node_type])
    {
        str_max_size = LOC_ENTRY_STR_MAX_LEN;
        node_loc = ast_node_get_location(node);

        if (chunk_extend_to_fit(text, str_max_size) == ERROR)
            return ERROR;

        real_size = sprintf(text->start + text->size,
                            node_entry_loc,
                            node_loc->line_num,
                            node_loc->column_num);

        if (real_size < 0)
            return ERROR;

        text->size += real_size;
    }

    // copy postfix with 0 byte
    memcpy(text->start + text->size, node_entry_postfix, sizeof(node_entry_postfix));
    text->size += sizeof(node_entry_postfix) - 1;
    return SUCCESS;
}

// max len of %ld is 20 digits => max len of child_entry is 20 * 2 + 5 bytes
#define CHILD_ENTRY_STR_MAX_LEN 47 
#define CHILD_ENTRY_STR "\t%ld\t->\t%ld;\n"
static const char child_entry_1[] = CHILD_ENTRY_STR;
static const char child_entry_2[] = CHILD_ENTRY_STR CHILD_ENTRY_STR;
static const char child_entry_3[] = CHILD_ENTRY_STR CHILD_ENTRY_STR CHILD_ENTRY_STR;

inline static default_retcode
dot_file_builder_create_conn_entry_1_child(
        struct extendable_chunk *text,
        const size_t node_ind,
        const size_t child_ind)
{
    int real_size;

    if (chunk_extend_to_fit(text, CHILD_ENTRY_STR_MAX_LEN + 1) == ERROR)
        return ERROR;
   
    real_size = sprintf(text->start + text->size,
                        child_entry_1,
                        node_ind,
                        child_ind);

    if (real_size < 0)
        return ERROR;

    text->size += real_size;
    return SUCCESS;
}

inline static default_retcode
dot_file_builder_create_conn_entry_2_child(
        struct extendable_chunk *text,
        const size_t node_ind,
        const size_t child_ind_1,
        const size_t child_ind_2)
{
    int real_size;

    if (chunk_extend_to_fit(text, CHILD_ENTRY_STR_MAX_LEN * 2 + 1) == ERROR)
        return ERROR;
   
    real_size = sprintf(text->start + text->size,
                        child_entry_2,
                        node_ind,
                        child_ind_1,
                        node_ind,
                        child_ind_2);

    if (real_size < 0)
        return ERROR;

    text->size += real_size;
    return SUCCESS;
}

inline static default_retcode
dot_file_builder_create_conn_entry_3_child(
        struct extendable_chunk *text,
        const size_t node_ind,
        const size_t child_ind_1,
        const size_t child_ind_2,
        const size_t child_ind_3)
{
    int real_size;

    if (chunk_extend_to_fit(text, CHILD_ENTRY_STR_MAX_LEN * 3 + 1) == ERROR)
        return ERROR;
   
    real_size = sprintf(text->start + text->size,
                        child_entry_3,
                        node_ind,
                        child_ind_1,
                        node_ind,
                        child_ind_2,
                        node_ind,
                        child_ind_3);

    if (real_size < 0)
        return ERROR;

    text->size += real_size;
    return SUCCESS;
}

inline static default_retcode
dot_file_builder_create_conn_entry_N_child(
        struct extendable_chunk *text,
        const size_t node_ind,
        const size_t *child_arr,
        const size_t N)
{
    size_t i;
    int real_size;

    if (chunk_extend_to_fit(text, CHILD_ENTRY_STR_MAX_LEN * N + 1) == ERROR)
        return ERROR;

    i = 0;

    switch (N % 3)
    {
        case 2:
            real_size = sprintf(text->start + text->size,
                                child_entry_2,
                                node_ind,
                                child_arr[0],
                                node_ind,
                                child_arr[1]);
            i += 2;
            break;

        case 1:
            real_size = sprintf(text->start + text->size,
                                child_entry_1,
                                node_ind,
                                child_arr[0]);
            i += 1;
            break;

        case 0:
            real_size = 0;
            break;
    }

    if (real_size < 0)
        return ERROR;

    text->size += real_size;

    for (; i < N; i += 3)
    {
        real_size = sprintf(text->start + text->size,
                            child_entry_3,
                            node_ind,
                            child_arr[i],
                            node_ind,
                            child_arr[i + 1],
                            node_ind,
                            child_arr[i + 2]);

        if (real_size < 0)
            return ERROR;

        text->size += real_size;
    }

    return SUCCESS;
}


static default_retcode
dot_file_builder_dump_node(
        struct dot_file_builder *builder,
        char *nodes_base,
        const size_t node_ind)
{
    union ast_node_ptr node;
    struct extendable_chunk *connections_text;

    connections_text = &builder->nodes_conn_string;
    node.unknown = nodes_base + node_ind;

    if (dot_file_builder_create_entry(builder, nodes_base, node_ind) == ERROR)
        return ERROR;

    switch (NODE_TYPE_MAP[node.header->type])
    {
        case NODE_TYPE_LEAF:
            break;

        case NODE_TYPE_1_CHILD:
            if (dot_file_builder_create_conn_entry_1_child(connections_text,
                                                           node_ind,
                                                           AST_NODE_1_CHILD(node))
                == ERROR)
                return ERROR;

            return dot_file_builder_dump_node(builder, nodes_base, AST_NODE_1_CHILD(node));

        case NODE_TYPE_2_CHILD:
            if (dot_file_builder_create_conn_entry_2_child(connections_text, 
                                                           node_ind,
                                                           AST_NODE_1_CHILD(node),
                                                           AST_NODE_2_CHILD(node))
                    == ERROR)
                return ERROR;

            if (dot_file_builder_dump_node(builder,
                                              nodes_base,
                                              AST_NODE_1_CHILD(node)) == ERROR)
                return ERROR;

            return dot_file_builder_dump_node(builder,
                                              nodes_base,
                                              AST_NODE_2_CHILD(node));

        case NODE_TYPE_3_CHILD:
            if (dot_file_builder_create_conn_entry_3_child(connections_text, 
                                                           node_ind,
                                                           AST_NODE_1_CHILD(node),
                                                           AST_NODE_2_CHILD(node),
                                                           AST_NODE_3_CHILD(node))
                == ERROR)
                return ERROR;

            if (dot_file_builder_dump_node(builder,
                                           nodes_base,
                                           AST_NODE_1_CHILD(node)) == ERROR)
                return ERROR;

            if (dot_file_builder_dump_node(builder,
                                           nodes_base,
                                           AST_NODE_2_CHILD(node)) == ERROR)
                return ERROR;

            return dot_file_builder_dump_node(builder,
                                              nodes_base,
                                              AST_NODE_3_CHILD(node));

        case NODE_TYPE_N_CHILD:
            if (dot_file_builder_create_conn_entry_N_child(connections_text, 
                                                           node_ind,
                                                           AST_NODE_N_CHILD_ARR(node),
                                                           AST_NODE_N_CHILD_NUM(node))
                == ERROR)
                return ERROR;

            for (size_t i = 0; i < AST_NODE_N_CHILD_NUM(node); i++)
            {
                if (dot_file_builder_dump_node(builder,
                                               nodes_base,
                                               AST_NODE_N_CHILD_ARR(node)[i]) == ERROR)
                    return ERROR;
            }

            break;

        case NODE_TYPE_PAR_LEAF:
            break;

        case NODE_TYPE_PAR_1_CHILD:
            if (dot_file_builder_create_conn_entry_1_child(connections_text,
                                                           node_ind,
                                                           AST_PAR_NODE_1_CHILD(node))
                == ERROR)
                return ERROR;

            return dot_file_builder_dump_node(builder,
                                              nodes_base,
                                              AST_PAR_NODE_1_CHILD(node));

        case NODE_TYPE_PAR_2_CHILD:
            if (dot_file_builder_create_conn_entry_2_child(connections_text,
                                                           node_ind,
                                                           AST_PAR_NODE_1_CHILD(node),
                                                           AST_PAR_NODE_2_CHILD(node))
                == ERROR)
                return ERROR;

            if (dot_file_builder_dump_node(builder,
                                           nodes_base,
                                           AST_PAR_NODE_1_CHILD(node)) == ERROR)
                return ERROR;

            return dot_file_builder_dump_node(builder,
                                              nodes_base,
                                              AST_PAR_NODE_2_CHILD(node));
 

        case NODE_TYPE_PAR_N_CHILD:
            if (dot_file_builder_create_conn_entry_N_child(connections_text, 
                                                           node_ind,
                                                           AST_PAR_NODE_N_CHILD_ARR(node),
                                                           AST_PAR_NODE_N_CHILD_NUM(node))
                == ERROR)
                return ERROR;

            for (size_t i = 0; i < AST_PAR_NODE_N_CHILD_NUM(node); i++)
                if (dot_file_builder_dump_node(builder,
                                               nodes_base,
                                               AST_PAR_NODE_N_CHILD_ARR(node)[i])
                    == ERROR)
                    return ERROR;

            break;
    }

    return SUCCESS;
}

default_retcode
syntax_tree_dump_dotfile(
        const struct syntax_tree *const self,
        FILE *f)
{
    int dumped;
    default_retcode res;
    struct dot_file_builder builder;

    res = ERROR;

    if (chunk_init(&builder.nodes_decl_string,
                   __DOT_FILE_CONTENTS_STRING_PREALLOC) == ERROR)
        return res;

    if (chunk_init(&builder.nodes_conn_string,
                   __DOT_FILE_CONTENTS_STRING_PREALLOC) == ERROR)
        goto EXIT_0;

    builder.tree = *self;

    if (dot_file_builder_dump_node(&builder, self->tree, self->top_ind) == ERROR)
        goto EXIT_1;

    dumped = fprintf(f, 
                     "digraph AST {\n%s\n%s}\n",
                     builder.nodes_decl_string.start,
                     builder.nodes_conn_string.start);

    if (dumped == (int)(builder.nodes_decl_string.size + builder.nodes_conn_string.size + 17))
        res = SUCCESS; 

EXIT_1:
    chunk_deinit(&builder.nodes_conn_string);
EXIT_0:
    chunk_deinit(&builder.nodes_decl_string);
    return res;
}
