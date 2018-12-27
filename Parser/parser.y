%{
/* 
 * File:   parser.y
 * Autor: Melissa y Palmi
 * Diciembre de 2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "attributes.h"
#include "intermediate_code.h"
#include "backpatch.h"
#include "symtab.h"
#include "stack.h"


extern int yylex();
extern int yylineno;

/* Ouput files */
FILE *contexts;

/* Funciones para el manejo de errores */
void yyerror2(char*, char*);
void yyerror(char *);

/* Variable para el conteo de direcciones */
int dir=0;

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

/* Variable para el unico atributo heredado de sentencia prima*/
labels lfalses;

/* Variable para la tabla de símbolos*/
symtab global_symbols;

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

/* Pila de tablas de símbolos para cada contexto. */
stack envs;

exp suma(exp e1, exp e2);
exp resta(exp e1, exp e2);
exp multiplicacion(exp e1, exp e2);
exp division(exp e1, exp e2);
exp get_numero(numero);
exp identificador(char *);
exp asignacion(char *id, exp e);

void gen_cond_goto(char dir[32]);
void gen_cond_rel(char e1[32], char e2[32], char dir[32], int op);

/* Funciones auxiliares para la comprobación de tipos */
int max_type(int t1, int t2);
char *ampliar(char *dir, int t1, int t2);
char *reducir(char *dir, int t1, int t2);


/* Funciones para generar temporales, etiquetas e indices */
char *newTemp();
char *newLabel();
char *newIndex();

%}

%code requires{
    typedef struct _bools{
        labels trues;
        labels falses;
    } bools;
}

%union{   
    int    rel;
    char   id[32];
    char*  car;
    char*  cadena;   
    exp    expr;
    type   tipo;
    numero num;
    labels siguientes;
    bools  *booleans;

    struct{
        labels siguientes;
        bool ifelse;
    } siguientesp;
}

%token<car> CAR
%token<id> ID  
%token<cadena> CADENA
%token<num> NUMERO  
%token TRUE FALSE
%token INT FLOAT DOUBLE VOID STRUCT CHAR
%token WHILE SWITCH FOR DO IF
%token RETURN FUNC 
%token COM PYC PUNES DOT
%token BREAK CASE DEFAULT
%token PRINT
%token NL
%token LKEY RKEY

%right ASIG
%left OR AND
%left IGUAL DIF
%left MAYOR MENOR MAYOR_IGUAL MENOR_IGUAL
%left MAS MENOS
%left MUL DIV MOD
%right NOT
%nonassoc LPAR RPAR LKEY RKEY LCOR RCOR
%left ELSE
%left IFX 


%type<tipo> tipo
%type<booleans> condicion
%type<siguientes> sentencia sentencias
%type<siguientesp> sentif
%type<expr> expresion parte_izq
%type<rel> relacional

%start programa

%%

programa:       { init(); }
            decl 
                { 
                    /* Guardamos la tabla más global. */
                    stack_peek(&envs, &global_symbols);
                }
            condicion
            funciones   {
                            print_context("Contexto global", "");
                            printf("programa -> decl funciones\n");
                            
                            finish();
                        };

decl :      tipo    {   
                        current_type = $1.type; 
                        current_dim  = $1.dim;
                    }      
            lista PYC decl {
                                printf("decl -> tipo lista PYC decl\n");
                            }
            | %empty {};

tipo:        VOID   {    
                        $$.type = 0;
                        $$.dim  = 0;
                        printf("tipo -> VOID\n");
                    }
            | CHAR {
                        $$.type = 1;
                        $$.dim  = 1;
                        printf("tipo -> CHAR\n");
                    }
            | INT   {
                        $$.type = 2;
                        $$.dim = 4;
                        printf("tipo -> INT\n");
                    }
            | FLOAT {
                        $$.type = 3;
                        $$.dim = 4;
                        printf("tipo -> FLOAT\n");
                    }
            | DOUBLE{
                        $$.type = 4;
                        $$.dim = 8;
                        printf("tipo -> DOUBLE\n");
                    }
            | STRUCT{   
                        struct_decl = true;
                        add_context(false);
                    }
                LKEY decl RKEY {
                                    $$.type = 5;
                                    $$.dim  = struct_dim;
                                    printf("tipo -> struct { decl }\n");
                                    del_context(false);
                                };

