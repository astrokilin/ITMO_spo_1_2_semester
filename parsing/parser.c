/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parsing/parse.y"

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

#line 97 "parsing/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSING_PARSER_H_INCLUDED
# define YY_YY_PARSING_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OF = 258,
    ARRAY = 259,
    BEG = 260,
    END = 261,
    BREAK = 262,
    WHILE = 263,
    UNTIL = 264,
    ELSE = 265,
    IF = 266,
    THEN = 267,
    DEF = 268,
    DOTS = 269,
    RETURN = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    EQUAL = 274,
    NOT_EQUAL = 275,
    LT_EQUAL = 276,
    GT_EQUAL = 277,
    FALSE = 278,
    TRUE = 279,
    ID = 280,
    STR = 281,
    CHAR = 282,
    NUMBER = 283,
    NUMBER_BIG = 284,
    NUMBER_OVERFLOW = 285,
    TYPE_BOOL = 286,
    TYPE_BYTE = 287,
    TYPE_UBYTE = 288,
    TYPE_SHORT = 289,
    TYPE_USHORT = 290,
    TYPE_INT = 291,
    TYPE_UINT = 292,
    TYPE_LONG = 293,
    TYPE_ULONG = 294,
    TYPE_HUGE = 295,
    TYPE_UHUGE = 296,
    TYPE_CHAR = 297,
    TYPE_STRING = 298,
    UMINUS = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "parsing/parse.y"

    size_t size;

