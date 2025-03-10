#include "data_structs/chunk.h"
#include "data_structs/sizes_map.h"
#include "cfg_ir.h"

inline static default_retcode
chunk_move_reinit(
        struct extendable_chunk *const self,
        struct extendable_chunk *const place,
        const size_t reinit_size)
{
    if (chunk_slim_down(self) == ERROR)
        return ERROR;

    *place = *self;
    chunk_deinit_shallow(self);

    return chunk_init(self, reinit_size);
}


static const char *const
BASIC_TYPE_TO_STR[] = 
{
    "U8",      // CFG_BASIC_TYPE_U8
    "S8",      // CFG_BASIC_TYPE_S8
    "U16",     // CFG_BASIC_TYPE_U16
    "S16",     // CFG_BASIC_TYPE_S16
    "U32",     // CFG_BASIC_TYPE_U32
    "S32",     // CFG_BASIC_TYPE_S32
    "U64",     // CFG_BASIC_TYPE_U64
    "S64",     // CFG_BASIC_TYPE_S64
    "Pointer"  // CFG_BASIC_TYPE_POINTER
};

static const unsigned char
TYPEREF_TO_BASIC_TYPE[] = 
{
    CFG_BASIC_TYPE_U8,      //SYNTAX_TREE_TYPEREF_BUILTIN_BOOL 
    CFG_BASIC_TYPE_S8,      //SYNTAX_TREE_TYPEREF_BUILTIN_BYTE
    CFG_BASIC_TYPE_U8,      //SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE
    CFG_BASIC_TYPE_S16,     //SYNTAX_TREE_TYPEREF_BUILTIN_SHORT
    CFG_BASIC_TYPE_U16,     //SYNTAX_TREE_TYPEREF_BUILTIN_USHORT
    CFG_BASIC_TYPE_S32,     //SYNTAX_TREE_TYPEREF_BUILTIN_INT
    CFG_BASIC_TYPE_U32,     //SYNTAX_TREE_TYPEREF_BUILTIN_UINT
    CFG_BASIC_TYPE_S64,     //SYNTAX_TREE_TYPEREF_BUILTIN_LONG
    CFG_BASIC_TYPE_U64,     //SYNTAX_TREE_TYPEREF_BUILTIN_ULONG
    CFG_BASIC_TYPE_S128,    //SYNTAX_TREE_TYPEREF_BUILTIN_HUGE
    CFG_BASIC_TYPE_U128,    //SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE
    CFG_BASIC_TYPE_U8       //SYNTAX_TREE_TYPEREF_BUILTIN_CHAR
};

/*
static const size_t
IR_TYPE_ENTRY_SIZES[] = 
{
    sizeof(struct ir_type_error_entry),    //IR_ERROR_TYPE
    sizeof(struct ir_type_memarea_entry),  //IR_MEMAREA_TYPE
    sizeof(struct ir_type_callable_entry), //IR_CALLABLE_TYPE
    sizeof(struct ir_type_param_entry)     //IR_PARAM_TYPE
};
*/

inline static unsigned char
det_constant_unsigned_min_type(const uint64_t constant)
{
    if (constant > UINT16_MAX)
    {
        if (constant > UINT32_MAX)
            return CFG_BASIC_TYPE_U64;
        
        return CFG_BASIC_TYPE_U32;
    }

    if (constant > UINT8_MAX)
        return CFG_BASIC_TYPE_U16;

    return CFG_BASIC_TYPE_U8;

}

inline static unsigned char
det_constant_signed_min_type(const uint64_t constant)
{
    if (constant > INT32_MAX)
    {
        if (constant > INT64_MAX)
            return CFG_BASIC_TYPE_S128;
        
        return CFG_BASIC_TYPE_S64;
    }

    if (constant > INT8_MAX)
    {
        if (constant > INT16_MAX)
            return CFG_BASIC_TYPE_S32;
        
        return CFG_BASIC_TYPE_S16;
    }

    return CFG_BASIC_TYPE_S8;
}

/*
enum types_balance_const_retcode
{
    BALANCE_CONST_CAST_EXPR,
    BALANCE_CONST_CAST_CONST
};

static enum types_balance_const_retcode
types_balance_const(
        const unsigned char prev_type,
        const uint64_t constant,
        unsigned char *const new_type)
{
    unsigned char tmp;

    if (prev_type % 2 == 1)
        tmp = det_constant_signed_min_type(constant);
    else
        tmp = det_constant_unsigned_min_type(constant);

    if (prev_type < tmp)
    {
        *new_type = tmp;
        return BALANCE_CONST_CAST_EXPR;
    }

    *new_type = prev_type;
    return BALANCE_CONST_CAST_CONST;
}

enum types_balance_binop_retcode
{
    BALANCE_TYPES_CAST_NO_NEED = 0,
    BALANCE_TYPES_CAST_LEFT = 2,
    BALANCE_TYPES_CAST_RIGHT = 4,
    BALANCE_TYPES_CAST_BOTH = 8
};

static enum types_balance_binop_retcode
types_balance_double(
        unsigned char left_type,
        unsigned char right_type,
        unsigned char machine_max_type,
        unsigned char *const new_type)
{
    enum types_balance_binop_retcode res;
    unsigned char tmp;

    res = BALANCE_TYPES_CAST_NO_NEED;
    machine_max_type /= 2;
    tmp = left_type / 2;

    if (tmp > machine_max_type)
    {
        left_type -= tmp - machine_max_type;
        res |= BALANCE_TYPES_CAST_LEFT;
    }

    if (left_type != right_type)
    {
        return res | BALANCE_TYPES_CAST_RIGHT;
    }

    *new_type = left_type;
    return res;
}
*/

//----------------------------- callable name table funcs --------------------------------

inline static default_retcode
ir_name_table_write_entry_start(
        struct extendable_chunk *const self,
        const size_t entires_num,
        union ir_type_entry_ptr *const place)
{
    if (chunk_extend_to_fit(self, entires_num * sizeof(union ir_type_entry_any))
        == ERROR)
        return ERROR;

    place->unknown = self->start + self->size;
    return SUCCESS;
}

inline static void
ir_name_table_write_entry_done(
        struct extendable_chunk *const self,
        const size_t written_size)
{
    self->size += written_size;
}

inline static default_retcode
ir_name_table_add_param_entry(
        struct extendable_chunk *const self,
        const size_t param_num,
        const size_t callable_ind)
{
    struct ir_type_param_entry *entry;

    if (chunk_extend_to_fit(self, sizeof(struct ir_type_param_entry) == ERROR))
        return ERROR;

    entry = (struct ir_type_param_entry*)(self->start + self->size);
    entry->header.entry_type = IR_PARAM_TYPE;
    entry->param_num = param_num;
    entry->callable_ind = callable_ind;
    self->size += sizeof(struct ir_type_param_entry);
    return SUCCESS;
}

inline static default_retcode
ir_name_table_add_memarea_entry(
        struct extendable_chunk *const self,
        const uint64_t size)
{
    struct ir_type_memarea_entry *entry;

    if (chunk_extend_to_fit(self, sizeof(struct ir_type_memarea_entry)) == ERROR)
        return ERROR;

    entry = (struct ir_type_memarea_entry*)(self->start + self->size);
    self->size += sizeof(struct ir_type_memarea_entry);

    entry->header.entry_type = IR_MEMAREA_TYPE;
    entry->size = size;
    return SUCCESS;
}

inline static default_retcode
ir_name_table_add_callable_entry(
        struct extendable_chunk *const self,
        const size_t ir_sourceitems_table_ind)
{
    struct ir_type_callable_entry *entry;

    if (chunk_extend_to_fit(self, sizeof(struct ir_type_callable_entry)) == ERROR)
        return ERROR;

    entry = (struct ir_type_callable_entry*)(self->start + self->size);
    self->size += sizeof(struct ir_type_callable_entry);

    entry->header.entry_type = IR_CALLABLE_TYPE;
    entry->ir_sourceitems_table_ind = ir_sourceitems_table_ind;
    return SUCCESS;
}

//------------------------------- tmp name tables stuff ----------------------------------

struct names_map_stack
{
    size_t stack_top_ind;
#define NAME_TABLES_STACK_PREALLOC_NUM  5
    struct extendable_chunk stack;
};


inline static default_retcode
names_map_stack_init(struct names_map_stack *const self)
{
    struct sizes_map *dict;

    if (chunk_init(&self->stack,
                   NAME_TABLES_STACK_PREALLOC_NUM * sizeof(struct sizes_map)) == ERROR)
        return ERROR;

    dict = (struct sizes_map*) self->stack.start;

    for (int i = 0; i < NAME_TABLES_STACK_PREALLOC_NUM; i++)
    {
        if (sizes_map_init(dict + i) == MAP_MEM_ERROR)
        {
            while (i > 0)
            {
                i--;
                sizes_map_deinit(dict + i);
            }

            sizes_map_deinit(dict);
            chunk_deinit(&self->stack);
            return ERROR;
        }

        self->stack.size += sizeof(struct sizes_map);
    }

    self->stack_top_ind = 0;
    return SUCCESS;
}

inline static void
names_map_stack_deinit(struct names_map_stack *const self)
{
    struct sizes_map *dict_start;
    struct sizes_map *dict_end;

    dict_start = (struct sizes_map*) self->stack.start;
    dict_end = (struct sizes_map*) (((char*) dict_start) + self->stack.size);

    for (;dict_start < dict_end; dict_start++)
        sizes_map_deinit(dict_start);

    chunk_deinit(&self->stack);
}

inline static default_retcode
names_map_stack_enter_scope(struct names_map_stack *const self)
{
    size_t cur_dict_offset;

    cur_dict_offset = self->stack_top_ind + sizeof(struct sizes_map);

    if (cur_dict_offset == self->stack.size)
    {
        if ((chunk_extend_to_fit(&self->stack, sizeof(struct sizes_map)) == ERROR)
            && (sizes_map_init((struct sizes_map*)(self->stack.start 
                                                     + cur_dict_offset)))
                == MAP_MEM_ERROR)
            return ERROR;

        self->stack.size = cur_dict_offset + sizeof(struct sizes_map);
    }

    self->stack_top_ind = cur_dict_offset;
    return SUCCESS; 
}

