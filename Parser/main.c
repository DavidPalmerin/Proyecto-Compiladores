/* 
 * File:   main.c
 * Author: Adrian Ulises Mercado Martinez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "attributes.h"
#include "backpatch.h"
#include "intermediate_code.h"

//extern FILE* yyin;

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;

// Archivo a leer
extern FILE *f;

// Archivos de salida
extern FILE *tokens_output;
extern FILE *errores_lexicos;
extern FILE *comentarios;
extern FILE *contexts;
extern FILE *err;
extern FILE *producciones;

//Colores 
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"

int main(int argc, char **argv) {
  if(argc < 2)	
    return -1;
  
  f = fopen(argv[1], "r");
  
  if (!f)	
    return -1;

  err = fopen("errores.txt", "w");
  contexts = fopen("contexts.txt", "w");
  comentarios = fopen("comentarios.txt", "w");
  producciones = fopen("producciones.txt", "w");
  tokens_output = fopen("tokens_output.txt", "w");
  errores_lexicos = fopen("errores_lexicos.txt", "w");

  yyin = f;
  yyout = tokens_output;

  int p = yyparse();
  
  if(p)
    printf(ANSI_COLOR_RED  "La entrada es rechazada de acuerdo a la gramática.\n" );
  else
    printf(ANSI_COLOR_GREEN "La entrada es aceptada de acuerdo a la gramática.\n" );

  fclose(f);
  fclose(tokens_output);  
  fclose(errores_lexicos);
  fclose(producciones);
  fclose(comentarios);
  fclose(contexts);
  fclose(err);
  return 0;
}