%{
	/*
     * Análizador Léxico.
     * Autores: Melissa Mendez Servín
     * 			Palmerin Morales David Gabriel.
     *
     * Github: https://github.com/DavidPalmerin/Proyecto-Compiladores
	*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>

	#include "attributes.h"
	#include "parser.tab.h"		

	/* Variables para analizador léxico. */
	int pos;
	
	/* Archivos de analisis. */
	FILE *f;
	FILE *tokens_output;
	FILE *errores_lexicos;
	FILE *comentarios;
%}

%option yylineno
%option noyywrap

%x q_comment_linea
%x q_comment_mult

letra   [a-zA-Z]
id      [_a-zA-Z][_a-zA-Z0-9]{0,30}
digito 	[0-9]
int    	[\-]?[0-9]+
char    \'[^']\'
float   [\-]?[0-9]*\.{digito}{1,7}
double  [\-]?[0-9]*\.{digito}{8,16}
cadena  \"[^"]*\"
espacio [ \t]
especial \\([^({digito}|{letra}|{esp})]|[(){}])

%%

"int"		{ 
				fprintf(tokens_output, "Encontré un tipo int %s\n", yytext);
				return INT;
			}

"float" 	{ 
				fprintf(tokens_output, "Encontré un tipo float%s\n", yytext);
				return FLOAT;
			}

"double"	{ 
				fprintf(tokens_output, "Encontré un DOUBLE %s\n", yytext);
				return DOUBLE;
			}

"char"		{ 
				fprintf(tokens_output, "Encontré un CHAR %s\n", yytext);
				return CHAR;
			}

"void"		{ 
				fprintf(tokens_output, "Encontré un VOID %s\n", yytext);
				return VOID;
			}


"struct"	{ 
				fprintf(tokens_output, "Encontré un STRUCT %s\n", yytext);
				return STRUCT;
			}


"if" 		{ 
				fprintf(tokens_output, "Encontré un IF %s\n", yytext);
				return IF;
			}

"else" 		{ 
				fprintf(tokens_output, "Encontré un ELSE %s\n", yytext);
				return ELSE;
			}

"while"		{ 
				fprintf(tokens_output, "Encontré un WHILE %s\n", yytext);
				return WHILE;
			}

"for"		{ 
				fprintf(tokens_output, "Encontré un FOR %s\n", yytext);
				return FOR;
			}

"do"		{ 
				fprintf(tokens_output, "Encontré un DO %s\n", yytext);
				return DO;
			}

"switch"	{ 
				fprintf(tokens_output, "Encontré un SWITCH %s\n", yytext);
				return SWITCH;
			}

"case"		{ 
				fprintf(tokens_output, "Encontré un CASE %s\n", yytext);
				return CASE;
			}

"default"	{ 
				fprintf(tokens_output, "Encontré un DEFAULT %s\n", yytext);
				return DEFAULT;
			}

"return"	{ 
				fprintf(tokens_output, "Encontré un RETURN %s\n", yytext);
				return RETURN;
			}

"break"		{ 
				fprintf(tokens_output, "Encontré un BREAK %s\n", yytext);
				return BREAK;
			}

"true"		{ 
				fprintf(tokens_output, "Encontré un TRUE %s\n", yytext);
				return TRUE;
			}

"false"		{ 
				fprintf(tokens_output, "Encontré un FALSE %s\n", yytext);
				return FALSE;
			}

"func"		{ 
				fprintf(tokens_output, "Encontré un FUNC %s\n", yytext);
				return FUNC;
			}


"print"		{
			  
				fprintf(tokens_output, "Encontré un print %s\n", yytext);
				return PRINT;
			}


"="			{ 
				fprintf(tokens_output, "Encontré un ASIG %s\n", yytext);
				return ASIG;
			}

"&&"		{ 
				fprintf(tokens_output, "Encontré un AND %s\n", yytext);
				return AND;
			}

"||"		{ 
				fprintf(tokens_output, "Encontré un OR %s\n", yytext);
				return OR;
			}

"=="		{ 
				fprintf(tokens_output, "Encontré un IGUAL %s\n", yytext);
				return IGUAL;
			}

"!="		{ 
				fprintf(tokens_output, "Encontré un DIF %s\n", yytext);
				return DIF;
			}

">"			{ 
				fprintf(tokens_output, "Encontré un MAYOR %s\n", yytext);
				return MAYOR;
			}

"<"			{ 
				fprintf(tokens_output, "Encontré un MENOR %s\n", yytext);
				return MENOR;
			}

">="		{ 
				fprintf(tokens_output, "Encontré un MAYOR_IGUAL %s\n", yytext);
				return MAYOR_IGUAL;
			}

