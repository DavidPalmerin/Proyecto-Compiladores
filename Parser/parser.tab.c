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
#include <string.h>
#include <stdbool.h>

/* Colores para mostra en terminal. */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#include "list.h"
#include "attributes.h"
#include "intermediate_code.h"
#include "backpatch.h"
#include "symtab.h"
#include "typetab.h"
#include "stack.h"


extern int yylex();
extern int yylineno;

/* Ouput files */
FILE *contexts;
FILE *err;
FILE *producciones;

/* Funciones para el manejo de errores */
void yyerror2(char*, char*);
void yyerror(char *);

/* Variable para el conteo de direcciones */
int dir=0;
int top_dir = 0;

/* Variables para guardar el tipo y ancho actual */
int current_type;
int current_dim;

/* Variable para iniciar el conteo de dimensiones en un struct*/
bool struct_decl = false;
int  struct_dim = 0;

/* Variable para indicar el conteo de dimensiones de una función */
int func_dim = 0;
bool func_decl = false;


/* Varaibles para contar las temporales, etiquetas e indices */
int label = 0;
int temp = 0;
int indice = 0;

int index_dim = 0;

/* Variable para el unico atributo heredado de sentencia prima*/
labels lcontrol;

/* Variable para la tabla de símbolos*/
symtab global_symbols;

/* Variable para la tabla de tipos*/
typetab global_types;

/* Variable para la tabla de funciones. */
funtab global_funcs;
int    num_params = 0;
int    call_params = 0;
char   curr_function[32];
stack  func_calls;
int    return_type = -1;

/* Pila para cases de switch*/
stack switchesback;
int   switch_call = 0;

/* Variable papra guardar el código intermedio que se va generando */
ic codigo_intermedio;

/* Etiquetas. */
labels etiquetas;

/* Funciones auxiliares al análisis semántico y generación de código intermedio */
void init();
void finish();
void add_context(bool func_context);
void del_context(bool context);
bool exists_main();
void print_context(char *s1, char *s2);
exp* call_function(exp *e);
void insert_sym(char id[32], env curr_env, int tipo);
int check_args_types(funrec *rec, exp expr);



/* Pila de tablas de símbolos para cada contexto. */
stack envs;

/* Lista para las dimensiones de un arreglo.*/
list dimensiones;

/* Auxiliares para errores. */
bool fail_decl = false;
bool imprime_ci = true;

exp math_function(exp e1, exp e2, int op);
exp get_numero(numero);
exp identificador(char *);
exp asignar(exp e1,exp e2);

void gen_cond_goto(char dir[32]);
bools * gen_cond_rel(char e1[32], char e2[32], int op);

/* Funciones auxiliares para la comprobación de tipos */
int max_type(int t1, int t2);
char *ampliar(char *dir, int t1, int t2);
char *reducir(char *dir, int t1, int t2);


/* Funciones para generar temporales, etiquetas e indices */
char *newTemp();
char *newLabel();
char *newIndex();


#line 203 "parser.tab.c" /* yacc.c:338  */
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
    LKEY = 286,
    RKEY = 287,
    ASIG = 288,
    OR = 289,
    AND = 290,
    IGUAL = 291,
    DIF = 292,
    MAYOR = 293,
    MENOR = 294,
    MAYOR_IGUAL = 295,
    MENOR_IGUAL = 296,
    MAS = 297,
    MENOS = 298,
    MUL = 299,
    DIV = 300,
    MOD = 301,
    NOT = 302,
    LPAR = 303,
    RPAR = 304,
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
#line 135 "parser.y" /* yacc.c:353  */
   
    int    rel;
    char   id[32];
    char*  car;
    char*  cadena;   
    exp    expr;
    int    tipo;
    int    cases;
    bool   args;
    numero num;
    labels siguientes;
    bools  *booleans;
    struct{
        labels siguientes;
        bool ifelse;
    } siguientesp;

#line 318 "parser.tab.c" /* yacc.c:353  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   244

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

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
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   194,   192,   208,   208,   215,   217,   221,
     225,   229,   233,   237,   237,   247,   319,   394,   408,   415,
     442,   413,   490,   498,   502,   504,   528,   553,   555,   557,
     561,   566,   571,   574,   584,   573,   603,   618,   602,   654,
     653,   684,   696,   683,   731,   747,   769,   778,   787,   786,
     837,   841,   851,   869,   850,   882,   884,   886,   888,   907,
     915,   964,  1030,  1087,  1092,  1097,  1102,  1107,  1112,  1119,
    1125,  1133,  1138,  1138,  1193,  1198,  1200,  1223,  1246,  1245,
    1265,  1264,  1285,  1292,  1297,  1302,  1311,  1320,  1322,  1323,
    1324,  1325,  1326,  1327
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
  "DOT", "BREAK", "CASE", "DEFAULT", "PRINT", "NL", "LKEY", "RKEY", "ASIG",
  "OR", "AND", "IGUAL", "DIF", "MAYOR", "MENOR", "MAYOR_IGUAL",
  "MENOR_IGUAL", "MAS", "MENOS", "MUL", "DIV", "MOD", "NOT", "LPAR",
  "RPAR", "LCOR", "RCOR", "ELSE", "IFX", "$accept", "programa", "$@1",
  "$@2", "decl", "$@3", "tipo", "$@4", "lista", "arreglo", "funciones",
  "$@5", "$@6", "argumentos", "lista_args", "parte_arr", "sentencias",
  "sentif", "sentencia", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "casos", "$@15", "$@16", "predeterm", "parte_izq",
  "var_arreglo", "expresion", "$@17", "parametros", "lista_param",
  "condicion", "$@18", "$@19", "relacional", YY_NULLPTR
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