lista :     lista 
            COM 
            ID  
            arreglo
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $3) != -1)
                    {
                        yyerror2("[ERROR] Ya existe un identificador con el nombre", $3);
                        return 1;
                    }                


                    if (current_type == 5)
                    {
                        yyerror("[ERROR] Struct solo puede tener un identificador.");
                        return 1;
                    }                    

                    sym symbol;
                    strcpy(symbol.id, $3);
                    symbol.type.type = current_type;
                    symbol.type.dim = current_dim;
                    symbol.dir  = dir;
                    dir += current_dim;
                    
                    stack_pop(&envs, &curr_env);
                    insert(&curr_env.symbols, symbol);
                    stack_push(&envs, &curr_env);
                    if (struct_decl)
                        struct_dim += current_dim;
                 
                    printf("lista -> lista , id arreglo\n");}
            
            | ID 
              arreglo
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) != -1)
                    {
                        yyerror2("[ERROR] Ya existe un identificador con el nombre", $1);
                        return 1;
                    }                

                    sym symbol;
                    strcpy(symbol.id, $1);
                    symbol.type.type = current_type;
                    symbol.type.dim = current_dim;
                    symbol.dir  = dir;

                    dir += current_dim;
                    stack_pop(&envs, &curr_env);
                    insert(&curr_env.symbols, symbol);
                    stack_push(&envs, &curr_env);
                    if (current_type != 5 && struct_decl)
                        struct_dim += current_dim;
                    printf("lista- >id arreglo\n");
                };

arreglo : LCOR NUMERO RCOR arreglo {
            current_dim *= atoi($2.val);
            printf("arreglo -> id arreglo\n");}
            | %empty {};