inline static void
names_map_stack_leave_scope(struct names_map_stack *const self)
{
    size_t cur_dict_offset;

    cur_dict_offset = self->stack_top_ind;

    sizes_map_reset((struct sizes_map*)(self->stack.start + cur_dict_offset));

    self->stack_top_ind = cur_dict_offset - sizeof(struct sizes_map);
}

inline static void
names_map_stack_reset_global(struct names_map_stack *const self)
{
    sizes_map_reset((struct sizes_map*)(self->stack.start));
}

enum names_map_stack_locate_name_retcode
{
    NAME_NOT_FOUND,
    NAME_FOUND,
    NAME_FOUND_GLOBAL
};

inline static enum names_map_stack_locate_name_retcode
names_map_stack_locate_name(
        const struct names_map_stack *const self,
        const size_t name_ind,
        size_t *const table_ind)
{
    struct sizes_map_pair pair;
    struct sizes_map *start;
    struct sizes_map *end;

    end = (struct sizes_map*) self->stack.start;
    start = (struct sizes_map*) (self->stack.start + self->stack_top_ind);

    for (;start > end; start--)
    { 
        if (sizes_map_get_first(start, name_ind, &pair) == SIZES_MAP_FOUND)
        {
            *table_ind = pair.val;
            return NAME_FOUND;
        }
    }

    // check global scope
    if (sizes_map_get_first(start, name_ind, &pair) == SIZES_MAP_FOUND)
    {
        *table_ind = pair.val;
        return NAME_FOUND_GLOBAL;
    }

    return NAME_NOT_FOUND;
}

inline static default_retcode
names_map_stack_add_name(
    struct names_map_stack *const self,
    const size_t name_ind,
    const size_t table_ind)
{
    struct sizes_map_pair p;   
    
    p.val = table_ind;
    p.key = name_ind;

    if (sizes_map_add((struct sizes_map*)(self->stack.start + self->stack_top_ind), p)
        != MAP_SUCCESS)
        return ERROR;

    return SUCCESS;
}

//------------------------------ type annotation structs ---------------------------------

