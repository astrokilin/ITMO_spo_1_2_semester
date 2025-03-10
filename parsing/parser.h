/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 106 "parsing/parser.h"

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
