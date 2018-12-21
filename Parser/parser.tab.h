/* A Bison parser, made by GNU Bison 3.2.3.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CAR = 258,
    ID = 259,
    CADENA = 260,
    NUMERO = 261,
    TRUE = 262,
    FALSE = 263,
    INT = 264,
    FLOAT = 265,
    DOUBLE = 266,
    VOID = 267,
    STRUCT = 268,
    CHAR = 269,
    WHILE = 270,
    SWITCH = 271,
    FOR = 272,
    DO = 273,
    IF = 274,
    RETURN = 275,
    FUNC = 276,
    COM = 277,
    PYC = 278,
    PUNES = 279,
    DOT = 280,
    BREAK = 281,
    CASE = 282,
    DEFAULT = 283,
    PRINT = 284,
    NL = 285,
    ASIG = 286,
    OR = 287,
    AND = 288,
    IGUAL = 289,
    DIF = 290,
    MAYOR = 291,
    MENOR = 292,
    MAYOR_IGUAL = 293,
    MENOR_IGUAL = 294,
    MAS = 295,
    MENOS = 296,
    MUL = 297,
    DIV = 298,
    MOD = 299,
    NOT = 300,
    LPAR = 301,
    RPAR = 302,
    LKEY = 303,
    RKEY = 304,
    LCOR = 305,
    RCOR = 306,
    ELSE = 307,
    IFX = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "parser.y" /* yacc.c:1912  */
   
  numero num;
  char id[32];
  char car;
  char* cadena;   
 

#line 119 "parser.tab.h" /* yacc.c:1912  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
