%{
/* 
 * Analizador Semántico.
 * Autores: Mendez Servin Melissa.
 *          Palmerin Morales David Gabriel.
 *
 * Github: https://github.com/DavidPalmerin/Proyecto-Compiladores
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
int  struct_backup = 0;

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
env    struct_env;

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
char * get_type_gen(int t);

/* Funciones para generar temporales, etiquetas e indices */
char *newTemp();
char *newLabel();
char *newIndex();

%}

%union{   
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
%type<cases> casos
%type<siguientes> sentencia sentencias
%type<siguientesp> sentif
%type<expr> expresion parte_izq var_arreglo
%type<rel> relacional
%type<args> parametros

%start programa

%%

programa:       { init(); }
            decl 
                { 
                    /* Guardamos la tabla más global. */
                    env my_env;
                    stack_peek(&envs, &my_env);
                    global_symbols = my_env.symbols;
                    global_types = my_env.types;

                }
            funciones   {
                            print_context("Contexto global", "");
                            fprintf(producciones,"programa -> decl funciones\n");
                            finish();
                        };

decl :      tipo    {   
                        current_type = $1;
                        current_dim = get_tam(&global_types,$1);
                        struct_dim = 0;
                    }      
            lista PYC decl {
                                fprintf(producciones,"decl -> tipo lista PYC decl\n");
                            }
            | %empty {};

tipo:        VOID   {    
                        $$ = 0;
                        fprintf(producciones,"tipo -> VOID\n");
                    }
            | CHAR {
                        $$ = 1;
                        fprintf(producciones,"tipo -> CHAR\n");
                    }
            | INT   {
                        $$ = 2;
                        fprintf(producciones,"tipo -> INT\n");
                    }
            | FLOAT {
                        $$ = 3;
                        fprintf(producciones,"tipo -> FLOAT\n");
                    }
            | DOUBLE{
                        $$ = 4;
                        fprintf(producciones,"tipo -> DOUBLE\n");
                    }
            | STRUCT{   
                        struct_decl = true;
                        add_context(false);
                    }
                LKEY decl RKEY {
                                    $$ = 5;
                                    fprintf(producciones,"tipo -> struct { decl }\n");
                                    //del_context(false);
                                };

lista :     lista 
            COM 
            ID  
            arreglo
                {
                    /* Verificamos la existencia del identificador. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $3) != -1)
                    {
                        yyerror2("Ya existe un identificador con el nombre", $3);
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
                        if (current_type == 5)
                        {   
                            int last_dir = dir;
                            symtab *syms = (symtab*) malloc(sizeof(symtab));
                            *syms = struct_env.symbols;
                            symbol.struct_content = syms;
                            symbol.dir = dir;
                            dir += struct_dim;
                        }
                        else{
                            symbol.dir = dir;
                            dir += current_dim;
                        }
                        strcpy(symbol.id, $3);
                        symbol.type = current_type;

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

                        if (struct_decl && current_dim >= 0){
                            struct_dim += current_dim;
                        }
                        
                        fprintf(producciones,"lista -> lista , id arreglo\n");}
                }
            | ID 
              arreglo
                {
                    /*Verifica la existencia del identificador. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) != -1)
                    {
                        yyerror2("Ya existe un identificador con el nombre", $1);
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
                            struct_dim = dir;
                            stack_peek(&envs, &struct_env);
                            symtab *syms = (symtab*) malloc(sizeof(symtab));
                            *syms = struct_env.symbols;
                            symbol.struct_content = syms;
                            struct_dim = last_dir;
                            del_context(false);
                            symbol.dir = top_dir;
                        }
                        else {
                            symbol.dir = dir;
                            dir += current_dim;
                        }
                        strcpy(symbol.id, $1);
                        symbol.type = current_type;

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

                        if (struct_decl && current_dim >= 0){
                            struct_dim += current_dim;
                        }

                        fprintf(producciones,"lista- >id arreglo\n");
                    }
                };

arreglo : LCOR NUMERO RCOR arreglo 
            {   
 	       if (current_type == 5){
	       	    fail_decl = true;
		    yyerror("No puedes asignar un arreglo como identificador a un struct");
	       } 
               if ($2.type == 2){
                    int num = atoi($2.val);
                    current_dim *= num;
                    list_append(&dimensiones, &num);
                    fprintf(producciones,"arreglo -> id arreglo\n");
                }
                else{ 
                    fail_decl = true;
                    yyerror("[ERROR ] La dimensión del arreglo se debe indicar con un entero.");
                };
                
            }
            | %empty 
                {
                    
                };

funciones : FUNC 
            tipo ID LPAR
                {
                    /* Asigna etiquetas a las funciones. */
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, $3);
                    insert_cuad(&codigo_intermedio, cuad);

                    /* Verifica el id de la función. 
                        Crea un contexto nuevo en la pila si el id es válido.
                    */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (search(&curr_env.symbols, $3) != -1)
                    {
                        yyerror2("Ya se ha definido anteriormente el identificador", $3);
                        imprime_ci = false;
                        fail_decl = true;
                    }else{
                            add_context(true);
                            func_decl = true;
                    }
                    return_type = $2;
                }
             argumentos 
             RPAR LKEY  decl sentencias RKEY 
                {
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else 
                    {
                        print_context("Contexto local de: ", $3);

                        /* Elimina el contexto de la función del tope de la pila y guarda el registro
                           de la función */
                        env fun_env;
                        stack_peek(&envs, &fun_env);

                        symtab *func_context = (symtab*) malloc(sizeof(symtab));
                        *func_context = fun_env.symbols;

                        funrec reg;
                        strcpy(reg.id, $3);
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
                        strcpy(symbol.id, $3);
                        symbol.type = $2;
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
             funciones 
                {fprintf(producciones,"funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
            | %empty    {
                            /* Verifica que la última función definida sea main. */
                            if (!exists_main())
                              return 1;
                            //print_funtable(&global_funcs);
                            num_params = 0;
                        };

argumentos : lista_args 
                        {
                           fprintf(producciones,"argumentos -> lista_args\n");
                        }
            | %empty {};

lista_args : lista_args COM tipo ID parte_arr 
                {
                    /* Verifica si existe el ID en el contexto actual o el padre. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $4) != -1)
                    {
                        yyerror2("Ya se ha definido anteriormente el identificador", $4);
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else 
                    {
                    insert_sym($4, curr_env, $3);

                    /* Variable para funciones. */
                    num_params += 1;
                    }
                    fprintf(producciones,"lista_args -> lista_args , tipo id parte_arr\n");
                }
            | tipo ID parte_arr 
                    {
                        /* Verifica si existe el ID en el contexto actual o el padre. */
                        env curr_env;
                        stack_peek(&envs, &curr_env);
                        if (depth_search(&curr_env.symbols, $2) != -1)
                        {
                            yyerror2("Ya se ha definido anteriormente el identificador", $2);
                            fail_decl = true;
                        }
                        
                        if(fail_decl){
                            fail_decl = false;
                            imprime_ci = false;
                        }
                        else{
                        insert_sym($2, curr_env, $1);

                        /* Variable para funciones. */
                        num_params += 1;
                        }
                        fprintf(producciones,"lista_args -> tipo id parte_arr\n");

                    }

parte_arr : LCOR RCOR parte_arr 
            {fprintf(producciones,"parte_arr -> [] parte_arr\n");}
            | %empty {};

sentencias : sentencias sentencia 
            {    
                fprintf(producciones,"sentencias -> sentencias sentencia\n");
            }
            | sentencia 
            {
                fprintf(producciones,"sentencias -> sentencia\n");
            };

sentif: ELSE sentencia {
                printf(ANSI_COLOR_RED "No se implementó función if else :(\n" ANSI_COLOR_RESET);
                return -1;
                $$.ifelse = true;
            }
    | %empty {$$.ifelse = false; };

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

                    char label[32], label2[32];
                    strcpy(label, newLabel());
                    strcpy(label2, newLabel());
                    backpatch(&$3->trues, label, &codigo_intermedio);
                    backpatch(&$3->falses, label2, &codigo_intermedio);
                }
            sentif
                
            | WHILE LPAR
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
             condicion
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&$4->trues));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                    
                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&$4->trues, label, &codigo_intermedio);
                }
             RPAR sentencia
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
                    get_first(&$4->falses));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);  

                    char label[32];
                    strcpy(label, newLabel());
                    backpatch(&$4->falses, label, &codigo_intermedio);
                    
                    fprintf(producciones,"sentencia -> while ( condicion) sentencia;\n"); 
                }
            | DO 
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
            sentencia WHILE LPAR condicion RPAR PYC
                {
                    char label[32], label2[32];
                    strcpy(label, pop_label(&lcontrol));
                    strcpy(label2, newLabel());
                    backpatch(&$6->trues, label, &codigo_intermedio);
                    backpatch(&$6->falses, label2, &codigo_intermedio);

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, label2);
                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"sentencia -> do sentencias while ( condicion) ;\n"); 
                } 
            | FOR LPAR sentencia PYC 
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
             condicion PYC
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, 
                    get_first(&$6->trues));
                    insert_cuad(&codigo_intermedio, cuad);
                }
             sentencia RPAR sentencia
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
                    get_first(&$6->falses));
                    insert_cuad(&codigo_intermedio, cuad);

                    char label[32], label2[32];
                    strcpy(label, newLabel());
                    strcpy(label2, newLabel());
                    backpatch(&$6->trues, label2, &codigo_intermedio);
                    backpatch(&$6->falses, label, &codigo_intermedio);

                    fprintf(producciones,"sentencia -> for ( sentencia ; condicion; sentencia ) sentencias\n");
                }

            | parte_izq ASIG expresion PYC
                {                       
                    call_params = 0;
                    if (strcmp($3.dir, "SF") != 0)
                    {
                        int compatible = max_type($1.type, $3.type);
                        if(compatible == -1) {
                            yyerror("No se puede asignar, tipos incompatibles.");
                            imprime_ci = false;
                        }
                        else {
                            asignar($1,$3);
                            fprintf(producciones,"sentencia -> parte_izq = expresion ;\n");
                        }
                    }
                }
            | RETURN expresion PYC
                {
                    if (return_type == 0)
                    {
                        yyerror(" La función no puede regresar argumentos pues es de tipo void");
                        imprime_ci = false;
                    }
                    else if (return_type < 5) 
                    {
                        int compatibles = max_type(return_type, $2.type);
                        if(compatibles == -1){
                            printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "Tipo de regreso incompatible con definición de la función, se está devolviendo un %s pero se espera un %s\n : en la línea %d\n",get_type_gen(return_type), get_type_gen($2.type), yylineno);
                            fprintf(err,"Error: Tipo de regreso incompatible con definición de la función, se está devolviendo un %s pero se espera un %s\n : en la línea %d\n",get_type_gen(return_type), get_type_gen($2.type), yylineno);
                            imprime_ci = false;
                        }
                    }

                    cuadrupla cuad;
                    cuad.op = RET;
                    strcpy(cuad.res, $2.dir);
                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"sentencia -> return expresion ;\n");
                }
            | RETURN PYC
                {
                    if (return_type != 0)
                    {
                        yyerror(" La función debe retornar una expresión");
                        imprime_ci = false;
                    }
                    fprintf(producciones,"sentencia -> return ;\n");
                }
            | LKEY sentencias RKEY
                {
                    char label[32];
                    $$ = $2;
                    strcpy(label, newLabel());
                    backpatch(&$2, label, &codigo_intermedio);
                    fprintf(producciones,"sentencia -> { sentencias }\n");
                }
            | SWITCH LPAR expresion RPAR
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
              LKEY casos predeterm RKEY
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
                        if (sw.link != $7) break;
                        stack_pop(&switchesback, &sw);
                        
                        char arg[32];
                        sprintf(arg, "%s = %s", $3.dir, sw.caso);

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
                    fprintf(producciones,"sentencia -> switch ( expresion ) { casos predeterm} ;\n");
                }
    
            | BREAK PYC 
                {
                    fprintf(producciones,"sentencia -> break ;\n");
                }
            | PRINT expresion PYC 
                {
                    char i[32];
                    strcpy(i, newIndex());
                    $$ = create_list(i);
                    fprintf(producciones,"sentencia -> print expresion ;\n");
                }
            ; 

