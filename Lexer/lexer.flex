%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "tokens.h"

	/* Variables para analizador léxico. */
	int pos;
	FILE *f;
	FILE *tokens_output;
	FILE *errores_lexicos;
%}

%option yylineno
%option noyywrap

id      [_a-zA-Z][_a-zA-Z0-9]*
digito 	[0-9]
int     [\-+]?[0-9]+
char    \'[a-zA-Z]\'
float   [\-+]?[0-9]*.?{digito}{1,7}
double  [\-+]?[0-9]*.?{digito}{8,16}
cadena  \".*\"
espacio [ \t]

%%

"int"		{ fprintf(tokens_output, "Encontré un tipo int %s\n", yytext);
			  //return INT;
			}

"float" 	{ fprintf(tokens_output, "Encontré un tipo float%s\n", yytext);
			  //return FLOAT;
			}

"double"	{ fprintf(tokens_output, "Encontré un DOUBLE %s\n", yytext);
			  //return DOUBLE;
			}
"char"		{ fprintf(tokens_output, "Encontré un CAR %s\n", yytext);
			  //return CAR;
			}
"void"		{ fprintf(tokens_output, "Encontré un VOID %s\n", yytext);
			  //return VOID;
			}

"struct"	{ fprintf(tokens_output, "Encontré un STRUCT %s\n", yytext);
			  //return STRUCT;
			}

"if" 		{ fprintf(tokens_output, "Encontré un IF %s\n", yytext);
			  //return IF;
			}

"while"		{ fprintf(tokens_output, "Encontré un WHILE %s\n", yytext);
			  //return WHILE;
			}
"for"		{ fprintf(tokens_output, "Encontré un FOR %s\n", yytext);
			  //return FOR;
			}
"do"		{ fprintf(tokens_output, "Encontré un DO %s\n", yytext);
			  //return DO;
			}
"switch"	{ fprintf(tokens_output, "Encontré un SWITCH %s\n", yytext);
			  //return SWITCH;
			}
"case"		{ fprintf(tokens_output, "Encontré un CASE %s\n", yytext);
			  //return CASE;
			}
"default"	{ fprintf(tokens_output, "Encontré un DEFAULT %s\n", yytext);
			  //return DEFAULT;
			}
"true"		{ fprintf(tokens_output, "Encontré un TRUE %s\n", yytext);
			  //return TRUE;
			}
"false"		{ fprintf(tokens_output, "Encontré un FALSE %s\n", yytext);
			  //return FALSE;
			}
"func"		{ fprintf(tokens_output, "Encontré un FUNC %s\n", yytext);
			  //return FUNC;
			}

"print"		{
			  fprintf(tokens_output, "Encontré un print %s\n", yytext);
			  //return PRINT;
			}

"="			{ fprintf(tokens_output, "Encontré un ASIG %s\n", yytext);
			  //return ASIG;
			}
"&&"		{ fprintf(tokens_output, "Encontré un AND %s\n", yytext);
			  //return AND;
			}
"||"		{ fprintf(tokens_output, "Encontré un OR %s\n", yytext);
			  //return OR;
			}
"=="		{ fprintf(tokens_output, "Encontré un IGUAL %s\n", yytext);
			  //return IGUAL;
			}
"!="		{ fprintf(tokens_output, "Encontré un DIF %s\n", yytext);
			  //return DIF;
			}
">"			{ fprintf(tokens_output, "Encontré un MAYOR %s\n", yytext);
			  //return MAYOR;
			}
"<"			{ fprintf(tokens_output, "Encontré un MENOR %s\n", yytext);
			  //return MENOR;
			}
">="		{ fprintf(tokens_output, "Encontré un MAYOR_IGUAL %s\n", yytext);
			  //return MAYOR_IGUAL;
			}
"<="		{ fprintf(tokens_output, "Encontré un MENOR_IUAL %s\n", yytext);
			  //return MENOR_IUAL;
			}
"+"			{ fprintf(tokens_output, "Encontré un MAS %s\n", yytext);
			  //return MAS;
			}
"-"			{ fprintf(tokens_output, "Encontré un MENOS %s\n", yytext);
			  //return MENOS;
			}
"*"			{ fprintf(tokens_output, "Encontré un MUL %s\n", yytext);
			  //return MUL;
			}
"/"			{ fprintf(tokens_output, "Encontré un DIV %s\n", yytext);
			  //return DIV;
			}
"%"			{ fprintf(tokens_output, "Encontré un MOD %s\n", yytext);
			  //return MOD;
			}

"!"			{ fprintf(tokens_output, "Encontré un NOT %s\n", yytext);
			  //return NOT;
			}
"("			{ fprintf(tokens_output, "Encontré un LPAR %s\n", yytext);
			  //return LPAR;
			}
")"			{ fprintf(tokens_output, "Encontré un RPAR %s\n", yytext);
			  //return RPAR;
			}
"{"			{ fprintf(tokens_output, "Encontré un LKEY %s\n", yytext);
			  //return LKEY;
			}
"}"			{ fprintf(tokens_output, "Encontré un RKEY %s\n", yytext);
			  //return RKEY;
			}
"["			{ fprintf(tokens_output, "Encontré un LCOR %s\n", yytext);
			  //return LCOR;
			}
"]"			{ fprintf(tokens_output, "Encontré un RCOR %s\n", yytext);
			  //return RCOR;
			}
";"			{ fprintf(tokens_output, "Encontré un PC %s\n", yytext);
			  //return PC;
			}
","			{ fprintf(tokens_output, "Encontré un COM %s\n", yytext);
			  //return COM;
			}
":"			{ fprintf(tokens_output, "Encontré un PUNES %s\n", yytext);
			  //return PUNES;
			}
"."			{ fprintf(tokens_output, "Encontré un DOT %s\n", yytext);
			  //return DOT;
			}

\n 			{
			 pos = 0;
			}

{id}		{
			 fprintf(tokens_output, "Encontré un id: %s\n", yytext);
			 //return ID;
			}

{char}		{ 
   			  fprintf(tokens_output, "Encontré un char: %s\n", yytext);
			  //return CAR;
			}

{float}		{ 
			  fprintf(tokens_output, "Encontré un float: %s\n", yytext);
			  //return NUMERO; 
			}
{double}	{ 
			  fprintf(tokens_output, "Encontré un double: %s\n", yytext);
			  //return NUMERO;
			}

{cadena}	{ 
			  fprintf(tokens_output, "Encontré una cadena: %s\n", yytext);
			  //return CADENA;
			}

{espacio}	{
			 pos++;
			 fprintf(tokens_output, "Encontré un espacio\n");
			}

.			{
				pos++;
				fprintf(errores_lexicos, "[ERROR] Se encontró una palabra inválida en la línea %d en la posición %d.", yylineno, pos);
			}

<<EOF>>		{
				return MYEOF;
			}



%%

int main(int argc, char** argv)
{
	f = fopen(argv[1], "r");
	tokens_output = fopen("tokens_output.txt", "w");
	errores_lexicos = fopen("errores_lexicos.txt", "w");

	yyin = f;
	yyout = tokens_output;

	yylex();

	fclose(yyin);
	fclose(yyout);
	fclose(errores_lexicos);
}


