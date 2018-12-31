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


int main(int argc, char **argv) {
  if(argc < 2)	
    return -1;
  
  f = fopen(argv[1], "r");
  
  if (!f)	
    return -1;

  err = fopen("errores.txt", "w");
  contexts = fopen("contexts.txt", "w");
  comentarios = fopen("comentarios.txt", "w");
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
  fclose(tokens_output);  
  fclose(errores_lexicos);
  fclose(comentarios);
  fclose(contexts);
  fclose(err);
  FILE * errores = fopen("errores.txt","r");
  if(errores){
    printf("\n -----------\t  [Errores]  \t-----------\n\n");
    char read;
    while((read = getc(errores)) != EOF)
        putchar(read);
    printf("\n -----------\t[Fin errores]\t-----------\n\n\n");
    fclose(errores);
  }
  return 0;
}