#line 198 "parsing/parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSING_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   954

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,    49,    47,    54,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
      45,    44,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   140,   141,   144,   146,   156,   164,   175,
     176,   177,   180,   187,   196,   197,   201,   202,   216,   230,
     243,   256,   269,   282,   295,   296,   309,   310,   324,   325,
     339,   340,   354,   355,   369,   370,   383,   384,   397,   411,
     412,   426,   429,   430,   433,   434,   438,   444,   450,   456,
     462,   468,   474,   480,   486,   492,   498,   504,   510,   516,
     522,   528,   529,   536,   542,   548,   555,   558,   565,   572,
     579,   586,   593,   602,   603,   604,   607,   609,   615,   621,
     627,   633,   639,   645,   651,   657,   663,   669,   675,   681,
     687,   700,   707
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OF", "ARRAY", "BEG", "END", "BREAK",
  "WHILE", "UNTIL", "ELSE", "IF", "THEN", "DEF", "DOTS", "RETURN", "AND",
  "OR", "NOT", "EQUAL", "NOT_EQUAL", "LT_EQUAL", "GT_EQUAL", "FALSE",
  "TRUE", "ID", "STR", "CHAR", "NUMBER", "NUMBER_BIG", "NUMBER_OVERFLOW",
  "TYPE_BOOL", "TYPE_BYTE", "TYPE_UBYTE", "TYPE_SHORT", "TYPE_USHORT",
  "TYPE_INT", "TYPE_UINT", "TYPE_LONG", "TYPE_ULONG", "TYPE_HUGE",
  "TYPE_UHUGE", "TYPE_CHAR", "TYPE_STRING", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "'('", "')'", "','", "';'", "'{'", "'}'",
  "'['", "']'", "$accept", "source", "sourceitem_list", "sourceitem",
  "func_def", "func_signature", "arg_list", "arg", "statement_list",
  "statement", "stat_or_srcitem_list", "stat_or_srcitem", "expr",
  "literal", "expr_list", "of_type_ref", "type_ref", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    61,    60,    62,    43,    45,    42,
      47,   299,    40,    41,    44,    59,   123,   125,    91,    93
};
# endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -41,     7,    -3,   -41,    -1,   -41,   -41,   -26,   -41,    35,
     200,    29,   -24,   -41,    15,   129,   -41,    18,   456,   468,
     499,   423,   889,   -41,   -41,    29,   -41,   -41,   -41,   -41,
     889,   889,    10,    32,   639,   -41,   911,   -41,    29,    35,
     -41,    74,   165,   -41,    76,   -41,   804,    78,   804,    77,
     533,    37,   -41,   654,   804,   -35,    11,   694,    34,    70,
     511,   542,   889,   889,   889,   889,   889,   889,   889,   889,
     889,   889,   889,   889,   889,   889,   -41,   889,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,    96,   -41,   -41,   -41,   -41,   -41,    32,   -41,
     -41,   235,   -41,   270,   -41,   375,   -41,   -41,   889,   -41,
     -41,   -41,   -41,    97,   709,    99,   749,   838,   819,   853,
     804,   853,   853,   838,   853,   853,    52,    52,    11,    11,
     804,    33,   579,    48,   -41,   -41,     6,    98,   764,   -41,
     -41,   305,   -41,   -41,   340,   -41,   889,   889,   -41,    36,
     -41,   410,   -41,   -41,   -41,   804,   595,    50,    53,   -41,
     -41,   -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     3,     5,     0,    15,    11,
       0,    13,     0,    10,     0,     0,     6,     0,     0,     0,
       0,     0,     0,    68,    67,    65,    69,    70,    71,    72,
       0,     0,     0,    14,     0,    66,     0,    12,     8,     0,
      16,     0,     0,    21,     0,    65,    15,     0,    15,     0,
       0,     0,    23,     0,    59,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,    22,     0,    90,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    76,     7,     9,    41,    40,    45,    44,    42,
      26,     0,    30,     0,    36,     0,    24,    25,     0,    17,
      61,    39,    38,     0,    15,     0,    15,    51,    52,    53,
      54,    57,    58,    46,    55,    56,    47,    48,    49,    50,
      74,     0,     0,     0,    27,    31,     0,    37,     0,    28,
      19,     0,    32,    20,     0,    62,     0,     0,    64,     0,
      34,     0,    18,    29,    33,    73,     0,     0,     0,    35,
      63,    91,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,   105,   -41,   -41,   -41,    72,   -40,   -37,
      81,   -41,   -18,   -41,   -41,   -11,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    97,     6,     8,    12,    13,    10,    33,
      42,    99,    34,    35,   131,    37,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    48,    50,    53,    54,    98,   101,     3,   103,   108,
       4,    58,    56,    57,    55,   -43,   150,   -43,   -43,   -43,
     109,   -43,    98,   -43,     7,   -43,     9,    93,   -43,    38,
      39,    65,    36,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
      60,    61,   114,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   -43,   132,
      11,    40,   -43,    75,   157,   158,   -43,   -43,   137,    77,
      40,    14,    65,    43,   141,    15,   144,    17,    18,    19,
      95,    20,   100,     4,   102,    21,   145,   146,    22,   104,
     138,   111,   106,    23,    24,    25,    26,    27,    28,    29,
     133,    73,    74,   139,    75,   142,   149,     5,   151,   161,
      77,    94,   162,    59,   159,     0,     0,     0,    30,     0,
       0,     0,    31,     0,     0,     0,    32,   112,   155,   156,
      41,     0,     0,     0,   -43,   -43,   -43,   -43,   -43,     0,
     -43,     0,   -43,     0,   -43,     0,     0,   -43,     0,     0,
       0,     0,   -43,   -43,   -43,   -43,   -43,   -43,   -43,     0,
       0,     0,     0,     0,     0,     0,    14,     0,     0,     0,
      15,    96,    17,    18,    19,     0,    20,   -43,     4,     0,
      21,   -43,     0,    22,     0,   -43,     0,     0,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,    16,    17,    18,    19,
       0,    20,     0,    30,     0,    21,     0,    31,    22,     0,
       0,    32,     0,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,    14,     0,     0,     0,
      15,   134,    17,    18,    19,     0,    20,     0,    30,     0,
      21,     0,    31,    22,     0,     0,    32,     0,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,   135,    17,    18,    19,
       0,    20,     0,    30,     0,    21,     0,    31,    22,     0,
       0,    32,     0,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,    14,     0,     0,     0,
      15,   153,    17,    18,    19,     0,    20,     0,    30,     0,
      21,     0,    31,    22,     0,     0,    32,     0,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,   154,    17,    18,    19,
       0,    20,     0,    30,     0,    21,     0,    31,    22,     0,
       0,    32,     0,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,   136,     0,     0,     0,
      15,     0,    17,    18,    19,     0,    20,     0,    30,     0,
      21,     0,    31,    22,     0,     0,    32,     0,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,     0,    17,    18,    19,
       0,    20,     0,    30,    51,    21,     0,    31,    22,     0,
       0,    32,     0,    23,    24,    25,    26,    27,    28,    29,
       0,    22,     0,     0,     0,     0,    23,    24,    45,    26,
      27,    28,    29,     0,     0,     0,     0,    44,    30,     0,
       0,     0,    31,     0,     0,     0,    32,     0,     0,    47,
       0,    30,     0,     0,    22,    31,     0,     0,    52,    23,
      24,    45,    26,    27,    28,    29,    22,     0,     0,     0,
       0,    23,    24,    45,    26,    27,    28,    29,     0,     0,
      49,     0,     0,     0,    30,     0,     0,     0,    31,     0,
       0,     0,   113,     0,     0,     0,    30,    22,     0,     0,
      31,     0,    23,    24,    45,    26,    27,    28,    29,    22,
       0,     0,     0,     0,    23,    24,    45,    26,    27,    28,
      29,     0,     0,   115,     0,   105,     0,    30,     0,    62,
      63,    31,    64,    65,    66,    67,     0,     0,     0,    30,
      22,     0,     0,    31,     0,    23,    24,    45,    26,    27,
      28,    29,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,    74,     0,    75,     0,     0,     0,     0,
      30,    77,     0,   147,    31,    62,    63,     0,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,    63,     0,    64,    65,    66,    67,     0,     0,
       0,     0,     0,    68,    69,    70,    71,    72,    73,    74,
       0,    75,     0,     0,     0,     0,     0,    77,   148,    68,
      69,    70,    71,    72,    73,    74,     0,    75,     0,     0,
       0,     0,     0,    77,   160,    62,    63,     0,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
      62,    63,     0,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,    68,    69,    70,    71,    72,    73,    74,
       0,    75,     0,     0,    76,     0,     0,    77,    68,    69,
      70,    71,    72,    73,    74,     0,    75,     0,     0,   107,
      62,    63,    77,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,     0,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,    68,    69,
      70,    71,    72,    73,    74,     0,    75,   110,     0,     0,
       0,     0,    77,    68,    69,    70,    71,    72,    73,    74,
       0,    75,     0,     0,   140,    62,    63,    77,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
      62,    63,     0,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,    68,    69,    70,    71,    72,    73,    74,
       0,    75,     0,     0,   143,     0,     0,    77,    68,    69,
      70,    71,    72,    73,    74,     0,    75,     0,     0,   152,
      62,    63,    77,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,     0,    64,    65,
      66,    67,     0,     0,     0,     0,     0,     0,    68,    69,
      70,    71,    72,    73,    74,     0,    75,    64,    65,    66,
      67,     0,    77,    68,    69,    70,    71,    72,    73,    74,
       0,    75,    64,    65,    66,    67,     0,    77,     0,     0,
       0,     0,    68,    69,    70,    71,    72,    73,    74,     0,
      75,     0,     0,     0,     0,     0,    77,     0,    69,    70,
      71,    72,    73,    74,     0,    75,     0,    22,     0,     0,
       0,    77,    23,    24,    45,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,    30,     0,     0,
       0,    31,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91
};

