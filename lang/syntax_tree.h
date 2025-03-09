#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "data_structs/compiler_integers.h"
#include "data_structs/string_map.h"
#include "data_structs/chunk.h"


// see syntax_tree.c for node type - struct type map
#define SYNTAX_TREE_SOURCE                   0

#define SYNTAX_TREE_FUNC_DEF                 1
#define SYNTAX_TREE_FUNC_UNTYPED_SIGN        2
#define SYNTAX_TREE_FUNC_TYPED_SIGN          3
#define SYNTAX_TREE_FUNC_UNTYPED_ARG         4
#define SYNTAX_TREE_FUNC_TYPED_ARG           5

#define SYNTAX_TREE_STATEMENT_DEFINE         6
#define SYNTAX_TREE_STATEMENT_DEFINEASSIGN   7
#define SYNTAX_TREE_STATEMENT_IF             8
#define SYNTAX_TREE_STATEMENT_IF_ELSE        9
#define SYNTAX_TREE_STATEMENT_WHILE          10
#define SYNTAX_TREE_STATEMENT_UNTIL          11
#define SYNTAX_TREE_STATEMENT_REPEAT_WHILE   12
#define SYNTAX_TREE_STATEMENT_REPEAT_UNTIL   13
#define SYNTAX_TREE_STATEMENT_BREAK          14
#define SYNTAX_TREE_STATEMENT_EXP            15
#define SYNTAX_TREE_STATEMENT_BLOCK          16
#define SYNTAX_TREE_STATEMENT_RETURN         17
#define SYNTAX_TREE_STATEMENT_RETURN_EXP     18

#define SYNTAX_TREE_EXPR_BINOP_ASSIGN        19
#define SYNTAX_TREE_EXPR_BINOP_PLUS          20
#define SYNTAX_TREE_EXPR_BINOP_MINUS         21
#define SYNTAX_TREE_EXPR_BINOP_MUL           22
#define SYNTAX_TREE_EXPR_BINOP_DIV           23
#define SYNTAX_TREE_EXPR_BINOP_AND           24
#define SYNTAX_TREE_EXPR_BINOP_OR            25
#define SYNTAX_TREE_EXPR_BINOP_EQUAL         26
#define SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL     27
#define SYNTAX_TREE_EXPR_BINOP_LESS          28
#define SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL    29
#define SYNTAX_TREE_EXPR_BINOP_GREATER       30
#define SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL 31

#define SYNTAX_TREE_EXPR_UNOP_MINUS          32
#define SYNTAX_TREE_EXPR_UNOP_NOT            33

#define SYNTAX_TREE_EXPR_CALL                34
#define SYNTAX_TREE_EXPR_RANGE               35
#define SYNTAX_TREE_EXPR_INDEX               36

#define SYNTAX_TREE_EXPR_PLACE               37
#define SYNTAX_TREE_EXPR_LITERAL_BOOL        38
#define SYNTAX_TREE_EXPR_LITERAL_CHAR        39
#define SYNTAX_TREE_EXPR_LITERAL_NUM         40
#define SYNTAX_TREE_EXPR_LITERAL_NUM_128     41
#define SYNTAX_TREE_EXPR_LITERAL_STR         42

#define SYNTAX_TREE_TYPEREF_BUILTIN_BOOL     43
#define SYNTAX_TREE_TYPEREF_BUILTIN_BYTE     44
#define SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE    45
#define SYNTAX_TREE_TYPEREF_BUILTIN_SHORT    46
#define SYNTAX_TREE_TYPEREF_BUILTIN_USHORT   47
#define SYNTAX_TREE_TYPEREF_BUILTIN_INT      48
#define SYNTAX_TREE_TYPEREF_BUILTIN_UINT     49
#define SYNTAX_TREE_TYPEREF_BUILTIN_LONG     50
#define SYNTAX_TREE_TYPEREF_BUILTIN_ULONG    51
#define SYNTAX_TREE_TYPEREF_BUILTIN_HUGE     52
#define SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE    53
#define SYNTAX_TREE_TYPEREF_BUILTIN_CHAR     54
#define SYNTAX_TREE_TYPEREF_BUILTIN_STRING   55
#define SYNTAX_TREE_TYPEREF_CUSTOM           56
#define SYNTAX_TREE_TYPEREF_ARRAY            57

//--------------------------------- nodes base structs -----------------------------------

#define AST_NODE_AVERAGE_SIZE 16

#define AST_NODE_TYPE(ast_node_ptr) \
    (((struct ast_node*)(ast_node_ptr))->type)
struct ast_node
{
    unsigned char type;
};