#define YYPACT_NINF -71

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -71,    16,   225,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,    -2,   -11,    46,   225,   225,   -71,    17,    25,
      52,    73,    84,   -71,    87,   225,   -71,    44,    43,    17,
     -71,   -71,    17,   -71,   225,   -71,    91,    47,    76,    49,
      69,   225,    62,   -71,   225,   111,    49,   158,    49,   -71,
     -23,    68,    71,    79,   -71,    80,    53,    98,   105,   158,
     122,   -71,    97,    83,   -71,   130,   105,   -71,   105,   158,
     158,    34,   -71,    85,   -71,   -71,   -71,    83,    20,   -71,
      60,   140,   -71,   -71,   105,   105,   -71,   172,    34,   148,
     113,   128,   -71,   -71,    34,    34,   167,    -3,    99,   -71,
     105,   105,   105,   105,   105,   -71,   -71,   -11,   156,   182,
     -71,    45,   -71,   -71,   101,   -71,    26,   -71,   -71,   -71,
     -71,   -71,   -71,   105,   -71,   -71,   -71,   105,    42,    42,
     -71,   -71,   -71,   -71,   -71,   -71,    96,   115,    34,    34,
     -71,   198,    34,    34,   158,   198,   103,   139,   158,   123,
      10,    36,   -71,   -71,   -71,   -71,   105,   -71,   141,   135,
     -71,   144,   112,   198,   162,   146,   149,   158,   -71,   158,
     -71,   -71,   158,   -71,   131,   -71,   158,   -71,   158,   158,
     -71,   123,   -71
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     7,     1,    10,    11,    12,     8,    13,     9,
       3,     5,     0,    22,     0,     7,     0,     4,    18,     0,
       0,     0,     0,    16,     0,     7,    14,     0,     0,    18,
       6,    19,    18,    15,    24,    17,     0,     0,    23,    28,
       0,     0,     0,    26,     7,     0,    28,     0,    28,    27,
      58,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    30,     0,    59,    25,     0,     0,    36,     0,     0,
       0,    87,    69,    72,    70,    71,    46,    68,     0,    50,
       0,     0,    20,    29,     0,     0,    60,     0,    87,     0,
       0,     0,    85,    86,    87,    87,     0,     0,     0,    45,
       0,     0,     0,     0,     0,    51,    47,    22,     0,     0,
      61,    37,    48,    41,     0,    82,     0,    93,    92,    88,
      89,    90,    91,     0,    78,    80,    33,    75,    63,    64,
      65,    66,    67,    21,    44,    62,     0,     0,    87,    87,
      83,    84,    87,    87,     0,    77,     0,    74,     0,    55,
       0,     0,    79,    81,    34,    73,     0,    38,     0,    57,
      42,     0,    32,    76,     0,     0,     0,     0,    40,     0,
      35,    52,     0,    49,     0,    31,     0,    56,     0,    53,
      43,    55,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,   -71,   -71,     5,   -71,   -13,   -71,   -71,   -21,
      75,   -71,   -71,   -71,   -71,   -42,   -58,   -71,   -55,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,     2,   -71,   -71,
     -71,   -71,   -47,   -49,   -71,   -71,   -71,   -70,   -71,   -71,
     -71
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    10,    14,    11,    12,    19,    23,
      17,    34,   107,    37,    38,    43,    60,   170,    61,   144,
     162,    88,   136,    70,   138,   167,   137,   159,   176,   181,
     166,    62,    77,    96,    98,   146,   147,    97,   142,   143,
     123
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      63,    81,    65,    21,    49,    83,    64,    78,    33,    80,
      16,    35,    63,    63,    90,    91,     3,    87,   111,    89,
      20,    36,    63,    63,   115,   116,    83,    66,    45,    15,
      30,   124,   125,   160,    63,   108,   109,    72,    73,    74,
      75,    92,    93,    99,   124,   125,   126,    24,    25,    47,
      18,   128,   129,   130,   131,   132,    72,    73,    74,    75,
     124,   125,   100,   101,   102,   103,   104,    22,   150,   151,
     124,   125,   152,   153,   141,   140,    76,    27,   145,   124,
     125,    94,    95,   105,    26,   161,   102,   103,   104,   154,
      28,    29,    31,   157,    32,    39,    40,    63,    41,    42,
      44,    63,   100,   101,   102,   103,   104,   163,    72,    73,
      74,    75,   174,    46,   175,    48,    67,   177,   179,    68,
      63,    79,    63,   180,    83,    63,    50,    69,    71,    63,
      84,    63,    63,    85,    86,    66,   113,    51,    52,    53,
      54,    55,    56,   114,    50,   148,   149,   127,    57,   139,
     158,    58,   155,    59,    82,    51,    52,    53,    54,    55,
      56,   156,    50,   165,   169,   164,    57,   168,   171,    58,
     172,    59,   106,    51,    52,    53,    54,    55,    56,   134,
     178,   173,   133,   182,    57,     0,     0,    58,     0,    59,
     100,   101,   102,   103,   104,     0,     0,   112,   100,   101,
     102,   103,   104,   117,   118,   119,   120,   121,   122,   100,
     101,   102,   103,   104,   100,   101,   102,   103,   104,     0,
       0,     0,     0,   110,   100,   101,   102,   103,   104,     0,
       0,     0,     0,   135,     4,     5,     6,     7,     8,     9,
     100,   101,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
      47,    59,    25,    16,    46,    60,    48,    56,    29,    58,
      21,    32,    59,    60,    69,    70,     0,    66,    88,    68,
      15,    34,    69,    70,    94,    95,    81,    50,    41,    31,
      25,    34,    35,    23,    81,    84,    85,     3,     4,     5,
       6,     7,     8,    23,    34,    35,    49,    22,    23,    44,
       4,   100,   101,   102,   103,   104,     3,     4,     5,     6,
      34,    35,    42,    43,    44,    45,    46,    50,   138,   139,
      34,    35,   142,   143,   123,    49,    23,     4,   127,    34,
      35,    47,    48,    23,    32,    49,    44,    45,    46,   144,
       6,     4,    48,   148,    51,     4,    49,   144,    22,    50,
      31,   148,    42,    43,    44,    45,    46,   156,     3,     4,
       5,     6,   167,    51,   169,     4,    48,   172,   176,    48,
     167,    23,   169,   178,   179,   172,     4,    48,    48,   176,
      33,   178,   179,    50,     4,    50,    23,    15,    16,    17,
      18,    19,    20,    15,     4,    49,    31,    48,    26,    48,
      27,    29,    49,    31,    32,    15,    16,    17,    18,    19,
      20,    22,     4,    28,    52,    24,    26,    23,     6,    29,
      24,    31,    32,    15,    16,    17,    18,    19,    20,    23,
      49,    32,   107,   181,    26,    -1,    -1,    29,    -1,    31,
      42,    43,    44,    45,    46,    -1,    -1,    49,    42,    43,
      44,    45,    46,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,     9,    10,    11,    12,    13,    14,
      42,    43,    44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    56,     0,     9,    10,    11,    12,    13,    14,
      58,    60,    61,    57,    59,    31,    21,    64,     4,    62,
      58,    60,    50,    63,    22,    23,    32,     4,     6,     4,
      58,    48,    51,    63,    65,    63,    60,    67,    68,     4,
      49,    22,    50,    69,    31,    60,    51,    58,     4,    69,
       4,    15,    16,    17,    18,    19,    20,    26,    29,    31,
      70,    72,    85,    86,    69,    25,    50,    48,    48,    48,
      77,    48,     3,     4,     5,     6,    23,    86,    87,    23,
      87,    70,    32,    72,    33,    50,     4,    87,    75,    87,
      72,    72,     7,     8,    47,    48,    87,    91,    88,    23,
      42,    43,    44,    45,    46,    23,    32,    66,    87,    87,
      51,    91,    49,    23,    15,    91,    91,    36,    37,    38,
      39,    40,    41,    94,    34,    35,    49,    48,    87,    87,
      87,    87,    87,    64,    23,    51,    76,    80,    78,    48,
      49,    87,    92,    93,    73,    87,    89,    90,    49,    31,
      91,    91,    91,    91,    72,    49,    22,    72,    27,    81,
      23,    49,    74,    87,    24,    28,    84,    79,    23,    52,
      71,     6,    24,    32,    72,    72,    82,    72,    49,    70,
      72,    83,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    56,    57,    55,    59,    58,    58,    60,    60,
      60,    60,    60,    61,    60,    62,    62,    63,    63,    65,
      66,    64,    64,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    73,    74,    72,    75,    76,    72,    77,
      72,    78,    79,    72,    72,    72,    72,    72,    80,    72,
      72,    72,    82,    83,    81,    81,    84,    84,    85,    85,
      85,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    87,    89,    89,    90,    90,    92,    91,
      93,    91,    91,    91,    91,    91,    91,    91,    94,    94,
      94,    94,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     4,     0,     5,     0,     1,     1,
       1,     1,     1,     0,     5,     4,     2,     4,     0,     0,
       0,    13,     0,     1,     0,     5,     3,     3,     0,     2,
       1,     2,     0,     0,     0,     8,     0,     0,     7,     0,
       8,     0,     0,    11,     4,     3,     2,     3,     0,     9,
       2,     3,     0,     0,     7,     0,     3,     0,     1,     1,
       3,     4,     4,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     0,     5,     1,     0,     3,     1,     0,     4,
       0,     4,     2,     3,     3,     1,     1,     0,     1,     1,
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
#line 192 "parser.y" /* yacc.c:1660  */
    { init(); }
#line 1547 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 3:
#line 194 "parser.y" /* yacc.c:1660  */
    { 
                    /* Guardamos la tabla más global. */
                    env my_env;
                    stack_peek(&envs, &my_env);
                    global_symbols = my_env.symbols;
                    global_types = my_env.types;

                }
#line 1560 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 4:
#line 202 "parser.y" /* yacc.c:1660  */
    {
                            print_context("Contexto global", "");
                            fprintf(producciones,"programa -> decl funciones\n");
                            finish();
                        }
#line 1570 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 5:
#line 208 "parser.y" /* yacc.c:1660  */
    {   
                        current_type = (yyvsp[0].tipo);
                        current_dim = get_tam(&global_types,(yyvsp[0].tipo));
                    }
#line 1579 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 6:
#line 212 "parser.y" /* yacc.c:1660  */
    {
                                fprintf(producciones,"decl -> tipo lista PYC decl\n");
                            }
#line 1587 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 7:
#line 215 "parser.y" /* yacc.c:1660  */
    {}
#line 1593 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 8:
#line 217 "parser.y" /* yacc.c:1660  */
    {    
                        (yyval.tipo) = 0;
                        fprintf(producciones,"tipo -> VOID\n");
                    }
#line 1602 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 9:
#line 221 "parser.y" /* yacc.c:1660  */
    {
                        (yyval.tipo) = 1;
                        fprintf(producciones,"tipo -> CHAR\n");
                    }
#line 1611 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 10:
#line 225 "parser.y" /* yacc.c:1660  */
    {
                        (yyval.tipo) = 2;
                        fprintf(producciones,"tipo -> INT\n");
                    }
#line 1620 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 11:
#line 229 "parser.y" /* yacc.c:1660  */
    {
                        (yyval.tipo) = 3;
                        fprintf(producciones,"tipo -> FLOAT\n");
                    }
#line 1629 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 12:
#line 233 "parser.y" /* yacc.c:1660  */
    {
                        (yyval.tipo) = 4;
                        fprintf(producciones,"tipo -> DOUBLE\n");
                    }
#line 1638 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 13:
#line 237 "parser.y" /* yacc.c:1660  */
    {   
                        struct_decl = true;
                        add_context(false);
                    }
#line 1647 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 14:
#line 241 "parser.y" /* yacc.c:1660  */
    {
                                    (yyval.tipo) = 5;
                                    fprintf(producciones,"tipo -> struct { decl }\n");
                                    //del_context(false);
                                }