funciones : FUNC 
            tipo ID LPAR
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (search(&curr_env.symbols, $3) != -1)
                    {
                        yyerror2("[ERROR] Ya se ha definido anteriormente el identificador", $3);
                        return 1;
                    }
                    add_context(true);
                    func_decl = true;
                }
             argumentos 
             RPAR LKEY  decl sentencias RKEY 
                {
                    print_context("Contexto local de: ", $3);

                    int func_tam = dir;
                    del_context(false);
                    
                    env curr_env;
                    stack_pop(&envs, &curr_env);

                    /* Agregamos el nombre de la función al contexto
                        donde se puede llamar. */
                    sym symbol;
                    strcpy(symbol.id, $3);
                    symbol.type = $2;
                    symbol.dir = dir;
                    dir += func_tam;

                    insert(&curr_env.symbols, symbol);
                    stack_push(&envs, &curr_env);

                    global_symbols = curr_env.symbols;
                    func_decl = false;
                }
             funciones 
                {printf("funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
            | %empty    {
                            if (!exists_main())
                                return 1;
                        };

argumentos : lista_args 
                        {
                            printf("argumentos -> lista_args\n");
                        }
            | %empty {};

lista_args : lista_args COM tipo ID parte_arr 
                {
                    /* Verifica si existe el ID en el contexto actual o el padre. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $4) != -1)
                    {
                        yyerror2("[ERROR] Ya se ha definido anteriormente el identificador", $4);
                        return 1;
                    }
                    printf("lista_args -> lista_args , tipo id parte_arr\n");
                }
            | tipo ID parte_arr 
                    {
                        /* Verifica si existe el ID en el contexto actual o el padre. */
                        env curr_env;
                        stack_peek(&envs, &curr_env);
                        if (depth_search(&curr_env.symbols, $2) != -1)
                        {
                            yyerror2("[ERROR] Ya se ha definido anteriormente el identificador", $2);
                            return 1;
                        }
                        printf("lista_args -> tipo id parte_arr\n");
                    }

parte_arr : LCOR RCOR parte_arr 
            {printf("parte_arr -> [] parte_arr\n");}
            | %empty {};

sentencias : sentencias sentencia {printf("sentencias -> sentencias sentencia\n");}
            | sentencia {printf("sentencias -> sentencia\n");};

sentif: ELSE sentencia | %empty{};

sentencia :  IF LPAR condicion RPAR 
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&$3->trues));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                }
             sentencia
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&$3->falses));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                }
              sentif
                
            | WHILE LPAR condicion RPAR sentencias 
                {
                    printf("sentencias -> while ( condicion ) sentencias\n");
                }
            | DO sentencias WHILE LPAR condicion RPAR PYC
                {
                    printf("sentencia -> do sentencias while ( condicion) ;\n"); 
                } 
            | FOR LPAR sentencia PYC condicion PYC sentencia RPAR sentencias
                {
                    printf("sentencia -> for ( sentencia ; condicion; sentencia ) sentencias\n");
                }
            | parte_izq ASIG expresion PYC
                {   
                    /*int compatible = max_type($1.type.type, $3.type.type);
                    if(compatible == -1) 
                        yyerror("Error: No se puede asignar, tipos incompatibles.");
                    else {*/
                        cuadrupla cuad;
                        cuad.op  = AS;
                        strcpy(&cuad.res, $1.dir);
                        strcpy(&cuad.op1, $3.dir);
                        insert_cuad(&codigo_intermedio, cuad);
                        printf("sentencia -> parte_izq = expresion\n");
                    //}
                }
            | RETURN expresion PYC
                {
                    printf("sentencia -> return expresion ;\n");
                }
            | RETURN PYC
                {
                    printf("sentencia -> return ;\n");
                }
            | LKEY sentencias RKEY
                {
                    printf("sentencia -> { sentencias }\n");
                }
            | SWITCH LPAR expresion RPAR LKEY casos predeterm RKEY
                {
                    printf("sentencia -> switch ( expresion ) { casos prederterm} \n");
                }
            | BREAK PYC 
                {
                    printf("sentencia -> break ;\n");
                }
            | PRINT expresion PYC 
                {
                    printf("sentencia -> print expresion ;\n");
                }
            ; 

casos : CASE PUNES NUMERO sentencia casos
        {printf("casos -> case : sentencia casos\n");}
            | %empty {};

predeterm : DEFAULT PUNES sentencia
            {printf("predeterm -> default : sentencia\n");}
            | %empty {};

parte_izq : ID  {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se ha declarado la variable", $1);
                        return 1;
                    }
                    strcpy($$.dir, $1);
                    $$.type = get_type(&curr_env.symbols, $1);
                    printf("parte_izq -> id\n");
                }
            | var_arreglo 
                {
                    printf("parte_izq -> var_arreglo\n");
                }
            | ID DOT ID 
                {
                    printf("parte_izq -> id.id\n");
                }

var_arreglo : ID LCOR expresion RCOR {printf("var_arreglo -> id [ expresion ] \n");}
            | var_arreglo LCOR expresion RCOR {printf("var_arreglo -> var arreglo [ expresion ]\n");};