casos : CASE PUNES NUMERO 
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
                strcpy(sw.caso, $3.val);
                sw.link = switch_call;
                stack_push(&switchesback, &sw);
            }
        sentencias
            {
                char *label = get_top_label(&lcontrol);
                cuadrupla cuad;
                cuad.op = GOTO;
                strcpy(cuad.op1, "");
                strcpy(cuad.op2, "");
                strcpy(cuad.res, label);
                insert_cuad(&codigo_intermedio, cuad);
            }
        casos 
            {   
                $$ = $7; fprintf(producciones, "casos : case : NUMERO sentencias casos");
            }
        | %empty {$$ = switch_call;};

predeterm : DEFAULT PUNES sentencia
            {fprintf(producciones,"predeterm -> default : sentencia\n");}
            | %empty {};

parte_izq : ID  {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("No se ha declarado la variable", $1);
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else{

                        strcpy($$.dir, $1);
                        $$.type = get_type(&curr_env.symbols, $1);
                    }
                    fprintf(producciones,"parte_izq -> id\n");
                }
            | var_arreglo 
                {
                    exp id;
                    strcpy(id.dir,$1.arr);
                    id.type = $1.type;
                    $$ = asignar(id,$1);
                    fprintf(producciones,"parte_izq -> var_arreglo\n");
                }
            | ID DOT ID 
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if(depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("No se ha declarado la variable", $1);
                        fail_decl = true;
                    }

                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else{
                        int type = get_type(&curr_env.symbols, $1);
                        if (type != 5)
                        {
                            yyerror2($1, "no es de tipo struct");
                            imprime_ci = false;
                            /* A fuerzas debe terminar el programa pues genera un segmentation fault. */
                            return -1;
                        }

                        env curr_env;
                        stack_peek(&envs, &curr_env);
                        symtab *struct_content = get_struct_content(&curr_env.symbols, $1);
                        if(depth_search(struct_content, $3) == -1)
                        {   
                            print_table(struct_content);
                            yyerror2("No existe tal atributo en el struct con nombre", $1);
                            fail_decl = true;
                        }
                        if(fail_decl){
                            fail_decl = false;
                            imprime_ci = false;
                        }
                        else{
                            //Asignar dirección.
                            // La direcicón de $1 está en env.symbols (o en parent) y la del atributo está en struct_content.
                            sprintf($$.dir, "%s.%s", $1, $3);
                            $$.type = get_type(struct_content, $3);
                        } 
                    }

                    fprintf(producciones,"parte_izq -> id.id\n");
                }