union ast_node_param
{
    size_t ind;
};

#define AST_PAR_NODE_PARAMETER(union_ast_node_ptr) \
    ((union_ast_node_ptr).par_header->parameter)
struct __ast_par_node
{
    struct ast_node header;
    union ast_node_param parameter;
};

struct __ast_node_children_header
{
    struct ast_node header;
    size_t num;
};

struct __ast_par_node_children_header
{
    struct __ast_par_node header;
    size_t num;
};

struct ast_node_location
{
    int line_num;
    int column_num;
};

//------------------------------ nodes without parameter ---------------------------------

#define AST_NODE_LEAF_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_node_leaf + 1))
struct ast_node_leaf
{
    struct ast_node header;
} __attribute__ ((aligned (sizeof(size_t))));

#define AST_NODE_1_CHILD(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_node_1_child->child_1) 
#define AST_NODE_1_CHILD_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_node_1_child + 1))
struct ast_node_1_child 
{
    struct ast_node header;
    size_t child_1;
};

#define AST_NODE_2_CHILD(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_node_2_child->child_2) 
#define AST_NODE_2_CHILD_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_node_2_child + 1))
struct ast_node_2_child 
{
    struct ast_node_1_child parent_struct;
    size_t child_2;
};

#define AST_NODE_3_CHILD(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_node_3_child->child_3) 
#define AST_NODE_3_CHILD_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_node_3_child + 1))
struct ast_node_3_child 
{
    struct ast_node_2_child parent_struct;
    size_t child_3;
};

#define AST_NODE_N_CHILD_NUM(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_node_N_child->header.num) 
#define AST_NODE_N_CHILD_ARR(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_node_N_child->children) 
#define AST_NODE_N_CHILD_LOC(union_ast_node_ptr, child_num)   \
    ((struct ast_node_location*)((union_ast_node_ptr).unknown \
     + sizeof(struct ast_node_N_child) + sizeof(size_t) * (child_num)))
struct ast_node_N_child
{
    struct __ast_node_children_header header;
    size_t children[];
};


//-------------------------------- nodes with parameter ----------------------------------

#define AST_PAR_NODE_LEAF_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_par_node_leaf + 1))
struct ast_par_node_leaf
{
    struct __ast_par_node header;
};

#define AST_PAR_NODE_1_CHILD(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_par_node_1_child->child_1) 
#define AST_PAR_NODE_1_CHILD_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_par_node_1_child + 1))
struct ast_par_node_1_child
{
    struct __ast_par_node header;
    size_t child_1;
};

#define AST_PAR_NODE_2_CHILD(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_par_node_2_child->child_2) 
#define AST_PAR_NODE_2_CHILD_LOC(union_ast_node_ptr) \
    ((struct ast_node_location*)((union_ast_node_ptr).ast_par_node_2_child + 1))
struct ast_par_node_2_child
{
    struct ast_par_node_1_child parent_struct;
    size_t child_2;
};

#define AST_PAR_NODE_N_CHILD_NUM(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_par_node_N_child->header.num) 
#define AST_PAR_NODE_N_CHILD_ARR(union_ast_node_ptr) \
    ((union_ast_node_ptr).ast_par_node_N_child->children) 
#define AST_PAR_NODE_N_CHILD_LOC(union_ast_node_ptr, child_num) \
    ((struct ast_node_location*)((union_ast_node_ptr).unknown   \
     + sizeof(struct ast_par_node_N_child) + sizeof(size_t) * (child_num)))
struct ast_par_node_N_child
{
    struct __ast_par_node_children_header header;
    size_t children[];
};

union ast_node_ptr
{
    struct ast_node *header;
    struct ast_node_leaf *ast_node_leaf;
    struct ast_node_1_child *ast_node_1_child;
    struct ast_node_2_child *ast_node_2_child;
    struct ast_node_3_child *ast_node_3_child;
    struct ast_node_N_child *ast_node_N_child;
    struct __ast_par_node *par_header;
    struct ast_par_node_leaf *ast_par_node_leaf;
    struct ast_par_node_1_child *ast_par_node_1_child;
    struct ast_par_node_2_child *ast_par_node_2_child;
    struct ast_par_node_N_child *ast_par_node_N_child;
    char *unknown;
};

struct ast_node_location*
ast_node_get_location(union ast_node_ptr);

//------------------------------------ main structs --------------------------------------

#define SYNTAX_TREE_NODE_BY_IND(ast_start, node_ind) \
    (((char*)(ast_start)) + (node_ind))
#define SYNTAX_TREE_NUM_BY_IND(start, ind) \
    (*(uint64_t*)(((char*)(start)) + (ind)))