#line 1657 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 15:
#line 251 "parser.y" /* yacc.c:1660  */
    {
                    /* Verificamos la existencia del identificador. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, (yyvsp[-1].id)) != -1)
                    {
                        yyerror2("Ya existe un identificador con el nombre", (yyvsp[-1].id));
                        fail_decl = true;
                    }                
                    if (current_type == 5)
                    {
                        yyerror("Struct solo puede tener un identificador.");
                        fail_decl = true;
                    }
                    if(current_type == 0)
                    {
                        yyerror("No se pueden declarar variables de tipo void.");
                        fail_decl = true;
                    }                        
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else{
                        /*Agregamos el elemento a la tabla de símbolos. Si es un arreglo
                          calcula su direccion. */
                        sym symbol;
                        strcpy(symbol.id, (yyvsp[-1].id));
                        symbol.type = current_type;
                        symbol.dir  = dir;
                        dir += current_dim;
                        
                        stack_pop(&envs, &curr_env);

                        int curr_tam = get_tam(&global_types,current_type);
                        bool primero = true; 
                        while(list_size(&dimensiones)){
                            int temp;
                            list_head(&dimensiones,&temp,1);
                            type tipo = new_type();
                            
                            if(primero)
                            {
                                tipo.base = symbol.type;
                                primero = false;
                            } 
                            else tipo.base = curr_env.types.count -1;

                            tipo.dim = temp;
                            curr_tam *= tipo.dim;
                            tipo.tam = curr_tam;
                            
                            insert_type(&curr_env.types,tipo);
                            //Cambiamos el tipo del id si es arreglo, apuntando a su última dim
                            symbol.type = curr_env.types.count -1;
                        }
                        primero = false;    
                        list_destroy(&dimensiones);
                        list_new(&dimensiones, 10,NULL);
                        
                        insert(&curr_env.symbols, symbol);
                        stack_push(&envs, &curr_env);
                        if (struct_decl){
                            struct_dim += current_dim;
                        }
                        
                        fprintf(producciones,"lista -> lista , id arreglo\n");}
                }
#line 1730 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 16:
#line 321 "parser.y" /* yacc.c:1660  */
    {
                    /*Verifica la existencia del identificador. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, (yyvsp[-1].id)) != -1)
                    {
                        yyerror2("Ya existe un identificador con el nombre", (yyvsp[-1].id));
                        fail_decl = true;
                    }
                    if(current_type == 0){
                        yyerror("No se pueden declarar variables de tipo void.");
                        fail_decl = true;
                    }                  
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else {
                        sym symbol;
                        /* Caso especial para structs. */
                        if (current_type == 5)
                        {   
                            int last_dir = dir;
                            env struct_env;
                            stack_peek(&envs, &struct_env);
                            symtab *syms = (symtab*) malloc(sizeof(symtab));
                            *syms = struct_env.symbols;
                            symbol.struct_content = syms;
                            del_context(false);
                            symbol.dir = top_dir;
                        }
                        else symbol.dir = dir;

                        strcpy(symbol.id, (yyvsp[-1].id));
                        symbol.type = current_type;
                        dir += current_dim;

                        stack_pop(&envs, &curr_env);
                        int curr_tam = get_tam(&global_types,current_type);
                        bool primero = true; 
                        while(list_size(&dimensiones)){
                            int temp;
                            list_head(&dimensiones,&temp,1);
                            type tipo = new_type();
                            
                            if(primero)
                            {
                                tipo.base = symbol.type;
                                primero = false;
                            } 
                            else tipo.base = curr_env.types.count -1;

                            tipo.dim = temp;
                            curr_tam *= tipo.dim;
                            tipo.tam = curr_tam;
                            
                            insert_type(&curr_env.types,tipo);
                            //Cambiamos el tipo del id si es arreglo, apuntando a su última dim
                            symbol.type = curr_env.types.count - 1;
                        }
                        primero = false;
                        list_destroy(&dimensiones);
                        list_new(&dimensiones, 10,NULL);

                        insert(&curr_env.symbols, symbol);
                        stack_push(&envs, &curr_env);
                        if (struct_decl){
                            struct_dim += current_dim;
                        }
                        fprintf(producciones,"lista- >id arreglo\n");
                    }
                }
#line 1807 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 17:
#line 395 "parser.y" /* yacc.c:1660  */
    {   
                if ((yyvsp[-2].num).type == 2){
                    int num = atoi((yyvsp[-2].num).val);
                    current_dim *= num;
                    list_append(&dimensiones, &num);
                    fprintf(producciones,"arreglo -> id arreglo\n");
                }
                else{ 
                    fail_decl = true;
                    yyerror("[ERROR ] La dimensión del arreglo se debe indicar con un entero.");
                };
                
            }
#line 1825 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 18:
#line 409 "parser.y" /* yacc.c:1660  */
    {
                    
                }
#line 1833 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 19:
#line 415 "parser.y" /* yacc.c:1660  */
    {
                    /* Asigna etiquetas a las funciones. */
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, (yyvsp[-1].id));
                    insert_cuad(&codigo_intermedio, cuad);

                    /* Verifica el id de la función. 
                        Crea un contexto nuevo en la pila si el id es válido.
                    */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (search(&curr_env.symbols, (yyvsp[-1].id)) != -1)
                    {
                        yyerror2("Ya se ha definido anteriormente el identificador", (yyvsp[-1].id));
                        imprime_ci = false;
                        fail_decl = true;
                    }else{
                            add_context(true);
                            func_decl = true;
                    }
                    return_type = (yyvsp[-2].tipo);
                }
#line 1863 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 20:
#line 442 "parser.y" /* yacc.c:1660  */
    {
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else 
                    {
                        print_context("Contexto local de: ", (yyvsp[-8].id));

                        /* Elimina el contexto de la función del tope de la pila y guarda el registro
                           de la función */
                        env fun_env;
                        stack_peek(&envs, &fun_env);

                        symtab *func_context = (symtab*) malloc(sizeof(symtab));
                        *func_context = fun_env.symbols;

                        funrec reg;
                        strcpy(reg.id, (yyvsp[-8].id));
                        reg.context = func_context;
                        reg.params = num_params;
                        reg.counter = 0;
                        insert_fun(&global_funcs, reg);

                        int func_tam = dir;
                        del_context(false);
                        
                        env curr_env;
                        stack_pop(&envs, &curr_env);

                        /* Agregamos el nombre de la función al contexto donde se puede llamar. */
                        sym symbol;
                        strcpy(symbol.id, (yyvsp[-8].id));
                        symbol.type = (yyvsp[-9].tipo);
                        symbol.dir = dir;
                        dir += func_tam;

                        insert(&curr_env.symbols, symbol);
                        stack_push(&envs, &curr_env);

                        global_symbols = curr_env.symbols;
                        func_decl = false;
                        num_params = 0;
                        //print_funtable(&global_funcs);
                    }
                }
#line 1914 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 21:
#line 489 "parser.y" /* yacc.c:1660  */
    {fprintf(producciones,"funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
#line 1920 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 22:
#line 490 "parser.y" /* yacc.c:1660  */
    {
                            /* Verifica que la última función definida sea main. */
                            if (!exists_main())
                              return 1;
                            //print_funtable(&global_funcs);
                            num_params = 0;
                        }
#line 1932 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 23:
#line 499 "parser.y" /* yacc.c:1660  */
    {
                           fprintf(producciones,"argumentos -> lista_args\n");
                        }
#line 1940 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 24:
#line 502 "parser.y" /* yacc.c:1660  */
    {}
#line 1946 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 25:
#line 505 "parser.y" /* yacc.c:1660  */
    {
                    /* Verifica si existe el ID en el contexto actual o el padre. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, (yyvsp[-1].id)) != -1)
                    {
                        yyerror2("Ya se ha definido anteriormente el identificador", (yyvsp[-1].id));
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else 
                    {
                    insert_sym((yyvsp[-1].id), curr_env, (yyvsp[-2].tipo));

                    /* Variable para funciones. */
                    num_params += 1;
                    }
                    fprintf(producciones,"lista_args -> lista_args , tipo id parte_arr\n");
                }
#line 1974 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 26:
#line 529 "parser.y" /* yacc.c:1660  */
    {
                        /* Verifica si existe el ID en el contexto actual o el padre. */
                        env curr_env;
                        stack_peek(&envs, &curr_env);
                        if (depth_search(&curr_env.symbols, (yyvsp[-1].id)) != -1)
                        {
                            yyerror2("Ya se ha definido anteriormente el identificador", (yyvsp[-1].id));
                            fail_decl = true;
                        }
                        
                        if(fail_decl){
                            fail_decl = false;
                            imprime_ci = false;
                        }
                        else{
                        insert_sym((yyvsp[-1].id), curr_env, (yyvsp[-2].tipo));

                        /* Variable para funciones. */
                        num_params += 1;
                        }
                        fprintf(producciones,"lista_args -> tipo id parte_arr\n");

                    }
#line 2002 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 27:
#line 554 "parser.y" /* yacc.c:1660  */
    {fprintf(producciones,"parte_arr -> [] parte_arr\n");}
#line 2008 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 28:
#line 555 "parser.y" /* yacc.c:1660  */
    {}
#line 2014 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 29:
#line 558 "parser.y" /* yacc.c:1660  */
    {    
                fprintf(producciones,"sentencias -> sentencias sentencia\n");
            }
#line 2022 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 30:
#line 562 "parser.y" /* yacc.c:1660  */
    {
                fprintf(producciones,"sentencias -> sentencia\n");
            }
#line 2030 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 31:
#line 566 "parser.y" /* yacc.c:1660  */
    {
                printf(ANSI_COLOR_RED "No se implementó función if else :(\n" ANSI_COLOR_RESET);
                return -1;
                (yyval.siguientesp).ifelse = true;
            }
#line 2040 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 32:
#line 571 "parser.y" /* yacc.c:1660  */
    {(yyval.siguientesp).ifelse = false; }
#line 2046 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 33:
#line 574 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&(yyvsp[-1].booleans)->trues));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                }
#line 2060 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 34:
#line 584 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&(yyvsp[-3].booleans)->falses));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);

                    char label[32], label2[32];
                    strcpy(label, newLabel());
                    strcpy(label2, newLabel());
                    backpatch(&(yyvsp[-3].booleans)->trues, label, &codigo_intermedio);
                    backpatch(&(yyvsp[-3].booleans)->falses, label2, &codigo_intermedio);
                }