var_arreglo : ID LCOR expresion RCOR 
            {
                env curr_env;
                stack_peek(&envs, &curr_env);
                if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("No se encontró el identificador", $1);
                        fail_decl = true;
                        return -1;
                    }
                strcpy($$.arr,$1);
                exp base_dir;
                sprintf(base_dir.dir,"%d",get_dir(&curr_env.symbols,$1));
                base_dir.type = 2;
                int curr_type = get_type(&curr_env.symbols,$1);
                if( $3.type != 2)
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

                    exp arr_index = $3;
                    //printf("->> Index: %s\n",arr_index.dir);
                    //printf("->> Tipo base: %d\n",base_type);

                    $$.type = base_type;
                    /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                    dir = base_dir + (index * tam_base) + ...*/
                    //Verificación, solo funciona con números (no expresiones).
                    if(arr_index.dir[0] != 't'){
                        if(atoi(arr_index.dir) < 0 || atoi(arr_index.dir) >=  get_dim(&curr_env.types,curr_type))
                            {
                                char * dim_f = (char*) malloc(32*sizeof(char));
                                sprintf(dim_f,"%d",get_dim(&curr_env.types,curr_type)-1);
                                yyerror2("Fuera de rango, index inávildo, se espera un número entre 0 y el ",dim_f);
                                imprime_ci = false;
                            }
                    }         
                    exp tam_act;
                    tam_act.type = 2;
                    sprintf(tam_act.dir, "%d",get_tam(&curr_env.types,base_type));
                    
                    exp curr_dir = math_function(arr_index,tam_act,ML);

                    strcpy($$.dir,math_function(base_dir,curr_dir,MA).dir);
                    //printf("->> Dir act: %s\n",$$.dir);
                    fprintf(producciones,"var_arreglo -> id [ expresion ] \n");
                    

                }
            }
            | var_arreglo LCOR expresion RCOR 
                { 
                if( $3.type != 2)
                    {
                    yyerror("Para acceder a un arreglo la expresión o número debe ser un entero ");
                    fail_decl = true;
                    }
                env curr_env;
                stack_peek(&envs, &curr_env);
                if($1.type == -1){
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
                        strcpy(base_dir.dir,$1.dir);
                        base_dir.type = 2;

                        //printf("CURR TYPE --->%d\n",$1.type);

                        int base_type = get_base(&curr_env.types,$1.type);

                        exp arr_index = $3;
                        //printf("->> Index: %s\n",arr_index.dir);
                        //printf("->> Tipo base: %d\n",base_type);
                            
                        $$.type = base_type;
                        /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                        dir = base_dir + (index * tam_base) + ...*/
                        //Verificación, solo funciona con números (no expresiones).
                        if(arr_index.dir[0] != 't'){
                            if(atoi(arr_index.dir) < 0 || atoi(arr_index.dir) >=  get_dim(&curr_env.types,$1.type))
                                {
                                    char * dim_f = (char*) malloc(32*sizeof(char));
                                    sprintf(dim_f,"%d",get_dim(&curr_env.types,$1.type)-1);
                                    yyerror2("Fuera de rango, index inávildo, se espera un número entre el 0 y el",dim_f);
                                    imprime_ci = false;
                                }
                        }
                        exp tam_act;
                        tam_act.type = 2;
                        sprintf(tam_act.dir,"%d", get_tam(&curr_env.types,base_type));
                        
                        exp curr_dir = math_function(arr_index,tam_act,ML);

                        strcpy($$.dir,math_function(base_dir,curr_dir,MA).dir);
                        //printf("->> Dir act: %s\n",$$.dir);

                        fprintf(producciones,"var_arreglo -> var arreglo [ expresion ]\n");
                    }
                };

