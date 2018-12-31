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
#include "typetab.h"
#include "stack.h"


extern int yylex();
extern int yylineno;

/* Ouput files */
FILE *contexts;
FILE *err;

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

int index_dim = 0;

/* Variable para el unico atributo heredado de sentencia prima*/
labels lfalses;

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
void gen_cond_rel(char e1[32], char e2[32], char dir[32], int op);

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
                            printf("programa -> decl funciones\n");
                            
                            finish();
                        };

decl :      tipo    {   
                        current_type = $1;
                        current_dim = get_tam(&global_types,$1);
                    }      
            lista PYC decl {
                                printf("decl -> tipo lista PYC decl\n");
                            }
            | %empty {};

tipo:        VOID   {    
                        $$ = 0;
                        printf("tipo -> VOID\n");
                    }
            | CHAR {
                        $$ = 1;
                        printf("tipo -> CHAR\n");
                    }
            | INT   {
                        $$ = 2;
                        printf("tipo -> INT\n");
                    }
            | FLOAT {
                        $$ = 3;
                        printf("tipo -> FLOAT\n");
                    }
            | DOUBLE{
                        $$ = 4;
                        printf("tipo -> DOUBLE\n");
                    }
            | STRUCT{   
                        struct_decl = true;
                        add_context(false);
                    }
                LKEY decl RKEY {
                                    $$ = 5;
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
                        fail_decl = true;
                    }                
                    if (current_type == 5)
                    {
                        yyerror("[ERROR] Struct solo puede tener un identificador.");
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

                        sym symbol;
                        strcpy(symbol.id, $3);
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
                        
                        printf("lista -> lista , id arreglo\n");}
                }
            | ID 
              arreglo
                {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) != -1)
                    {
                        yyerror2("[ERROR] Ya existe un identificador con el nombre", $1);
                        fail_decl = true;
                    }
                    if(current_type == 0){
                        yyerror("[ERROR] No se pueden declarar variables de tipo void.");
                        fail_decl = true;
                    }                  
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else {
                        sym symbol;
                        strcpy(symbol.id, $1);
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
                            symbol.type = curr_env.types.count - 1;
                        }
                        primero = false;
                        list_destroy(&dimensiones);
                        list_new(&dimensiones, 10,NULL);

                        insert(&curr_env.symbols, symbol);
                        stack_push(&envs, &curr_env);
                        if (current_type != 5 && struct_decl){
                            struct_dim += current_dim;
                        }
                        printf("lista- >id arreglo\n");
                    }
                };