#line 2081 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 36:
#line 603 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    char label[32];

                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(label, newLabel());
                    strcpy(cuad.res, label);
                    insert_cuad(&codigo_intermedio, cuad);
                    
                    /*Guarda la etiqueta de la condición*/
                    push_label(&lcontrol, label);
                }
#line 2100 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 37:
#line 618 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&(yyvsp[0].booleans)->trues));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                    
                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&(yyvsp[0].booleans)->trues, label, &codigo_intermedio);
                }
#line 2118 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 38:
#line 632 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla c;
                    c.op = GOTO;
                    strcpy(c.op1, "");
                    strcpy(c.op2, "");
                    strcpy(c.res, pop_label(&lcontrol));
                    insert_cuad(&codigo_intermedio, c);

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&(yyvsp[-3].booleans)->falses));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);  

                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&(yyvsp[-3].booleans)->falses, label, &codigo_intermedio);
                }
#line 2144 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 39:
#line 654 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    char label[32];

                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(label, newLabel());
                    strcpy(cuad.res, label);
                    insert_cuad(&codigo_intermedio, cuad);
                    push_label(&lcontrol, label);
                }
#line 2161 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 40:
#line 667 "parser.y" /* yacc.c:1660  */
    {
                    char label[32], label2[32];
                    strcpy(label, pop_label(&lcontrol));
                    strcpy(label2, newLabel());
                    backpatch(&(yyvsp[-2].booleans)->trues, label, &codigo_intermedio);
                    backpatch(&(yyvsp[-2].booleans)->falses, label2, &codigo_intermedio);

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, label2);
                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"sentencia -> do sentencias while ( condicion) ;\n"); 
                }
#line 2182 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 41:
#line 684 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    char label[32];
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(label, newLabel());
                    strcpy(cuad.res, label);
                    insert_cuad(&codigo_intermedio, cuad);
                    push_label(&lcontrol, label);
                }
#line 2198 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 42:
#line 696 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&(yyvsp[-1].booleans)->trues));
                    insert_cuad(&codigo_intermedio, cuad);
                }
#line 2212 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 43:
#line 706 "parser.y" /* yacc.c:1660  */
    {   
                    cuadrupla c;
                    c.op = GOTO;
                    strcpy(c.op1, "");
                    strcpy(c.op2, "");
                    strcpy(c.res, pop_label(&lcontrol));
                    insert_cuad(&codigo_intermedio, c);

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&(yyvsp[-5].booleans)->falses));
                    insert_cuad(&codigo_intermedio, cuad);

                    char label[32], label2[32];
                    strcpy(label, newLabel());
                    strcpy(label2, newLabel());
                    backpatch(&(yyvsp[-5].booleans)->trues, label2, &codigo_intermedio);
                    backpatch(&(yyvsp[-5].booleans)->falses, label, &codigo_intermedio);

                    fprintf(producciones,"sentencia -> for ( sentencia ; condicion; sentencia ) sentencias\n");
                }
#line 2241 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 44:
#line 732 "parser.y" /* yacc.c:1660  */
    {                       
                    call_params = 0;
                    if (strcmp((yyvsp[-1].expr).dir, "SF") != 0)
                    {
                        int compatible = max_type((yyvsp[-3].expr).type, (yyvsp[-1].expr).type);
                        if(compatible == -1) {
                            yyerror("No se puede asignar, tipos incompatibles.");
                            imprime_ci = false;
                        }
                        else {
                            asignar((yyvsp[-3].expr),(yyvsp[-1].expr));
                            fprintf(producciones,"sentencia -> parte_izq = expresion\n");
                        }
                    }
                }
#line 2261 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 45:
#line 748 "parser.y" /* yacc.c:1660  */
    {
                    if (return_type == 0)
                    {
                        yyerror(" La función no puede regresar argumentos pues es de tipo void");
                        imprime_ci = false;
                    }
                    else if (return_type < 5) 
                    {
                        if(return_type != (yyvsp[-1].expr).type){
                            yyerror("Tipo de regreso incompatible con definición de la función");
                            imprime_ci = false;
                        }
                    }

                    cuadrupla cuad;
                    cuad.op = RET;
                    strcpy(cuad.res, (yyvsp[-1].expr).dir);
                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"sentencia -> return expresion ;\n");
                }
#line 2287 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 46:
#line 770 "parser.y" /* yacc.c:1660  */
    {
                    if (return_type != 0)
                    {
                        yyerror(" La función debe retornar una expresión");
                        imprime_ci = false;
                    }
                    fprintf(producciones,"sentencia -> return ;\n");
                }
#line 2300 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 47:
#line 779 "parser.y" /* yacc.c:1660  */
    {
                    char label[32];
                    (yyval.siguientes) = (yyvsp[-1].siguientes);
                    strcpy(label, newLabel());
                    backpatch(&(yyvsp[-1].siguientes), label, &codigo_intermedio);
                    fprintf(producciones,"sentencia -> { sentencias }\n");
                }
#line 2312 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 48:
#line 787 "parser.y" /* yacc.c:1660  */
    {
                    push_label(&lcontrol, newLabel());
                    push_label(&lcontrol, newLabel());
                    switch_call++;

                    cuadrupla cuad;
                    cuad.op = GOTO;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_top_label_previous(&lcontrol));
                    insert_cuad(&codigo_intermedio, cuad);
                }
#line 2329 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 49:
#line 800 "parser.y" /* yacc.c:1660  */
    {

                    cuadrupla c;
                    c.op = LB;
                    strcpy(c.op1, "");
                    strcpy(c.op2, "");
                    strcpy(c.res, get_top_label_previous(&lcontrol));
                    insert_cuad(&codigo_intermedio, c);

                    while(stack_size(&switchesback) > 0)
                    {
                        switches sw;
                        stack_peek(&switchesback, &sw);
                        if (sw.link != (yyvsp[-2].cases)) break;
                        stack_pop(&switchesback, &sw);
                        
                        char arg[32];
                        sprintf(arg, "%s = %s", (yyvsp[-6].expr).dir, sw.caso);

                        cuadrupla cuad;
                        cuad.op = IFF;
                        strcpy(cuad.op1, arg);
                        strcpy(cuad.op2, "");
                        strcpy(cuad.res, sw.label);
                        insert_cuad(&codigo_intermedio, cuad);
                    }

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, pop_label(&lcontrol));
                    insert_cuad(&codigo_intermedio, cuad);

                    pop_label(&lcontrol);
                }
#line 2370 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 50:
#line 838 "parser.y" /* yacc.c:1660  */
    {
                    fprintf(producciones,"sentencia -> break ;\n");
                }
#line 2378 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 51:
#line 842 "parser.y" /* yacc.c:1660  */
    {
                    char i[32];
                    strcpy(i, newIndex());
                    (yyval.siguientes) = create_list(i);
                    fprintf(producciones,"sentencia -> print expresion ;\n");
                }
#line 2389 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 52:
#line 851 "parser.y" /* yacc.c:1660  */
    {
                cuadrupla cuad;
                char index[32];
                strcpy(index, newLabel());

                cuad.op = LB;
                strcpy(cuad.op1, "");
                strcpy(cuad.op2, "");
                strcpy(cuad.res, index);
                insert_cuad(&codigo_intermedio, cuad);

                switches sw;
                strcpy(sw.label, index);
                strcpy(sw.caso, (yyvsp[0].num).val);
                sw.link = switch_call;
                stack_push(&switchesback, &sw);
            }