expresion:   expresion MAS expresion 
                {
                    $$ = math_function($1,$3,MA);
                    fprintf(producciones,"expresion -> expresion + expresion \n");
                }
            | expresion MENOS expresion 
                {
                    $$ = math_function($1,$3,MEN);
                    fprintf(producciones,"expresion -> expresion - expresion \n");
                }
            | expresion MUL expresion
                {
                    $$ = math_function($1,$3,ML);
                    fprintf(producciones,"expresion -> expresion * expresion \n");
                }
            | expresion DIV expresion
                {
                    $$ = math_function($1,$3,DV);
                    fprintf(producciones,"expresion -> expresion / expresion \n");
                }
            | expresion MOD expresion
                {
                    $$ = math_function($1,$3,MD);
                    fprintf(producciones,"expresion -> expresion mod expresion \n");
                }
            | var_arreglo
                {
                    exp id;
                    strcpy(id.dir,$1.arr);
                    $$ = asignar(id,$1);
                    fprintf(producciones,"expresion -> var_arreglo\n");
                }
            | CAR 
                {   
                    $$.type = 1;
                    strcpy($$.dir, $1);
                    fprintf(producciones,"expresion -> car %s\n", $1);
                }
            | CADENA 
                {
                    $$.type = 6;
                    $$.cadena = (char*) malloc(sizeof(char*));
                    strcpy($$.cadena,$1);
                    fprintf(producciones,"expresion -> cadena %s\n", $1);
                }
            | NUMERO 
                {   $$.type = $1.type;
                    strcpy($$.dir, $1.val);
                    fprintf(producciones,"expresion -> num %s\n", $1.val);
                }
            | ID  {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("No se encontró el identificador", $1);
                        return -1;
                    }

                    if (is_function(&global_funcs, $1))
                    {
                        funrec rec = *get_rec(&global_funcs, $1);
                        stack_push(&func_calls, &rec);
                    }

                    strcpy(curr_function, $1);
                  }                   
                LPAR parametros RPAR 
                {   
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (is_function(&global_funcs, $1))
                    {   
                        funrec rec;
                        stack_pop(&func_calls, &rec);
                        if (rec.params != rec.counter)
                        {
                            char *msg = (char*) malloc(sizeof(char*));
                            sprintf(msg, "Se esperaban %d argumentos en la función %s, pero se encontraron %d", rec.params, rec.id, rec.counter);
                            yyerror(msg);
                            fail_decl = true;                            
                        }
                    }
                    else if ($4)
                    {
                        yyerror2("No corresponde a una función el identificador", $1);
                        fail_decl = true;
                    }


                    /* Asigna tipo esperado. */
                    strcpy($$.dir, $1);
                    $$.type = get_type(&curr_env.symbols,$1);
                    fprintf(producciones,"expresion -> id %s ( parametros )\n", $1);
                }
            ;