struct callable_tmp_name_table_postfix
{
    size_t callables_offset;
    size_t objects_num;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_type_entr_header
{
#define TMP_NAME_UNDEF_TYPE        0
#define TMP_NAME_BASIC_TYPE        1
#define TMP_NAME_ARRAY_TYPE        2
#define TMP_NAME_RECORD_TYPE       3
#define TMP_NAME_CALLABLE_TYPE     4
#define TMP_NAME_CALLABLE_REF_TYPE 5
    unsigned char entry_type;
};

struct tmp_name_tbl_type_entr_undef
{
    struct tmp_name_tbl_type_entr_header header;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_type_entr_basic
{
    struct tmp_name_tbl_type_entr_header header;
    unsigned char basic_type;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_type_entr_array
{
    struct tmp_name_tbl_type_entr_header header;
    size_t dimensions_num;
    uint64_t size;
    size_t next_type_offset;
    uint64_t dim_sizes[];
};

struct tmp_name_tbl_type_entr_callable_ref
{
    struct tmp_name_tbl_type_entr_header header;
    size_t tmp_read_tbl_ind;
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_type_entr_subfield
{
    uint64_t field_size;
    size_t str_ind;
    size_t type_offset;
};

struct tmp_name_tbl_type_entr_callable
{
    struct tmp_name_tbl_type_entr_header header;
    size_t sourceitems_tbl_ind;
    size_t args_num;
    size_t returns_num;
    size_t next_type_offset;
    struct tmp_name_tbl_type_entr_subfield data[];
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_type_entr_record
{
    struct tmp_name_tbl_type_entr_header header;
    uint64_t size;
    size_t entries_num;
    size_t next_type_offset;
    struct tmp_name_tbl_type_entr_subfield data[];
};

union tmp_name_tbl_type_ptr
{
    struct tmp_name_tbl_type_entr_header *header;
    struct tmp_name_tbl_type_entr_basic *basic;
    struct tmp_name_tbl_type_entr_array *array;
    struct tmp_name_tbl_type_entr_callable *callable;
    struct tmp_name_tbl_type_entr_callable_ref *callable_ref;
    struct tmp_name_tbl_type_entr_record *record;
    struct tmp_name_tbl_type_entr_undef *undef;
    char * unknown;
};

//-------------------------------- tmp_name_tbl entries ----------------------------------

struct tmp_name_tbl_entr
{
    size_t ind;
    // tmp_name_tbl_type_entry
    char data[];
} __attribute__ ((aligned (sizeof(uint64_t))));

struct tmp_name_tbl_callable_entr
{
    size_t ind;
    size_t statements_num;
    size_t *statements_ind_arr;
    // struct tmp_name_tbl_type_entr_callable
    char data[];
} __attribute__ ((aligned (sizeof(uint64_t))));

//--------------------------------- cfg nodes builder ------------------------------------

DEFINE_TYPED_CHUNK_LIST(ind_stack, size_t)

struct cfg_nodes_builder
{
#define CFG_NODES_BUILDER_POOL_PREALLOC_BYTES 4096
    struct extendable_chunk nodes_pool;
#define CFG_NODES_BUILDER_STACK_PREALLOC_BYTES 128
    struct extendable_chunk loop_stack;
#define CFG_NODES_BUILDER_DRAIN_PREALLOC_BYTES 512
    struct extendable_chunk drain_stack;
#define CFG_NODES_BUILDER_RET_DRAIN_PREALLOC_BYTES 128
    struct extendable_chunk ret_drain_stack;
};

inline static void
cfg_nodes_builder_reset(struct cfg_nodes_builder *const self)
{
    struct cfg_node *p = (struct cfg_node*) self->nodes_pool.start;

    p->child_1 = sizeof(struct cfg_node);
    p->child_2 = 0;

    self->nodes_pool.size = sizeof(struct cfg_node);

    self->loop_stack.size = 0;
    self->drain_stack.size = 0;
    self->ret_drain_stack.size = 0;
}

inline static default_retcode
cfg_nodes_builder_init(struct cfg_nodes_builder *const self)
{
    if (chunk_init(&self->nodes_pool, CFG_NODES_BUILDER_POOL_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_0;
 
    if (chunk_init(&self->loop_stack, CFG_NODES_BUILDER_STACK_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_1;

    if (chunk_init(&self->drain_stack, CFG_NODES_BUILDER_DRAIN_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_2;

    if (chunk_init(&self->ret_drain_stack,
                   CFG_NODES_BUILDER_RET_DRAIN_PREALLOC_BYTES)
        == ERROR)
        goto ERROR_EXIT_3;

    cfg_nodes_builder_reset(self);
    return SUCCESS;

ERROR_EXIT_3:
    chunk_deinit(&self->drain_stack);
ERROR_EXIT_2:
    chunk_deinit(&self->loop_stack);
ERROR_EXIT_1:
    chunk_deinit(&self->nodes_pool);
ERROR_EXIT_0:
    return ERROR;
}

inline static void
cfg_nodes_builder_deinit(struct cfg_nodes_builder *const self)
{
    chunk_deinit(&self->nodes_pool);
    chunk_deinit(&self->loop_stack);
    chunk_deinit(&self->drain_stack);
    chunk_deinit(&self->ret_drain_stack);
}

inline static default_retcode
cfg_nodes_builder_add_node(
        struct cfg_nodes_builder *const self,
        const size_t pool_size,
        int line,
        int column,
        size_t child_1_ind,
        size_t child_2_ind)
{
    struct cfg_node *p;

    if (chunk_extend_to_fit(&self->nodes_pool, sizeof(struct cfg_node)) == ERROR)
        return ERROR;

    p = (struct cfg_node*)(self->nodes_pool.start + pool_size);
    self->nodes_pool.size += sizeof(struct cfg_node);

    p->line = line;
    p->column = column;

    p->child_1 = child_1_ind;
    p->child_2 = child_2_ind;
    return SUCCESS;
}

inline static default_retcode
cfg_nodes_builder_pump_node(struct cfg_nodes_builder *const self, const size_t i)
{
    return ind_stack_append(&self->drain_stack, i);
}

inline static void
cfg_nodes_builder_drain_nodes(
        struct cfg_nodes_builder *const self,
        const char *const nodes_pool_base,
        const size_t start_size,
        const size_t i)
{
    size_t *start = (size_t*)(self->drain_stack.start + start_size);
    const size_t *const end = (size_t*)
                              (self->drain_stack.start + self->drain_stack.size);

    for (; start < end; start++)
        ((struct cfg_node*)(nodes_pool_base + *start))->child_1 = i;

    self->drain_stack.size = start_size;
}

inline static default_retcode
cfg_nodes_builder_pump_ret_nodes(
        struct cfg_nodes_builder *const self,
        const size_t start_size)
{

    if (chunk_append_from(&self->ret_drain_stack,
                          self->drain_stack.start + start_size,
                          self->drain_stack.size - start_size)
        == ERROR)
        return ERROR;

    self->drain_stack.size = start_size;
    return SUCCESS;
}

inline static default_retcode
cfg_nodes_builder_pump_ret_node(struct cfg_nodes_builder *const self, const size_t i)
{
    return ind_stack_append(&self->ret_drain_stack, i);
}

inline static default_retcode
cfg_nodes_builder_loop_stack_append(struct cfg_nodes_builder *const self, const size_t i)
{
    return ind_stack_append(&self->loop_stack, i);
}

enum cfg_nodes_builder_loop_stack_pop_retcode
{
    CFG_NODES_BREAK_NOT_FOUND,
    CFG_NODES_BREAK_SUCCESS
};

inline static enum cfg_nodes_builder_loop_stack_pop_retcode
cfg_nodes_builder_loop_stack_pop(struct cfg_nodes_builder *const self, size_t *const ind)
{
    if (self->loop_stack.size == 0)
        return CFG_NODES_BREAK_NOT_FOUND;

    *ind = ind_stack_pop(&self->loop_stack);
    return CFG_NODES_BREAK_SUCCESS;
}

static default_retcode
cfg_nodes_builder_finish(
        struct cfg_nodes_builder *const self,
        struct extendable_chunk *const place)
{
    struct cfg_node *last;
    size_t *start;
    char *nodes_pool_base;
    const size_t *end;
    const size_t cur_size = self->nodes_pool.size;

    // add last node
    if (chunk_extend_to_fit(&self->nodes_pool, sizeof(struct cfg_node)) == ERROR)
        return ERROR;

    nodes_pool_base = self->nodes_pool.start;

    last = (struct cfg_node*)(nodes_pool_base + cur_size);
    last->child_1 = 0;
    last->child_2 = 0;
    self->nodes_pool.size = cur_size + sizeof(struct cfg_node);

    // drain all remaining nodes
    cfg_nodes_builder_drain_nodes(self, nodes_pool_base, 0, cur_size);

    // drain all return nodes
    start = (size_t*)self->ret_drain_stack.start;
    end = (size_t*)(self->ret_drain_stack.start + self->ret_drain_stack.size);

    for (;start < end; start++)
        ((struct cfg_node*)(nodes_pool_base + *start))->child_1 = cur_size;

    if (chunk_move_reinit(&self->nodes_pool,
                          place,
                          CFG_NODES_BUILDER_POOL_PREALLOC_BYTES)
        == ERROR)
        return ERROR;

    cfg_nodes_builder_reset(self);
    return SUCCESS;
}


//------------------------------------- ir builder ---------------------------------------

struct ir_builder
{
    // read only struct!
    struct syntax_tree tree;

    struct names_map_stack names_map_stack;  
#define IR_BUILDER_TMP_NAME_TABLE_PREALLOC_BYTES 512
    struct extendable_chunk callable_tmp_name_table_read;
    struct extendable_chunk callable_tmp_name_table_write;
    struct extendable_chunk tmp_name_table;
#define IR_BUILDER_NAME_TABLE_PREALLOC_BYTES 512
    struct extendable_chunk cur_table;
#define IR_BUILDER_SOURCEITEMS_TABLE_PREALLOC_BYTES 4096
    struct extendable_chunk sourceitems_table;
#define IR_EXP_BUILD_PREALLOC_BYTES 128
    struct extendable_chunk ir_exp_build_space;  
    struct cfg_nodes_builder cfg_builder;
    unsigned char is_broken;
    unsigned char max_machine_word_type;
    unsigned char max_machine_word_size;
};

enum ir_builder_retcode
{
    IR_BUILDER_ERROR,
    IR_BUILDER_SEM_ERROR,
    IR_BUILDER_SUCCESS
};

static default_retcode
ir_builder_process_ast(struct ir_builder*);

inline static default_retcode
ir_builder_init(
        struct ir_builder *const self,
        const unsigned char max_machine_word_type,
        const struct syntax_tree *const tree)
{
    self->tree = *tree;
    self->is_broken = 0;
    self->max_machine_word_type = max_machine_word_type;
    self->max_machine_word_size = BASIC_TYPE_SIZE_CALC(max_machine_word_type);

    if (names_map_stack_init(&self->names_map_stack) == ERROR)
        goto ERROR_EXIT_0;

    if (chunk_init(&self->callable_tmp_name_table_read,
                   IR_BUILDER_TMP_NAME_TABLE_PREALLOC_BYTES)
        == ERROR)
        goto ERROR_EXIT_1;

    if (chunk_init(&self->callable_tmp_name_table_write,
                   IR_BUILDER_TMP_NAME_TABLE_PREALLOC_BYTES)
        == ERROR)
        goto ERROR_EXIT_2;

    if (chunk_init(&self->tmp_name_table, IR_BUILDER_TMP_NAME_TABLE_PREALLOC_BYTES)
        == ERROR)
        goto ERROR_EXIT_3;

    if (chunk_init(&self->cur_table, IR_BUILDER_NAME_TABLE_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_4;

    if (chunk_init(&self->sourceitems_table, IR_BUILDER_SOURCEITEMS_TABLE_PREALLOC_BYTES)
        == ERROR)
        goto ERROR_EXIT_5;

    if (chunk_init(&self->ir_exp_build_space, IR_EXP_BUILD_PREALLOC_BYTES) == ERROR)
        goto ERROR_EXIT_6;

    if (cfg_nodes_builder_init(&self->cfg_builder) == ERROR)
        goto ERROR_EXIT_7;
    
    if (ir_builder_process_ast(self) != ERROR)
        return SUCCESS;

    cfg_nodes_builder_deinit(&self->cfg_builder);
ERROR_EXIT_7:
    chunk_deinit(&self->ir_exp_build_space);
ERROR_EXIT_6:
    chunk_deinit(&self->sourceitems_table);
ERROR_EXIT_5:
    chunk_deinit(&self->cur_table);
ERROR_EXIT_4:
    chunk_deinit(&self->tmp_name_table);
ERROR_EXIT_3:
    chunk_deinit(&self->callable_tmp_name_table_write);
ERROR_EXIT_2:
    chunk_deinit(&self->callable_tmp_name_table_read);
ERROR_EXIT_1:
    names_map_stack_deinit(&self->names_map_stack);
ERROR_EXIT_0:
    return ERROR;
}


inline static void
ir_builder_deinit(struct ir_builder *const self)
{
    cfg_nodes_builder_deinit(&self->cfg_builder);
    chunk_deinit(&self->ir_exp_build_space);
    chunk_deinit(&self->sourceitems_table);
    chunk_deinit(&self->cur_table);
    chunk_deinit(&self->tmp_name_table);
    chunk_deinit(&self->callable_tmp_name_table_write);
    chunk_deinit(&self->callable_tmp_name_table_read);
    names_map_stack_deinit(&self->names_map_stack);
}

inline static default_retcode
ir_builder_finish(struct ir_builder *const self, struct ir *const res)
{
    if (chunk_slim_down(&self->sourceitems_table) == ERROR)
        return ERROR;

    res->global_sym_table = self->sourceitems_table;

    cfg_nodes_builder_deinit(&self->cfg_builder);
    chunk_deinit(&self->ir_exp_build_space);
    chunk_deinit(&self->cur_table);
    chunk_deinit(&self->tmp_name_table);
    chunk_deinit(&self->callable_tmp_name_table_write);
    chunk_deinit(&self->callable_tmp_name_table_read);
    names_map_stack_deinit(&self->names_map_stack);
    return SUCCESS;
}

//----------------------------- error generating functions -------------------------------

inline static void
ir_builder_gen_err_name_cstom_tpes(
        struct ir_builder *const self,
        const size_t string_ind,
        const struct ast_node_location * const loc)
{
    self->is_broken = 1;
    fprintf(stderr,
            "(%d, %d): custom types are unsopported (%s)\n",
            loc->line_num,
            loc->column_num,
            string_map_get_str_ptr(&self->tree.strings, string_ind));
}

inline static void
ir_builder_gen_err_name_redef(
        struct ir_builder *const self,
        const size_t string_ind,
        const struct ast_node_location * const loc)
{
    self->is_broken = 1;
    fprintf(stderr,
            "(%d, %d): redifinition of name %s\n",
            loc->line_num,
            loc->column_num,
            string_map_get_str_ptr(&self->tree.strings, string_ind));
}

inline static void
ir_builder_gen_err_types_mismatch(
        struct ir_builder *const self,
        const size_t string_ind,
        const struct ast_node_location * const loc,
        const unsigned char lvalue_basic_type,
        const unsigned char rvalue_basic_type)
{
    self->is_broken = 1;
    fprintf(stderr, 
            "(%d, %d): types mismatch for %s, %s vs %s\n",
            loc->line_num,
            loc->column_num,
            string_map_get_str_ptr(&self->tree.strings, string_ind),
            BASIC_TYPE_TO_STR[lvalue_basic_type],
            BASIC_TYPE_TO_STR[rvalue_basic_type]);
}

inline static void
ir_builder_gen_err_name_notfound(
        struct ir_builder *const self,
        const struct ast_node_location * const loc,
        const size_t string_ind)
{
    self->is_broken = 1;
    fprintf(stderr, 
            "(%d, %d): name %s is not presented in scope\n",
            loc->line_num,
            loc->column_num,
            string_map_get_str_ptr(&self->tree.strings, string_ind));
}

inline static void
ir_builder_gen_err_not_integer(
        struct ir_builder *const self,
        const struct ast_node_location * const loc,
        const size_t string_ind)
{
    self->is_broken = 1;
    fprintf(stderr, 
            "(%d, %d): name %s is not presentable as int\n",
            loc->line_num,
            loc->column_num,
            string_map_get_str_ptr(&self->tree.strings, string_ind));
}

inline static void
ir_builder_gen_err_simple(
        struct ir_builder *const self,
        const struct ast_node_location * const loc,
        const char *const msg)
{
    self->is_broken = 1;
    fprintf(stderr, "(%d, %d): %s\n", loc->line_num, loc->column_num, msg);
}

//------------------------------ type annotation building --------------------------------

static enum ir_builder_retcode
tmp_name_tbl_try_annotate(
        struct extendable_chunk*,
        char*,
        size_t,
        uint64_t*,
        struct ir_builder*);

static enum ir_builder_retcode
tmp_name_tbl_typeref_annotate_array(
        struct extendable_chunk *const self,
        char *const tree_base,
        const size_t cur_tmp_entr_ind, 
        const size_t typeref_ind,
        const size_t my_dim,
        uint64_t *const prev_dim_size_p,
        struct ir_builder *const ir_builder)
{ 
    enum ir_builder_retcode res;
    union ast_node_ptr node;
    union tmp_name_tbl_type_ptr my_type;
    uint64_t my_elem_num;
    uint64_t dim_size;

    node.unknown = tree_base + typeref_ind;

    if (node.header->type == SYNTAX_TREE_TYPEREF_ARRAY)
    {
        if (chunk_extend_to_fit(self, sizeof(uint64_t)) == ERROR)
            return IR_BUILDER_ERROR;

        self->size += sizeof(uint64_t);

        if (tmp_name_tbl_typeref_annotate_array(self,
                                              tree_base,
                                              cur_tmp_entr_ind,
                                              AST_PAR_NODE_1_CHILD(node),
                                              my_dim + 1,
                                              &dim_size,
                                              ir_builder)
            == IR_BUILDER_ERROR)
            return IR_BUILDER_ERROR;

        my_elem_num = SYNTAX_TREE_NUM_BY_IND(ir_builder->tree.numbers,
                                             AST_PAR_NODE_PARAMETER(node).ind);

        if (unlikely(__builtin_mul_overflow(dim_size, my_elem_num, &dim_size)))
        { 
            ir_builder_gen_err_simple(ir_builder,
                                      AST_PAR_NODE_LEAF_LOC(node),
                                      "size of type exceeds 64 bits");
            return IR_BUILDER_SEM_ERROR;
        }

        my_type.unknown = self->start + cur_tmp_entr_ind;
        my_type.array->dim_sizes[my_dim] = dim_size;
        *prev_dim_size_p = dim_size;
        return IR_BUILDER_SUCCESS;
    }

    // last typeref
    res = tmp_name_tbl_try_annotate(self, tree_base, typeref_ind, &dim_size, ir_builder);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    my_type.unknown = self->start + cur_tmp_entr_ind;
    my_type.array->dimensions_num = my_dim;
    *prev_dim_size_p = dim_size;
    return IR_BUILDER_SUCCESS;
}

inline static enum ir_builder_retcode
tmp_name_tbl_try_annotate(
        struct extendable_chunk *const self,
        char *const tree_base,
        size_t typeref_node_ind,
        uint64_t *const type_len,
        struct ir_builder *const ir_builder)
{
    enum ir_builder_retcode res;
    union ast_node_ptr node;
    union tmp_name_tbl_type_ptr entry;
    uint64_t type_size;
    size_t tmp_name_tbl_saved_size;
    int node_type;
    unsigned char basic_type;

    node.unknown = tree_base + typeref_node_ind;
    node_type = node.header->type;
    tmp_name_tbl_saved_size = self->size;

    switch(node_type)
    {
        case SYNTAX_TREE_TYPEREF_BUILTIN_BOOL:
        case SYNTAX_TREE_TYPEREF_BUILTIN_BYTE:
        case SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE:
        case SYNTAX_TREE_TYPEREF_BUILTIN_CHAR:
        case SYNTAX_TREE_TYPEREF_BUILTIN_SHORT:
        case SYNTAX_TREE_TYPEREF_BUILTIN_USHORT:
        case SYNTAX_TREE_TYPEREF_BUILTIN_INT:
        case SYNTAX_TREE_TYPEREF_BUILTIN_UINT:
        case SYNTAX_TREE_TYPEREF_BUILTIN_LONG:
        case SYNTAX_TREE_TYPEREF_BUILTIN_ULONG:
        case SYNTAX_TREE_TYPEREF_BUILTIN_HUGE:
        case SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE:
        case SYNTAX_TREE_TYPEREF_BUILTIN_STRING:
            if (chunk_extend_to_fit(self, sizeof(struct tmp_name_tbl_type_entr_basic))
                == ERROR)
                return IR_BUILDER_ERROR;

            entry.unknown = self->start + tmp_name_tbl_saved_size;
            entry.basic->header.entry_type = TMP_NAME_BASIC_TYPE;
            basic_type = TYPEREF_TO_BASIC_TYPE[node_type
                                               - SYNTAX_TREE_TYPEREF_BUILTIN_BOOL];
            entry.basic->basic_type= basic_type;

            self->size += sizeof(struct tmp_name_tbl_type_entr_basic);

            if (node_type == SYNTAX_TREE_TYPEREF_BUILTIN_STRING)
                *type_len = ir_builder->max_machine_word_size;
            else
                *type_len = BASIC_TYPE_SIZE_CALC(basic_type);

            return IR_BUILDER_SUCCESS; 

        case SYNTAX_TREE_TYPEREF_ARRAY:
            if (chunk_extend_to_fit(self, sizeof(struct tmp_name_tbl_type_entr_array))
                == ERROR)
                return IR_BUILDER_ERROR;

            self->size += sizeof(struct tmp_name_tbl_type_entr_array);

            res = tmp_name_tbl_typeref_annotate_array(self,
                                                    tree_base,
                                                    tmp_name_tbl_saved_size,
                                                    typeref_node_ind,
                                                    0,
                                                    &type_size,
                                                    ir_builder);

            if (res != IR_BUILDER_SUCCESS)
                return res;

            entry.unknown = self->start + tmp_name_tbl_saved_size;
            entry.array->size = type_size;
            entry.array->next_type_offset = self->size - tmp_name_tbl_saved_size;
            entry.header->entry_type = TMP_NAME_ARRAY_TYPE;
            return IR_BUILDER_SUCCESS;

        case SYNTAX_TREE_TYPEREF_CUSTOM:
            ir_builder_gen_err_name_cstom_tpes(ir_builder,
                                               AST_PAR_NODE_PARAMETER(node).ind,
                                               AST_PAR_NODE_1_CHILD_LOC(node)); 
            return IR_BUILDER_SEM_ERROR;
    }

        return IR_BUILDER_SUCCESS; 
}

static default_retcode
tmp_name_tbl_append_typeref_annotation(
        struct extendable_chunk *const self,
        const size_t typeref_ind,
        uint64_t *const type_size,
        struct ir_builder *const ir_builder)
{
    union tmp_name_tbl_type_ptr type;
    const size_t start_tmp_tbl_ind = self->size;

    switch (tmp_name_tbl_try_annotate(self,
                                      ir_builder->tree.tree,
                                      typeref_ind,
                                      type_size,
                                      ir_builder))
    {
        case IR_BUILDER_ERROR:
            return ERROR;

        case IR_BUILDER_SEM_ERROR:
            if (chunk_extend_to_fit(self, sizeof(struct tmp_name_tbl_type_entr_undef))
                == ERROR)
                return ERROR;

            type.unknown = self->start + start_tmp_tbl_ind;
            type.header->entry_type = TMP_NAME_UNDEF_TYPE;
            self->size += sizeof(struct tmp_name_tbl_type_entr_undef);
            *type_size = 0;
            return SUCCESS;

        case IR_BUILDER_SUCCESS:
            return SUCCESS;
    }

    return SUCCESS;
}

static default_retcode
tmp_name_tbl_append_callable_annotation(
        struct extendable_chunk *const self,
        union ast_node_ptr node, // func sign node
        const size_t sourceitems_tbl_ind,
        struct ir_builder *const ir_builder) 
{
    union tmp_name_tbl_type_ptr entry;
    size_t tmp;
    size_t args_num;
    size_t returns_num;
    uint64_t type_size;
    char *tmp_name_tbl_base;

    char *const tree_base = ir_builder->tree.tree;
    const size_t this_entry_ind = self->size;
    const size_t child_num = AST_PAR_NODE_N_CHILD_NUM(node);
    const size_t *const child_ind_arr = AST_PAR_NODE_N_CHILD_ARR(node);

    type_size = 0;
    // extend with size of this callable annotation entry
    tmp = sizeof(struct tmp_name_tbl_type_entr_callable)
          + sizeof(struct tmp_name_tbl_type_entr_subfield) * child_num;

    if (chunk_extend_to_fit(self, tmp) == ERROR)
        return ERROR;

    self->size += tmp;
    args_num = 0;
    returns_num = 0;

    for (size_t i = 0; i < child_num; i++)
    {
        node.unknown = tree_base + child_ind_arr[i];
        tmp = self->size;
        
        switch (node.header->type)
        {
            case SYNTAX_TREE_FUNC_UNTYPED_ARG:
                if (chunk_extend_to_fit(self, sizeof(struct tmp_name_tbl_type_entr_basic))
                    == ERROR)
                    return ERROR;

                tmp_name_tbl_base = self->start;
                entry.unknown = tmp_name_tbl_base + this_entry_ind;
                entry.callable->data[i].field_size = 32;
                entry.callable->data[i].str_ind = AST_PAR_NODE_PARAMETER(node).ind;
                entry.callable->data[i].type_offset = tmp;

                entry.unknown = tmp_name_tbl_base + tmp;
                entry.header->entry_type = TMP_NAME_BASIC_TYPE;
                entry.basic->basic_type = CFG_BASIC_TYPE_S32;
                self->size += sizeof(struct tmp_name_tbl_type_entr_basic);

                args_num++;
                break;

            case SYNTAX_TREE_FUNC_TYPED_ARG:
                if (tmp_name_tbl_append_typeref_annotation(self,
                                                           AST_PAR_NODE_1_CHILD(node),
                                                           &type_size,
                                                           ir_builder)
                    == ERROR)
                    return ERROR;

                tmp_name_tbl_base = self->start;
                entry.unknown = tmp_name_tbl_base + this_entry_ind;
                entry.callable->data[i].field_size = type_size;
                entry.callable->data[i].str_ind = AST_PAR_NODE_PARAMETER(node).ind;
                entry.callable->data[i].type_offset = tmp;
                args_num++;
                break;

            default:
                if (tmp_name_tbl_append_typeref_annotation(self,
                                                           child_ind_arr[i],
                                                           &type_size,
                                                           ir_builder)
                    == ERROR)
                    return ERROR;

                tmp_name_tbl_base = self->start;
                entry.unknown = tmp_name_tbl_base + this_entry_ind;
                entry.callable->data[i].field_size = type_size;
                entry.callable->data[i].str_ind = 0; // for later use
                entry.callable->data[i].type_offset = tmp;
                returns_num++;
                break; 
        }
    }

    tmp_name_tbl_base = self->start;
    entry.unknown = tmp_name_tbl_base + this_entry_ind;
    entry.header->entry_type = TMP_NAME_CALLABLE_TYPE;
    entry.callable->args_num = args_num;
    entry.callable->returns_num = returns_num;
    entry.callable->sourceitems_tbl_ind = sourceitems_tbl_ind;
    entry.callable->next_type_offset = self->size - this_entry_ind;
    return SUCCESS;
}

//------------------------------- name adding functions ----------------------------------

inline static enum ir_builder_retcode
ir_builder_check_name_redef(
        struct ir_builder *const self,
        const size_t str_ind,
        const union ast_node_ptr node)
{
    size_t table_ind;

    if (names_map_stack_locate_name(&self->names_map_stack,
                                     str_ind,
                                     &table_ind) != NAME_NOT_FOUND)
    {
        ir_builder_gen_err_name_redef(self, str_ind, ast_node_get_location(node));
        return IR_BUILDER_SEM_ERROR;
    }

    return IR_BUILDER_SUCCESS;
}

inline static enum ir_builder_retcode
ir_builder_write_name(
        struct ir_builder *const self,
        struct tmp_name_tbl_entr *const tmp_name_entr,
        const union ast_node_ptr node,
        const size_t callable_name_tbl_ind)
{
    const size_t str_ind = AST_PAR_NODE_PARAMETER(node).ind;
    const enum ir_builder_retcode res = ir_builder_check_name_redef(self, str_ind, node);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    tmp_name_entr->ind = callable_name_tbl_ind;

    if (names_map_stack_add_name(&self->names_map_stack,
                                 str_ind,
                                 self->tmp_name_table.size)
        == ERROR)
        return IR_BUILDER_ERROR;

    return IR_BUILDER_SUCCESS;
}

/*
static enum ir_builder_retcode
ir_builder_add_annotated_name(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        const size_t callable_name_tbl_ind,
        uint64_t *const type_len)
{
    const size_t str_ind = AST_PAR_NODE_PARAMETER(node).ind;
    enum ir_builder_retcode res = ir_builder_add_name(self, node, callable_name_tbl_ind);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    res = tmp_name_tbl_try_annotate(&self->tmp_name_table,
                                    self->tree.tree,
                                    AST_PAR_NODE_1_CHILD(node),
                                    type_len,
                                    self);

    if (res == IR_BUILDER_ERROR || names_map_stack_add_name(&self->names_map_stack,
                                                            str_ind,
                                                            self->tmp_name_table.size)
        == ERROR)
        return IR_BUILDER_ERROR;

    return res;
}
*/

//static enum ir_builder_retcode
static enum ir_builder_retcode
ir_builder_add_annotated_callable(
        struct ir_builder *const self,
        const union ast_node_ptr node,       // func sign node
        const union ast_node_ptr f_def_node, // func def node
        const size_t sourceitems_tbl_ind,
        const size_t name_tbl_ind)
{
    enum ir_builder_retcode res;
    struct tmp_name_tbl_entr *entry;
    struct tmp_name_tbl_callable_entr *callable_entry;
    union tmp_name_tbl_type_ptr type;
    const size_t str_ind = AST_PAR_NODE_PARAMETER(node).ind;
    const size_t callable_tmp_write_ind = self->callable_tmp_name_table_write.size;

    // form entry on tmp_name_tbl
    
    if (chunk_extend_to_fit(&self->tmp_name_table,
                            sizeof(struct tmp_name_tbl_entr)
                            + sizeof(struct tmp_name_tbl_type_entr_callable_ref))
        == ERROR)
        return IR_BUILDER_ERROR;

    entry = (struct tmp_name_tbl_entr*)
            (self->tmp_name_table.start + self->tmp_name_table.size);
    self->tmp_name_table.size += sizeof(struct tmp_name_tbl_entr)
                                 + sizeof(struct tmp_name_tbl_type_entr_callable_ref);


    res = ir_builder_write_name(self, entry, node, name_tbl_ind);

    if (res != IR_BUILDER_SUCCESS)
        return res;
 
    type.unknown = entry->data;
    type.header->entry_type = TMP_NAME_CALLABLE_REF_TYPE;
    type.callable_ref->tmp_read_tbl_ind = callable_tmp_write_ind;

   // form entry on callable_tmp_name_tbl_write
    if (chunk_extend_to_fit(&self->callable_tmp_name_table_write,
                            sizeof(struct tmp_name_tbl_callable_entr))
        == ERROR)
        return IR_BUILDER_ERROR;

    callable_entry = (struct tmp_name_tbl_callable_entr*)
                     (self->callable_tmp_name_table_write.start + callable_tmp_write_ind);
    self->callable_tmp_name_table_write.size += sizeof(struct tmp_name_tbl_callable_entr);


    callable_entry->ind = str_ind;
    // first child is func sign
    callable_entry->statements_num = AST_NODE_N_CHILD_NUM(f_def_node) - 1;
    callable_entry->statements_ind_arr = AST_NODE_N_CHILD_ARR(f_def_node) + 1;

    if (tmp_name_tbl_append_callable_annotation(&self->callable_tmp_name_table_write,
                                                node,
                                                sourceitems_tbl_ind,
                                                self)
        == ERROR)
        return IR_BUILDER_ERROR;

    return res;
}

static default_retcode
ir_builder_add_annotated_ready(
        struct ir_builder *const self,
        const size_t str_ind,
        const uint64_t type_size,
        union tmp_name_tbl_type_ptr type)
{
    struct tmp_name_tbl_entr *entr;
    size_t type_offset = 0;

    const size_t name_ind = self->tmp_name_table.size;
    const size_t local_tbl_ind = self->cur_table.size;

    if (names_map_stack_add_name(&self->names_map_stack, str_ind, name_ind) == ERROR)
        return ERROR;

    switch(type.header->entry_type)
    {
        case TMP_NAME_BASIC_TYPE:
            type_offset = sizeof(struct tmp_name_tbl_type_entr_basic);
            break;

        case TMP_NAME_ARRAY_TYPE:
            type_offset = type.array->next_type_offset;
            break;
    }

    // form tmp_name_tbl entry
    if (chunk_extend_to_fit(&self->tmp_name_table,
                            sizeof(struct tmp_name_tbl_entr) + type_offset)
        == ERROR)
        return ERROR;

    entr = (struct tmp_name_tbl_entr*)
           (self->tmp_name_table.start + self->tmp_name_table.size);
    entr->ind = local_tbl_ind;
    memcpy(entr->data, type.unknown, type_offset);
    self->tmp_name_table.size += sizeof(struct tmp_name_tbl_entr) + type_offset;


    // form entry on local tbl
    return ir_name_table_add_memarea_entry(&self->cur_table, type_size);
}


//-------------------------- callable preprocessing functions ----------------------------

static enum ir_builder_retcode
ir_builder_def_named_callable(
        struct ir_builder *const self,
        union ast_node_ptr node,
        union ast_node_ptr func_def_node)
{
    enum ir_builder_retcode res;
    struct ir_sourceitems_table_entry *src_items_entr;
    union tmp_name_tbl_type_ptr type;
    union ir_type_entry_ptr ir_type;
    size_t f_args_returns_num;
    size_t f_args_num;
    size_t f_returns_num;
    size_t sourceitems_entry_size;

    const size_t f_name_ind = AST_PAR_NODE_PARAMETER(node).ind;
    const size_t f_name_len = string_map_get_str_len(&self->tree.strings, f_name_ind);
    const size_t f_name_pad_len = sizeof(uint64_t) - f_name_len % sizeof(uint64_t);
    const size_t tmp_name_tbl_ind = self->callable_tmp_name_table_write.size;
    const size_t sourceitems_tbl_ind = self->sourceitems_table.size;
    const size_t local_tbl_ind = self->cur_table.size;

    // add to all tables except sourceitems
    res = ir_builder_add_annotated_callable(self,
                                            node,
                                            func_def_node,
                                            sourceitems_tbl_ind, 
                                            local_tbl_ind);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    type.unknown = ((struct tmp_name_tbl_callable_entr*)
                   (self->callable_tmp_name_table_write.start + tmp_name_tbl_ind))
                   ->data;

    f_args_num = type.callable->args_num;
    f_returns_num = type.callable->returns_num;
    f_args_returns_num = f_args_num + f_returns_num;
              
    sourceitems_entry_size = f_name_len
                             + f_name_pad_len
                             + sizeof(struct ir_sourceitems_table_entry)
                             + sizeof(struct ir_type_memarea_entry)
                             * f_args_returns_num;

    // start adding to sourceitems table and local name table
    if (chunk_extend_to_fit(&self->sourceitems_table, sourceitems_entry_size)
        == ERROR)
        return IR_BUILDER_ERROR;

    self->sourceitems_table.size += sourceitems_entry_size;
    src_items_entr = (struct ir_sourceitems_table_entry*)
                     (self->sourceitems_table.start + sourceitems_tbl_ind);

    src_items_entr->name_size = f_name_len + f_name_pad_len;
    src_items_entr->args_size = f_args_num * sizeof(struct ir_type_memarea_entry);
    src_items_entr->returns_size = f_returns_num * sizeof(struct ir_type_memarea_entry);

    memcpy(src_items_entr->data,
           string_map_get_str_ptr(&self->tree.strings, f_name_ind),
           f_name_len);
    memset(src_items_entr->data + f_name_len, 0, f_name_pad_len);

    ir_type.unknown = src_items_entr->data;

    for (size_t i = 0; i < f_args_returns_num; i++)
    {
        ir_type.unknown += sizeof(struct ir_type_memarea_entry) * i;
        ir_type.header->entry_type = IR_MEMAREA_TYPE;
        ir_type.memarea->size = type.callable->data[i].field_size;
    }

    if (ir_name_table_add_callable_entry(&self->cur_table, sourceitems_tbl_ind) == ERROR)
        return IR_BUILDER_ERROR;

    return IR_BUILDER_SUCCESS;
}

static enum ir_builder_retcode
ir_builder_def_anon_callable(
        struct ir_builder *const self,
        union ast_node_ptr node,
        union ast_node_ptr func_def_node)
{
    enum ir_builder_retcode res;
    struct ir_sourceitems_table_entry *src_items_entr;
    union tmp_name_tbl_type_ptr type;
    union ir_type_entry_ptr ir_type;
    size_t f_args_returns_num;
    size_t f_args_num;
    size_t f_returns_num;
    size_t sourceitems_entry_size;

    const size_t tmp_name_tbl_ind = self->callable_tmp_name_table_write.size;
    const size_t sourceitems_tbl_ind = self->sourceitems_table.size;
    const size_t local_tbl_ind = self->cur_table.size;

    // add to all tables except sourceitems
    res = ir_builder_add_annotated_callable(self,
                                            node,
                                            func_def_node,
                                            sourceitems_tbl_ind, 
                                            local_tbl_ind);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    type.unknown = ((struct tmp_name_tbl_callable_entr*)
                   (self->callable_tmp_name_table_write.start + tmp_name_tbl_ind))
                   ->data;

    f_args_num = type.callable->args_num;
    f_returns_num = type.callable->returns_num;
    f_args_returns_num = f_args_num + f_returns_num;
    sourceitems_entry_size = sizeof(struct ir_type_memarea_entry)
                             * f_args_returns_num
                             + sizeof(struct ir_sourceitems_table_entry);

    // start adding to sourceitems table and local name table
    if (chunk_extend_to_fit(&self->sourceitems_table, sourceitems_entry_size)
        == ERROR)
        return IR_BUILDER_ERROR;

    self->sourceitems_table.size += sourceitems_entry_size;
    src_items_entr = (struct ir_sourceitems_table_entry*)
                     (self->sourceitems_table.start + sourceitems_tbl_ind);

    src_items_entr->name_size = 0;
    src_items_entr->args_size = f_args_num * sizeof(struct ir_type_memarea_entry);
    src_items_entr->returns_size = f_returns_num * sizeof(struct ir_type_memarea_entry);

    ir_type.unknown = src_items_entr->data;

    for (size_t i = 0; i < f_args_returns_num; i++)
    {
        ir_type.unknown += sizeof(struct ir_type_memarea_entry) * i;
        ir_type.header->entry_type = IR_MEMAREA_TYPE;
        ir_type.memarea->size = type.callable->data[i].field_size;
    }

    if (ir_name_table_add_callable_entry(&self->cur_table, sourceitems_tbl_ind) == ERROR)
        return IR_BUILDER_ERROR;

    return IR_BUILDER_SUCCESS;
}

inline static default_retcode
tmp_name_tbl_callable_add_pack(
        struct extendable_chunk *const self,
        const size_t pack_start_offset,
        const size_t pack_objects_num)
{
    struct callable_tmp_name_table_postfix *p;

    if (chunk_extend_to_fit(self, sizeof(struct callable_tmp_name_table_postfix))
        == ERROR)
        return ERROR;

    p = (struct callable_tmp_name_table_postfix*)(self->start + self->size);
    self->size += sizeof(struct callable_tmp_name_table_postfix);

    p->callables_offset = pack_start_offset;
    p->objects_num = pack_objects_num;
    return SUCCESS;
}

//---------------------------- expression building routines ------------------------------
/*
static enum ir_builder_retcode
ir_builder_exp_multiply_by_const_ptr(
        struct ir_builder *const self,
        const unsigned char prev_type,
        const uint64_t constant,
        const char perfom_addition)
{
    union ir_exp_tree_node_ptr exp_node;
    size_t written_size;

    const unsigned char machine_word_type = self->max_machine_word_type;
    // start writing expression
    written_size = sizeof(struct ir_exp_tree_const_node)
                    + sizeof(struct ir_exp_tree_op_node);

    if (chunk_extend_to_fit(&self->ir_exp_build_space,
                            sizeof(struct ir_exp_tree_const_node)
                            + sizeof(struct ir_exp_tree_op_node) * 3)
        == ERROR) 
        return IR_BUILDER_ERROR;

    exp_node.unknown = self->ir_exp_build_space.start + self->ir_exp_build_space.size;

    if (prev_type != machine_word_type)
    {
        exp_node.header->type = IR_EXP_UNOP_CAST;
        exp_node.header->op_base_type = machine_word_type;
        exp_node.unknown += sizeof(struct ir_exp_tree_op_node);
        written_size += sizeof(struct ir_exp_tree_op_node);
    }

    exp_node.header->type = IR_EXP_LEAF_CONST;
    exp_node.header->op_base_type = machine_word_type;
    exp_node.constant->val = constant; 
    exp_node.unknown += sizeof(struct ir_exp_tree_const_node);

    exp_node.header->type = IR_EXP_BINOP_MUL;
    exp_node.header->op_base_type = machine_word_type;

    if (perfom_addition)
    {
        exp_node.unknown += sizeof(struct ir_exp_tree_op_node);
        exp_node.header->type = IR_EXP_UNOP_CAST;
        exp_node.header->op_base_type = machine_word_type;
        written_size += sizeof(struct ir_exp_tree_op_node);
    }

    self->ir_exp_build_space.size += written_size; 
    return IR_BUILDER_SUCCESS;
}

*/
//----------------------------- nodes processing functions -------------------------------
/*
static enum ir_builder_retcode
ir_builder_process_exp(
        struct ir_builder*,
        union ast_node_ptr,
        union tmp_name_tbl_type_ptr*);

static enum ir_builder_retcode
ir_builder_process_l_exp(
        struct ir_builder*,
        union ast_node_ptr,
        union tmp_name_tbl_type_ptr*);

static default_retcode
ir_builder_process_funcdef(struct ir_builder*, size_t);

static enum ir_builder_retcode
ir_builder_process_exp_place_basic(
        struct ir_builder*,
        union ast_node_ptr,
        struct tmp_name_tbl_entr**);
inline static enum ir_builder_retcode

ir_builder_process_define(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        const size_t local_name_tbl_ind)
{
    uint64_t type_len;
    const enum ir_builder_retcode res = ir_builder_add_annotated_name(self,
                                                                      node,
                                                                      local_name_tbl_ind,
                                                                      &type_len);

    if (res != IR_BUILDER_SUCCESS)
        return res;

    if (ir_name_table_add_memarea_entry(&self->cur_table, type_len) == ERROR)
        return IR_BUILDER_ERROR;

    return res;
}

static enum ir_builder_retcode
ir_builder_process_exp_place(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        struct tmp_name_tbl_entr **const place)
{
    size_t tmp;
    union ir_exp_tree_node_ptr exp_ptr;
    struct tmp_name_tbl_entr *entry;
    const size_t str_ind = AST_PAR_NODE_PARAMETER(node).ind;

    if (names_map_stack_locate_name(&self->names_map_stack, str_ind, &tmp)
        == NAME_NOT_FOUND)
    {
        ir_builder_gen_err_name_notfound(self, AST_PAR_NODE_LEAF_LOC(node), str_ind);
        return IR_BUILDER_SEM_ERROR;
    }

    entry = (struct tmp_name_tbl_entr*)(self->tmp_name_table.start + tmp);

    if (chunk_extend_to_fit(&self->ir_exp_build_space,
                            sizeof(struct ir_exp_tree_label_node))
        == ERROR)
        return IR_BUILDER_ERROR;

   exp_ptr.unknown = self->ir_exp_build_space.start + self->ir_exp_build_space.size; 
   exp_ptr.header->type = IR_EXP_LEAF_LABEL;
   exp_ptr.header->op_base_type = self->max_machine_word_type;
   exp_ptr.label->val = entry->ind;

   self->ir_exp_build_space.size += sizeof(struct ir_exp_tree_label_node);
   *place = entry;
   return IR_BUILDER_SUCCESS; 
}

static enum ir_builder_retcode
ir_builder_process_exp_place_basic(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        struct tmp_name_tbl_entr **const place)
{
    size_t tmp;
    union ir_exp_tree_node_ptr exp_ptr;
    union tmp_name_tbl_type_ptr type_entry;
    struct tmp_name_tbl_entr *entry;
    const size_t str_ind = AST_PAR_NODE_PARAMETER(node).ind;

    if (names_map_stack_locate_name(&self->names_map_stack, str_ind, &tmp)
        == NAME_NOT_FOUND)
    {
        ir_builder_gen_err_name_notfound(self, AST_PAR_NODE_LEAF_LOC(node), str_ind);
        return IR_BUILDER_SEM_ERROR;
    }

    entry = (struct tmp_name_tbl_entr*)(self->tmp_name_table.start + tmp);

    if (chunk_extend_to_fit(&self->ir_exp_build_space,
                            sizeof(struct ir_exp_tree_op_node)
                            + sizeof(struct ir_exp_tree_label_node))
        == ERROR)
        return IR_BUILDER_ERROR;

   exp_ptr.unknown = self->ir_exp_build_space.start + self->ir_exp_build_space.size; 
   exp_ptr.header->type = IR_EXP_LEAF_LABEL;
   exp_ptr.header->op_base_type = self->max_machine_word_type;
   exp_ptr.label->val = entry->ind;

   type_entry.unknown = entry->data;

   if (type_entry.header->entry_type != TMP_NAME_BASIC_TYPE)
   {
       ir_builder_gen_err_not_integer(self, AST_PAR_NODE_LEAF_LOC(node), str_ind);
       return IR_BUILDER_SEM_ERROR;
   }

   exp_ptr.unknown += sizeof(struct ir_exp_tree_label_node);
   exp_ptr.header->type = IR_EXP_UNOP_READ;
   exp_ptr.header->op_base_type = type_entry.basic->basic_type;

   self->ir_exp_build_space.size += sizeof(struct ir_exp_tree_label_node)
                                    + sizeof(struct ir_exp_tree_op_node);
   *place = entry;
   return IR_BUILDER_SUCCESS; 
}

static enum ir_builder_retcode
ir_builder_process_exp_ind_routine(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        union tmp_name_tbl_type_ptr *const continue_type,
        size_t *const continue_dim)
{
    union ast_node_ptr child;
    enum ir_builder_retcode res;
    size_t my_dim;
    union tmp_name_tbl_type_ptr arr_type;
    union tmp_name_tbl_type_ptr braces_type;
    char perfom_addition;

    const char *const tree_base = self->tree.tree;
    const size_t start_exp_size = self->ir_exp_build_space.size;

    child.unknown = SYNTAX_TREE_NODE_BY_IND(tree_base, AST_PAR_NODE_1_CHILD(node));

    if (child.header->type == SYNTAX_TREE_EXPR_INDEX)
    {
        res = ir_builder_process_exp_ind_routine(self,
                                                child,
                                                &arr_type,
                                                &my_dim);

        if (res != IR_BUILDER_SUCCESS)
            return res;

        perfom_addition = 1;
    }
    else
    {
        res = ir_builder_process_l_exp(self, child, &arr_type);

        if (res != IR_BUILDER_SUCCESS)
            return res;

        if (arr_type.header->entry_type != TMP_NAME_ARRAY_TYPE)
        {
            ir_builder_gen_err_simple(self,
                                  ast_node_get_location(child),
                                  "expression is not an array");
            self->ir_exp_build_space.size = start_exp_size;
            return IR_BUILDER_SEM_ERROR;
        }

        my_dim = 0;
        perfom_addition = 0;
    }

    child.unknown = SYNTAX_TREE_NODE_BY_IND(tree_base, AST_PAR_NODE_2_CHILD(node));
    res = ir_builder_process_exp(self, child, &braces_type);

    if (res != IR_BUILDER_SUCCESS)
    {
        self->ir_exp_build_space.size = start_exp_size;
        return res;
    }

    // semantics checks
    if (braces_type.header->entry_type != TMP_NAME_BASIC_TYPE)
    {
        ir_builder_gen_err_simple(self,
                                  ast_node_get_location(child),
                                  "expression cannot be used as array index");
        self->ir_exp_build_space.size = start_exp_size;
        return IR_BUILDER_SEM_ERROR;
    }

    if (my_dim >= arr_type.array->dimensions_num)
    {
        ir_builder_gen_err_simple(self,
                                  ast_node_get_location(child),
                                  "addressement of a dimension exceeding" \
                                  "the array dimensionality");
        self->ir_exp_build_space.size = start_exp_size;
        return IR_BUILDER_SEM_ERROR;
    }

    *continue_type = arr_type;
    *continue_dim = my_dim + 1;
    return ir_builder_exp_multiply_by_const_ptr(self,
                                                braces_type.basic->basic_type,
                                                arr_type.array->dim_sizes[my_dim],
                                                perfom_addition);
}

static enum ir_builder_retcode
ir_builder_process_l_exp(
        struct ir_builder *const self,
        const union ast_node_ptr node,
        union tmp_name_tbl_type_ptr *const continue_type)
{    
    size_t tmp;
    union ir_exp_tree_node_ptr exp_ptr;
    struct tmp_name_tbl_entr *entry;
    size_t parameter;
    union tmp_name_tbl_type_ptr type;
    union tmp_name_tbl_type_ptr type_second;
    enum ir_builder_retcode res;
    uint64_t tmp_64; 
    union ast_node_ptr child;
    char *tmp_ptr;

    switch (node.header->type)
    {
        case SYNTAX_TREE_EXPR_BINOP_ASSIGN:
            tmp_ptr = self->tree.tree;
            child.unknown = SYNTAX_TREE_NODE_BY_IND(tmp_ptr, AST_NODE_1_CHILD(node));
            res = ir_builder_process_l_exp(self, child, &type);

            if (res != IR_BUILDER_SUCCESS)
                return res;

            child.unknown = SYNTAX_TREE_NODE_BY_IND(tmp_ptr, AST_NODE_2_CHILD(node));
            res = ir_builder_process_exp(self, child, &type_second);

            if (res != IR_BUILDER_SUCCESS)
                return res;

            if (chunk_extend_to_fit(&self->ir_exp_build_space,
                                    sizeof(struct ir_exp_tree_op_node))
                == ERROR)
                return IR_BUILDER_ERROR;

            exp_ptr.unknown = self->ir_exp_build_space.start
                              + self->ir_exp_build_space.size;
            exp_ptr.header->type = IR_EXP_BINOP_WRITE;
            exp_ptr.header->op_base_type = type_second.header->entry_type;
            self->ir_exp_build_space.size += sizeof(struct ir_exp_tree_op_node);

        case SYNTAX_TREE_EXPR_PLACE:
            parameter = AST_PAR_NODE_PARAMETER(node).ind;

            if (names_map_stack_locate_name(&self->names_map_stack, parameter, &tmp)
                == NAME_NOT_FOUND)
            {
                ir_builder_gen_err_name_notfound(self,
                                                 AST_PAR_NODE_LEAF_LOC(node),
                                                 parameter);
                return IR_BUILDER_SEM_ERROR;
            }

            entry = (struct tmp_name_tbl_entr*)(self->tmp_name_table.start + tmp);

            if (chunk_extend_to_fit(&self->ir_exp_build_space,
                                    sizeof(struct ir_exp_tree_label_node))
                == ERROR)
                return IR_BUILDER_ERROR;

            exp_ptr.unknown = self->ir_exp_build_space.start
                              + self->ir_exp_build_space.size; 
            exp_ptr.header->type = IR_EXP_LEAF_LABEL;
            exp_ptr.header->op_base_type = self->max_machine_word_type;
            exp_ptr.label->val = entry->ind;

            self->ir_exp_build_space.size += sizeof(struct ir_exp_tree_label_node);
            continue_type->unknown = entry->data;
            return IR_BUILDER_SUCCESS; 

        case SYNTAX_TREE_EXPR_INDEX:
            res = ir_builder_process_exp_ind_routine(self, node, &type, &tmp_64);

            if (res != IR_BUILDER_SUCCESS)
                return res;

            *continue_type = type;
            return IR_BUILDER_SUCCESS; 
           
        default:
            ir_builder_gen_err_simple(self,
                                      ast_node_get_location(node),
                                      "expression is not correct lvalue");
            return IR_BUILDER_SEM_ERROR;

    }
}
*/

static default_retcode
ir_builder_build_cfg_nodes(
        struct ir_builder *const self,
        size_t cur_pump_size,
        size_t *children_start_ptr,
        size_t *const children_end_ptr)
{
    union ast_node_ptr node;
    union ast_node_ptr tmp_node;
    struct cfg_node *cur_cfg_node;
    size_t cur_node_ind;
    size_t *tmp_ind_ptr;
    size_t tmp;
    size_t counter;
    size_t offset;
    char *cfg_base;
    struct ast_node_location *loc;

    char *const tree_base = self->tree.tree;

    cfg_base = self->cfg_builder.nodes_pool.start;

    for (;children_start_ptr < children_end_ptr; children_start_ptr++)
    {
        cur_node_ind = self->cfg_builder.nodes_pool.size;
        node.unknown = SYNTAX_TREE_NODE_BY_IND(tree_base, *children_start_ptr);

        switch (node.header->type)
        {
            case SYNTAX_TREE_STATEMENT_DEFINE:
                /*
                last_name_table_ind = self->cur_table.size;

                if (ir_builder_process_define(self, node, last_name_table_ind)
                    == IR_BUILDER_ERROR)
                    return IR_BUILDER_ERROR;

                */

                continue;

            case SYNTAX_TREE_STATEMENT_DEFINEASSIGN: 
                loc = AST_PAR_NODE_2_CHILD_LOC(node);
                // add next flow node
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_pump_node(&self->cfg_builder, cur_node_ind)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  cur_node_ind,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  0)
                       == ERROR)
                    return ERROR;
                break;

            case SYNTAX_TREE_STATEMENT_IF:
                loc = AST_NODE_2_CHILD_LOC(node);
                // add node with 'if' expression
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_pump_node(&self->cfg_builder, cur_node_ind)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  cur_node_ind,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  cur_node_ind + sizeof(struct cfg_node))
                       == ERROR)
                    return ERROR;

                tmp_ind_ptr = &AST_NODE_2_CHILD(node);

                if (ir_builder_build_cfg_nodes(self,
                                               cur_pump_size + sizeof(size_t),
                                               tmp_ind_ptr,
                                               tmp_ind_ptr + 1)
                    == ERROR)
                    return ERROR;
                break;

            case SYNTAX_TREE_STATEMENT_IF_ELSE:
                loc = AST_NODE_3_CHILD_LOC(node);
                // add node with 'if' expression
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_add_node(&self->cfg_builder,
                                               cur_node_ind,
                                               loc->line_num,
                                               loc->column_num,
                                               0,
                                               cur_node_ind + sizeof(struct cfg_node))
                    == ERROR)
                    return ERROR;

                tmp_ind_ptr = &AST_NODE_2_CHILD(node);

                if (ir_builder_build_cfg_nodes(self,
                                               cur_pump_size,
                                               tmp_ind_ptr,
                                               tmp_ind_ptr + 1)
                    == ERROR)
                    return ERROR;
 
                cfg_base = self->cfg_builder.nodes_pool.start;
                cur_cfg_node = (struct cfg_node*)(cfg_base + cur_node_ind);
                cur_cfg_node->child_1 = self->cfg_builder.nodes_pool.size;
                tmp_ind_ptr = &AST_NODE_3_CHILD(node);

                if (ir_builder_build_cfg_nodes(self,
                                               self->cfg_builder.drain_stack.size,
                                               tmp_ind_ptr,
                                               tmp_ind_ptr + 1)
                    == ERROR)
                    return ERROR;

                break;

            case SYNTAX_TREE_STATEMENT_WHILE:
                loc = AST_NODE_N_CHILD_LOC(node, AST_NODE_N_CHILD_NUM(node));
                // add node with 'while' expression
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_pump_node(&self->cfg_builder, cur_node_ind)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  cur_node_ind,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  cur_node_ind + sizeof(struct cfg_node))
                       == ERROR
                    || cfg_nodes_builder_loop_stack_append(&self->cfg_builder,
                                                           cur_node_ind)
                        == ERROR)
                    return ERROR;

                tmp_ind_ptr = AST_NODE_N_CHILD_ARR(node);

                if (ir_builder_build_cfg_nodes(self,
                                               cur_pump_size + sizeof(size_t),
                                               tmp_ind_ptr + 1,
                                               tmp_ind_ptr + AST_NODE_N_CHILD_NUM(node))
                    == ERROR)
                    return ERROR;

                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size + sizeof(size_t),
                                              cur_node_ind);

                break;

            case SYNTAX_TREE_STATEMENT_UNTIL:
                break;

            case SYNTAX_TREE_STATEMENT_REPEAT_WHILE:
                loc = AST_NODE_2_CHILD_LOC(node);
                tmp_ind_ptr = &AST_NODE_1_CHILD(node);

                if (ir_builder_build_cfg_nodes(self,
                                               cur_pump_size,
                                               tmp_ind_ptr,
                                               tmp_ind_ptr + 1) 
                    == ERROR)
                    return ERROR;

                tmp = self->cfg_builder.nodes_pool.size;
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              tmp);

                if (cfg_nodes_builder_pump_node(&self->cfg_builder, tmp)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  tmp,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  cur_node_ind)
                       == ERROR)
                    return ERROR; 
                break;

            case SYNTAX_TREE_STATEMENT_REPEAT_UNTIL:
                break;

            case SYNTAX_TREE_STATEMENT_BREAK:
                loc = AST_NODE_LEAF_LOC(node);

                if (cfg_nodes_builder_loop_stack_pop(&self->cfg_builder, &tmp)
                    == CFG_NODES_BREAK_NOT_FOUND)
                {
                    ir_builder_gen_err_simple(self,
                                              ast_node_get_location(node),
                                              "'break' do not match any loop");
                    continue;
                }

                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              tmp);
                return SUCCESS;