static const yytype_int16 yycheck[] =
{
      18,    19,    20,    21,    22,    42,    46,     0,    48,    44,
      13,     1,    30,    31,    25,     5,    10,     7,     8,     9,
      55,    11,    59,    13,    25,    15,    52,    38,    18,    53,
      54,    20,     3,    23,    24,    25,    26,    27,    28,    29,
       8,     9,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    48,    77,
      25,    55,    52,    52,    28,    29,    56,    57,   105,    58,
      55,     1,    20,    55,   114,     5,   116,     7,     8,     9,
       6,    11,     6,    13,     6,    15,    53,    54,    18,    12,
     108,    57,    55,    23,    24,    25,    26,    27,    28,    29,
       4,    49,    50,     6,    52,     6,    58,     2,    10,    59,
      58,    39,    59,    32,   151,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    57,   146,   147,
       1,    -1,    -1,    -1,     5,     6,     7,     8,     9,    -1,
      11,    -1,    13,    -1,    15,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
       5,     6,     7,     8,     9,    -1,    11,    48,    13,    -1,
      15,    52,    -1,    18,    -1,    56,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     5,     6,     7,     8,     9,
      -1,    11,    -1,    48,    -1,    15,    -1,    52,    18,    -1,
      -1,    56,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
       5,     6,     7,     8,     9,    -1,    11,    -1,    48,    -1,
      15,    -1,    52,    18,    -1,    -1,    56,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     5,     6,     7,     8,     9,
      -1,    11,    -1,    48,    -1,    15,    -1,    52,    18,    -1,
      -1,    56,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
       5,     6,     7,     8,     9,    -1,    11,    -1,    48,    -1,
      15,    -1,    52,    18,    -1,    -1,    56,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     5,     6,     7,     8,     9,
      -1,    11,    -1,    48,    -1,    15,    -1,    52,    18,    -1,
      -1,    56,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
       5,    -1,     7,     8,     9,    -1,    11,    -1,    48,    -1,
      15,    -1,    52,    18,    -1,    -1,    56,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     5,    -1,     7,     8,     9,
      -1,    11,    -1,    48,     1,    15,    -1,    52,    18,    -1,
      -1,    56,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    18,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,     1,    48,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,     1,
      -1,    48,    -1,    -1,    18,    52,    -1,    -1,    55,    23,
      24,    25,    26,    27,    28,    29,    18,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
       1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    48,    18,    -1,    -1,
      52,    -1,    23,    24,    25,    26,    27,    28,    29,    18,
      -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,     1,    -1,    12,    -1,    48,    -1,    16,
      17,    52,    19,    20,    21,    22,    -1,    -1,    -1,    48,
      18,    -1,    -1,    52,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    52,    -1,    -1,    -1,    -1,
      48,    58,    -1,    14,    52,    16,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,    44,
      45,    46,    47,    48,    49,    50,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    58,    59,    16,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    -1,    -1,    55,    -1,    -1,    58,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    -1,    -1,    55,
      16,    17,    58,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    -1,    -1,
      -1,    -1,    58,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    -1,    -1,    55,    16,    17,    58,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    -1,    -1,    55,    -1,    -1,    58,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    -1,    -1,    55,
      16,    17,    58,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    19,    20,    21,
      22,    -1,    58,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    19,    20,    21,    22,    -1,    58,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    45,    46,
      47,    48,    49,    50,    -1,    52,    -1,    18,    -1,    -1,
      -1,    58,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    48,    -1,    -1,
      -1,    52,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,    13,    63,    64,    25,    65,    52,
      68,    25,    66,    67,     1,     5,     6,     7,     8,     9,
      11,    15,    18,    23,    24,    25,    26,    27,    28,    29,
      48,    52,    56,    69,    72,    73,     3,    75,    53,    54,
      55,     1,    70,    55,     1,    25,    72,     1,    72,     1,
      72,     1,    55,    72,    72,    75,    72,    72,     1,    70,
       8,     9,    16,    17,    19,    20,    21,    22,    44,    45,
      46,    47,    48,    49,    50,    52,    55,    58,    25,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    76,    75,    67,     6,     6,    63,    69,    71,
       6,    68,     6,    68,    12,    12,    55,    55,    44,    55,
      53,    57,    57,     1,    72,     1,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    74,    72,     4,     6,     6,     1,    69,    72,     6,
      55,    68,     6,    55,    68,    53,    54,    14,    59,    58,
      10,    10,    55,     6,     6,    72,    72,    28,    29,    69,
      59,    59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    64,    65,    65,    66,
      66,    66,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    74,    74,    74,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     4,     5,     4,     3,
       1,     0,     2,     1,     2,     0,     2,     3,     5,     4,
       4,     2,     2,     2,     3,     3,     3,     4,     4,     5,
       3,     4,     4,     5,     5,     6,     3,     4,     3,     3,
       3,     3,     2,     0,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     6,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 62: /* sourceitem_list  */
#line 120 "parsing/parse.y"
            { 
			    for (size_t i = 0; i < ((*yyvaluep).size); i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
#line 1475 "parsing/parser.c"
        break;

    case 63: /* sourceitem  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1481 "parsing/parser.c"
        break;

    case 64: /* func_def  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1487 "parsing/parser.c"
        break;

    case 65: /* func_signature  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1493 "parsing/parser.c"
        break;

    case 66: /* arg_list  */
#line 120 "parsing/parse.y"
            { 
			    for (size_t i = 0; i < ((*yyvaluep).size); i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
#line 1502 "parsing/parser.c"
        break;

    case 67: /* arg  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1508 "parsing/parser.c"
        break;

    case 68: /* statement_list  */
#line 120 "parsing/parse.y"
            { 
			    for (size_t i = 0; i < ((*yyvaluep).size); i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
#line 1517 "parsing/parser.c"
        break;

    case 69: /* statement  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1523 "parsing/parser.c"
        break;

    case 70: /* stat_or_srcitem_list  */
#line 120 "parsing/parse.y"
            { 
			    for (size_t i = 0; i < ((*yyvaluep).size); i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
#line 1532 "parsing/parser.c"
        break;

    case 71: /* stat_or_srcitem  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1538 "parsing/parser.c"
        break;

    case 72: /* expr  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1544 "parsing/parser.c"
        break;

    case 73: /* literal  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1550 "parsing/parser.c"
        break;

    case 74: /* expr_list  */
#line 120 "parsing/parse.y"
            { 
			    for (size_t i = 0; i < ((*yyvaluep).size); i++)
                    ast_builder_remove_node(&bison_ast_builder);
            }
#line 1559 "parsing/parser.c"
        break;

    case 75: /* of_type_ref  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1565 "parsing/parser.c"
        break;

    case 76: /* type_ref  */
#line 108 "parsing/parse.y"
            { ast_builder_remove_node(&bison_ast_builder); }
#line 1571 "parsing/parser.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 132 "parsing/parse.y"
           {
               CHECK_ERROR(ast_builder_new_node_N_child(
                   &bison_ast_builder,
                   SYNTAX_TREE_SOURCE,
                   (yyvsp[0].size)));
           }
#line 1872 "parsing/parser.c"
    break;

  case 3:
#line 140 "parsing/parse.y"
                                             { (yyval.size) = (yyvsp[-1].size) + 1; }
#line 1878 "parsing/parser.c"
    break;

  case 4:
#line 141 "parsing/parse.y"
                                                             { (yyval.size) = 0;      }
#line 1884 "parsing/parser.c"
    break;

  case 6:
#line 147 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_N_child(
                     &bison_ast_builder,
                     SYNTAX_TREE_FUNC_DEF,
                     (yyvsp[-1].size) + 1));
             }
#line 1895 "parsing/parser.c"
    break;

  case 7:
#line 157 "parsing/parse.y"
                   {
                       CHECK_ERROR(ast_builder_new_par_node_N_child(
                           &bison_ast_builder,
                           SYNTAX_TREE_FUNC_TYPED_SIGN,
                           (union ast_node_param) (yyvsp[-4].size),
                           (yyvsp[-2].size) + 1));
                   }
#line 1907 "parsing/parser.c"
    break;

  case 8:
#line 165 "parsing/parse.y"
                   {
					   
                       CHECK_ERROR(ast_builder_new_par_node_N_child(
                           &bison_ast_builder,
                           SYNTAX_TREE_FUNC_UNTYPED_SIGN,
                           (union ast_node_param) (yyvsp[-3].size),
                           (yyvsp[-1].size)));
				   }
#line 1920 "parsing/parser.c"
    break;

  case 9:
#line 175 "parsing/parse.y"
                            { (yyval.size) = (yyvsp[-2].size) + 1; }
#line 1926 "parsing/parser.c"
    break;

  case 10:
#line 176 "parsing/parse.y"
                                    { (yyval.size) = 1;      }
#line 1932 "parsing/parser.c"
    break;

  case 11:
#line 177 "parsing/parse.y"
                                            { (yyval.size) = 0;      }
#line 1938 "parsing/parser.c"
    break;

  case 12:
#line 181 "parsing/parse.y"
            {
            CHECK_ERROR(ast_builder_new_par_node_1_child(
                &bison_ast_builder,
                SYNTAX_TREE_FUNC_TYPED_ARG,
                (union ast_node_param) (yyvsp[-1].size)));
        }
#line 1949 "parsing/parser.c"
    break;

  case 13:
#line 188 "parsing/parse.y"
            {
		    CHECK_ERROR(ast_builder_new_par_node_leaf(
                &bison_ast_builder,
                SYNTAX_TREE_FUNC_UNTYPED_ARG,
                (union ast_node_param) (yyvsp[0].size)));
        }
#line 1960 "parsing/parser.c"
    break;

  case 14:
#line 196 "parsing/parse.y"
                                          { (yyval.size) = (yyvsp[-1].size) + (yyvsp[0].size); }
#line 1966 "parsing/parser.c"
    break;

  case 15:
#line 197 "parsing/parse.y"
                                                      { (yyval.size) = 0;       }
#line 1972 "parsing/parser.c"
    break;

  case 16:
#line 201 "parsing/parse.y"
                            { (yyval.size) = 0; }
#line 1978 "parsing/parser.c"
    break;

  case 17:
#line 203 "parsing/parse.y"
                                { 
                    CHECK_ERROR(ast_builder_new_par_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_DEFINE,
                        (union ast_node_param) (yyvsp[-2].size)));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
				}
#line 1996 "parsing/parser.c"
    break;

  case 18:
#line 217 "parsing/parse.y"
                            { 
                    CHECK_ERROR(ast_builder_new_par_node_2_child(
                        &bison_ast_builder,
                         SYNTAX_TREE_STATEMENT_DEFINEASSIGN,
                        (union ast_node_param) (yyvsp[-4].size))); 

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2014 "parsing/parser.c"
    break;

  case 19:
#line 231 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_REPEAT_WHILE));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2031 "parsing/parser.c"
    break;

  case 20:
#line 244 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_REPEAT_UNTIL));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2048 "parsing/parser.c"
    break;

  case 21:
#line 257 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_leaf(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BREAK));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2065 "parsing/parser.c"
    break;

  case 22:
#line 270 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_EXP));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2082 "parsing/parser.c"
    break;

  case 23:
#line 283 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_leaf(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_RETURN));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2099 "parsing/parser.c"
    break;

  case 24:
#line 295 "parsing/parse.y"
                                       { (yyval.size) = 0; }
#line 2105 "parsing/parser.c"
    break;

  case 25:
#line 297 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_1_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_RETURN_EXP));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2122 "parsing/parser.c"
    break;

  case 26:
#line 309 "parsing/parse.y"
                                          { (yyval.size) = 0; }
#line 2128 "parsing/parser.c"
    break;

  case 27:
#line 311 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_WHILE,
                        (yyvsp[-1].size) + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2146 "parsing/parser.c"
    break;

  case 28:
#line 324 "parsing/parse.y"
                                                    { (yyval.size) = (yyvsp[-3].size); }
#line 2152 "parsing/parser.c"
    break;

  case 29:
#line 326 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_WHILE,
                        (yyvsp[-1].size) + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = (yyvsp[-4].size) + 1;
                }
#line 2170 "parsing/parser.c"
    break;

  case 30:
#line 339 "parsing/parse.y"
                                          { (yyval.size) = 0; }
#line 2176 "parsing/parser.c"
    break;

  case 31:
#line 341 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_UNTIL,
                        (yyvsp[-1].size) + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2194 "parsing/parser.c"
    break;

  case 32:
#line 354 "parsing/parse.y"
                                                    { (yyval.size) = (yyvsp[-3].size); }
#line 2200 "parsing/parser.c"
    break;

  case 33:
#line 356 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_UNTIL,
                        (yyvsp[-1].size) + 1));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = (yyvsp[-4].size) + 1;
                }
#line 2218 "parsing/parser.c"
    break;

  case 34:
#line 369 "parsing/parse.y"
                                                  { (yyval.size) = 0; }
#line 2224 "parsing/parser.c"
    break;

  case 35:
#line 371 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_3_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_IF_ELSE));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2241 "parsing/parser.c"
    break;

  case 36:
#line 383 "parsing/parse.y"
                                        { (yyval.size) = 0; }
#line 2247 "parsing/parser.c"
    break;

  case 37:
#line 385 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_2_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_IF));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2264 "parsing/parser.c"
    break;

  case 38:
#line 398 "parsing/parse.y"
                            {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BLOCK,
                        (yyvsp[-1].size)));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2282 "parsing/parser.c"
    break;

  case 39:
#line 411 "parsing/parse.y"
                            { (yyval.size) = 0; }
#line 2288 "parsing/parser.c"
    break;

  case 40:
#line 413 "parsing/parse.y"
                {
                    CHECK_ERROR(ast_builder_new_node_N_child(
                        &bison_ast_builder,
                        SYNTAX_TREE_STATEMENT_BLOCK,
                        (yyvsp[-1].size)));

                    CHECK_ERROR(ast_builder_save_node_pos(
                        &bison_ast_builder,
                        (yyloc).first_line,
                        (yyloc).first_column));

                    (yyval.size) = 1;
                }
#line 2306 "parsing/parser.c"
    break;

  case 41:
#line 426 "parsing/parse.y"
                            { (yyval.size) = 0; }
#line 2312 "parsing/parser.c"
    break;

  case 42:
#line 429 "parsing/parse.y"
                                                            { (yyval.size) = (yyvsp[-1].size) + 1; }
#line 2318 "parsing/parser.c"
    break;

  case 43:
#line 430 "parsing/parse.y"
                                                                                { (yyval.size) = 0;      }
#line 2324 "parsing/parser.c"
    break;

  case 46:
#line 439 "parsing/parse.y"
                 {
			CHECK_ERROR(ast_builder_new_node_2_child(
				&bison_ast_builder,
				SYNTAX_TREE_EXPR_BINOP_ASSIGN));
	 	 }
#line 2334 "parsing/parser.c"
    break;

  case 47:
#line 445 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_PLUS));
         }