parametros: lista_param 
                {
                    $$ = true; 
                    fprintf(producciones,"parametros-> lista_param\n");
                }
            | %empty {$$ = false;};

lista_param: lista_param COM expresion 
                {
                    cuadrupla cuad;
                    cuad.op = PARAM;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    
                    if (is_function(&global_funcs, $3.dir) == 0)
                        strcpy(cuad.res, $3.dir);
                    else{
                        exp *e = call_function(&$3);
                        strcpy(cuad.res, e->dir);
                    }

                    funrec rec;
                    stack_pop(&func_calls, &rec);
                    if (check_args_types(&rec, $3) < 0)
                        return -1;

                    rec.counter++;
                    stack_push(&func_calls, &rec);

                    insert_cuad(&codigo_intermedio, cuad);

                    fprintf(producciones,"lista_param -> lista_param , expresion\n");
                }
            | expresion 
                {
                    /* Si es una variable entonces hay error pues no debe tener parámetros.*/
                    if(!is_function(&global_funcs, curr_function))
                    {
                        yyerror2("No corresponde a una función el identificador", curr_function);
                        return -1;
                    }

                    cuadrupla cuad;
                    cuad.op = PARAM;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    if (is_function(&global_funcs, $1.dir) == 0)
                        strcpy(cuad.res, $1.dir);
                    else{
                        exp *e = call_function(&$1);
                        strcpy(cuad.res, e->dir);
                    }
                    
                    funrec rec;
                    stack_pop(&func_calls, &rec);
                    if(check_args_types(&rec, $1) < 0)
                        return -1;

                    rec.counter++;
                    stack_push(&func_calls, &rec);

                    insert_cuad(&codigo_intermedio, cuad);
                    fprintf(producciones,"lista_param -> expresion\n");
                };

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
                    fprintf(producciones,"condicion -> condicion && condicion \n");
                 }
            | condicion AND 
                {
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&$1->trues));
                    insert_cuad(&codigo_intermedio, cuad);
                }
              condicion     
                {
                    char label[32];
                    strcpy(label, newLabel());
                    
                    $$ = (bools*) malloc(sizeof(bools));
                    $$->falses = merge(&$1->falses, &$4->falses);
                    $$->trues = $4->trues;
                    backpatch(&$1->trues, label, &codigo_intermedio);
                    
                    fprintf(producciones,"condicion -> condicion && condicion \n");
                }
            | NOT condicion 
                {   
                    $$ = (bools*) malloc(sizeof(bools));
                    $$->falses = $2->trues;
                    $$->trues  = $2->falses;
                    fprintf(producciones,"condicion -> ! condicion \n");
                }
            | LPAR condicion RPAR 
                {   
                    $$ = $2;
                    fprintf(producciones,"condicion -> ( condicion )\n");
                }
            | expresion relacional expresion
                {
                    $$  = gen_cond_rel($1.dir, $3.dir, $2);
                    fprintf(producciones,"condicion -> expresion rel expresion \n");
                }
            | TRUE 
                {   
                    $$ = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    $$->trues = create_list(dir);
                    gen_cond_goto(dir);
                    fprintf(producciones,"condicion -> true \n");
                }
            | FALSE 
                {  
                    $$ = (bools*) malloc(sizeof(bools));
                    char dir[32];
                    strcpy(dir, newIndex());
                    $$->falses = create_list(dir);
                    gen_cond_goto(dir);
                    fprintf(producciones,"condicion -> false \n");
                }
            | %empty {} ;    