            case SYNTAX_TREE_STATEMENT_EXP:
                loc = AST_NODE_1_CHILD_LOC(node);
                // add next flow node
                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_pump_node(&self->cfg_builder, cur_node_ind)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  cur_node_ind,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  0)
                       == ERROR)
                    return ERROR;
                break;


                break;

            case SYNTAX_TREE_STATEMENT_BLOCK: 
                if (names_map_stack_enter_scope(&self->names_map_stack) == ERROR)
                    return ERROR;

                // walk the block and find all function definitions
                counter = 0;
                offset = self->callable_tmp_name_table_write.size;
                tmp_ind_ptr = AST_NODE_N_CHILD_ARR(node);
                tmp  = AST_NODE_N_CHILD_NUM(node);

                for (size_t i = 0; i < tmp; i++)
                {
                    node.unknown = tree_base + tmp_ind_ptr[i];

                    if (node.header->type == SYNTAX_TREE_FUNC_DEF)
                    {
                        counter++;
                        tmp_node.unknown = tree_base + AST_NODE_N_CHILD_ARR(node)[0];
                        
                        if (ir_builder_def_anon_callable(self, tmp_node, node)
                            == IR_BUILDER_ERROR)
                            return ERROR;
                    }
                }

                if (counter > 0
                    && tmp_name_tbl_callable_add_pack(&self->callable_tmp_name_table_write,
                                                      offset,
                                                      counter)
                    == ERROR)
                    return ERROR;

