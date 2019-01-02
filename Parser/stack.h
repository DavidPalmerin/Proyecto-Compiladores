#ifndef __STACK_H
#define __STACK_H

/*
 * Estructura de datos: Pila
 * Se obtiene del siguiente sitio: 
 * https://pseudomuto.com/2013/06/implementing-a-generic-stack-in-c/
*/

#include "list.h"
 
/* Implementación de pilas basada en listas ligadas. Ver list.h */
typedef struct {
  list *list;
} stack;
 
/* Declaraciones de funciones. */
void stack_new(stack *s, int elementSize, freeFunction freeFn);
void stack_destroy(stack *s);
void stack_push(stack *s, void *element);
void stack_pop(stack *s, void *element);
void stack_peek(stack *s, void *element);
void stack_top(stack *s, void *element);
int stack_size(stack *s);

#endif