relacional: MAYOR { $$ = GT; fprintf(producciones,"rel-> >\n"); }
          | MENOR { $$ = LT; fprintf(producciones,"rel->  <\n");}
          | MAYOR_IGUAL { $$ = GE; fprintf(producciones,"rel->  >=\n");}
          | MENOR_IGUAL { $$ = LE; fprintf(producciones,"rel->  <=\n");}
          | DIF { $$ = NE; fprintf(producciones,"rel->  !=\n");}
          | IGUAL { $$ = EQ; fprintf(producciones,"rel->  ==\n");};
%%

/*
 * Función para imprimir un error con el mensaje deseado.
 * Se usan colores para hacer los comentarios amigables al usuario.
 *
 * Autor: Mendez Servin Melissa.
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
 * Autor: Mendez Servin Melissa.
 *        Palmerin Morales David Gabriel.
 */
void yyerror2(char *s, char *n){
    printf(ANSI_COLOR_RED"Error:"ANSI_COLOR_RESET " %s %s: en la línea %d\n",s, n, yylineno);    
    fprintf(err,"%s %s: en la línea %d\n",s, n, yylineno);
}

/* Inicializa las variables necesarias para el análisis, tales como 
 * pilas, tablas globales, etc.
 * 
 * Autores: Mendez Servin Melissa. 
 *          Palmerin Morales David Gabriel.
 */