arreglo : LCOR NUMERO RCOR arreglo 
            {   
                if ($2.type == 2){
                    int num = atoi($2.val);
                    current_dim *= num;
                    list_append(&dimensiones, &num);
                    printf("arreglo -> id arreglo\n");
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
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, $3);
                    insert_cuad(&codigo_intermedio, cuad);

                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (search(&curr_env.symbols, $3) != -1)
                    {
                        yyerror2("[ERROR] Ya se ha definido anteriormente el identificador", $3);
                        imprime_ci = false;
                        fail_decl = true;
                    }else{
                            add_context(true);
                            func_decl = true;
                        }
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
                        print_funtable(&global_funcs);
                    }
                }
             funciones 
                {printf("funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
            | %empty    {
                            if (!exists_main())
                              return 1;
                            print_funtable(&global_funcs);
                            num_params = 0;
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
                        printf("lista_args -> tipo id parte_arr\n");

                    }

parte_arr : LCOR RCOR parte_arr 
            {printf("parte_arr -> [] parte_arr\n");}
            | %empty {};

sentencias : sentencias sentencia 
            {    
                printf("sentencias -> sentencias sentencia\n");
            }
            | sentencia 
            {
                 printf("sentencias -> sentencia\n");
            };

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

                    char label[32], label2[32];
                    strcpy(label, newLabel());
                    strcpy(label2, newLabel());
                    backpatch(&$3->trues, label, &codigo_intermedio);
                    backpatch(&$3->falses, label2, &codigo_intermedio);
                }
            sentif
            {


            }
                
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
                    push_label(&lfalses, label);
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
                    strcpy(c.res, pop_label(&lfalses));
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
                    push_label(&lfalses, label);
                }
            sentencia WHILE LPAR condicion RPAR PYC
                {
                    char label[32], label2[32];
                    strcpy(label, pop_label(&lfalses));
                    strcpy(label2, newLabel());
                    backpatch(&$6->trues, label, &codigo_intermedio);
                    backpatch(&$6->falses, label2, &codigo_intermedio);

                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, label2);
                    insert_cuad(&codigo_intermedio, cuad);

                    printf("sentencia -> do sentencias while ( condicion) ;\n"); 
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
                    push_label(&lfalses, label);
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
                    strcpy(c.res, pop_label(&lfalses));
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

                    printf("sentencia -> for ( sentencia ; condicion; sentencia ) sentencias\n");
                }

            | parte_izq ASIG expresion PYC
                {                       
                    call_params = 0;
                    int compatible = max_type($1.type, $3.type);
                    if(compatible == -1) {
                        yyerror("Error: No se puede asignar, tipos incompatibles.");
                        imprime_ci = false;
                    }
                    else {
                        asignar($1,$3);
                        printf("sentencia -> parte_izq = expresion\n");
                    }
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
                    char label[32];
                    $$ = $2;
                    strcpy(label, newLabel());
                    backpatch(&$2, label, &codigo_intermedio);
                    printf("sentencia -> { sentencias }\n");
                }
            | SWITCH LPAR expresion RPAR
                {
                    push_label(&lfalses, newLabel());
                    push_label(&lfalses, newLabel());
                    switch_call++;

                    cuadrupla cuad;
                    cuad.op = GOTO;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_top_label_previous(&lfalses));
                    insert_cuad(&codigo_intermedio, cuad);
                }
              LKEY casos predeterm RKEY
                {

                    cuadrupla c;
                    c.op = LB;
                    strcpy(c.op1, "");
                    strcpy(c.op2, "");
                    strcpy(c.res, get_top_label_previous(&lfalses));
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
                    strcpy(cuad.res, pop_label(&lfalses));
                    insert_cuad(&codigo_intermedio, cuad);

                    pop_label(&lfalses);
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
                char *label = get_top_label(&lfalses);
                cuadrupla cuad;
                cuad.op = GOTO;
                strcpy(cuad.op1, "");
                strcpy(cuad.op2, "");
                strcpy(cuad.res, label);
                insert_cuad(&codigo_intermedio, cuad);
            }
        casos { $$ = $7; }
        | %empty {$$ = switch_call;};

predeterm : DEFAULT PUNES sentencia
            {printf("predeterm -> default : sentencia\n");}
            | %empty {};

parte_izq : ID  {
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se ha declarado la variable", $1);
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
                    printf("parte_izq -> id\n");
                }
            | var_arreglo 
                {
                    exp id;
                    strcpy(id.dir,$1.arr);
                    id.type = $1.type;
                    $$ = asignar(id,$1);
                    printf("parte_izq -> var_arreglo\n");
                }
            | ID DOT ID 
                {
                    printf("parte_izq -> id.id\n");
                }

