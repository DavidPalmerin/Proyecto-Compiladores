%{
/* 
 * File:   parser.y
 * Autor: Melissa y Palmi
 * Diciembre de 2018
 */
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *);
//void yyerror(char*, char*);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
extern FILE *yyout;
extern FILE *f;
extern FILE *tokens_output;
extern FILE *errores_lexicos;
%}

%union{
  struct {
    char sval;
  }car;
  struct {
    char* sval;
  }cadena;
  struct {
    int ival;
  }num;
 }

%token<car> CAR 
%token<cadena> ID CADENA
%token<num> NUMERO  
%token TRUE FALSE
%token INT FLOAT DOUBLE VOID STRUCT CHAR
%token WHILE SWITCH FOR DO
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
%left IF
%left ELSE

%start programa

%%

programa: decl funciones;

decl : tipo lista PYC 
            | ;

tipo:         INT 
            | FLOAT 
            | DOUBLE
            | CHAR
            | VOID
            | STRUCT LKEY decl RKEY;

lista : lista COM ID arreglo
            | ID arreglo;

arreglo : LCOR NUMERO RCOR arreglo
            | ;

funciones : FUNC tipo ID LPAR argumentos RPAR LKEY  decl sentencias RKEY funciones
            | ;

argumentos : lista_args
            | ;

lista_args : lista_args COM tipo ID parte_arr
            | tipo ID parte_arr

parte_arr : LCOR RCOR parte_arr
            | ;

sentencias : sentencias sentencia 
            | sentencia;

sentencia : IF LPAR condicion RPAR sentencia
            | IF LPAR condicion RPAR sentencias ELSE sentencia
            | WHILE LPAR condicion RPAR sentencia 
            | DO sentencia WHILE LPAR condicion RPAR PYC 
            | FOR LPAR sentencia PYC condicion PYC sentencia RPAR sentencia
            | parte_izq ASIG expresion PYC
            | RETURN expresion PYC
            | RETURN PYC
            | LKEY sentencia RKEY
            | SWITCH LPAR expresion RPAR LKEY casos predeterm RKEY
            | BREAK PYC
            | PRINT expresion PYC;

casos : CASE PUNES sentencia predeterm
            | ;

predeterm : DEFAULT PUNES sentencia
            | ;

parte_izq : ID
            | var_arreglo
            | ID DOT ID

var_arreglo : ID LCOR expresion RCOR
            | var_arreglo LCOR expresion RCOR ;

expresion: expresion MAS expresion
            | expresion MENOS expresion
            | expresion MUL expresion
            | expresion DIV expresion
            | expresion MOD expresion
            | var_arreglo
            | CAR
            | CADENA 
            | NUMERO
            | ID LPAR parametros RPAR;

parametros: lista_param
            | ;

lista_param: lista_param COM expresion
            | expresion;

condicion: condicion OR condicion 
            | condicion AND condicion 
            | NOT condicion 
            | LPAR condicion RPAR 
            | expresion relacional expresion
            | TRUE 
            | FALSE; 

relacional: MAYOR | MENOR | MAYOR_IGUAL | MENOR_IGUAL | DIF | IGUAL;
%%
void yyerror(char *s){
    printf("%s: en la línea %d\n",s, yylineno);
}

int main(int argc, char **argv) {
  if(argc < 2)	return -1;
  f= fopen(argv[1], "r");
  if (!f)	return -1;
  tokens_output = fopen("tokens_output.txt", "w");
  errores_lexicos = fopen("errores_lexicos.txt", "w");

  yyin = f;
  yyout = tokens_output;

  int p = yyparse();
  if(p)
    printf("La entrada es rechazada de acuerdo a la gramática.\n");
  else
    printf("La entrada es aceptada de acuerdo a la gramática.\n");
  fclose(f);
  return 0;
}