void init()
{
    create_code(&codigo_intermedio);
    create_labels(&etiquetas);
    create_funtab(&global_funcs);

    stack_new(&switchesback, sizeof(switches), NULL);
    stack_new(&func_calls, sizeof(funrec), NULL);
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
 * Autores: Mendez Servin Melissa. 
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

/*
 * Devuelve el tipo de mayor dimensión, funciona también
 * para determinar la compatibilidad entre tipos, es decir,
 * si son numeros ambos o bien se trata de una cadena y un
 * arreglo de chars, en otro caso devuelve -1.
 *
 * Autora : Mendez Servin Melissa.
 */
int max_type(int t1, int t2){
    //printf("TIPO 1: %d, TIPO 2: %d\n",t1,t2);
    if (t1 == t2) return t1;
    else {
        /*Si son ambos números. */
        if (t1 > 1 && t1 < 5 && 
            t2 > 1 && t2 < 5){
                if (t1 < t2){return t2;} 
                else {return t1;} 
        } 
        if (t1 > 6 &&  t2 == 6)
            return t1; //Es posible que se intenta asignar una cadena a una char unidimensional
        /*Si no son números -> tipos incompatibles.
         Por ahora no se pude hacer int a char*/    
        return -1;
    } 
}

/* Asina a la expresión e1 el valor de la dirección de 
 * de la expresión e2, generando el código intermedio 
 * y expresión correspondiente.
 *
 * Autora : Mendez Servin Melissa. 
 */
exp asignar(exp e1, exp e2){
    exp e;
    if (is_function(&global_funcs, e2.dir) == 1)
        call_function(&e2);
    cuadrupla cuad;
    env curr_env;
    stack_peek(&envs, &curr_env);
    /* Si se está pidiendo asignar un arreglo, i.e, e2.arr == ID
       Verifica que exista el id. */
    if (depth_search(&curr_env.symbols, e2.arr) != -1)
    {
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
    else
    {
        strcpy(&cuad.res, e1.dir);
        strcpy(e.dir, e1.dir);
        int t1 = e1.type;
        int t2 = e2.type;
        e.type = t1;
        if(t1 > 6 && t2 == 6){
            int base = get_base(&curr_env.types, t1);
            //Se va a asignar una cadena a un arreglo de chars unidimensional
            if(base == 1){    
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
                    printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "Fuera de rango, se está intentando asignar una cadena con longitud %d a un arreglo de chars con dimension %d menor : línea %d\n", len, dim, yylineno);
                    fprintf(err,"Error: Fuera de rango, se está intentando asignar una cadena con longitud %d a un arreglo de chars con dimension %d menor : línea %d\n", len, dim, yylineno);
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

/* Reduce el tipo de de un número, donde dir es la dirección 
 * del numero a reducir de tipo t, y  w ( el tipo menor) al 
 * que se va a reducir. Devuelve la dirección de la variable
 * resultante.
 * (int a = (int) 2.0)
 *
 * Autora: Mendez Servin Melissa.
 */
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

/* Amplia el tipo de de un número, donde dir es la dirección 
 * del numero a ampliar de tipo t, y  w ( el tipo mayor) al 
 * que se va a reducir.Devuelve la dirección de la variable
 * resultante.
 * (double a = (double) 2)
 *
 * Autora: Mendez Servin Melissa.
 */
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
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Cast de int a double: línea %d\n", yylineno);
        if (t == 3)
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Cast de float a double: línea %d\n", yylineno);
        return temp;
    }        
    return "SF";
}

/* Devuelve la expresión correspondiente a la operación
 * dada y lo traduce a código intermedio. 
 * 
 * Autora : Mendez Servin Melissa.
 */
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
 *        Melissa Mendez Sevin
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
 * Autores: Mendez Servin Melissa.
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
 * Autor: Palmerin Morales David Gabriel
 *        Mendez Servin Melissa.
 */
int check_args_types(funrec *rec, exp expr)
{   
    if (rec->counter < rec->params)
    {
        int i = rec->counter;
        int tipo = rec->context->symbols[i].type;
        int compatible = max_type(tipo, expr.type);
        if (compatible == -1)
        {   
            printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "Argumentos no compatibles la función ");
            printf("%s: %s es de tipo %s y se espera de tipo %s : en la línea %d\n", curr_function, expr.dir, get_type_gen(expr.type), get_type_gen(tipo), yylineno);
            fprintf(err,"Error: Argumentos no compatibles la función %s: %s es de tipo %s y se espera de tipo %s : en la línea %d\n",curr_function, expr.dir, get_type_gen(expr.type), get_type_gen(tipo), yylineno);
            return -1;
        }
        if (tipo != expr.type){
            printf(ANSI_COLOR_CYAN "Warning: " ANSI_COLOR_RESET "Puede haber pérdida de información, el arguemnto es ");
            printf("tipo %s y se dio un %s en la función %s : en la línea %d\n", get_type_gen(tipo), get_type_gen(expr.type), curr_function, yylineno);
        }
        fprintf(producciones,"func %s", expr.dir);
    }
    else
    {   
        yyerror2("Se encontraron más argumentos de los esperados en el identificador", rec->id);
        return -1;
    }
    return 0;
}
/*
 * Devuelve el nombre del tipo correspodiente al número dado.
 * 
 * Autora: Mendez Servin Melissa.
 */
char * get_type_gen(int t){
    char *tipo = (char*) malloc(32*sizeof(char));
    switch(t){
        case 0 : return "(void)"; break;
        case 1 : return "(char)"; break;
        case 2 : return "(int)"; break;
        case 3 : return "(float)"; break;
        case 4 : return "(double)"; break;
        case 5 : return "(struct)"; break;
    }
}