expresion:   expresion  
             MAS expresion 
                {
                    char *t = (char*) malloc(32 * sizeof(char));
                    strcpy(t, newTemp());
                    strcpy($$.dir, t);
                    int max = max_type($1.type.type,$3.type.type);
                    if(max==-1) 
                        yyerror("Error: Tipos incompatibles.");
                    else{
                        cuadrupla cuad;
                        cuad.op = MA;
                        strcpy(cuad.res, $$.dir);
                        strcpy(cuad.op1, $1.dir);
                        strcpy(cuad.op2, $3.dir);
                        insert_cuad(&codigo_intermedio, cuad);
                        printf("expresion -> expresion + expresion \n");
                    }
                }
            | expresion MENOS expresion 
                {
                    /* Análogo a suma. */
                    printf("expresion -> expresion - expresion \n");
                }
            | expresion MUL expresion
                {
                    /* Análogo a suma. */
                    printf("expresion -> expresion * expresion \n");
                }
            | expresion DIV expresion
                {
                    /* Análogo a suma. */
                    printf("expresion -> expresion / expresion \n");
                }
            | expresion MOD expresion
                {
                    /* Análogo a suma. */
                    printf("expresion -> expresion mod expresion \n");
                }
            | var_arreglo
                {
                    printf("expresion -> var_arreglo\n");
                }
            | CAR 
                {   
                    strcpy($$.dir, $1);
                    printf("expresion -> car %s\n", $1);
                }
            | CADENA 
                {
                    printf("expresion -> cadena %s\n", $1);
                }
            | NUMERO 
                {   $$.type.type = $1.type;
                    strcpy($$.dir, $1.val);
                    printf("expresion -> num %s\n", $1.val);
                }
            | ID     
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se encontró el identificador", $1);
                        return 1;
                }
                }                     
                LPAR parametros RPAR 
                {   
                    strcpy($$.dir, $1);
                    //Buscar tipo $1.type?
                    printf("expresion -> id %s ( parametros )\n", $1);
                }
            ;

parametros: lista_param {printf("parametros-> lista_param\n");}
            | %empty {};

lista_param: lista_param COM expresion 
            {printf("lista_param -> lista_param , expresion\n");}
            | expresion {printf("lista_param -> expresion\n");};

condicion:  condicion OR 
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&$1->falses));
                    insert_cuad(&codigo_intermedio, cuad);
                 } 
            condicion    
                {
                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&$1->falses, label, &codigo_intermedio);
                    $$ = (bools*) malloc(sizeof(bools));
                    $$->trues = merge(&$1->trues, &$4->trues);
                    $$->falses = $4->falses;

                    printf("CURRRENT LABEEEEEEELS");
                    print_list_labels(&$$->trues);
                    print_list_labels(&$$->falses);
                    printf("condicion -> condicion && condicion \n");
                 }
            | condicion AND 
                {
                    /*
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first($1.falses));
                    insert_cuad(&codigo_intermedio, cuad);
                    */
                }
              condicion     
                {
                    /*
                    char label[32];
                    strcpy(label, newLabel());
                    $$.falses = merge(&$1.falses, &$4.falses);
                    $$.trues = $4.trues;
                    backpatch(&$1.trues, label, &codigo_intermedio);
                    printf("condicion -> condicion && condicion \n");
                    */
                }
            | NOT condicion 
                {   
                    /*
                    $$.falses = $2.trues;
                    $$.trues  = $2.falses;
                    printf("condicion -> ! condicion \n");
                    */
                }
            | LPAR condicion RPAR 
                {
                    /*
                    $$.trues = $2.trues;
                    $$.falses = $2.falses;
                    */
                }
            | expresion relacional expresion
                {
                    //Falta ver sus tipooooooooooooooooooos.
                    printf("condicion -> expresion rel expresion \n");
                }
            | TRUE 
                {   
                    $$ = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    $$->trues = create_list(dir);
                    gen_cond_goto(dir);
                    printf("condicion -> true \n");
                }
            | FALSE 
                {  
                    $$ = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    $$->falses = create_list(dir);
                    gen_cond_goto(dir);
                    printf("condicion -> false \n");
                }
            | %empty {} ;    

relacional: MAYOR { $$ = GT; printf("rel-> >\n"); }
          | MENOR { $$ = LT; printf("rel->  <\n");}
          | MAYOR_IGUAL { $$ = GE; printf("rel->  >=\n");}
          | MENOR_IGUAL { $$ = LE; printf("rel->  <=\n");}
          | DIF { $$ = NE; printf("rel->  !=\n");}
          | IGUAL { $$ = EQ; printf("rel->  ==\n");};
