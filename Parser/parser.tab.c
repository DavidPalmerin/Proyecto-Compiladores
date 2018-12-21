/* A Bison parser, made by GNU Bison 3.2.3.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y" /* yacc.c:338  */

/* 
 * File:   parser.y
 * Autor: Melissa y Palmi
 * Diciembre de 2018
 */
#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"


void yyerror(char *);
//void yyerror(char*, char*);

extern int yylex();
extern int yylineno;


#line 89 "parser.tab.c" /* yacc.c:338  */
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

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 21 "parser.y" /* yacc.c:353  */
   
  numero num;
  char id[32];
  char car;
  char* cadena;   
 

#line 194 "parser.tab.c" /* yacc.c:353  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   311

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    56,    56,    58,    59,    61,    62,    63,    64,    65,
      66,    68,    69,    71,    72,    74,    75,    77,    78,    80,
      81,    83,    85,    87,    88,    90,    92,    94,    96,    98,
     100,   102,   104,   106,   108,   110,   112,   113,   116,   118,
     120,   122,   124,   125,   126,   128,   129,   131,   133,   135,
     137,   139,   141,   143,   144,   145,   146,   149,   150,   152,
     154,   156,   158,   160,   162,   164,   166,   167,   169,   170,
     171,   172,   173,   174
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CAR", "ID", "CADENA", "NUMERO", "TRUE",
  "FALSE", "INT", "FLOAT", "DOUBLE", "VOID", "STRUCT", "CHAR", "WHILE",
  "SWITCH", "FOR", "DO", "IF", "RETURN", "FUNC", "COM", "PYC", "PUNES",
  "DOT", "BREAK", "CASE", "DEFAULT", "PRINT", "NL", "ASIG", "OR", "AND",
  "IGUAL", "DIF", "MAYOR", "MENOR", "MAYOR_IGUAL", "MENOR_IGUAL", "MAS",
  "MENOS", "MUL", "DIV", "MOD", "NOT", "LPAR", "RPAR", "LKEY", "RKEY",
  "LCOR", "RCOR", "ELSE", "IFX", "$accept", "programa", "decl", "tipo",
  "lista", "arreglo", "funciones", "argumentos", "lista_args", "parte_arr",
  "sentencias", "sentif", "sentencia", "casos", "predeterm", "parte_izq",
  "var_arreglo", "expresion", "parametros", "lista_param", "condicion",
  "relacional", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     272,   -66,   -66,   -66,   -66,   -18,   -66,    10,     3,    28,
     272,   -66,   272,   -66,   -14,    74,     7,    54,    70,   -66,
      76,   272,   -66,    49,    36,   -14,   -66,   272,   -14,   -66,
      96,    56,    79,   -66,    61,    75,   272,    67,   -66,   272,
     120,    61,   176,    61,   -66,   -22,    80,    81,    83,   176,
      84,    43,   123,   195,   176,   124,   -66,   121,   105,   -66,
     150,   195,    64,   195,   176,   193,    64,   -66,   -17,   -66,
     -66,   -66,   105,    42,   -66,   225,   141,     3,   -66,   195,
     195,   -66,   219,   -66,   -66,    64,    64,   254,     6,   259,
     142,   118,   102,   195,   -66,   195,   195,   195,   195,   195,
     -66,   -66,   -66,   231,   236,   -66,   -66,   104,   -66,   -66,
     -66,   -66,   -66,   -66,   195,    64,    64,   176,   133,    64,
      64,   176,   267,   119,   146,   -38,   -38,   -66,   -66,   -66,
     -66,   -66,   -66,   267,   -66,   -66,   210,   144,    41,   115,
      73,   -66,   -66,   195,   145,   155,   176,   159,   176,   267,
     178,   162,   138,   156,   -66,   227,   176,   176,   -66,   176,
     144,   -66,   210,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     5,     6,     7,     9,     0,     8,     0,    16,     0,
       4,     1,     0,     2,    14,     0,     0,     0,     0,    12,
       0,     4,    10,     0,     0,    14,     3,    18,    14,    11,
       0,     0,    17,    13,    22,     0,     0,     0,    20,     4,
       0,    22,     0,    22,    21,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,     0,    43,    19,
       0,     0,     0,     0,     0,     0,     0,    53,     0,    54,
      55,    33,    52,     0,    36,     0,     0,    16,    23,     0,
       0,    44,     0,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    32,     0,     0,     0,     0,     0,
      37,    34,    15,     0,     0,    45,    63,     0,    73,    72,
      68,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    57,    47,    48,    49,    50,    51,
      31,    46,    64,    65,    61,    62,    28,    39,     0,     0,
      26,    27,    56,     0,     0,    41,     0,     0,     0,    59,
       0,     0,     0,     0,    29,    25,     0,     0,    35,     0,
      39,    40,    30,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,    -2,    -1,   -66,    17,   127,   -66,   -66,   -25,
     -40,   -66,   -24,    46,   -66,   -66,   -42,   -36,   -66,   -66,
     -65,   -66
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    15,    19,    13,    31,    32,    38,
     136,   141,    56,   145,   152,    57,    72,    87,   123,   124,
      88,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    92,    55,    60,    97,    98,    99,    58,    16,    65,
      11,    17,    58,    58,    76,    73,    44,    75,    59,    26,
     106,   107,    58,    58,    12,    82,    30,    89,    61,    93,
      10,    78,    14,    61,    58,    40,    18,    42,   115,   116,
      90,    78,    29,   103,   104,    33,    67,    68,    69,    70,
     134,   135,    78,   117,   138,   139,    22,   122,    23,   125,
     126,   127,   128,   129,   146,    94,    71,    67,    68,    69,
      70,    83,    84,   115,   116,    58,    24,    45,   133,    58,
      25,   140,    95,    96,    97,    98,    99,    28,    46,    47,
      48,    49,    50,    51,    58,    27,    20,    21,    58,    52,
      34,    36,    53,    35,    58,    58,    58,   149,   155,    85,
      86,    37,    78,    58,    58,    58,    78,    58,    41,   162,
      58,    54,   153,    39,    43,   148,    62,    63,    45,    64,
      66,    78,   160,   161,   115,   116,   115,   116,    78,    46,
      47,    48,    49,    50,    51,    45,    74,   115,   116,   121,
      52,   132,    79,    53,    81,    80,    46,    47,    48,    49,
      50,    51,   147,    45,   120,   119,   142,    52,   143,   150,
      53,   144,    54,    77,    46,    47,    48,    49,    50,    51,
      45,   137,   154,   151,   156,    52,   157,   158,    53,    54,
     101,    46,    47,    48,    49,    50,    51,    45,    67,    68,
      69,    70,    52,   159,   102,    53,   163,    54,    91,    47,
      48,    49,    50,    51,    45,     0,     0,     0,     0,    52,
       0,     0,    53,     0,    54,    46,    47,    48,    49,    50,
      51,    45,     0,     0,     0,     0,    52,     0,     0,    53,
       0,    54,    46,    47,    48,    49,    50,    51,   100,     0,
       0,     0,     0,    52,   130,     0,    53,     0,    -1,    95,
      96,    97,    98,    99,     0,    95,    96,    97,    98,    99,
     105,    95,    96,    97,    98,    99,    95,    96,    97,    98,
      99,     1,     2,     3,     4,     5,     6,   131,   108,   109,
     110,   111,   112,   113,    95,    96,    97,    98,    99,    95,
      96,    97,    98,    99,     0,     0,   118,    95,    96,    97,
      98,    99
};

