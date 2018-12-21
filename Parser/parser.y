%{
/* 
 * File:   parser.y
 * Autor: Melissa y Palmi
 * Diciembre de 2018
 */
#include <stdio.h>
#include <stdlib.h>


#include "attributes.h"
#include "symtab.h"
#include "backpatch.h"
#include "intermediate_code.h"
#include <stdbool.h>
#include <string.h>

extern int yylex();
extern int yylineno;

// Manejo de errores
void yyerror(char *);
void yyerror2(char*, char*);

/* Variable para el conteo de direcciones */
int dir=0;

/* Variables para guardar el tipo y ancho actual */
int current_type;
int current_dim;

/* Varaibles para contar las temporales, etiquetas e indices */
int label;
int temp;
int indice;

/* Variable para el unico atributo heredado de sentencia prima*/
labels lfalses;


/* Variable para la tabla de símbolos*/
symtab tabla_de_simbolos;

/* Variable papra guardar el código intermedio que se va generando */
ic codigo_intermedio;


/* Funciones auxiliares al análisis semántico y generación de código intermedio */
void init();
void finish();

exp suma(exp e1, exp e2);
exp resta(exp e1, exp e2);
exp multiplicacion(exp e1, exp e2);
exp division(exp e1, exp e2);
exp get_numero(numero);
exp identificador(char *);
exp asignacion(char *id, exp e);

/* Funciones auxiliares para la comprobación de tipos */
int max(int t1, int t2);
char *ampliar(char *dir, int t1, int t2);
char *reducir(char *dir, int t1, int t2);


/* Funciones para generar temporales, etiquetas e indices */
char *newTemp();
char *newLabel();
char *newIndex();

%}