                // walk block again normally

                if (ir_builder_build_cfg_nodes(self,
                                               cur_pump_size,
                                               tmp_ind_ptr,
                                               tmp_ind_ptr + tmp) 
                    == ERROR)
                    return ERROR;

                names_map_stack_leave_scope(&self->names_map_stack);
                break;

            case SYNTAX_TREE_STATEMENT_RETURN:
                return cfg_nodes_builder_pump_ret_nodes(&self->cfg_builder, cur_pump_size);

            case SYNTAX_TREE_STATEMENT_RETURN_EXP:
                loc = AST_NODE_1_CHILD_LOC(node);

                cfg_nodes_builder_drain_nodes(&self->cfg_builder,
                                              cfg_base,
                                              cur_pump_size,
                                              cur_node_ind);

                if (cfg_nodes_builder_pump_ret_node(&self->cfg_builder, cur_node_ind)
                    == ERROR
                    || cfg_nodes_builder_add_node(&self->cfg_builder,
                                                  cur_node_ind,
                                                  loc->line_num,
                                                  loc->column_num,
                                                  0,
                                                  0)
                       == ERROR)
                    return ERROR;
 


        }
    }

    return SUCCESS;
}

static default_retcode
ir_builder_process_funcdef(
        struct ir_builder *const self,
        struct tmp_name_tbl_callable_entr *const callable_entr)
{
    union tmp_name_tbl_type_ptr func_type_ptr;
    union tmp_name_tbl_type_ptr arg_type_ptr;
    struct tmp_name_tbl_type_entr_subfield *arg_sub_field;
    struct ir_sourceitems_table_entry *src_entr;
    size_t args;

