%{
    #include "lexer.h"
	#include "lang/syntax_tree.h"
	#include "data_structs/string_map.h"

	#define YYERROR_VERBOSE 1

    #define CHECK_ERROR(x)           \
		do 							 \
			switch((x)) 			 \
			{ 						 \
				case ERROR:  		 \
					{YYABORT;} 	  	 \
				case SUCCESS: 		 \
					break;			 \
			} 						 \
		while(0)

	#ifdef YYDEBUG
  		int yydebug = 1;
	#endif

    void yyerror(const char *msg);

    extern struct ast_builder bison_ast_builder;
%}

%locations

%union
{
    size_t size;
}

%token OF
%token ARRAY
%token BEG
%token END
%token BREAK
%token WHILE
%token UNTIL
%token ELSE
%token IF
%token THEN
%token DEF
%token DOTS
%token RETURN

%token AND
%token OR
%token NOT
%token EQUAL
%token NOT_EQUAL
%token LT_EQUAL
%token GT_EQUAL

%token FALSE
%token TRUE
%token <size> ID
%token <size> STR
%token <size> CHAR
%token <size> NUMBER
%token <size> NUMBER_BIG
%token <size> NUMBER_OVERFLOW

%token TYPE_BOOL
%token TYPE_BYTE
%token TYPE_UBYTE
%token TYPE_SHORT
%token TYPE_USHORT
%token TYPE_INT
%token TYPE_UINT
%token TYPE_LONG
%token TYPE_ULONG
%token TYPE_HUGE
%token TYPE_UHUGE
%token TYPE_CHAR
%token TYPE_STRING


%precedence NOT
%left OR
%left AND
%right '='
%precedence EQUAL LT_EQUAL GT_EQUAL '<' '>'
%left '+' '-'
%left '*' '/'
%precedence UMINUS

%precedence WHILE
%precedence UNTIL

/* dangling else solution */
%precedence THEN
%precedence ELSE

%type <size> error
%type <size> sourceitem
%type <size> sourceitem_list
%type <size> func_def
%type <size> func_signature
%type <size> arg_list
%type <size> statement
%type <size> statement_list
%type <size> stat_or_srcitem_list
%type <size> expr_list

%destructor { ast_builder_remove_node(&bison_ast_builder); }
                sourceitem
                func_def
                func_signature 
				arg
			    statement
				stat_or_srcitem
				expr
				literal
				of_type_ref
				type_ref