#line 2344 "parsing/parser.c"
    break;

  case 48:
#line 451 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_MINUS));
         }
#line 2354 "parsing/parser.c"
    break;

  case 49:
#line 457 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_MUL));
         }
#line 2364 "parsing/parser.c"
    break;

  case 50:
#line 463 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_DIV));
         }
#line 2374 "parsing/parser.c"
    break;

  case 51:
#line 469 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_AND));
         }
#line 2384 "parsing/parser.c"
    break;

  case 52:
#line 475 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_OR));
         }
#line 2394 "parsing/parser.c"
    break;

  case 53:
#line 481 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_EQUAL));
         }
#line 2404 "parsing/parser.c"
    break;

  case 54:
#line 487 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_NOT_EQUAL));
         }
#line 2414 "parsing/parser.c"
    break;

  case 55:
#line 493 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_LESS));
         }
#line 2424 "parsing/parser.c"
    break;

  case 56:
#line 499 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_GREATER));
         }
#line 2434 "parsing/parser.c"
    break;

  case 57:
#line 505 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_LESS_EQUAL));
         }
#line 2444 "parsing/parser.c"
    break;

  case 58:
#line 511 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_BINOP_GREATER_EQUAL));
         }
#line 2454 "parsing/parser.c"
    break;

  case 59:
#line 517 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_1_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_UNOP_NOT));
         }
#line 2464 "parsing/parser.c"
    break;

  case 60:
#line 523 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_1_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_UNOP_MINUS));
         }
#line 2474 "parsing/parser.c"
    break;

  case 62:
#line 530 "parsing/parse.y"
         {
             CHECK_ERROR(ast_builder_new_node_N_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_CALL,
                 (yyvsp[-1].size) + 1));
         }
#line 2485 "parsing/parser.c"
    break;

  case 63:
#line 537 "parsing/parse.y"
        {
             CHECK_ERROR(ast_builder_new_node_3_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_RANGE));
        }
#line 2495 "parsing/parser.c"
    break;

  case 64:
#line 543 "parsing/parse.y"
        {
             CHECK_ERROR(ast_builder_new_node_2_child(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_INDEX));
        }
#line 2505 "parsing/parser.c"
    break;

  case 65:
#line 549 "parsing/parse.y"
        {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_PLACE,
                 (union ast_node_param) (yyvsp[0].size)));
	    }
#line 2516 "parsing/parser.c"
    break;

  case 67:
#line 559 "parsing/parse.y"
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_BOOL,
                 ((union ast_node_param) (size_t) 1)));
            }
#line 2527 "parsing/parser.c"
    break;

  case 68:
#line 566 "parsing/parse.y"
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_BOOL,
                 ((union ast_node_param) (size_t) 0)));
            }
#line 2538 "parsing/parser.c"
    break;

  case 69:
#line 573 "parsing/parse.y"
            { 
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_STR,
                 (union ast_node_param) (yyvsp[0].size)));
            }
#line 2549 "parsing/parser.c"
    break;

  case 70:
#line 580 "parsing/parse.y"
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_CHAR,
                 (union ast_node_param) (yyvsp[0].size)));
            }
#line 2560 "parsing/parser.c"
    break;

  case 71:
#line 587 "parsing/parse.y"
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_NUM,
                 (union ast_node_param) (yyvsp[0].size)));
           }
#line 2571 "parsing/parser.c"
    break;

  case 72:
#line 594 "parsing/parse.y"
            {
             CHECK_ERROR(ast_builder_new_par_node_leaf(
                 &bison_ast_builder,
                 SYNTAX_TREE_EXPR_LITERAL_NUM_128,
                 (union ast_node_param) (yyvsp[0].size)));
           }
#line 2582 "parsing/parser.c"
    break;

  case 73:
#line 602 "parsing/parse.y"
                               { (yyval.size) = (yyvsp[-2].size) + 1; }
#line 2588 "parsing/parser.c"
    break;

  case 74:
#line 603 "parsing/parse.y"
                                       { (yyval.size) = 1;      }
#line 2594 "parsing/parser.c"
    break;

  case 75:
#line 604 "parsing/parse.y"
                                       { (yyval.size) = 0;      }
#line 2600 "parsing/parser.c"
    break;

  case 77:
#line 610 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_BOOL));
             }
#line 2610 "parsing/parser.c"
    break;

  case 78:
#line 616 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_BYTE));
             }
#line 2620 "parsing/parser.c"
    break;

  case 79:
#line 622 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UBYTE));
             }
#line 2630 "parsing/parser.c"
    break;

  case 80:
#line 628 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_SHORT));
             }
#line 2640 "parsing/parser.c"
    break;

  case 81:
#line 634 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_USHORT));
             }
#line 2650 "parsing/parser.c"
    break;

  case 82:
#line 640 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_INT));
             }
#line 2660 "parsing/parser.c"
    break;

  case 83:
#line 646 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UINT));
             }
#line 2670 "parsing/parser.c"
    break;

  case 84:
#line 652 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_LONG));
             }
#line 2680 "parsing/parser.c"
    break;

  case 85:
#line 658 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_ULONG));
             }
#line 2690 "parsing/parser.c"
    break;

  case 86:
#line 664 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_HUGE));
             }