#line 2411 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 53:
#line 869 "parser.y" /* yacc.c:1660  */
    {
                char *label = get_top_label(&lcontrol);
                cuadrupla cuad;
                cuad.op = GOTO;
                strcpy(cuad.op1, "");
                strcpy(cuad.op2, "");
                strcpy(cuad.res, label);
                insert_cuad(&codigo_intermedio, cuad);
            }
#line 2425 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 54:
#line 879 "parser.y" /* yacc.c:1660  */
    {   
                (yyval.cases) = (yyvsp[0].cases); fprintf(producciones, "casos : case : NUMERO sentencias casos");
            }
#line 2433 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 55:
#line 882 "parser.y" /* yacc.c:1660  */
    {(yyval.cases) = switch_call;}
#line 2439 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 56:
#line 885 "parser.y" /* yacc.c:1660  */
    {fprintf(producciones,"predeterm -> default : sentencia\n");}
#line 2445 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 57:
#line 886 "parser.y" /* yacc.c:1660  */
    {}
#line 2451 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 58:
#line 888 "parser.y" /* yacc.c:1660  */
    {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, (yyvsp[0].id)) == -1)
                    {
                        yyerror2("No se ha declarado la variable", (yyvsp[0].id));
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else{
                        strcpy((yyval.expr).dir, (yyvsp[0].id));
                        (yyval.expr).type = get_type(&curr_env.symbols, (yyvsp[0].id));
                    }
                    fprintf(producciones,"parte_izq -> id\n");
                }
#line 2475 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 59:
#line 908 "parser.y" /* yacc.c:1660  */
    {
                    exp id;
                    strcpy(id.dir,(yyvsp[0].expr).arr);
                    id.type = (yyvsp[0].expr).type;
                    (yyval.expr) = asignar(id,(yyvsp[0].expr));
                    fprintf(producciones,"parte_izq -> var_arreglo\n");
                }
#line 2487 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 60:
#line 916 "parser.y" /* yacc.c:1660  */
    {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if(depth_search(&curr_env.symbols, (yyvsp[-2].id)) == -1)
                    {
                        yyerror2("No se ha declarado la variable", (yyvsp[-2].id));
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else{
                        int type = get_type(&curr_env.symbols, (yyvsp[-2].id));
                        if (type != 5)
                        {
                            yyerror2((yyvsp[-2].id), "no es de tipo struct");
                            imprime_ci = false;
                            /* A fuerzas debe terminar el programa pues genera un segmentation fault. */
                            return -1;
                        }

                        env curr_env;
                        stack_peek(&envs, &curr_env);
                        symtab *struct_content = get_struct_content(&curr_env.symbols, (yyvsp[-2].id));
                        if(depth_search(struct_content, (yyvsp[0].id)) == -1)
                        {   
                            print_table(struct_content);
                            yyerror2("No existe tal atributo en el struct con nombre", (yyvsp[-2].id));
                            fail_decl = true;
                        }
                        if(fail_decl){
                            fail_decl = false;
                            imprime_ci = false;
                        }
                        else{
                            //Asignar dirección.
                            // La direcicón de $1 está en env.symbols (o en parent) y la del atributo está en struct_content.
                            strcmp((yyval.expr).dir,newTemp());
                            
                            (yyval.expr).type = get_type(struct_content, (yyvsp[0].id));
                        } 
                    }

                    fprintf(producciones,"parte_izq -> id.id\n");
                }
#line 2539 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 61:
#line 965 "parser.y" /* yacc.c:1660  */
    {
                env curr_env;
                stack_peek(&envs, &curr_env);
                if (depth_search(&curr_env.symbols, (yyvsp[-3].id)) == -1)
                    {
                        yyerror2("No se encontró el identificador", (yyvsp[-3].id));
                        fail_decl = true;
                        return -1;
                    }
                strcpy((yyval.expr).arr,(yyvsp[-3].id));
                exp base_dir;
                sprintf(base_dir.dir,"%d",get_dir(&curr_env.symbols,(yyvsp[-3].id)));
                base_dir.type = 2;
                int curr_type = get_type(&curr_env.symbols,(yyvsp[-3].id));

                if( (yyvsp[-1].expr).type != 2)
                    {
                    yyerror("Para acceder a un arreglo la expresión o número debe ser un entero ");
                    fail_decl = true;
                    }
                if( curr_type == 5)
                    {
                    yyerror("Acceso inválido, es tipo struct y se está intentando acceder como un arreglo ");
                    fail_decl = true;
                    }
                if(fail_decl)
                {
                    fail_decl = false;
                    imprime_ci = false;
                }
                else
                {
                    int base_type = get_base(&curr_env.types,curr_type);

                    exp arr_index = (yyvsp[-1].expr);
                    //printf("->> Index: %s\n",arr_index.dir);
                    //printf("->> Tipo base: %d\n",base_type);

                    (yyval.expr).type = base_type;
                    /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                    dir = base_dir + (index * tam_base) + ...*/
                    //Verificación, solo funciona con números (no expresiones).
                    if(arr_index.dir[0] != 't'){
                        if(atoi(arr_index.dir) < 0 || atoi(arr_index.dir) >=  get_dim(&curr_env.types,curr_type))
                            {
                                yyerror("Fuera de rango, index inávildo.");
                                imprime_ci = false;
                            }
                    }
                    else
                    {                 
                    exp tam_act;
                    tam_act.type = 2;
                    sprintf(tam_act.dir, "%d",get_tam(&curr_env.types,base_type));
                    
                    exp curr_dir = math_function(arr_index,tam_act,ML);

                    strcpy((yyval.expr).dir,math_function(base_dir,curr_dir,MA).dir);
                    //printf("->> Dir act: %s\n",$$.dir);
                    }
                    fprintf(producciones,"var_arreglo -> id [ expresion ] \n");
                    

                }
            }
#line 2609 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 62:
#line 1031 "parser.y" /* yacc.c:1660  */
    { 
                if( (yyvsp[-1].expr).type != 2)
                    {
                    yyerror("Para acceder a un arreglo la expresión o número debe ser un entero ");
                    fail_decl = true;
                    }
                env curr_env;
                stack_peek(&envs, &curr_env);
                if((yyvsp[-3].expr).type == -1){
                    yyerror("Fuera de rango ");
                    fail_decl = true;
                }
                if(fail_decl)
                {
                    fail_decl = false;
                    imprime_ci = false;
                }
                else
                    {
                        exp base_dir;
                        strcpy(base_dir.dir,(yyvsp[-3].expr).dir);
                        base_dir.type = 2;

                        //printf("CURR TYPE --->%d\n",$1.type);

                        int base_type = get_base(&curr_env.types,(yyvsp[-3].expr).type);

                        exp arr_index = (yyvsp[-1].expr);
                        //printf("->> Index: %s\n",arr_index.dir);
                        //printf("->> Tipo base: %d\n",base_type);
                            
                        (yyval.expr).type = base_type;
                        /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                        dir = base_dir + (index * tam_base) + ...*/
                        //Verificación, solo funciona con números (no expresiones).
                        if(arr_index.dir[0] != 't'){
                            if(atoi(arr_index.dir) < 0 || atoi(arr_index.dir) >=  get_dim(&curr_env.types,(yyvsp[-3].expr).type))
                                {
                                    yyerror("Fuera de rango, index inávildo.");
                                    imprime_ci = false;
                                }
                        }
                        else
                        {  
                        exp tam_act;
                        tam_act.type = 2;
                        sprintf(tam_act.dir,"%d", get_tam(&curr_env.types,base_type));
                        
                        exp curr_dir = math_function(arr_index,tam_act,ML);

                        strcpy((yyval.expr).dir,math_function(base_dir,curr_dir,MA).dir);
                        }
                        fprintf(producciones,"var_arreglo -> var arreglo [ expresion ]\n");
                    }
                }
#line 2669 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 63:
#line 1088 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr) = math_function((yyvsp[-2].expr),(yyvsp[0].expr),MA);
                    fprintf(producciones,"expresion -> expresion + expresion \n");
                }
#line 2678 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 64:
#line 1093 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr) = math_function((yyvsp[-2].expr),(yyvsp[0].expr),MEN);
                    fprintf(producciones,"expresion -> expresion - expresion \n");
                }
#line 2687 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 65:
#line 1098 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr) = math_function((yyvsp[-2].expr),(yyvsp[0].expr),ML);
                    fprintf(producciones,"expresion -> expresion * expresion \n");
                }
#line 2696 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 66:
#line 1103 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr) = math_function((yyvsp[-2].expr),(yyvsp[0].expr),DV);
                    fprintf(producciones,"expresion -> expresion / expresion \n");
                }
