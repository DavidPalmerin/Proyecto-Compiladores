#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h> 
#include "list.h"
 

/*
 * Inicializa una nueva lista.
 * Recibe el apuntador a la lista para crearle memoria.
 * Recibe elementSize que es el tamaño de los elementos que almacena.
 * Recibe freeFn una función para liberar memoria.
*/
void list_new(list *list, int elementSize, freeFunction freeFn)
{
  assert(elementSize > 0);
  list->logicalLength = 0;
  list->elementSize = elementSize;
  list->head = list->tail = NULL;
  list->freeFn = freeFn;
}

/*
 * Función para eliminar una lista.
 * Recibe el apuntador de la lista que eliminaremos.
 * Usa la función freeFn.
*/ 
void list_destroy(list *list)
{
  listNode *current;
  while(list->head != NULL) {
    current = list->head;
    list->head = current->next;

    if(list->freeFn) {
      list->freeFn(current->data);
    }

    free(current->data);
    free(current);
  }
}
 
/*
 * Función que agrega un elemento al inicio de la lista.
 * Recibe el apuntador a la lista.
 * Recibe el elemento a agregar.
*/
void list_prepend(list *list, void *element)
{
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  memcpy(node->data, element, list->elementSize);

  node->next = list->head;
  list->head = node;

  // first node?
  if(!list->tail) {
    list->tail = list->head;
  }

  list->logicalLength++;
}
 
/*
 * Función que agrega un nuevo elemento a la lista hasta el final.
 * Recibe un apuntador a la lista
 * Recibe el elemento que queremos agregar.
*/
void list_append(list *list, void *element)
{
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  node->next = NULL;

  memcpy(node->data, element, list->elementSize);

  if(list->logicalLength == 0) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->logicalLength++;
}

/* Obtiene el primer elemento de la lista
 * Recibe el apuntador a la lista.
 * Recibe un elemento donde se guardara el apuntador a la cabeza.
*/
void list_first(list *list, void *element)
{
  element = list->head;
}

/*
 * Obtiene y elimina el primer elemento de la lista.
 * Recibe el apuntador a la lista.
 * Recibe el elemento donde se guardará la cabeza.
 * Recibe un entero para indicar si se elimina el elemento.
 * 1 Indica eliminar el elemento.
 * Cualquier otro numero no lo eliminará.
*/
void list_head(list *list, void *element, int removeFromList)
{
  assert(list->head != NULL);
 
  listNode *node = list->head;
  memcpy(element, node->data, list->elementSize);
 
  if(removeFromList == 1) {
    list->head = node->next;
    list->logicalLength--;
 
    free(node->data);
    free(node);
  }
}

/*
 * Otiene una copiia del último elemento de la lista.
 * Recibe el apuntador a lista.
 * Recibe el elemento donde se guardará la copia. 
*/ 
void list_tail(list *list, void *element)
{
  assert(list->tail != NULL);
  listNode *node = list->tail;
  memcpy(element, node->data, list->elementSize);
}
 
/*
 * Obtiene la longitud de la lista.
 * Recibe un apuntador a la lista.
 * Regresa un entero que es el numero de elementos en la lista.
*/
int list_size(list *list)
{
  return list->logicalLength;
}
