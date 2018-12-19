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

// Archivo a leer
extern FILE *f;

// Archivos de salida
extern FILE *tokens_output;
extern FILE *errores_lexicos;
extern FILE *comentarios;
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

%start programa

%%

programa: decl funciones {printf("programa -> decl funciones\n");};

decl : tipo lista PYC {printf("decl -> tipo lista PYC\n");}
            | ;

tipo:         INT {printf("tipo -> int\n");}
            | FLOAT {printf("tipo -> float\n");}
            | DOUBLE {printf("tipo -> double\n");}
            | CHAR {printf("tipo -> char\n");}
            | VOID {printf("tipo -> void\n");}
            | STRUCT LKEY decl RKEY {printf("tipo -> struct { decl }\n");};

lista : lista COM ID arreglo {printf("lista -> lista , id arreglo\n");}
            | ID arreglo {printf("lista- >id arreglo\n");};

arreglo : LCOR NUMERO RCOR arreglo {printf("arreglo -> id arreglo\n");}
            | ;

funciones : FUNC tipo ID LPAR argumentos RPAR LKEY  decl sentencias RKEY funciones {printf("funciones -> fun tipo id ( argumentos ) { decl sentencias } funciones\n");}
            | ;

argumentos : lista_args {printf("argumentos -> lista_args\n");}
            | ;

lista_args : lista_args COM tipo ID parte_arr {printf("lista_args -> lista_args , tipo id parte_arr\n");}
            | tipo ID parte_arr {printf("lista_args -> tipo id parte_arr\n");}

parte_arr : LCOR RCOR parte_arr 
            {printf("parte_arr -> [] parte_arr\n");}
            | ;

sentencias : sentencias sentencia {printf("sentencias -> sentencias sentencia\n");}
            | sentencia {printf("sentencias -> sentencia\n");};

sentencia : IF LPAR condicion RPAR sentencias 
            {printf("sentencias -> if ( condicion ) sentencias\n");}
            | IF LPAR condicion RPAR sentencias ELSE sentencias {printf("sentencias -> if ( condicion ) sentencias else sentencias\n");}
            | WHILE LPAR condicion RPAR sentencias 
            {printf("sentencias -> while ( condicion ) sentencias\n");}
            | DO sentencias WHILE LPAR condicion RPAR PYC
            {printf("sentencias -> do sentencias while ( condicion ) sentencias ;\n");} 
            | FOR LPAR sentencia PYC condicion PYC sentencia RPAR sentencias
            {printf("sentencias -> for ( sentencia ; condicion; sentencia ) sentencias\n");}
            | parte_izq ASIG expresion PYC
            {printf("sentencias -> parte_izq = expresion\n");}
            | RETURN expresion PYC
            {printf("sentencias -> return expresion ;\n");}
            | RETURN PYC
            {printf("sentencias -> return ;\n");}
            | LKEY sentencia RKEY
            {printf("sentencias -> { sentencia }\n");}
            | SWITCH LPAR expresion RPAR LKEY casos predeterm RKEY
            {printf("sentencias -> switch ( expresion ) { casos prederterm} \n");}
            | BREAK PYC {printf("sentencias -> break ;\n");}
            | PRINT expresion PYC 
            {printf("sentencias -> print expresion ;\n");}; 

casos : CASE PUNES sentencia predeterm
        {printf("casos -> case : sentencia perdeterm\n");}
            | ;

predeterm : DEFAULT PUNES sentencia
            {printf("predeterm -> default : sentencia\n");}
            | ;

parte_izq : ID {printf("parte_izq -> id\n");}
            | var_arreglo {printf("parte_izq -> var_arreglo\n");}
            | ID DOT ID {printf("parte_izq -> id.id\n");}

var_arreglo : ID LCOR expresion RCOR {printf("var_arreglo -> id [ expresion ] \n");}
            | var_arreglo LCOR expresion RCOR {printf("var_arreglo -> var arreglo [ expresion ]\n");};

expresion: expresion MAS expresion 
            {printf("expresion -> expresion + expresion \n");}
            | expresion MENOS expresion 
            {printf("expresion -> expresion - expresion \n");}
            | expresion MUL expresion
            {printf("expresion -> expresion * expresion \n");}
            | expresion DIV expresion
            {printf("expresion -> expresion / expresion \n");}
            | expresion MOD expresion
            {printf("expresion -> expresion mod expresion \n");}
            | var_arreglo
            {printf("expresion -> var_arreglo\n");}
            | CAR {printf("expresion -> car\n");}
            | CADENA {printf("expresion -> cadena\n");}
            | NUMERO {printf("expresion -> num\n");}
            | ID LPAR parametros RPAR 
            {printf("expresion -> id ( parametros )\n");};

parametros: lista_param {printf("parametros-> lista_param\n");}
            | ;

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

int main(int argc, char **argv) {
  if(argc < 2)	return -1;
  f= fopen(argv[1], "r");
  if (!f)	return -1;
  tokens_output = fopen("tokens_output.txt", "w");
  errores_lexicos = fopen("errores_lexicos.txt", "w");
  comentarios = fopen("comentarios.txt", "w");

  yyin = f;
  yyout = tokens_output;

  int p = yyparse();
  if(p)
    printf("La entrada es rechazada de acuerdo a la gramática.\n");
  else
    printf("La entrada es aceptada de acuerdo a la gramática.\n");

  fclose(f);
  fclose(tokens_output);  
  fclose(errores_lexicos);
  fclose(comentarios);
  return 0;
}