#line 2705 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 67:
#line 1108 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr) = math_function((yyvsp[-2].expr),(yyvsp[0].expr),MD);
                    fprintf(producciones,"expresion -> expresion mod expresion \n");
                }
#line 2714 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 68:
#line 1113 "parser.y" /* yacc.c:1660  */
    {
                    exp id;
                    strcpy(id.dir,(yyvsp[0].expr).arr);
                    (yyval.expr) = asignar(id,(yyvsp[0].expr));
                    fprintf(producciones,"expresion -> var_arreglo\n");
                }
#line 2725 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 69:
#line 1120 "parser.y" /* yacc.c:1660  */
    {   
                    (yyval.expr).type = 1;
                    strcpy((yyval.expr).dir, (yyvsp[0].car));
                    fprintf(producciones,"expresion -> car %s\n", (yyvsp[0].car));
                }
#line 2735 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 70:
#line 1126 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.expr).type = 6;
                    (yyval.expr).cadena = (char*) malloc(sizeof(char*));
                    strcpy((yyval.expr).cadena,(yyvsp[0].cadena));

                    fprintf(producciones,"expresion -> cadena %s\n", (yyvsp[0].cadena));
                }
#line 2747 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 71:
#line 1134 "parser.y" /* yacc.c:1660  */
    {   (yyval.expr).type = (yyvsp[0].num).type;
                    strcpy((yyval.expr).dir, (yyvsp[0].num).val);
                    fprintf(producciones,"expresion -> num %s\n", (yyvsp[0].num).val);
                }
#line 2756 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 72:
#line 1138 "parser.y" /* yacc.c:1660  */
    {
                    stack_push(&func_calls, (yyvsp[0].id));
                    stack_peek(&func_calls, curr_function);
                  }
#line 2765 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 73:
#line 1143 "parser.y" /* yacc.c:1660  */
    {   
                    /* Verifica que exista el id. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, (yyvsp[-4].id)) == -1)
                    {
                        yyerror2("No se encontró el identificador", (yyvsp[-4].id));
                        fail_decl = true;
                    }
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                        strcpy((yyval.expr).dir, "SF");
                        (yyval.expr).type = -1;
                    }
                    else
                    {
                        if (is_function(&global_funcs, (yyvsp[-4].id)))
                        {
                            funrec *rec = get_rec(&global_funcs, (yyvsp[-4].id));
                            if (rec->params != rec->counter)
                            {
                                char *msg = (char*) malloc(sizeof(char*));
                                sprintf(msg, "Se esperaban %d argumentos en la función %s, pero se encontraron %d", rec->params, rec->id, rec->counter);
                                yyerror(msg);
                                fail_decl = true;                            
                            }
                            rec->counter = 0;
                        }
                        else if ((yyvsp[-1].args))
                        {
                            yyerror2("No corresponde a una función el identificador", (yyvsp[-4].id));
                            fail_decl = true;
                        }
                        if(fail_decl){
                            fail_decl = false;
                            imprime_ci = false;
                        }
                        else
                        {
                        stack_pop(&func_calls, &curr_function);
                        /* Asigna tipo esperado. */
                        strcpy((yyval.expr).dir, (yyvsp[-4].id));
                        (yyval.expr).type = get_type(&curr_env.symbols,(yyvsp[-4].id));
                        }
                    }
                    fprintf(producciones,"expresion -> id %s ( parametros )\n", (yyvsp[-4].id));
                }
#line 2818 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 74:
#line 1194 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.args) = true; 
                    fprintf(producciones,"parametros-> lista_param\n");
                }
#line 2827 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 75:
#line 1198 "parser.y" /* yacc.c:1660  */
    {(yyval.args) = false;}
#line 2833 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 76:
#line 1201 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = PARAM;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    if (is_function(&global_funcs, (yyvsp[0].expr).dir) == 0)
                    {
                        strcpy(cuad.res, (yyvsp[0].expr).dir);
                    }
                    else{
                        exp *e = call_function(&(yyvsp[0].expr));
                        strcpy(cuad.res, e->dir);
                    }

                    funrec *rec = get_rec(&global_funcs, curr_function);
                    if (check_args_types(rec, (yyvsp[0].expr)) < 0)
                        return -1;

                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"lista_param -> lista_param , expresion\n");
                }
#line 2860 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 77:
#line 1224 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = PARAM;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    if (is_function(&global_funcs, (yyvsp[0].expr).dir) == 0)

                        strcpy(cuad.res, (yyvsp[0].expr).dir);
                    else{
                        exp *e = call_function(&(yyvsp[0].expr));
                        strcpy(cuad.res, e->dir);
                    }
                    
                    funrec *rec = get_rec(&global_funcs, curr_function);
                    if(check_args_types(rec, (yyvsp[0].expr)) < 0)
                        return -1;
                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"lista_param -> expresion\n");
                }
#line 2885 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 78:
#line 1246 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&(yyvsp[-1].booleans)->falses));
                    insert_cuad(&codigo_intermedio, cuad);
                 }
#line 2898 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 79:
#line 1255 "parser.y" /* yacc.c:1660  */
    {
                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&(yyvsp[-3].booleans)->falses, label, &codigo_intermedio);
                    (yyval.booleans) = (bools*) malloc(sizeof(bools));
                    (yyval.booleans)->trues = merge(&(yyvsp[-3].booleans)->trues, &(yyvsp[0].booleans)->trues);
                    (yyval.booleans)->falses = (yyvsp[0].booleans)->falses;
                    fprintf(producciones,"condicion -> condicion && condicion \n");
                 }
#line 2912 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 80:
#line 1265 "parser.y" /* yacc.c:1660  */
    {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&(yyvsp[-1].booleans)->trues));
                    insert_cuad(&codigo_intermedio, cuad);
                }
#line 2925 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 81:
#line 1274 "parser.y" /* yacc.c:1660  */
    {
                    char label[32];
                    strcpy(label, newLabel());
                    
                    (yyval.booleans) = (bools*) malloc(sizeof(bools));
                    (yyval.booleans)->falses = merge(&(yyvsp[-3].booleans)->falses, &(yyvsp[0].booleans)->falses);
                    (yyval.booleans)->trues = (yyvsp[0].booleans)->trues;
                    backpatch(&(yyvsp[-3].booleans)->trues, label, &codigo_intermedio);
                    
                    fprintf(producciones,"condicion -> condicion && condicion \n");
                }
#line 2941 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 82:
#line 1286 "parser.y" /* yacc.c:1660  */
    {   
                    (yyval.booleans) = (bools*) malloc(sizeof(bools));
                    (yyval.booleans)->falses = (yyvsp[0].booleans)->trues;
                    (yyval.booleans)->trues  = (yyvsp[0].booleans)->falses;
                    fprintf(producciones,"condicion -> ! condicion \n");
                }
#line 2952 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 83:
#line 1293 "parser.y" /* yacc.c:1660  */
    {   
                    (yyval.booleans) = (yyvsp[-1].booleans);
                    fprintf(producciones,"condicion -> ( condicion )\n");
                }
#line 2961 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 84:
#line 1298 "parser.y" /* yacc.c:1660  */
    {
                    (yyval.booleans)  = gen_cond_rel((yyvsp[-2].expr).dir, (yyvsp[0].expr).dir, (yyvsp[-1].rel));
                    fprintf(producciones,"condicion -> expresion rel expresion \n");
                }
#line 2970 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 85:
#line 1303 "parser.y" /* yacc.c:1660  */
    {   
                    (yyval.booleans) = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    (yyval.booleans)->trues = create_list(dir);
                    gen_cond_goto(dir);
                    fprintf(producciones,"condicion -> true \n");
                }
#line 2983 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 86:
#line 1312 "parser.y" /* yacc.c:1660  */
    {  
                    (yyval.booleans) = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    (yyval.booleans)->falses = create_list(dir);
                    gen_cond_goto(dir);
                    fprintf(producciones,"condicion -> false \n");
                }
#line 2996 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 87:
#line 1320 "parser.y" /* yacc.c:1660  */
    {}
#line 3002 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 88:
#line 1322 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = GT; fprintf(producciones,"rel-> >\n"); }
#line 3008 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 89:
#line 1323 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = LT; fprintf(producciones,"rel->  <\n");}
#line 3014 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 90:
#line 1324 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = GE; fprintf(producciones,"rel->  >=\n");}
#line 3020 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 91:
#line 1325 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = LE; fprintf(producciones,"rel->  <=\n");}
#line 3026 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 92:
#line 1326 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = NE; fprintf(producciones,"rel->  !=\n");}
#line 3032 "parser.tab.c" /* yacc.c:1660  */
    break;

  case 93:
#line 1327 "parser.y" /* yacc.c:1660  */
    { (yyval.rel) = EQ; fprintf(producciones,"rel->  ==\n");}
#line 3038 "parser.tab.c" /* yacc.c:1660  */
    break;