"<="		{ 
				fprintf(tokens_output, "Encontré un MENOR_IGUAL %s\n", yytext);
				return MENOR_IGUAL;
			}

"+"			{ 
				fprintf(tokens_output, "Encontré un MAS %s\n", yytext);
				return MAS;
			}

"-"			{ 
				fprintf(tokens_output, "Encontré un MENOS %s\n", yytext);
				return MENOS;
			}

"*"			{ 
				fprintf(tokens_output, "Encontré un MUL %s\n", yytext);
				return MUL;
			}

"/"			{ 
				fprintf(tokens_output, "Encontré un DIV %s\n", yytext);
				return DIV;
			}

"%"			{ 
				fprintf(tokens_output, "Encontré un MOD %s\n", yytext);
				return MOD;
			}


"!"			{ 
				fprintf(tokens_output, "Encontré un NOT %s\n", yytext);
				return NOT;
			}

"("			{ 
				fprintf(tokens_output, "Encontré un LPAR %s\n", yytext);
				return LPAR;
			}

")"			{ 
				fprintf(tokens_output, "Encontré un RPAR %s\n", yytext);
				return RPAR;
			}

"{"			{ 
				fprintf(tokens_output, "Encontré un LKEY %s\n", yytext);
				return LKEY;
			}

"}"			{ 
				fprintf(tokens_output, "Encontré un RKEY %s\n", yytext);
				return RKEY;
			}

"["			{ 
				fprintf(tokens_output, "Encontré un LCOR %s\n", yytext);
				return LCOR;
			}

"]"			{ 
				fprintf(tokens_output, "Encontré un RCOR %s\n", yytext);
				return RCOR;
			}

";"			{ 
				fprintf(tokens_output, "Encontré un PYC %s\n", yytext);
				return PYC;
			}

","			{ 
				fprintf(tokens_output, "Encontré un COM %s\n", yytext);
				return COM;
			}

":"			{ 
				fprintf(tokens_output, "Encontré un PUNES %s\n", yytext);
				return PUNES;
			}

"."			{ 
				fprintf(tokens_output, "Encontré un DOT %s\n", yytext);
				return DOT;
			}

\n 			{
				pos = 0;
			}

{id}		{
				fprintf(tokens_output, "Encontré un id: %s\n", yytext);
				strcpy(yylval.id, yytext);
				return ID;
			}

{char}		{ 
				fprintf(tokens_output, "Encontré un char: %s\n", yytext);
				yylval.car = yytext;
				return CAR;
			}

{especial}		{ 
				fprintf(tokens_output, "Encontré un símbolo especial: %s\n", yytext);
				yylval.car = yytext;
				return CAR;
			}

{int}		{ 
				fprintf(tokens_output, "Encontré un int: %s\n", yytext);
				strcpy(yylval.num.val, yytext);
				yylval.num.type = 2;	
				return NUMERO; 
			}

{float}		{ 
				fprintf(tokens_output, "Encontré un float: %s\n", yytext);
				strcpy(yylval.num.val, yytext);
				yylval.num.type = 3;
				return NUMERO; 
			}

{double}	{ 
				fprintf(tokens_output, "Encontré un double: %s\n", yytext);
				strcpy(yylval.num.val, yytext);
				yylval.num.type = 4;
				return NUMERO;
			}

{cadena}	{ 
				fprintf(tokens_output, "Encontré una cadena: %s\n", yytext);
				yylval.cadena = yytext;
				return CADENA;
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
				return 0;
			}

"/*"		{
			  pos += 2;
			  fprintf(comentarios, "\nEncontré el siguiente comentario multilínea en la línea %d: \n\t", yylineno);
			  BEGIN(q_comment_mult);
			}

"//"		{
			  pos += 2;
			  fprintf(comentarios, "\nEncontré el siguiente comentario unilínea en la línea %d: \n\t", yylineno);
			  BEGIN(q_comment_linea);
			}

<q_comment_linea>.* 	{
							pos += strlen(yytext);
							fprintf(comentarios, "\t%s\n", yytext);
							BEGIN(INITIAL);
						}

<q_comment_mult>[^"*/"] {
							pos += strlen(yytext);
							fprintf(comentarios, "%s", yytext);
						}

<q_comment_mult>"*/"	{
							pos += 2;
							fprintf(comentarios, "\n");
							BEGIN(INITIAL);
						}

%%
/*
int main(int argc, char** argv)
{
	f = fopen(argv[1], "r");
	tokens_output = fopen("tokens_output.txt", "w");
	errores_lexicos = fopen("errores_lexicos.txt", "w");
	comentarios = fopen("comentarios.txt", "w");

	yyin = f;
	yylex();

	fclose(yyin);
	fclose(yyout);
	fclose(errores_lexicos);
	fclose(comentarios);
}
*/