static const yytype_int16 yycheck[] =
{
      42,    66,    42,    25,    42,    43,    44,    49,    10,    49,
       0,    12,    54,    55,    54,    51,    41,    53,    43,    21,
      85,    86,    64,    65,    21,    61,    27,    63,    50,    46,
      48,    55,     4,    50,    76,    36,    50,    39,    32,    33,
      64,    65,    25,    79,    80,    28,     3,     4,     5,     6,
     115,   116,    76,    47,   119,   120,    49,    93,     4,    95,
      96,    97,    98,    99,    23,    23,    23,     3,     4,     5,
       6,     7,     8,    32,    33,   117,     6,     4,   114,   121,
       4,   121,    40,    41,    42,    43,    44,    51,    15,    16,
      17,    18,    19,    20,   136,    46,    22,    23,   140,    26,
       4,    22,    29,    47,   146,   147,   148,   143,   148,    45,
      46,    50,   136,   155,   156,   157,   140,   159,    51,   159,
     162,    48,   146,    48,     4,    52,    46,    46,     4,    46,
      46,   155,   156,   157,    32,    33,    32,    33,   162,    15,
      16,    17,    18,    19,    20,     4,    23,    32,    33,    47,
      26,    47,    31,    29,     4,    50,    15,    16,    17,    18,
      19,    20,    47,     4,    46,    23,    47,    26,    22,    24,
      29,    27,    48,    49,    15,    16,    17,    18,    19,    20,
       4,    48,    23,    28,     6,    26,    24,    49,    29,    48,
      49,    15,    16,    17,    18,    19,    20,     4,     3,     4,
       5,     6,    26,    47,    77,    29,   160,    48,    15,    16,
      17,    18,    19,    20,     4,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    29,    -1,    48,    15,    16,    17,    18,    19,
      20,     4,    -1,    -1,    -1,    -1,    26,    -1,    -1,    29,
      -1,    48,    15,    16,    17,    18,    19,    20,    23,    -1,
      -1,    -1,    -1,    26,    23,    -1,    29,    -1,    48,    40,
      41,    42,    43,    44,    -1,    40,    41,    42,    43,    44,
      51,    40,    41,    42,    43,    44,    40,    41,    42,    43,
      44,     9,    10,    11,    12,    13,    14,    51,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    40,
      41,    42,    43,    44,    -1,    -1,    47,    40,    41,    42,
      43,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    14,    55,    56,    57,
      48,     0,    21,    60,     4,    58,    56,    57,    50,    59,
      22,    23,    49,     4,     6,     4,    56,    46,    51,    59,
      57,    61,    62,    59,     4,    47,    22,    50,    63,    48,
      57,    51,    56,     4,    63,     4,    15,    16,    17,    18,
      19,    20,    26,    29,    48,    64,    66,    69,    70,    63,
      25,    50,    46,    46,    46,    64,    46,     3,     4,     5,
       6,    23,    70,    71,    23,    71,    64,    49,    66,    31,
      50,     4,    71,     7,     8,    45,    46,    71,    74,    71,
      66,    15,    74,    46,    23,    40,    41,    42,    43,    44,
      23,    49,    60,    71,    71,    51,    74,    74,    34,    35,
      36,    37,    38,    39,    75,    32,    33,    47,    47,    23,
      46,    47,    71,    72,    73,    71,    71,    71,    71,    71,
      23,    51,    47,    71,    74,    74,    64,    48,    74,    74,
      64,    65,    47,    22,    27,    67,    23,    47,    52,    71,
      24,    28,    68,    66,    23,    64,     6,    24,    49,    47,
      66,    66,    64,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    58,    58,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      68,    68,    69,    69,    69,    70,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    72,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    75,    75,
      75,    75,    75,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     4,     0,     1,     1,     1,     1,     1,
       4,     4,     2,     4,     0,    11,     0,     1,     0,     5,
       3,     3,     0,     2,     1,     3,     1,     5,     5,     7,
       9,     4,     3,     2,     3,     8,     2,     3,     5,     0,
       3,     0,     1,     1,     3,     4,     4,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     4,     1,     0,     3,
       1,     3,     3,     2,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 56 "parser.y" /* yacc.c:1660  */
    {printf("programa -> decl funciones\n");}
#line 1419 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 3:
#line 58 "parser.y" /* yacc.c:1660  */
    {printf("decl -> tipo lista PYC decl\n");}
#line 1425 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 4:
#line 59 "parser.y" /* yacc.c:1660  */
    {}
#line 1431 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 5:
#line 61 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> int\n");}
#line 1437 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 6:
#line 62 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> float\n");}
#line 1443 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 7:
#line 63 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> double\n");}
#line 1449 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 8:
#line 64 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> char\n");}
#line 1455 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 9:
#line 65 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> void\n");}
#line 1461 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 10:
#line 66 "parser.y" /* yacc.c:1660  */
    {printf("tipo -> struct { decl }\n");}
#line 1467 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 11:
#line 68 "parser.y" /* yacc.c:1660  */
    {printf("lista -> lista , id arreglo\n");}
#line 1473 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 12:
#line 69 "parser.y" /* yacc.c:1660  */
    {printf("lista- >id arreglo\n");}
#line 1479 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 13:
#line 71 "parser.y" /* yacc.c:1660  */
    {printf("arreglo -> id arreglo\n");}
#line 1485 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 14:
#line 72 "parser.y" /* yacc.c:1660  */
    {}
#line 1491 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 15:
#line 74 "parser.y" /* yacc.c:1660  */
    {printf("funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
#line 1497 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 16:
#line 75 "parser.y" /* yacc.c:1660  */
    {}
#line 1503 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 17:
#line 77 "parser.y" /* yacc.c:1660  */
    {printf("argumentos -> lista_args\n");}
#line 1509 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 18:
#line 78 "parser.y" /* yacc.c:1660  */
    {}
#line 1515 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 19:
#line 80 "parser.y" /* yacc.c:1660  */
    {printf("lista_args -> lista_args , tipo id parte_arr\n");}
#line 1521 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 20:
#line 81 "parser.y" /* yacc.c:1660  */
    {printf("lista_args -> tipo id parte_arr\n");}
#line 1527 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 21:
#line 84 "parser.y" /* yacc.c:1660  */
    {printf("parte_arr -> [] parte_arr\n");}
#line 1533 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 22:
#line 85 "parser.y" /* yacc.c:1660  */
    {}
#line 1539 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 23:
#line 87 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> sentencias sentencia\n");}
#line 1545 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 24:
#line 88 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> sentencia\n");}
#line 1551 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 25:
#line 91 "parser.y" /* yacc.c:1660  */
    {printf("sentif -> else sentencias\n");}
#line 1557 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 27:
#line 95 "parser.y" /* yacc.c:1660  */
    {printf("sentencia -> if ( condicion ) sentencias sentif\n");}
#line 1563 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 28:
#line 97 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> while ( condicion ) sentencias\n");}
#line 1569 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 29:
#line 99 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> do sentencias while ( condicion) ;\n"); }
#line 1575 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 30:
#line 101 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> for ( sentencia ; condicion; sentencia ) sentencias\n");}
#line 1581 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 31:
#line 103 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> parte_izq = expresion\n");}
#line 1587 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 32:
#line 105 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> return expresion ;\n");}
#line 1593 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 33:
#line 107 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> return ;\n");}
#line 1599 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 34:
#line 109 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> { sentencias }\n");}
#line 1605 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 35:
#line 111 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> switch ( expresion ) { casos prederterm} \n");}
#line 1611 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 36:
#line 112 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> break ;\n");}
#line 1617 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 37:
#line 114 "parser.y" /* yacc.c:1660  */
    {printf("sentencias -> print expresion ;\n");}
#line 1623 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 38:
#line 117 "parser.y" /* yacc.c:1660  */
    {printf("casos -> case : sentencia casos\n");}
#line 1629 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 39:
#line 118 "parser.y" /* yacc.c:1660  */
    {}
#line 1635 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 40:
#line 121 "parser.y" /* yacc.c:1660  */
    {printf("predeterm -> default : sentencia\n");}
#line 1641 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 41:
#line 122 "parser.y" /* yacc.c:1660  */
    {}
#line 1647 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 42:
#line 124 "parser.y" /* yacc.c:1660  */
    {printf("parte_izq -> id\n");}
#line 1653 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 43:
#line 125 "parser.y" /* yacc.c:1660  */
    {printf("parte_izq -> var_arreglo\n");}
#line 1659 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 44:
#line 126 "parser.y" /* yacc.c:1660  */
    {printf("parte_izq -> id.id\n");}
#line 1665 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 45:
#line 128 "parser.y" /* yacc.c:1660  */
    {printf("var_arreglo -> id [ expresion ] \n");}
#line 1671 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 46:
#line 129 "parser.y" /* yacc.c:1660  */
    {printf("var_arreglo -> var arreglo [ expresion ]\n");}
#line 1677 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 47:
#line 132 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> expresion + expresion \n");}
#line 1683 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 48:
#line 134 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> expresion - expresion \n");}
#line 1689 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 49:
#line 136 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> expresion * expresion \n");}
#line 1695 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 50:
#line 138 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> expresion / expresion \n");}
#line 1701 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 51:
#line 140 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> expresion mod expresion \n");}
#line 1707 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 52:
#line 142 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> var_arreglo\n");}
#line 1713 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 53:
#line 143 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> car %c\n", (yyvsp[0].car));}
#line 1719 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 54:
#line 144 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> cadena %s\n", (yyvsp[0].cadena));}
#line 1725 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 55:
#line 145 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> num %s\n", (yyvsp[0].num).val);}
#line 1731 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 56:
#line 147 "parser.y" /* yacc.c:1660  */
    {printf("expresion -> id %s ( parametros )\n", (yyvsp[-3].id));}
#line 1737 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 57:
#line 149 "parser.y" /* yacc.c:1660  */
    {printf("parametros-> lista_param\n");}
#line 1743 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 58:
#line 150 "parser.y" /* yacc.c:1660  */
    {}
#line 1749 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 59:
#line 153 "parser.y" /* yacc.c:1660  */
    {printf("lista_param -> lista_param , expresion\n");}
#line 1755 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 60:
#line 154 "parser.y" /* yacc.c:1660  */
    {printf("lista_param -> expresion\n");}
#line 1761 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 61:
#line 157 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> condicion || condicion \n");}
#line 1767 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 62:
#line 159 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> condicion && condicion \n");}
#line 1773 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 63:
#line 161 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> ! condicion \n");}
#line 1779 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 64:
#line 163 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> ( condicion ) \n");}
#line 1785 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 65:
#line 165 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> expresion rel expresion \n");}
#line 1791 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 66:
#line 166 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> true \n");}
#line 1797 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 67:
#line 167 "parser.y" /* yacc.c:1660  */
    {printf("condicion -> false\n");}
#line 1803 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 68:
#line 169 "parser.y" /* yacc.c:1660  */
    {printf("rel-> >\n");}
#line 1809 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 69:
#line 170 "parser.y" /* yacc.c:1660  */
    {printf("rel->  <\n");}
#line 1815 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 70:
#line 171 "parser.y" /* yacc.c:1660  */
    {printf("rel->  >=\n");}
#line 1821 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 71:
#line 172 "parser.y" /* yacc.c:1660  */
    {printf("rel->  <=\n");}
#line 1827 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 72:
#line 173 "parser.y" /* yacc.c:1660  */
    {printf("rel->  !=\n");}
#line 1833 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 73:
#line 174 "parser.y" /* yacc.c:1660  */
    {printf("rel->  ==\n");}
#line 1839 "parser.tab.c" /* yacc.c:1660  */
    break;


#line 1843 "parser.tab.c" /* yacc.c:1660  */
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 175 "parser.y" /* yacc.c:1903  */

void yyerror(char *s){
    printf("%s: en la línea %d\n",s, yylineno);
}


/*
mif :  IF LPAR condicion RPAR mif ELSE mif {printf("mif -> if ( condicion ) mif else mif\n");}
            | sentencias {printf("mif -> sentencias\n");};

uif : IF LPAR condicion RPAR sentencias  
      {printf("uif -> if ( condicion ) sentencias\n");}
      | IF LPAR condicion RPAR mif ELSE uif
      {printf("uif -> if ( condicion ) mif else uif\n");};

sentif : ELSE sentencias
        {printf("sentif -> else sentencias\n");}
        | %prec IFX %empty {};
*/
