%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <string.h>

    #include "parser.h"
    #include "lang/syntax_tree.h"

	#define YY_USER_ACTION                                \
		do 							                      \
		{												  \
			if (yy_act == 1) 		                      \
			{ 						 	                  \
				yylloc.first_line   += yyleng;            \
				yylloc.last_line    += yyleng;            \
				yylloc.first_column = 0;	              \
				yylloc.last_column  = 0;	              \
			}							                  \
			else						                  \
			{							                  \
				yylloc.first_column = yylloc.last_column; \
				yylloc.last_column  += yyleng; 			  \
			}											  \
		}												  \
		while(0);

	extern struct ast_builder bison_ast_builder;
	extern void yyerror(const char *);

	inline static void    install_string(char);
	inline static size_t  install_num(void);
%}

%option noyywrap

newline		\n+
comment		#[^\n]*
ws     		[ \t]+
letter 		[A-Za-z_]
digit  		[0-9]
id     		{letter}({letter}|{digit})*
str    		\"[^\"\\]*(\\.[^\"\\]*)*\"
char   		'[^']'
hex	   		0[xX][0-9A-Fa-f]+
bits   		0[bB][01]+
dec    		{digit}+
number      {hex}|{bits}|{dec}

%%

{newline}	{/* do nothing */}
{comment}   {/* do nothing */}
{ws}        {/* do nothing */}

bool 	    { return TYPE_BOOL;   }
byte|i8     { return TYPE_BYTE;   }
ubyte|u8 	{ return TYPE_UBYTE;  }
short|i16	{ return TYPE_SHORT;  }
ushort|u16	{ return TYPE_USHORT; }
int|i32 	{ return TYPE_INT;    }
uint|u32	{ return TYPE_UINT;   }
long|i64	{ return TYPE_LONG;   }
ulong|u64 	{ return TYPE_ULONG;  }
i128        { return TYPE_HUGE;   }
u128        { return TYPE_UHUGE;  }
char 	    { return TYPE_CHAR;   }
string 	    { return TYPE_STRING; }

and		{ return AND;       }
or		{ return OR;        }
not		{ return NOT;       }
==      { return EQUAL;     }
!=      { return NOT_EQUAL; }
\<=     { return LT_EQUAL;  }
>=      { return GT_EQUAL;  }

of		{ return OF;     }
array	{ return ARRAY;  }
begin	{ return BEG;    }
end		{ return END;    }
break	{ return BREAK;  }
while	{ return WHILE;  }
until	{ return UNTIL;  }
else	{ return ELSE;   }
if		{ return IF;     }
then 	{ return THEN;   }
def		{ return DEF;    }
\.\.    { return DOTS;   }
return  { return RETURN; }


true  	 { yylval.size = 0;         return FALSE;         }
false  	 { yylval.size = 1;         return TRUE;          }

{str} 	 { install_string(1);        return STR;          }

{char} 	 { yylval.size = yytext[0]; return CHAR;          }

{number} { 							return install_num(); }

{id}     { install_string(0);       return ID;        	  }

. 	     {                          return yytext[0]; 	  }
%%

inline static void
install_string(const char trim)
{
	switch (ast_builder_add_res_str(&bison_ast_builder,
									yytext + trim,
									yyleng - trim * 2,
                                    (size_t*) &yylval))
	{
		case AST_BUILDER_ADD_RES_STR_ERROR:
			fprintf(stderr, "internal error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			break;

		case AST_BUILDER_ADD_RES_STR_NO_SPACE:
			fprintf(stderr, "cannot store: %s\n", yytext);
			exit(EXIT_FAILURE);
			break;

		default:
			break;
	}
}

inline static size_t
install_num(void)
{
	switch (ast_builder_add_res_num(&bison_ast_builder,
									yytext,
									yyleng,
                                    (size_t*) &yylval))
	{
		case AST_BUILDER_ADD_RES_NUM_ERROR:
			fprintf(stderr, "internal error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			break;

		case AST_BUILDER_ADD_RES_NUM_NO_SPACE:
			fprintf(stderr, "cannot store: %s\n", yytext);
			exit(EXIT_FAILURE);
			break;

		case AST_BUILDER_ADD_RES_NUM_TOO_BIG:
			yyerror("integer literal exceeds 128 bit type max length, \
					 truncating to 64 bit");
			return NUMBER;

		case AST_BUILDER_ADD_RES_NUM_SUCCESS_NORMAL:
			return NUMBER;

		case AST_BUILDER_ADD_RES_NUM_SUCCESS_BIG:
			return NUMBER_BIG;
	}
}


