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
int label;
int temp;
int indice;

/* Variable para el unico atributo heredado de sentencia prima*/
labels lfalses;

/* Variable para la tabla de símbolos*/
symtab global_symbols;

/* Variable papra guardar el código intermedio que se va generando */
ic codigo_intermedio;


/* Funciones auxiliares al análisis semántico y generación de código intermedio */
void init();
void finish();
void add_context(bool func_context);
void del_context(bool context);
bool exists_main();
void print_context(char *s1, char *s2);

/* Pila de tablas de símbolos para cada contexto. */
stack envs;

exp math_function(exp e1, exp e2,int op);
exp resta(exp e1, exp e2);
exp multiplicacion(exp e1, exp e2);
exp division(exp e1, exp e2);
exp get_numero(numero);
exp identificador(char *);
void asignar(exp e1,exp e2);

/* Funciones auxiliares para la comprobación de tipos */
int max_type(int t1, int t2);
char *ampliar(char *dir, int t, int w);
char *reducir(char *dir, int t, int w);


/* Funciones para generar temporales, etiquetas e indices */
char *newTemp();
char *newLabel();
char *newIndex();

%}

%union{   
    char   id[32];
    //char   dir[32];
    char*  car;
    char*  cadena;   
    exp    expr;
    type   tipo;
    numero num;
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
%type<siguientes> sentencia sentencias
%type<expr> expresion parte_izq
%type<bools> condicion


%start programa

%%

programa:       { init(); }
            decl 
                { 
                    /* Guardamos la tabla más global. */
                    stack_peek(&envs, &global_symbols);
                }
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
                    printf("lista- >id arreglo\n");};

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

sentif : sentencias ELSE sentencias
        {printf("sentif -> else sentencias\n");}
        | sentencias;

sentencia :  IF LPAR condicion RPAR sentif
                {
                    printf("sentencia -> if ( condicion ) sentencias sentif\n");
                }
            | WHILE LPAR condicion RPAR sentencias 
                {
                    printf("sentencias -> while ( condicion ) sentencias\n");
                }
            | DO sentencias WHILE LPAR condicion RPAR PYC
                {
                    printf("sentencias -> do sentencias while ( condicion) ;\n"); 
                } 
            | FOR LPAR sentencia PYC condicion PYC sentencia RPAR sentencias
                {
                    printf("sentencias -> for ( sentencia ; condicion; sentencia ) sentencias\n");
                }
            | parte_izq ASIG expresion PYC
                {   
                    int max = max_type($1.type.type, $3.type.type);
                    if(max == -1) 
                        yyerror("Error: No se puede asignar, tipos incompatibles.");
                    else 
                    {
                        asignar($1,$3);
                        printf("sentencias -> parte_izq = expresion\n");
                    }
                }
            | RETURN expresion PYC
                {
                    printf("sentencias -> return expresion ;\n");
                }
            | RETURN PYC
                {
                    printf("sentencias -> return ;\n");
                }
            | LKEY sentencias RKEY
                {
                    printf("sentencias -> { sentencias }\n");
                }
            | SWITCH LPAR expresion RPAR LKEY casos predeterm RKEY
                {
                    printf("sentencias -> switch ( expresion ) { casos prederterm} \n");
                }
            | BREAK PYC 
                {
                    printf("sentencias -> break ;\n");
                }
            | PRINT expresion PYC 
                {
                    printf("sentencias -> print expresion ;\n");
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
                    $$ = math_function($1,$3,MA);
                    printf("expresion -> expresion + expresion \n");
                }
            | expresion MENOS expresion 
                {
                    $$ = math_function($1,$3,MEN);
                    printf("expresion -> expresion - expresion \n");
                }
            | expresion MUL expresion
                {
                    $$ = math_function($1,$3,ML);
                    printf("expresion -> expresion * expresion \n");
                }
            | expresion DIV expresion
                {
                    $$ = math_function($1,$3,DV);
                    printf("expresion -> expresion / expresion \n");
                }
            | expresion MOD expresion
                {
                    $$ = math_function($1,$3,MD);
                    printf("expresion -> expresion mod expresion \n");
                }
            | var_arreglo
                {
                    printf("expresion -> var_arreglo\n");
                }
            | CAR 
                {   
                    $$.type.type = 1;
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
                LPAR parametros RPAR 
                {   
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se encontró el identificador", $1);
                        return 1;
                    }
                    strcpy($$.dir, $1);
                    $$.type = get_type(&curr_env.symbols, $1); 
                    printf("expresion -> id %s ( parametros )\n", $1);
                }
            ;

