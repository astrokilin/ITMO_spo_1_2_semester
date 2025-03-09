#ifndef CFG_IR_H
#define CFG_IR_H

#include "data_structs/compiler_integers.h"
#include "data_structs/string_map.h"
#include "syntax_tree.h"

//------------------------------------ basic types ---------------------------------------

#define CFG_BASIC_TYPE_U8           0
#define CFG_BASIC_TYPE_S8           1

#define CFG_BASIC_TYPE_U16          2
#define CFG_BASIC_TYPE_S16          3

#define CFG_BASIC_TYPE_U32          4
#define CFG_BASIC_TYPE_S32          5

#define CFG_BASIC_TYPE_U64          6
#define CFG_BASIC_TYPE_S64          7

#define CFG_BASIC_TYPE_U128         8
#define CFG_BASIC_TYPE_S128         9

#define BASIC_TYPE_SIZE_CALC(basic_type) ((((basic_type) >> 1) + 1) << 3)

#define CFG_EXTENDED_TYPE_POINTER   10

//-------------------------------------- cfg node ----------------------------------------

struct cfg_node
{
    int line;
    int column;
    size_t child_1; // child index cannot be 0
    size_t child_2;
};

//---------------------------------- expression tree -------------------------------------

// ir expression tree is a prefix form tree (string?)
struct ir_exp_tree_node
{
#define IR_EXP_N_OP_CALL            0

#define IR_EXP_BINOP_WRITE          1
#define IR_EXP_BINOP_ADD            2
#define IR_EXP_BINOP_SUB            3
#define IR_EXP_BINOP_MUL            4
#define IR_EXP_BINOP_DIV            5
#define IR_EXP_BINOP_AND            6
#define IR_EXP_BINOP_OR             7

#define IR_EXP_UNOP_ARITHM_INV      8
#define IR_EXP_UNOP_LOGIC_INV       9
#define IR_EXP_UNOP_READ            10
#define IR_EXP_UNOP_WRITE           11
#define IR_EXP_UNOP_CAST            12

#define IR_EXP_LEAF_CONST           13
#define IR_EXP_LEAF_CONST_128       14
#define IR_EXP_LEAF_LABEL           15
    unsigned char type;
    unsigned char op_base_type;
};

struct ir_exp_tree_op_node
{
    struct ir_exp_tree_node header;
} __attribute__ ((aligned (sizeof(size_t))));

struct ir_exp_tree_n_op_node
{
    struct ir_exp_tree_node header;
    size_t childer_num;
} __attribute__ ((aligned (sizeof(size_t))));

struct ir_exp_tree_label_node
{
    struct ir_exp_tree_node header;
    size_t val;
} __attribute__ ((aligned (sizeof(size_t))));

struct ir_exp_tree_const_node
{
    struct ir_exp_tree_node header;
    uint64_t val;
} __attribute__ ((aligned (sizeof(size_t))));

struct ir_exp_tree_const_128_node
{
    struct ir_exp_tree_node header;
    uint128_t val;
} __attribute__ ((aligned (sizeof(size_t))));

union ir_exp_tree_node_ptr
{
    struct ir_exp_tree_node *header;
    struct ir_exp_tree_op_node *op;
    struct ir_exp_tree_n_op_node *n_op;
    struct ir_exp_tree_const_node *constant;
    struct ir_exp_tree_const_128_node *big_constant;
    struct ir_exp_tree_label_node *label;
    char *unknown;
};

//------------------------------------- ir tables ----------------------------------------

struct ir_type_entry_header
{
#define IR_ERROR_TYPE           0
#define IR_MEMAREA_TYPE         1
#define IR_CALLABLE_TYPE        2
#define IR_PARAM_TYPE           3
    unsigned char entry_type;
};

struct ir_type_error_entry
{
    struct ir_type_entry_header header;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct ir_type_memarea_entry
{
    struct ir_type_entry_header header;
    uint64_t size;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct ir_type_callable_entry
{
    struct ir_type_entry_header header;
    size_t ir_sourceitems_table_ind;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct ir_type_param_entry
{
    struct ir_type_entry_header header;
    size_t param_num;
    size_t callable_ind;
} __attribute__ ((aligned (sizeof(uint64_t))));

union ir_type_entry_any
{
    struct ir_type_error_entry      error_entry;
    struct ir_type_memarea_entry    chunk_entry;
    struct ir_type_callable_entry   callable_entry;
    struct ir_type_param_entry      param_entry;
};

union ir_type_entry_ptr
{
    struct ir_type_entry_header *header;
    struct ir_type_error_entry *error;
    struct ir_type_memarea_entry *memarea;
    struct ir_type_callable_entry *callable;
    struct ir_type_param_entry *param;
    char * unknown; 
};

//--------------------------------- sourceitems_table ------------------------------------

#define IR_SOURCEITEMS_TABLE_GET_NAME(ir_sourceitems_table_ptr) \
    ((char*)((ir_sourceitems_table_ptr)->data))
#define IR_SOURCEITEMS_TABLE_MOVE_TO_ARGS(name_ptr, name_len) \
    ((struct ir_type_entry*)(((char*)(name_ptr)) + (name_len)))
#define IR_SOURCEITEMS_TABLE_MOVE_TO_RETURNS(args_ptr, args_len) \
    ((struct ir_type_entry*)(((char*)(args_ptr)) + (args_len)))
#define IR_SOURCEITEMS_TABLE_MOVE_TO_SUBCALLABLES(returns_ptr, returns_len) \
    ((size_t*)(((char*)(returns_ptr)) + (returns_len)))
struct ir_sourceitems_table_entry
{
    struct extendable_chunk cfg_nodes;
    struct extendable_chunk name_table;
    size_t name_size;
    size_t args_size;
    size_t returns_size;
    // unsigned char name[name_size]
    // padding to uint64_t len
    // struct ir_type_entry args[args_size]
    // struct ir_type_entry returns[returns_size]
    char data[];
} __attribute__ ((aligned (sizeof(uint64_t))));

union ir_sourceitems_table_entry_ptr
{
    struct ir_sourceitems_table_entry *entry;
    char *unknown;
};

struct ir_sourceitems_table_ind_iter
{
    size_t __tbl_size;
    size_t cur_tbl_ind;
    union ir_sourceitems_table_entry_ptr e;
};

inline static void
ir_sourceitems_table_ind_iter_init(
        struct ir_sourceitems_table_ind_iter *const self,
        const struct extendable_chunk *const tbl)
{
    self->__tbl_size = tbl->size;
    self->cur_tbl_ind = 0;
    self->e.unknown = tbl->start;
}

inline static int
ir_sourceitems_table_ind_is_valid(const struct ir_sourceitems_table_ind_iter *const self)
{
    return self->cur_tbl_ind < self->__tbl_size;
}

inline static void
ir_sourceitems_table_ind_iter_next(struct ir_sourceitems_table_ind_iter *const self)
{
    const size_t step = self->e.entry->name_size
                       + self->e.entry->args_size
                       + self->e.entry->returns_size
                       + sizeof(struct ir_sourceitems_table_entry);

    self->e.unknown += step;
    self->cur_tbl_ind += step;
}

//------------------------------------- ir itself ----------------------------------------

struct ir
{
    struct extendable_chunk global_sym_table;
};

enum ir_init_retcode
{
    IR_INIT_ERROR,
    IR_INIT_SEMANTIC_ERRORS,
    IR_INIT_SUCCESS
};

enum ir_init_retcode
ir_init(struct ir*, const struct syntax_tree*);

void
ir_deinit(struct ir*);

default_retcode
ir_dump(const struct ir*, FILE*);

#endif
