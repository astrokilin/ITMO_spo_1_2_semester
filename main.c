#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "parsing/parser.h"
#include "lang/syntax_tree.h"
#include "lang/cfg_ir.h"

struct ast_builder bison_ast_builder;

int main(int argc, char **argv)
{
    FILE *fptr;
    struct syntax_tree AST;
    struct ir IR;
    char should_print_ast = 0;
    char *ast_dump_file_path = 0;
    char should_print_ir = 0;
    char *ir_dump_file_path = 0;
    int opt;

    while ((opt = getopt (argc, argv, "a:i:")) != -1)
        switch (opt)
        {
            case 'a':
                should_print_ast = 1;
                ast_dump_file_path = optarg;
                break;

            case 'i':
                should_print_ir = 1;
                ir_dump_file_path = optarg;
                break;

            case '?':
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                break;
        }

    ast_builder_init(&bison_ast_builder);

    switch (yyparse())
    {
        case 0:
            break;

        case 1:
            ast_builder_deinit(&bison_ast_builder);
            return 1;

        case 2:
            fprintf(stderr, "internal error: %s\n", strerror(errno));
            ast_builder_deinit(&bison_ast_builder);
            return 1;
    }

    if (ast_builder_finish(&bison_ast_builder, &AST) == ERROR)
    {
        ast_builder_deinit(&bison_ast_builder);
        return 1;
    }

    // TODO: rewrite this mess
    if (should_print_ast)
    {
        if (strlen(ast_dump_file_path) == 1 && ast_dump_file_path[0] == '-')
        {
            fprintf(stderr, "ast dot dump:\n");
            syntax_tree_dump_dotfile(&AST, stderr);
        }
        else if ((fptr = fopen(ast_dump_file_path, "w")) == NULL)
        {
            fprintf(stderr, "cannot open file to dump ast\n");
            ast_builder_deinit(&bison_ast_builder);
            return 1;
        }
        else
        {
            fprintf(stderr, "ast dot dump:\n");
            syntax_tree_dump_dotfile(&AST, fptr);
            fclose(fptr);
        }
    }

    switch (ir_init(&IR, &AST)) 
    {
        case IR_INIT_ERROR:
            syntax_tree_deinit(&AST);
            return 1;

        case IR_INIT_SEMANTIC_ERRORS:
            syntax_tree_deinit(&AST);
            fprintf(stderr, "semantic_errors\n");
            return 1;

        case IR_INIT_SUCCESS:
            break;
    }

    syntax_tree_deinit(&AST);

    // TODO: rewrite this mess
    if (should_print_ir)
    {
        if (strlen(ir_dump_file_path) == 1 && ir_dump_file_path[0] == '-')
        {
            fprintf(stderr, "ir dump:\n");
            ir_dump(&IR, stderr);
        }
        else if ((fptr = fopen(ir_dump_file_path, "w")) == NULL)
        {
            ir_deinit(&IR);
            return 1;
        }
        else
        {
            fprintf(stderr, "ir dump:\n");
            ir_dump(&IR, fptr);
            fclose(fptr);
        }
    }

    ir_deinit(&IR);
    return 0;
}