#line 3042 "parser.tab.c" /* yacc.c:1660  */
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
#line 1328 "parser.y" /* yacc.c:1903  */


/*
 * Función para imprimir un error con el mensaje deseado.
 * Se usan colores para hacer los comentarios amigables al usuario.
 *
 * Autor: Melissa Mendez Servín
 *        Palmerin Morales David Gabriel.
*/
void yyerror(char *s){
    printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "%s: en la línea %d\n",s, yylineno);
    fprintf(err,"%s: en la línea %d\n",s, yylineno);
}

/*
 * Función para imprimir un error concatenando los dos mensajes recibidos.
 * El mensaje s será primero que el mensaje n.
 * 
 * Autor: Melissa Mendez Servín
 *        Palmerin Morales David Gabriel.
 */
void yyerror2(char *s, char *n){
    printf(ANSI_COLOR_RED"Error:"ANSI_COLOR_RESET " %s %s: en la línea %d\n",s, n, yylineno);    
    fprintf(err,"%s %s: en la línea %d\n",s, n, yylineno);
}

/* Inicializa las variables necesarias para el análisis, tales como 
 * pilas, tablas globales, etc.
 * 
 * Autores: Melissa Mendez Servín 
 *          Palmerin Morales David Gabriel.
 */
void init()
{
    create_code(&codigo_intermedio);
    create_labels(&etiquetas);
    create_funtab(&global_funcs);

    stack_new(&switchesback, sizeof(switches), NULL);
    stack_new(&func_calls, sizeof(char) * 32, NULL);
    stack_new(&envs, sizeof(typetab) + sizeof(symtab) , NULL);
    symtab sym_tab;
    create_table(&sym_tab, NULL);
    sym_tab.parent = NULL;

    typetab type_tab;
    create_table_types(&type_tab, NULL);
   
    env initial_env;
    initial_env.symbols = sym_tab;
    initial_env.types = type_tab;
    global_types = initial_env.types;
    stack_push(&envs, &initial_env);

    list_new(&dimensiones, 10,NULL);
}

/* Función qu finaliza el análisis semántico.
 * Se encarga de determinar si se debe de imprimir el código intermedio
 * esto sucede si no ocurrió ningún error en el programa de entrada.
 *
 * Autores: Melissa Mendez Servín 
 *.         Palmerin Morales David Gabriel.
 */
void finish()
{
    if(imprime_ci){
        print_code(&codigo_intermedio);
        printf(ANSI_COLOR_GREEN "¡Código compilado!" ANSI_COLOR_RESET " Ver archivo:" ANSI_COLOR_YELLOW " codigo.ci\n" ANSI_COLOR_RESET);
    }

}

/* Imprime en un archivo la tabla de símbolos actual.
 * La tabla de símbolos se encuentra en el ambiente del tope de la pila envs.
 * Autor: Palmerín Morales David Gabriel.
 */
void print_context(char *s1, char *s2)
{
    env curr_env;
    stack_peek(&envs, &curr_env);
    fprintf(contexts, "~ %s %s\n", s1, s2);
    fprint_table(&curr_env.symbols, contexts);
    fprint_table_types(&curr_env.types,contexts);
    fprintf(contexts, "\n");
}

/* 
 * Agrega un env nuevo a la pila envs. 
 * Esta función se usa cuando queremos generar un contexto nuevo.
 * Para el lenguaje dado, se suele usar cuando detectamos un struct y func.
 * Recibe un booleano que indica si el nuevo contexto es para una función.
 * Además, e encarga de guardar la dirección de la tabla de símbolos actual, 
 * para que al regresar al contexto podamos saber donde continuar indexando.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
void add_context(bool func_context)
{
    /* Guardamos la última dirección usada en el ambiente actual. */
    env curr_env;
    stack_pop(&envs, &curr_env);
    curr_env.symbols.last_dir = dir;
    stack_push(&envs, &curr_env);

    /* Nueva tabla de símbolos. */
    symtab new_symtab;
    typetab new_typetab;
    if (func_context){
        create_table(&new_symtab, &global_symbols);
        create_table_types(&new_typetab, &global_types);
    }
    else{
        create_table(&new_symtab, NULL);
        create_table_types(&new_typetab, NULL);
    }
    /* Finalmente, creamos el nuevo ambiente. */
    env my_env;
    my_env.symbols = new_symtab;
    my_env.types = new_typetab;

    stack_push(&envs, &my_env);
    dir = 0;
}

/*
 * Elimina el contexto del tope de la pila.
 * Al eliminarlo actualiza la variable dir para continuar un 
 * correcto indexado.
 * Recibe un booleano si se desea imprimir en consola el contexto 
 * eliminado.
 *
 * Autor: Palmerín Morales David Gabriel.
 *
*/
void del_context(bool print_context)
{
    env curr_env;
    stack_pop(&envs, &curr_env);
    if (print_context)
    {
        print_table(&curr_env.symbols);
        print_table_types(&curr_env.types);
    }

    if (stack_size(&envs) > 0)
    {   
        stack_peek(&envs, &curr_env);
        top_dir = curr_env.symbols.last_dir;
        dir += curr_env.symbols.last_dir;
    }
}

