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

/* Varaibles para contar las temporales, etiquetas e indices */
int label;
int temp;
int indice;

/* Variable para el unico atributo heredado de sentencia prima*/
labels lfalses;

/* Variable para la tabla de símbolos*/
// symtab tabla_de_simbolos;

/* Variable papra guardar el código intermedio que se va generando */
ic codigo_intermedio;


/* Funciones auxiliares al análisis semántico y generación de código intermedio */
void init();
void finish();
void add_context();
void del_context(bool context);

/* Pila de tablas de símbolos para cada contexto. */
stack envs;

exp suma(exp e1, exp e2);
exp resta(exp e1, exp e2);
exp multiplicacion(exp e1, exp e2);
exp division(exp e1, exp e2);
exp get_numero(numero);
exp identificador(char *);
exp asignacion(char *id, exp e);

/* Funciones auxiliares para la comprobación de tipos */
int max_type(int t1, int t2);
char *ampliar(char *dir, int t1, int t2);
char *reducir(char *dir, int t1, int t2);


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

programa:   { init(); }
            decl 
            funciones   {
                            env curr_env;
                            stack_peek(&envs, &curr_env);

                            print_table(&curr_env.symbols);    
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
                        add_context();
                    }
                LKEY decl RKEY {
                                    $$.type = 5;
                                    $$.dim  = struct_dim;
                                    printf("tipo -> struct { decl }\n");
                                    del_context(true);
                                };

lista :     lista 
            COM 
            ID  
            arreglo
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (search(&curr_env.symbols, $3) != -1)
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
                    if (search(&curr_env.symbols, $1) != -1)
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

funciones : FUNC tipo ID LPAR argumentos RPAR LKEY  decl sentencias RKEY funciones {printf("funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
            | %empty {};

argumentos : lista_args {printf("argumentos -> lista_args\n");}
            | %empty {};

lista_args : lista_args COM tipo ID parte_arr {printf("lista_args -> lista_args , tipo id parte_arr\n");}
            | tipo ID parte_arr {printf("lista_args -> tipo id parte_arr\n");}

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
                    int compatible = max_type($1.type.type, $3.type.type);
                    if(compatible == -1) 
                        yyerror("Error: No se puede asignar, tipos incompatibles.");
                    else {
                        cuadrupla cuad;
                        cuad.op  = AS;
                        strcpy(&cuad.res, $1.dir);
                        strcpy(&cuad.op1, $3.dir);
                        insert_cuad(&codigo_intermedio, cuad);
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
                    if (search(&curr_env.symbols, $1) == -1)
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
            | ID LPAR parametros RPAR 
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
    create_table(&sym_tab);

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

void add_context()
{
    /* Guardamos la última dirección usada en el ambiente actual. */
    env curr_env;
    stack_pop(&envs, &curr_env);
    curr_env.symbols.last_dir = dir;
    stack_push(&envs, &curr_env);

    /* Nueva tabla de símbolos. */
    symtab new_symtab;
    create_table(&new_symtab);

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
        printf("\n~ Tabla de Símbolos:\n");
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

int max_type(int t1, int t2){
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