    size_t *const statements_ind_arr = callable_entr->statements_ind_arr;
    const size_t statements_num = callable_entr->statements_num;
  
    if (names_map_stack_enter_scope(&self->names_map_stack) == ERROR)
        return ERROR;

    func_type_ptr.unknown = callable_entr->data;
    args = func_type_ptr.callable->args_num;

    for (size_t i = 0; i < args; i++)
    {
        arg_sub_field = &func_type_ptr.callable->data[i];
        arg_type_ptr.unknown = func_type_ptr.unknown + arg_sub_field->type_offset;

        if (ir_builder_add_annotated_ready(self,
                                           arg_sub_field->str_ind,
                                           arg_sub_field->field_size,
                                           arg_type_ptr)
            == ERROR)
            return ERROR;
    }

    if (ir_builder_build_cfg_nodes(self,
                                   0,
                                   statements_ind_arr,
                                   statements_ind_arr + statements_num)
        == ERROR)
        return ERROR;

    src_entr = (struct ir_sourceitems_table_entry*)
               (self->sourceitems_table.start
                + func_type_ptr.callable->sourceitems_tbl_ind);

    if (cfg_nodes_builder_finish(&self->cfg_builder, &src_entr->cfg_nodes) == ERROR
        || chunk_move_reinit(&self->cur_table,
                             &src_entr->name_table,
                             IR_BUILDER_NAME_TABLE_PREALLOC_BYTES)
            == ERROR)
        return ERROR;