/*
 * Se encarga de crear una etiqueta temporal para las variables.
 *
 * Autor: Adrian Ulises Mercado Martínez
*/
char* newTemp(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

/*
 * Se encarga de crear una etiqueta para las MIPS.
 *
 * Autor: Adrian Ulises Mercado Martínez
*/
char* newLabel(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

/*
 * Se encarga de crear una índice temporal para fines de backpatching.
 *
 * Autor: Adrian Ulises Mercado Martínez
*/
char* newIndex(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
}

/*
 * Verifica que la última función definida sea main.
 * 
 * Autor: Palmerin Morales David Gabriel.
*/
bool exists_main()
{
    int index = global_symbols.count - 1;
    if (index >= 0)
    {
        sym symbol = global_symbols.symbols[index];
        if (strcmp(symbol.id, "main") != 0)
        {
            yyerror("No se encontró la declaración de la función main");
            return false;
        }
    }
    return true;
}


int max_type(int t1, int t2){
    //printf("TIPO 1: %d, TIPO 2: %d\n",t1,t2);
    if (t1 == t2) return t1;
    else {
        /*Si son ambos números. */
        if (t1 > 1 && t1 < 5 && 
            t2 > 1 && t2 < 5){
                if (t1 < t2){return t2;}
        } 
        else {return t1;}  
        if (t1 > 6 &&  t2 == 6)
            return -2; //Es posible que se intenta asignar una cadena a una char unidimensional
        /*Si no son números -> tipos incompatibles.
         Por ahora no se pude hacer int a char*/    
        return -1;
    } 
}

/* Asina a e1 el valor de la dirección de e2*/
exp asignar(exp e1, exp e2){
    exp e;

    if (is_function(&global_funcs, e2.dir) == 1)
        call_function(&e2);
    cuadrupla cuad;
    env curr_env;
    stack_peek(&envs, &curr_env);
    /* Si se está pidiendo asignar un arreglo, i.e, e2.arr == ID*/
    if(strlen(e2.arr) > 0) {
        /* Verifica que exista el id. */
        if (depth_search(&curr_env.symbols, e2.arr) == -1)
        {
            yyerror2("No se encontró el identificador", e2.arr);
            imprime_ci = false;

        }
        else{
            cuad.op = AS_ARR;
            char *temp = (char*) malloc(32*sizeof(char));
            strcpy(temp, newTemp());
            strcpy(&cuad.res, temp);  // T =
            strcpy(&cuad.op1,e1.dir); //     ID
            strcpy(&cuad.op2,e2.dir); //         [VAL]
            insert_cuad(&codigo_intermedio, cuad);
            strcpy(e.dir,temp);
            e.type = e2.type;
            return e;
        }
    }
    else
    {
        strcpy(&cuad.res, e1.dir);
        strcpy(e.dir, e1.dir);
        int t1 = e1.type;
        int t2 = e2.type;
        e.type = t1;
        if(t1 > 6 && t2 == 6){
            int base = get_base(&curr_env.types, t1);
            if(base == 1){ //Se va a asignar una cadena a un arreglo de chars unidimensional
                int dim = get_dim(&curr_env.types,t1);
                int len = strlen(e2.cadena);
                if(len <= dim +2){
                    cuad.op  = ASS;
                    cuad.string_op = (char*) malloc(sizeof(char*));
                    strcpy(cuad.string_op, e2.cadena);
                    insert_cuad(&codigo_intermedio, cuad);
                    return e;
                }
                else 
                {
                    fail_decl = true;
                    //char *msg = (char*) malloc(sizeof(char*));
                    //sprintf(msg, "Fuera de rango, se está intentando asignar una cadena con longitud %d a un arreglo de chars con dimension %d menor.",len, dim);
                    yyerror("Fuera de rango, se está intentando asignar una cadena con longitud a un arreglo de chars con dimension menor.");
                    imprime_ci = false;
                }
            }
            else 
            {
                yyerror("Solo se pueden asignar cadenas a arreglos unidimensionas de tipo char.");
                imprime_ci = false;
            }
        }
        else{
            cuad.op  = AS;
            if(t1 <= t2) {
                char *op1 = reducir(e2.dir, t2, t1);
                if (strcmp(op1, "SF") != 0){
                    strcpy(&cuad.op1, op1);
                }
                else {
                    yyerror("Ocurrió un error de asignación.");
                }
            }
            else strcpy(&cuad.op1, ampliar(e2.dir,t2,t1));
            insert_cuad(&codigo_intermedio, cuad);
            return e;
        }
    }
}

/*
 * Crea una llamada a una función.
 * Se crea una asignación AS, y el lado derecho consta 
 * de call f n, donde call es una palabra para indicar a llamar
 * la función, f es el identificador de la función, y n
 * el número de argumentos que recibe.
 * Agrega al código intermedio esta asignación.
 *
 * Autor: Palmerin Morales David Gabriel. 
*/
exp* call_function(exp *e)
{
    cuadrupla cuad;
    char temp[32];
    char op1[32];
    funrec rec = *get_rec(&global_funcs, e->dir);        

    sprintf(op1, "call %s %d", e->dir, rec.params);
    strcpy(temp, newTemp());

    cuad.op = AS;
    strcpy(cuad.op1, op1);
    strcpy(cuad.op2, "");
    strcpy(cuad.res, temp);
    insert_cuad(&codigo_intermedio, cuad);
    strcpy(e->dir, temp);
    
    return e;
}

/* Ampliar el numero de la expresion con dirección dir,
    de tipo t al tipo w (menor).(int a = 2.0 (int))*/
char *reducir(char * dir, int t, int w){
    // Si son del mismo tipo, no es necesario hacer la reducción
    char *temp = (char*) malloc(32*sizeof(char));
    if(t == w) {
        strcpy(temp,dir);;
        return temp;
    }
    cuadrupla c;
    c.op = CT;
    if(w == 2){ //Si vamos a castear a int
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(temp, newTemp());
        strcpy(c.res, temp);
        insert_cuad(&codigo_intermedio, c);
        if(t == 3){ //un float
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Pérdida de información, se está asignando un float a un int: línea %d\n", yylineno);
            return temp; 
        }        
        if(t == 4){ //un double
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Pérdida de información, se está asignando un double a un int: línea %d\n", yylineno);
            return temp; 
        }          
    }
    if(w == 3){ //Si vamos a castear a float
        if(t == 4){ //un double
            strcpy(c.op1, "(float)");
            strcpy(c.op2, dir);
            strcpy(temp, newTemp());
            strcpy(c.res, temp);
            insert_cuad(&codigo_intermedio, c); 
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Pérdida de información, se está asignando un double a un float: línea %d\n", yylineno);
            return temp; 
        }        
    }
    return "SF";
}

/* Ampliar el numero de la expresion con dirección dir,
    de tipo t al tipo w (más grande).*/
char *ampliar(char *dir, int t, int w){
    char *temp = (char*) malloc(32*sizeof(char));
    if( t==w){
        strcpy(temp,dir);
        return temp;
    } 
    cuadrupla c;
    c.op = CT;
    if( w == 3){
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(temp, newTemp());
        strcpy(c.res, temp);
        insert_cuad(&codigo_intermedio, c);
        if (t == 2)
            printf("Cast de int a float..\n");
        return temp;
    }        
    if( w == 4){
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(temp, newTemp());
        strcpy(c.res, temp);
        insert_cuad(&codigo_intermedio, c);
        if (t == 2)
            printf("Cast de int a double.\n");
        if (t == 3)
            printf("Cast de float a double.\n");
        return temp;
    }        
    return "SF";
}

/* Te devuelve la expresión correspondiente a la operación
    dada y lo traduce a código intermedio. */
exp math_function(exp e1, exp e2, int op){
    exp e;
    int max = max_type(e1.type,e2.type);
    e.type = max;
    if(max==-1) 
        yyerror("Tipos incompatibles");
    else{
        char *t = (char*) malloc(32 * sizeof(char));
        strcpy(t, newTemp());
        strcpy(e.dir, t);
        cuadrupla cuad;
        cuad.op = op;
        strcpy(cuad.res, e.dir);
        strcpy(cuad.op1, ampliar(e1.dir,e1.type,max));
        strcpy(cuad.op2, ampliar(e2.dir,e2.type,max));
        insert_cuad(&codigo_intermedio, cuad);
        }
    return e;
}

/*
 * Genera condiciones goto hacia la dirección recibida.
 * Además la agrega al codigo intermedio.
 * Se usan en condicion para True y False.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
void gen_cond_goto(char dir[32])
{
    if (strlen(dir) == 0)
        return;
    cuadrupla cuad;
    cuad.op = GOTO;
    strcpy(cuad.res, dir);
    strcpy(cuad.op1, "");
    strcpy(cuad.op2, "");
    insert_cuad(&codigo_intermedio, cuad);
}

/*
 * Genera saltos para condicionales binarias.
 * Crea índices en las listas trues y falses de una condición
 * para que posteriormente estos índices se puedan hacer backpatch
 * con alguna etiqueta.
 *
 * Autor: Adrian Ulises Mercado Martínez
*/
bools * gen_cond_rel(char e1[32], char e2[32], int op)
{
    char i[32];
    char i2[32];
    char temp[32];
    strcpy(i, newIndex());
    strcpy(i2, newIndex());
    strcpy(temp, newTemp());

    bools * b = (bools*) malloc(sizeof(bools));
    b->trues = create_list(i);
    b->falses = create_list(i2);

    cuadrupla c, c1, c2;
    
    c.op = op;
    strcpy(c.op1, e1);
    strcpy(c.op2, e2);
    strcpy(c.res, temp);

    c1.op = IFF;
    strcpy(c1.op1, temp);
    strcpy(c1.op2, "GOTO");
    strcpy(c1.res, i);

    c2.op = GOTO;
    strcpy(c2.op1, "");
    strcpy(c2.op2, "");
    strcpy(c2.res, i2);

    insert_cuad(&codigo_intermedio, c);
    insert_cuad(&codigo_intermedio, c1);
    insert_cuad(&codigo_intermedio, c2);

    return b;
}

/*
 * Agrega un elemento a la tabla de símbolos actual.
 * Actualiza las variables necesarias como dir.
 * Verifica las dimensiones y calcula la nueva direccion para
 * tal tabla de símbolos.
 *
 * Autores: Melissa Mendez Servín
 *          Palmerin Morales David Gabriel.
*/
void insert_sym(char id[32], env curr_env, int tipo)
{
    sym symbol;
    strcpy(symbol.id, id);
    symbol.type = tipo;
    symbol.dir  = dir;
    dir += current_dim;
    
    stack_pop(&envs, &curr_env);
    insert(&curr_env.symbols, symbol);
    
    int i = 0;
    int curr_tam = get_tam(&global_types,current_type);
    bool primero = true; 
    while(list_size(&dimensiones)){
        int temp;
        list_head(&dimensiones,&temp,1);
        type tipo = new_type();
        
        if(primero)
        {
            tipo.base = symbol.type;
            primero = false;
        } 
        else tipo.base = curr_env.types.count -1;

        tipo.dim = temp;
        curr_tam *= tipo.dim;
        tipo.tam = curr_tam;
        
        int r = insert_type(&curr_env.types,tipo);    
    }
    primero = false;    
    list_destroy(&dimensiones);
    list_new(&dimensiones, 10,NULL);
    
    stack_push(&envs, &curr_env);
    //if(struct_decl) struct_dim += current_dim;
}

/*
 * Verifica el tipado de los argumentos de una función.
 * Cada función tiene su definición de qué argumentos recibe y en qué orden.
 * Al momento de realizar una llamada se debe verificar que estos argumentos
 * coincidan con el tipo especificado en su definición.
 * En caso de no coincidir, entonces se considera como error y se avisa al programador.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
int check_args_types(funrec *rec, exp expr)
{
    if (rec->counter < rec->params)
    {
        int i = rec->counter;
        int tipo = rec->context->symbols[i].type;
        fprintf(producciones,"func %s", expr.dir);
        if (tipo != expr.type)
        {
            char *msg = (char*) malloc(sizeof(char*));
            sprintf(msg, "Argumentos no compatibles en la función %s: %s es de tipo %d y se esperaba de tipo %d", curr_function, expr.dir, expr.type, tipo);
            yyerror(msg);
            return -1;
        }
        rec->counter++;
    }
    else
    {
        yyerror2("Se encontraron más argumentos de los esperados en el identificador", rec->id);
        return -1;
    }
    return 0;
}
