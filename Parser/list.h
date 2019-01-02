#ifndef __LIST_H
#define __LIST_H

/*
 * Estructura de datos: Lista
 * Se obtiene del siguiente sitio: 
 * https://pseudomuto.com/2013/05/implementing-a-generic-linked-list-in-c/
*/
 
typedef void (*freeFunction)(void *);
 
 
typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;
 
typedef struct {
  int logicalLength;
  int elementSize;
  listNode *head;
  listNode *tail;
  freeFunction freeFn;
} list;
 
void list_new(list *list, int elementSize, freeFunction freeFn);
void list_destroy(list *list);
 
void list_prepend(list *list, void *element);
void list_append(list *list, void *element);
void list_first(list *list, void *element);
int list_size(list *list);

void list_head(list *list, void *element, int removeFromList);
void list_tail(list *list, void *element); 

#endif