#line 2700 "parsing/parser.c"
    break;

  case 87:
#line 670 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_UHUGE));
             }
#line 2710 "parsing/parser.c"
    break;

  case 88:
#line 676 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_CHAR));
             }
#line 2720 "parsing/parser.c"
    break;

  case 89:
#line 682 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_BUILTIN_STRING));
             }
#line 2730 "parsing/parser.c"
    break;

  case 90:
#line 688 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_par_node_leaf(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_CUSTOM,
                     (union ast_node_param) (yyvsp[0].size)));

                CHECK_ERROR(ast_builder_save_node_pos(
                            &bison_ast_builder,
                            (yyloc).first_line,
                            (yyloc).first_column));

             }
#line 2747 "parsing/parser.c"
    break;

  case 91:
#line 701 "parsing/parse.y"
             {
                 CHECK_ERROR(ast_builder_new_par_node_1_child(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_ARRAY,
                     (union ast_node_param) (yyvsp[-1].size)));
             }
#line 2758 "parsing/parser.c"
    break;

  case 92:
#line 708 "parsing/parse.y"
             {
				 CHECK_ERROR(ast_builder_res_num_reinsert_128_as_64(
					 &bison_ast_builder,
                     (size_t) (yyvsp[-1].size),
                     (size_t*)&(yyvsp[-1].size)));

   				fprintf(stderr, "** (%d, %d): array length cannot be 128 bit integer literal, \
					   truncating to 64 bit\n", (yylsp[-1]).first_line, (yylsp[-1]).first_column);

                 CHECK_ERROR(ast_builder_new_par_node_1_child(
                     &bison_ast_builder,
					 SYNTAX_TREE_TYPEREF_ARRAY,
                     (union ast_node_param) (yyvsp[-1].size)));	
             }
#line 2777 "parsing/parser.c"
    break;


#line 2781 "parsing/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 723 "parsing/parse.y"


void yyerror(const char *msg) {
   fprintf(stderr, "** (%d, %d): %s\n", yylloc.first_line, yylloc.first_column, msg);
}