parametros: lista_param {printf("parametros-> lista_param\n");}
            | %empty {};

lista_param: lista_param COM expresion 
            {printf("lista_param -> lista_param , expresion\n");}
            | expresion {printf("lista_param -> expresion\n");};

condicion: condicion OR condicion  
            {printf("condicion -> condicion || condicion \n");}
            | condicion AND condicion 
            {printf("condicion -> condicion && condicion \n");}
            | NOT condicion 
            {printf("condicion -> ! condicion \n");}
            | LPAR condicion RPAR 
            {printf("condicion -> ( condicion ) \n");}
            | expresion relacional expresion
            {printf("condicion -> expresion rel expresion \n");}
            | TRUE {printf("condicion -> true \n");}
            | FALSE {printf("condicion -> false\n");}; 

relacional: MAYOR {printf("rel-> >\n");}
          | MENOR {printf("rel->  <\n");}
          | MAYOR_IGUAL {printf("rel->  >=\n");}
          | MENOR_IGUAL {printf("rel->  <=\n");}
          | DIF {printf("rel->  !=\n");}
          | IGUAL {printf("rel->  ==\n");};
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
    printf("TIPO 1: %d, TIPO 2: %d\n",t1,t2);
    if (t1 == t2) return t1;
    else {
        /*Si son ambos números. */
        if (t1 > 1 && t1 < 5 && 
            t2 > 1 && t2 < 5) 
            if (t1 < t2) return t2;
            else return t1;
        /*Si no son números -> tipos incompatibles.
         Por ahora no se pude hacer int a char*/    
        return -1;
    } 
}

/* Asina a e1 el valor de la dirección de e2*/
void asignar(exp e1, exp e2){
    cuadrupla cuad;
    cuad.op  = AS;
    strcpy(&cuad.res, e1.dir);
    int t1 = e1.type.type;
    int t2 = e2.type.type;
    if(t1 <= t2) strcpy(&cuad.op1, reducir(e2.dir,t2,t1));
    else strcpy(&cuad.op1,ampliar(e2.dir,t2,t1));
    insert_cuad(&codigo_intermedio, cuad);
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
            printf("Pérdida de información, se está asignando un float a un int.\n");
            return temp; 
        }        
        if(t == 4){ //un double
            printf("Pérdida de información, se está asignando un double a un int.\n");
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
            printf("Pérdida de información, se está asignando un double a un float.\n");
            return temp; 
        }        
    }
    printf("Error: Esto no debería ocurrir\n");
              
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
    printf("Error: Esto no debería ocurrir\n");
}

/* Te devuelve la expresión correspondiente a la operación
    dada y lo traduce a código intermedio. */
exp math_function(exp e1, exp e2, int op){
    exp e;
    int max = max_type(e1.type.type,e2.type.type);
    e.type.type = max;
    if(max==-1) 
        yyerror("Error: Tipos incompatibles.");
    else{
        char *t = (char*) malloc(32 * sizeof(char));
        strcpy(t, newTemp());
        strcpy(e.dir, t);
        cuadrupla cuad;
        cuad.op = op;
        strcpy(cuad.res, e.dir);
        strcpy(cuad.op1, ampliar(e1.dir,e1.type.type,max));
        strcpy(cuad.op2, ampliar(e2.dir,e2.type.type,max));
        insert_cuad(&codigo_intermedio, cuad);
        }
    return e;
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