%union{   
  numero num;
  char id[32];
  char car;
  char* cadena;
  exp expr;
  type tipo;
  labels siguientes;   
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
%type<booleanos> condicion
%type<expr> expresion
%type<siguientes> sentencia sentencias
%start programa

%%

programa: {init();} decl 
          {print_table(&tabla_de_simbolos);}
          funciones {printf("programa -> decl funciones\n");};

decl : tipo {current_type = $1.type; current_dim = $1.dim;}
       lista PYC decl {printf("decl -> tipo lista PYC decl\n");}
      | %empty {};

tipo:         INT //{$$.type = 0; $$.dim = 4;
              {printf("tipo -> int\n");}
            | FLOAT {$$.type =1; $$.dim = 4;
              printf("tipo -> float\n");}
            | DOUBLE {$$.type= 2; $$.dim = 8; 
              printf("tipo -> double\n");}
            | CHAR {printf("tipo -> char\n");}
            | VOID {printf("tipo -> void\n");}
            | STRUCT LKEY decl RKEY {printf("tipo -> struct { decl }\n");};

lista : lista COM ID arreglo 
         /* { sym s;
            strcpy(s.id, $3);
            s.type = current_type;
            s.dir = dir;
            dir+= current_dim;
            insert(&tabla_de_simbolos, s);*/{
            printf("lista -> lista , id arreglo\n");}
            | ID arreglo 
          { sym s;
            strcpy(s.id, $1);
            s.type = current_type;
            s.dir = dir;
            dir+= current_dim;
            insert(&tabla_de_simbolos, s);
            printf("lista- >id arreglo\n");};

arreglo : LCOR NUMERO RCOR arreglo {printf("arreglo -> id arreglo\n");}
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

sentencias : sentencias { 
            cuadrupla c;
            c.op = LB;
            strcpy(c.op1, "");
            strcpy(c.op2, "");
            strcpy(c.res, get_first(&$1));
            insert_cuad(&codigo_intermedio, c);} 
            sentencia 
            {
                char label[32];
                strcpy(label,newLabel());
                $$ = $3;                
                backpatch(&$1, label, &codigo_intermedio);
                printf("sentencias -> sentencias sentencia\n");  
            }
            | sentencia {
                char label[32];
                strcpy(label, newLabel());
                $$ = $1;
                backpatch(&$1, label, &codigo_intermedio);
                printf("sentencias -> sentencia\n");};

sentif : sentencias ELSE sentencias
        {printf("sentif -> else sentencias\n");}
        | sentencias;

sentencia :  IF LPAR condicion RPAR sentif
            {printf("sentencia -> if ( condicion ) sentencias sentif\n");}
            | WHILE LPAR condicion RPAR sentencias 
            {printf("sentencias -> while ( condicion ) sentencias\n");}
            | DO sentencias WHILE LPAR condicion RPAR PYC
            {printf("sentencias -> do sentencias while ( condicion) ;\n"); } 
            | FOR LPAR sentencia PYC condicion PYC sentencia RPAR sentencias
            {printf("sentencias -> for ( sentencia ; condicion; sentencia ) sentencias\n");}
            | parte_izq ASIG expresion PYC {
                char i[32];
                strcpy(i, newIndex());
                $$ = create_list(i);
                //asignacion($1, $3); 
                printf("sentencias -> parte_izq = expresion\n");}
            | RETURN expresion PYC
            {printf("sentencias -> return expresion ;\n");}
            | RETURN PYC
            {printf("sentencias -> return ;\n");}
            | LKEY sentencias RKEY
            {printf("sentencias -> { sentencias }\n");}
            | SWITCH LPAR expresion RPAR LKEY casos predeterm RKEY
            {printf("sentencias -> switch ( expresion ) { casos prederterm} \n");}
            | BREAK PYC {printf("sentencias -> break ;\n");}
            | PRINT expresion PYC 
            {printf("sentencias -> print expresion ;\n");}; 

casos : CASE PUNES NUMERO sentencia casos
        {printf("casos -> case : sentencia casos\n");}
            | %empty {};

predeterm : DEFAULT PUNES sentencia
            {printf("predeterm -> default : sentencia\n");}
            | %empty {};

parte_izq : ID {printf("parte_izq -> id\n");}
            | var_arreglo {printf("parte_izq -> var_arreglo\n");}
            | ID DOT ID {printf("parte_izq -> id.id\n");}

var_arreglo : ID LCOR expresion RCOR {printf("var_arreglo -> id [ expresion ] \n");}
            | var_arreglo LCOR expresion RCOR {printf("var_arreglo -> var arreglo [ expresion ]\n");};

expresion: expresion MAS expresion 
            {$$ =suma($1, $3); 
              printf("expresion -> expresion + expresion \n");}
            | expresion MENOS expresion 
            {$$ =resta($1, $3);
             printf("expresion -> expresion - expresion \n");}
            | expresion MUL expresion
            {$$ = multiplicacion($1, $3);
              printf("expresion -> expresion * expresion \n");}
            | expresion DIV expresion
            {$$ =division($1, $3);
             printf("expresion -> expresion / expresion \n");}
            | expresion MOD expresion
            {printf("expresion -> expresion mod expresion \n");}
            | var_arreglo
            {printf("expresion -> var_arreglo\n");}
            | CAR {printf("expresion -> car %c\n", $1);}
            | CADENA {printf("expresion -> cadena %s\n", $1);}
            | NUMERO {printf("expresion -> num %s\n", $1.val);}
            | ID LPAR parametros RPAR 
            {printf("expresion -> id %s ( parametros )\n", $1);};

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
            | expresion relacional expresion               {printf("condicion -> expresion rel expresion \n");}
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


void yyerror2(char *c, char *c2){
    strcat(c, c2);
    yyerror(c);
}

void init(){    
    create_table(&tabla_de_simbolos);
    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
}

void finish(){    
    print_code(&codigo_intermedio);    
}

exp suma(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MA;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp resta(exp e1, exp e2){
    exp e;
    cuadrupla c;
    char t[32];
    e.type = max(e1.type, e2.type);
    
    if( e.type==-1) yyerror("Error de tipos");
    else{
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MEN;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp multiplicacion(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = ML;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp division(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = DV;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp asignacion(char *id, exp e){
    exp e1;
    int tipo = get_type(&tabla_de_simbolos, id);
    if( tipo != -1){        
        e1.type = e.type;
        strcpy(e1.dir, id);
        cuadrupla c;
        c.op = AS;
        strcpy(c.op1, reducir(e.dir, tipo, e.type));
        strcpy(c.op2, "");
        strcpy(c.res, id);
        insert_cuad(&codigo_intermedio, c);  
        
    }else{
        yyerror("El identificador no fue declarado\n");
    }
    return e1;
}


exp get_numero(numero n){
    exp e;
    e.type = n.type;
    strcpy(e.dir, n.val);
    return e;
}

exp identificador(char *id){
    exp e;
    if(search(&tabla_de_simbolos, id)!=-1){
        e.type = get_type(&tabla_de_simbolos, id);
        strcpy(e.dir, id);
    }else{
        yyerror("Error semantico: el identificador no existe");
    }
    return e;
}


int max(int t1, int t2){
    if( t1==t2) return t1;
    if( t1 ==0 && t2 == 1) return 1;
    if( t1 ==1 && t2 == 0) return 1;    
    if( t1 ==0 && t2 == 2) return 2;
    if( t1 ==2 && t2 == 0) return 2;
    if( t1 ==2 && t2 == 1) return 2;
    if( t1 ==1 && t2 == 2) return 2;
    else return -1;
}

char *ampliar(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }            
}


char *reducir(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("Pérdida de información se esta asignando un float a un int\n");
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("Pérdida de información se esta asignando un double a un int\n");
        return t;
    }        
    
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("Perdida de información se esta asignando un double a un float\n");
        return t;
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