var_arreglo : ID LCOR expresion RCOR 
            {
                env curr_env;
                stack_peek(&envs, &curr_env);
                if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se encontró el identificador", $1);
                        fail_decl = true;
                    }
                strcpy($$.arr,$1);
                exp base_dir;
                sprintf(base_dir.dir,"%d",get_dir(&curr_env.symbols,$1));
                base_dir.type = 2;
                int curr_type = get_type(&curr_env.symbols,$1);

                if( $3.type != 2)
                    {
                    yyerror("[ERROR] Para acceder a un arreglo la expresión o número debe ser un entero ");
                    fail_decl = true;
                    }
                if( curr_type == 5)
                    {
                    yyerror("[ERROR] Acceso inválido, es tipo struct y se está intentando acceder como un arreglo ");
                    fail_decl = true;
                    }
                if(fail_decl)
                {
                    fail_decl = false;
                    imprime_ci = false;
                }
                else
                {
                    printf("CURR TYPE --->%d\n",curr_type);

                    int base_type = get_base(&curr_env.types,curr_type);

                    exp arr_index = $3;
                    printf("->> Index: %s\n",arr_index.dir);
                    printf("->> Tipo base: %d\n",base_type);
                    
                    /*index > -1
                    exp menosuno;
                    menosuno.type = 2;
                    sprintf(menosuno.dir,"%d",-1);
                    bools * condicion = relational_op(arr_index,menosuno,GT);
                    cuadrupla cuad;
                    cuad.op = LB;
                    strcpy(cuad.op1, "");
                    strcpy(cuad.op2, "");
                    strcpy(cuad.res, get_first(&condicion->trues));
                    if (strcmp(cuad.res, "") != 0)
                        insert_cuad(&codigo_intermedio, cuad);
                    */
                    $$.type = base_type;
                    /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                    dir = base_dir + (index * tam_base) + ...*/
                    
                    exp tam_act;
                    tam_act.type = 2;
                    sprintf(tam_act.dir, "%d",get_tam(&curr_env.types,base_type));
                    
                    exp curr_dir = math_function(arr_index,tam_act,ML);

                    strcpy($$.dir,math_function(base_dir,curr_dir,MA).dir);
                    printf("->> Dir act: %s\n",$$.dir);

                    printf("var_arreglo -> id [ expresion ] \n");
                    

                }
            }
            | var_arreglo LCOR expresion RCOR 
                { 
                if( $3.type != 2)
                    {
                    yyerror("[ERROR] Para acceder a un arreglo la expresión o número debe ser un entero ");
                    fail_decl = true;
                    }
                env curr_env;
                stack_peek(&envs, &curr_env);
                if($1.type == -1){
                    yyerror("[ERROR] Fuera de rango ");
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

                        printf("CURR TYPE --->%d\n",$1.type);

                        int base_type = get_base(&curr_env.types,$1.type);

                        exp arr_index = $3;
                        printf("->> Index: %s\n",arr_index.dir);
                        printf("->> Tipo base: %d\n",base_type);
                            
                        $$.type = base_type;
                        /*Creamos la exp con el valor del tamaño del tipo base para multiplicar y obtner la dirección nueva
                        dir = base_dir + (index * tam_base) + ...*/
                        
                        exp tam_act;
                        tam_act.type = 2;
                        sprintf(tam_act.dir,"%d", get_tam(&curr_env.types,base_type));
                        
                        exp curr_dir = math_function(arr_index,tam_act,ML);

                        strcpy($$.dir,math_function(base_dir,curr_dir,MA).dir);
                      
                        printf("var_arreglo -> var arreglo [ expresion ]\n");
                    }
                };

expresion:   expresion MAS expresion 
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
                    exp id;
                    strcpy(id.dir,$1.arr);
                    $$ = asignar(id,$1);
                    printf("expresion -> var_arreglo\n");
                }
            | CAR 
                {   
                    $$.type = 1;
                    strcpy($$.dir, $1);
                    printf("expresion -> car %s\n", $1);
                }
            | CADENA 
                {
                    $$.type = 6;
                    $$.cadena = (char*) malloc(sizeof(char*));
                    strcpy($$.cadena,$1);

                    printf("expresion -> cadena %s\n", $1);
                }
            | NUMERO 
                {   $$.type = $1.type;
                    strcpy($$.dir, $1.val);
                    printf("expresion -> num %s\n", $1.val);
                }
            | ID  {
                    stack_push(&func_calls, $1);
                  }                   
                LPAR parametros RPAR 
                {   
                    /* Verifica que exista el id. */
                    env curr_env;
                    stack_peek(&envs, &curr_env);
                    if (depth_search(&curr_env.symbols, $1) == -1)
                    {
                        yyerror2("[ERROR] No se encontró el identificador", $1);
                        fail_decl = true;
                    }
                    if(fail_decl){
                        fail_decl = false;
                        imprime_ci = false;
                    }
                    else
                    {
                        if (is_function(&global_funcs, $1))
                        {
                            funrec *rec = get_rec(&global_funcs, $1);
                            if (rec->params != rec->counter)
                            {
                                char *msg = (char*) malloc(sizeof(char*));
                                sprintf(msg, "[ERROR] Se esperaban %d argumentos en la función %s, pero se encontraron %d", rec->params, rec->id, call_params);
                                yyerror(msg);
                                fail_decl = true;                            
                            }
                            rec->counter = 0;
                        }
                        else if ($4)
                        {
                            yyerror2("[ERROR] No corresponde a una función el identificador", $1);
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
                        strcpy($$.dir, $1);
                        $$.type = get_type(&curr_env.symbols,$1);
                        }
                    }
                    printf("expresion -> id %s ( parametros )\n", $1);
                }
            ;