%destructor { 
			    for (size_t i = 0; i < $$; i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
			    stat_or_srcitem_list
                sourceitem_list
                statement_list
                arg_list
                expr_list

%%
source : sourceitem_list
           {
               CHECK_ERROR(ast_builder_new_node_N_child(
                   &bison_ast_builder,
                   SYNTAX_TREE_SOURCE,
                   $1));
           }
       ;

sourceitem_list : sourceitem_list sourceitem { $$ = $1 + 1; }
				| %empty                     { $$ = 0;      }
				;

sourceitem : func_def ;

func_def : DEF func_signature statement_list END
             {
                 CHECK_ERROR(ast_builder_new_node_N_child(
                     &bison_ast_builder,
                     SYNTAX_TREE_FUNC_DEF,
                     $3 + 1));
             }
         ;


func_signature : ID '(' arg_list ')' of_type_ref
                   {
                       CHECK_ERROR(ast_builder_new_par_node_N_child(
                           &bison_ast_builder,
                           SYNTAX_TREE_FUNC_TYPED_SIGN,
                           (union ast_node_param) $1,
                           $3 + 1));
                   }
               | ID '(' arg_list ')'
                   {
					   
                       CHECK_ERROR(ast_builder_new_par_node_N_child(
                           &bison_ast_builder,
                           SYNTAX_TREE_FUNC_UNTYPED_SIGN,
                           (union ast_node_param) $1,
                           $3));
				   }
			   ;

arg_list : arg_list ',' arg { $$ = $1 + 1; }
		 | arg              { $$ = 1;      }   
		 | %empty		    { $$ = 0;      }
		 ;

arg : ID of_type_ref
	    {
            CHECK_ERROR(ast_builder_new_par_node_1_child(
                &bison_ast_builder,
                SYNTAX_TREE_FUNC_TYPED_ARG,
                (union ast_node_param) $1));
        }
    | ID
	    {
		    CHECK_ERROR(ast_builder_new_par_node_leaf(
                &bison_ast_builder,
                SYNTAX_TREE_FUNC_UNTYPED_ARG,
                (union ast_node_param) $1));
        }
	;

statement_list : statement_list statement { $$ = $1 + $2; }
			   | %empty                   { $$ = 0;       }
			   ;


statement	: error ';' { $$ = 0; }
			| ID of_type_ref ';'
				{ 
                    CHECK_ERROR(ast_builder_new_par_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_DEFINE,
                        (union ast_node_param) $1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
				}
			| ID of_type_ref '=' expr ';'
			    { 
                    CHECK_ERROR(ast_builder_new_par_node_2_child(
                        &bison_ast_builder,
                         SYNTAX_TREE_STATEMENT_DEFINEASSIGN,
                        (union ast_node_param) $1)); 

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
            | statement WHILE expr ';'
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_REPEAT_WHILE));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
            | statement UNTIL expr ';'
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_REPEAT_UNTIL));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
            | BREAK ';'
                {
                    CHECK_ERROR(ast_builder_new_node_leaf(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BREAK));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
		    | expr ';'
                {
                    CHECK_ERROR(ast_builder_new_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_EXP));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
		    | RETURN ';'
                {
                    CHECK_ERROR(ast_builder_new_node_leaf(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_RETURN));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }	
		    | RETURN error ';' { $$ = 0; }	
		    | RETURN expr ';'
                {
                    CHECK_ERROR(ast_builder_new_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_RETURN_EXP));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
			| WHILE error END { $$ = 0; }
            | WHILE expr statement_list END
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_WHILE,
                        $3 + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
			| statement WHILE error END { $$ = $1; }
            | statement WHILE expr statement_list END
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_WHILE,
                        $4 + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = $1 + 1;
                }
			| UNTIL error END { $$ = 0; }
            | UNTIL expr statement_list END
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_UNTIL,
                        $3 + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
			| statement UNTIL error END { $$ = $1; }
            | statement UNTIL expr statement_list END
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_UNTIL,
                        $4 + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = $1 + 1;
                }
			| IF expr THEN error ELSE { $$ = 0; }
            | IF expr THEN statement ELSE statement
                {
                    CHECK_ERROR(ast_builder_new_node_3_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_IF_ELSE));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
			| IF error THEN { $$ = 0; }
            | IF expr THEN statement
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_IF));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
		    | '{' stat_or_srcitem_list '}'
			    {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BLOCK,
                        $2));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
            | '{' error '}' { $$ = 0; }
		    | BEG stat_or_srcitem_list END
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BLOCK,
                        $2));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        @$.first_line,
                        @$.first_column));

                    $$ = 1;
                }
            | BEG error END { $$ = 0; }
            ;

stat_or_srcitem_list : stat_or_srcitem_list stat_or_srcitem { $$ = $1 + 1; }
					 | %empty                               { $$ = 0;      }
                     ;

stat_or_srcitem : statement
				| sourceitem
			    ;


