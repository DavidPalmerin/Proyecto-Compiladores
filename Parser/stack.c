#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#include "stack.h"
 
/*
 * Inicializa una pila creando nuevo espacio y actualizando sus atributos.
 * Recibe s que es el apuntador a la pila.
 * elementSize que es el tamaño de los elementos que contendrá (se recomienda sizeof).
 * freeFn una función para liberar memoria.
*/
void stack_new(stack *s, int elementSize, freeFunction freeFn)
{
  s->list = malloc(sizeof(list));
  // make sure the malloc call didn't fail...
  assert(s->list != NULL);
 
  list_new(s->list, elementSize, freeFn);
}
 
/*
 * Elimina el stack recibido s. 
*/
void stack_destroy(stack *s)
{
  list_destroy(s->list);
  free(s->list);
}
 
/*
 * Agrega un elemento al tope de la pila.
 * Recibe el apuntador s que es la pila.
 * Recibe el elemento element que es el que aregaremos.
*/
void stack_push(stack *s, void *element)
{
  list_prepend(s->list, element);
}
 
/*
 * Elimina el elemento en el tope de la pila.
 * Recibe la pila de la que queremos eliminar el tope.
 * Recibe un apuntador element donde guardará el 
 * elemento eliminado.
*/
void stack_pop(stack *s, void *element)
{
  // don't pop an empty stack!
  assert(stack_size(s) > 0);

  list_head(s->list, element, 1);
}
 
/*
 * Obtiene una copia del eleemnto en el tope de la pila.
 * Recibe s el apuntador a la pila en cuestión.
 * Un apuntador element que es donde guardará la copia del tope.
*/
void stack_peek(stack *s, void *element)
{
  assert(stack_size(s) > 0);
  list_head(s->list, element, 0);
}

/*
 * Obtiene el tope de la pila.
 * Recibe el apuntador a la pila.
 * Recibe el un apuntador donde guardará el elemento.
*/
void stack_top(stack *s, void *element)
{
  list_first(s->list, element);
}
 
/*
 * Obtiene el número de elementos de la pila.
 * Recibe el apuntador a la pila.
*/
int stack_size(stack *s)
{
  return list_size(s->list);
}