%%

void yyerror(char *s){
    printf("%s: en la línea %d\n",s, yylineno);
}

void yyerror2(char *s, char *n){
    printf("%s %s: en la línea %d\n",s, n, yylineno);
}

void init()
{
    create_code(&codigo_intermedio);
    create_labels(&etiquetas);

    stack_new(&envs, sizeof(symtab) + sizeof(stack), NULL);
    symtab sym_tab;
    create_table(&sym_tab, NULL);
    sym_tab.parent = NULL;

    stack exprs;
    stack_new(&exprs, 32 * sizeof(char), NULL);

    env initial_env;
    initial_env.symbols = sym_tab;
    initial_env.exprs   = exprs;

    stack_push(&envs, &initial_env);
}

void finish()
{
    print_code(&codigo_intermedio);
}

void print_context(char *s1, char *s2)
{
    env curr_env;
    stack_peek(&envs, &curr_env);
    fprintf(contexts, "~ %s %s\n", s1, s2);
    fprint_table(&curr_env.symbols, contexts);
    fprintf(contexts, "\n");
}

void add_context(bool func_context)
{
    /* Guardamos la última dirección usada en el ambiente actual. */
    env curr_env;
    stack_pop(&envs, &curr_env);
    curr_env.symbols.last_dir = dir;
    stack_push(&envs, &curr_env);

    /* Nueva tabla de símbolos. */
    symtab new_symtab;
    if (func_context)
        create_table(&new_symtab, &global_symbols);
    else
        create_table(&new_symtab, NULL);


    /* Nueva pila para expresiones. */
    stack exprs;
    stack_new(&exprs, 32 * sizeof(char), NULL);

    /* Finalmente, creamos el nuevo ambiente. */
    env my_env;
    my_env.symbols = new_symtab;
    my_env.exprs = exprs;

    stack_push(&envs, &my_env);
    dir = 0;
}

void del_context(bool print_context)
{
    env curr_env;
    stack_pop(&envs, &curr_env);
    if (print_context)
    {
        print_table(&curr_env.symbols);
    }

    if (stack_size(&envs) > 0)
    {   
        stack_peek(&envs, &curr_env);
        dir = curr_env.symbols.last_dir;
    }
}

char* newTemp(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

char* newLabel(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

char* newIndex(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
}

bool exists_main()
{
    int index = global_symbols.count - 1;
    if (index >= 0)
    {
        sym symbol = global_symbols.symbols[index];
        if (strcmp(symbol.id, "main") != 0)
        {
            yyerror("[ERROR] No se encontró la declaración de la función main");
            return false;
        }
    }
    return true;
}

int max_type(int t1, int t2){
    if (t1 == t2) return t1;
    else {
        /*Si son ambos números. */
        if (t1 > 1 && t1 < 5 && 
            t2 > 1 && t2 < 5) 
            if (t1 < t2) return t2;
            else
            {
                return t1;
            } 
        /*Si no son números -> tipos incompatibles.
         Por ahora no se pude hacer int a char*/    
        return -1;
    } 
}

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

void gen_cond_rel(char e1[32], char e2[32], char dir[32], int op)
{
    char *t = (char*) malloc(32 * sizeof(char));
    strcpy(t, newTemp());
    
    cuadrupla cuad;
    cuad.op = op;
    strcpy(cuad.op1, e1);
    strcpy(cuad.op2, e2);
    strcpy(cuad.res, t);
    insert_cuad(&codigo_intermedio, cuad);

    cuadrupla iff;
    iff.op  = IFF;
    strcpy(iff.op1, t);
    strcpy(iff.res, dir);
    insert_cuad(&codigo_intermedio, iff);
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


-- Esto lo reconoce el lexer.
sentif : sentencias ELSE sentencias
        {printf("sentif -> else sentencias\n");}
        | sentencias;
*/