expr : expr '=' expr
	 	 {
			CHECK_ERROR(ast_builder_new_node_2_child(
				&bison_ast_builder,
				SYNTAX_TREE_EXPR_BINOP_ASSIGN));
	 	 }
	 | expr '+' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_PLUS));
         }
	 | expr '-' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_MINUS));
         }
     | expr '*' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_MUL));
         }
     | expr '/' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_DIV));
         }
     | expr AND expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_AND));
         }
     | expr OR expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_OR));
         }
     | expr EQUAL expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_EQUAL));
         }
     | expr NOT_EQUAL expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL));
         } 
     | expr '<' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_LESS));
         }
     | expr '>' expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_GREATER));
         }
     | expr LT_EQUAL expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL));
         }
     | expr GT_EQUAL expr
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL));
         }
	 | NOT expr
         {
             CHECK_ERROR(ast_builder_new_node_1_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_UNOP_NOT));
         }
	 | '-' expr %prec UMINUS
         {
             CHECK_ERROR(ast_builder_new_node_1_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_UNOP_MINUS));
         }
	 | '(' expr ')'
	 | expr '(' expr_list ')'
         {
             CHECK_ERROR(ast_builder_new_node_N_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_CALL,
                 $3 + 1));
         }
	 | expr '[' expr DOTS expr ']'
        {
             CHECK_ERROR(ast_builder_new_node_3_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_RANGE));
        }
	 | expr '[' expr ']'
        {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_INDEX));
        }
	 | ID
        {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_PLACE,
                 (union ast_node_param) $1));
	    }
     | literal
     ;

literal : TRUE
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_BOOL,
                 ((union ast_node_param) (size_t) 1)));
            }
		| FALSE
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_BOOL,
                 ((union ast_node_param) (size_t) 0)));
            }
		| STR
            { 
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_STR,
                 (union ast_node_param) $1));
            }
		| CHAR
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_CHAR,
                 (union ast_node_param) $1));
            }
		| NUMBER
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_NUM,
                 (union ast_node_param) $1));
           }
		| NUMBER_BIG
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_NUM_128,
                 (union ast_node_param) $1));
           }
		;

expr_list : expr_list ',' expr { $$ = $1 + 1; }
		  | expr               { $$ = 1;      }
		  | %empty             { $$ = 0;      }
          ;

of_type_ref : OF type_ref ;

type_ref : TYPE_BOOL
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_BOOL));
             }
         | TYPE_BYTE
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_BYTE));
             }
         | TYPE_UBYTE
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE));
             }
         | TYPE_SHORT
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_SHORT));
             }
         | TYPE_USHORT
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_USHORT));
             }
         | TYPE_INT
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_INT));
             }
         | TYPE_UINT
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UINT));
             }
         | TYPE_LONG
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_LONG));
             }
         | TYPE_ULONG
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_ULONG));
             }
         | TYPE_HUGE
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_HUGE));
             }
         | TYPE_UHUGE
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE));
             }
         | TYPE_CHAR
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_CHAR));
             }
         | TYPE_STRING
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_STRING));
             }
		 | ID
             {
                 CHECK_ERROR(ast_builder_new_par_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_CUSTOM,
                     (union ast_node_param) $1));

                CHECK_ERROR(ast_builder_save_node_pos(
                            &bison_ast_builder,
                            @$.first_line,
                            @$.first_column));

             }
		 | type_ref ARRAY '[' NUMBER ']'
             {
                 CHECK_ERROR(ast_builder_new_par_node_1_child(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_ARRAY,
                     (union ast_node_param) $4));
             }
		 | type_ref ARRAY '[' NUMBER_BIG ']'
             {
				 CHECK_ERROR(ast_builder_res_num_reinsert_128_as_64(
					 &bison_ast_builder,
                     (size_t) $4,
                     (size_t*)&$4));

   				fprintf(stderr, "** (%d, %d): array length cannot be 128 bit integer literal, \
					   truncating to 64 bit\n", @4.first_line, @4.first_column);

                 CHECK_ERROR(ast_builder_new_par_node_1_child(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_ARRAY,
                     (union ast_node_param) $4));	
             }
         ;
%%

void yyerror(const char *msg) {
   fprintf(stderr, "** (%d, %d): %s\n", yylloc.first_line, yylloc.first_column, msg);
}