    names_map_stack_leave_scope(&self->names_map_stack);
    return SUCCESS;
}

static default_retcode
ir_builder_process_ast(struct ir_builder *const self)
{
    size_t *child_arr;
    size_t child_num;
    union ast_node_ptr node;
    union ast_node_ptr tmp_node;
    struct extendable_chunk tmp;
    struct callable_tmp_name_table_postfix pack;
    size_t read_tbl_size;
    struct tmp_name_tbl_callable_entr *callable_entry;
    const char *read_tbl_start;
    // top node is always source node 
    char *const ast_start = self->tree.tree;

    node.unknown = ast_start + self->tree.top_ind;
    child_num = AST_NODE_N_CHILD_NUM(node);
    child_arr = AST_NODE_N_CHILD_ARR(node);
 
    for (size_t i = 0; i < child_num; i++)
    {
        //func def node
        node.unknown = ast_start + child_arr[i];
        tmp_node.unknown = ast_start + AST_NODE_N_CHILD_ARR(node)[0];
                        
        if (ir_builder_def_named_callable(self, tmp_node, node) == IR_BUILDER_ERROR)
            return ERROR;
    }

    if (child_num > 0
        && tmp_name_tbl_callable_add_pack(&self->callable_tmp_name_table_write,
                                          0,
                                          child_num)
        == ERROR)
        return ERROR;

    while (self->callable_tmp_name_table_write.size != 0)
    {
        // swap tbls
        tmp = self->callable_tmp_name_table_write;
        self->callable_tmp_name_table_write = self->callable_tmp_name_table_read;
        self->callable_tmp_name_table_read = tmp;

        read_tbl_start = self->callable_tmp_name_table_read.start;
        read_tbl_size = self->callable_tmp_name_table_read.size;
        self->callable_tmp_name_table_read.size = 0;

        do
        {
            pack = *(struct callable_tmp_name_table_postfix*)
                    (read_tbl_start
                     + read_tbl_size
                     - sizeof(struct callable_tmp_name_table_postfix));
            read_tbl_size = pack.callables_offset;

            while (pack.objects_num--)
            {
                callable_entry = (struct tmp_name_tbl_callable_entr*)
                                 (read_tbl_start + pack.callables_offset);

                if (ir_builder_process_funcdef(self, callable_entry) == ERROR)
                    return ERROR;

                pack.callables_offset += ((struct tmp_name_tbl_type_entr_callable*)
                                         (callable_entry->data))->next_type_offset
                                         + sizeof(struct tmp_name_tbl_callable_entr);
            }
        }
        while(read_tbl_size);
    }

    return SUCCESS;
}