#define SYNTAX_TREE_NUM_BIG_BY_IND(start, ind) \
    (*(uint128_t*)(((char*)(start)) + (ind)))
struct syntax_tree
{
    size_t top_ind;
    char *tree;
    struct string_map strings;
    char *numbers;
    char *big_numbers;
};

inline static void
syntax_tree_deinit(struct syntax_tree *self)
{
    free(self->tree);
    string_map_deinit(&self->strings);
    free(self->numbers);
    free(self->big_numbers);
}

inline static struct ast_node*
syntax_tree_get_top_node(const struct syntax_tree *const self)
{
    return (struct ast_node*)(self->tree + self->top_ind);
}

inline static struct ast_node*
syntax_tree_get_node(const struct syntax_tree *const self, const size_t ind)
{
    return (struct ast_node*)(self->tree + ind);
}

inline static uint64_t
syntax_tree_get_num(const struct syntax_tree *const self, const size_t ind)
{
    return *(uint64_t*)(self->numbers + ind);
}

inline static uint128_t
syntax_tree_get_num_big(const struct syntax_tree *const self, const size_t ind)
{
    return *(uint128_t*)(self->big_numbers + ind);
}


#ifdef DEBUG

default_retcode
syntax_tree_dump_dotfile(const struct syntax_tree*, FILE*);

#endif


struct __ast_builder_hash_entry
{
    size_t str_ind;
    uint32_t hash;
};

struct __ast_builder_hash_tbl
{
    struct __ast_builder_hash_entry *entries;
    uint32_t size;
    uint16_t cap_ind;
};

struct ast_builder
{
    struct extendable_chunk tree;
    struct extendable_chunk nodes_stack;
    struct string_map_builder string_builder;
    struct extendable_chunk uint64_chunk;
    struct extendable_chunk uint128_chunk;
    struct __ast_builder_hash_tbl uint64_map;
    struct __ast_builder_hash_tbl uint128_map;
    struct __ast_builder_hash_tbl strings_map;
};

#define AST_BUILDER_NODES(ast_builder_ptr) \
    (&((ast_builder_ptr)->tree.nodes))

default_retcode
ast_builder_init(struct ast_builder*);

void
ast_builder_deinit(struct ast_builder*);

default_retcode
ast_builder_finish(struct ast_builder*, struct syntax_tree*);

enum ast_builder_add_res_num_retcode
{
    AST_BUILDER_ADD_RES_NUM_ERROR,
    AST_BUILDER_ADD_RES_NUM_NO_SPACE,
    AST_BUILDER_ADD_RES_NUM_TOO_BIG,
    AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL,
    AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG
};

enum ast_builder_add_res_num_retcode
ast_builder_add_res_num(struct ast_builder*, const char*, size_t, size_t*);

default_retcode
ast_builder_res_num_reinsert_128_as_64(struct ast_builder*, size_t, size_t*);

enum ast_builder_add_res_str_retcode
{
    AST_BUILDER_ADD_RES_STR_ERROR,
    AST_BUILDER_ADD_RES_STR_NO_SPACE,
    AST_BUILDER_ADD_RES_STR_SUCCESS
};

enum ast_builder_add_res_str_retcode
ast_builder_add_res_str(struct ast_builder*, const char*, size_t, size_t*);

void
ast_builder_remove_node(struct ast_builder*);

default_retcode
ast_builder_save_node_pos(
        struct ast_builder*,
        const int,
        const int);

default_retcode
ast_builder_new_node_leaf(
        struct ast_builder*,
        const unsigned char);

default_retcode
ast_builder_new_node_1_child(
        struct ast_builder*,
        const unsigned char);

default_retcode
ast_builder_new_node_2_child(
        struct ast_builder*,
        const unsigned char);

default_retcode
ast_builder_new_node_3_child(
        struct ast_builder*,
        const unsigned char);

default_retcode
ast_builder_new_node_N_child(
        struct ast_builder*,
        const unsigned char, 
        const size_t);

default_retcode
ast_builder_new_par_node_leaf(
        struct ast_builder*,
        const unsigned char, 
        const union ast_node_param);

default_retcode
ast_builder_new_par_node_1_child(
        struct ast_builder*,
        const unsigned char, 
        const union ast_node_param);

default_retcode
ast_builder_new_par_node_2_child(
        struct ast_builder*,
        const unsigned char, 
        const union ast_node_param);

default_retcode
ast_builder_new_par_node_N_child(
        struct ast_builder*,
        const unsigned char, 
        const union ast_node_param,
        const size_t);
#endif