parametros: lista_param 
                {
                    $$ = true; 
                    printf("parametros-> lista_param\n");
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
                    insert_cuad(&codigo_intermedio, cuad);

                    stack_peek(&func_calls, curr_function);
                    funrec *rec = get_rec(&global_funcs, curr_function);

                    if (check_args_types(rec, $3) < 0)
                        return 1;

                    printf("lista_param -> lista_param , expresion\n");
                }
            | expresion 
                {
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
                    insert_cuad(&codigo_intermedio, cuad);
                    
                    stack_peek(&func_calls, curr_function);
                    funrec *rec = get_rec(&global_funcs, curr_function);

                    if (check_args_types(rec, $1) < 0)
                        return 1;
                    
                    printf("lista_param -> expresion\n");
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
                    char i[32];
                    char i2[32];
                    char temp[32];
                    strcpy(i, newIndex());
                    strcpy(i2, newIndex());
                    strcpy(temp, newTemp());

                    $$ = (bools*) malloc(sizeof(bools));
                    $$->trues = create_list(i);
                    $$->falses = create_list(i2);

                    cuadrupla c, c1, c2;
                    
                    c.op = $2;
                    strcpy(c.op1, $1.dir);
                    strcpy(c.op2, $3.dir);
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
    fprintf(err,"%s: en la línea %d\n",s, yylineno);
}

void yyerror2(char *s, char *n){
    printf("%s %s: en la línea %d\n",s, n, yylineno);
    fprintf(err,"%s %s: en la línea %d\n",s, n, yylineno);
}

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

void finish()
{
    if(imprime_ci)
        print_code(&codigo_intermedio);
}

void print_context(char *s1, char *s2)
{
    env curr_env;
    stack_peek(&envs, &curr_env);
    fprintf(contexts, "~ %s %s\n", s1, s2);
    fprint_table(&curr_env.symbols, contexts);
    fprint_table_types(&curr_env.types,contexts);
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
    printf("TIPO 1: %d, TIPO 2: %d\n",t1,t2);
    if (t1 == t2) return t1;
    else {
        /*Si son ambos números. */
        if (t1 > 1 && t1 < 5 && 
            t2 > 1 && t2 < 5) 
            if (t1 < t2) return t2;
        else return t1;  
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
            yyerror2("[ERROR] No se encontró el identificador", e2.arr);
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
                printf("---------------ENTROOOOO %s\n", e2.cadena);
                int len = strlen(e2.cadena);
                if(len <= dim +2){
                    cuad.op  = ASS;
                    cuad.string_op = (char*) malloc(sizeof(char*));
                    printf("-----> cadena : %s\n", e2.cadena);
                    strcpy(cuad.string_op, e2.cadena);
                    insert_cuad(&codigo_intermedio, cuad);
                    return e;
                }
                else 
                {
                    fail_decl = true;
                    //char *msg = (char*) malloc(sizeof(char*));
                    //sprintf(msg, "[ERROR] Fuera de rango, se está intentando asignar una cadena con longitud %d a un arreglo de chars con dimension %d menor.",len, dim);
                    yyerror("[ERROR] Fuera de rango, se está intentando asignar una cadena con longitud a un arreglo de chars con dimension menor.");
                    imprime_ci = false;
                }
            }
            else 
            {
                yyerror("[ERROR] Solo se pueden asignar cadenas a arreglos unidimensionas de tipo char.");
                imprime_ci = false;
            }
        }
        else{
        cuad.op  = AS;
            if(t1 <= t2) strcpy(&cuad.op1, reducir(e2.dir,t2,t1));
            else strcpy(&cuad.op1,ampliar(e2.dir,t2,t1));
            insert_cuad(&codigo_intermedio, cuad);
            return e;
        }
    }
}

exp* call_function(exp *e)
{
    cuadrupla cuad;
    char temp[32];
    char op1[32];
    funrec rec = *get_rec(&global_funcs, e->dir);        

    sprintf(op1, "call %s, %d", e->dir, rec.params);
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
    int max = max_type(e1.type,e2.type);
    e.type = max;
    if(max==-1) 
        yyerror("Error: Tipos incompatibles.");
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
    if (struct_decl){
        struct_dim += current_dim;
         printf("->>>struct:%d\n",struct_dim);
        /*type arr = new_type();
        arr.base = symbol.type;
        arr.tam = struct_dim;
        */
    }
}

int check_args_types(funrec *rec, exp expr)
{
    if (rec->counter < rec->params)
    {
        int i = rec->counter;
        int tipo = rec->context->symbols[i].type;
        printf("FUNC %s", expr.dir);
        print_table(rec->context->symbols);
        if (tipo != expr.type)
        {
            char *msg = (char*) malloc(sizeof(char*));
            sprintf(msg, "[ERROR] Argumentos no compatibles en la función %s: %s es de tipo %d y se esperaba de tipo %d", curr_function, expr.dir, expr.type, tipo);
            yyerror(msg);
            return -1;
        }
        rec->counter++;
    }
    else
    {
        //El identificador no cerresponde a un funcion.
    }
    return 0;
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