//---------------------------------- ir public funcs -------------------------------------

enum ir_init_retcode
ir_init(struct ir *const self, const struct syntax_tree *const tree)
{
    struct ir_builder builder;

    if (ir_builder_init(&builder, CFG_BASIC_TYPE_U64, tree) == ERROR)
        return IR_INIT_ERROR;

    if (builder.is_broken)
    {
        ir_builder_deinit(&builder);
        return IR_INIT_SEMANTIC_ERRORS;
    }

    ir_builder_finish(&builder, self);
    return IR_INIT_SUCCESS; 
}

void
ir_deinit(struct ir *const self)
{
    struct ir_sourceitems_table_ind_iter tbl_iter;

    for (ir_sourceitems_table_ind_iter_init(&tbl_iter, &self->global_sym_table);
         ir_sourceitems_table_ind_is_valid(&tbl_iter);
         ir_sourceitems_table_ind_iter_next(&tbl_iter))
    {
        chunk_deinit(&tbl_iter.e.entry->cfg_nodes);
        chunk_deinit(&tbl_iter.e.entry->name_table);
    }

    chunk_deinit(&self->global_sym_table);
    return;
}

//---------------------------------- ir dumping stuff ------------------------------------

default_retcode
ir_dump(const struct ir *const self, FILE *f)
{
    struct ir_sourceitems_table_ind_iter tbl_iter;
    size_t cfg_ind;
    size_t cfg_size;
    char *cfg_base;
    struct cfg_node *c_node;

    for (ir_sourceitems_table_ind_iter_init(&tbl_iter, &self->global_sym_table);
         ir_sourceitems_table_ind_is_valid(&tbl_iter);
         ir_sourceitems_table_ind_iter_next(&tbl_iter))
    {
        fprintf(f, "CALLABLE ID\t%ld\n", tbl_iter.cur_tbl_ind);

        if (tbl_iter.e.entry->name_size > 0)
            fprintf(f, "TYPE:\t\tvisible\nSYM_NAME:\t%s\n", tbl_iter.e.entry->data);
        else
            fprintf(f, "TYPE:\t\tanonimous\n");

        cfg_ind = sizeof(struct cfg_node);
        cfg_base = tbl_iter.e.entry->cfg_nodes.start;
        cfg_size = tbl_iter.e.entry->cfg_nodes.size - sizeof(struct cfg_node);

        fprintf(f,
                "cfg dot dump:\n\tdigraph CFG {\n"
                "\t0\t[label=\"START\"];\n\t\t0\t->\t%ld;\n\n"
                "\t%ld\t[label=\"END\"];\n\n",
                cfg_ind,
                cfg_size);


        for (;cfg_ind < cfg_size; cfg_ind += sizeof(struct cfg_node))
        {
            c_node = (struct cfg_node*) (cfg_base + cfg_ind);

            if (c_node->child_2)
            {
                fprintf(f,
                        "\t%ld\t[label=\"%d, %d\" shape=rect];\n"
                        "\t%ld\t->\t%ld\t[label=\"true\"];\n"
                        "\t%ld\t->\t%ld\t[label=\"false\"];\n\n",
                        cfg_ind,
                        c_node->line,
                        c_node->column,
                        cfg_ind,
                        c_node->child_2,
                        cfg_ind,
                        c_node->child_1);
                    // no debug
            }
            else
            {
                fprintf(f,
                        "\t%ld\t[label=\"%d, %d\" shape=rect];\n"
                        "\t%ld\t->\t%ld;\n\n",
                        cfg_ind,
                        c_node->line,
                        c_node->column,
                        cfg_ind,
                        c_node->child_1);
                    // not debug
            } 
       }

        fprintf(f, "\t}\n\n");
    }

    return SUCCESS;
}
