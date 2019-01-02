/* 
 * File:   attributes.c
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:59
 */

#include "attributes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Elimina el ultimo elemento agregado en labels.
 * Recibe el apuntador a labels.
 * Regresa el label que contiene.
*/
char *pop_label(labels* ls){
    char *t= (char*) malloc(32*sizeof(char));
    if(ls->count>-1){        
        strcpy(t,ls->label[ls->count-1]);
        ls->count--;        
    }
    return t;
}

/*
 * Agrega un nuevo label al labels recibido.
 * Recibe labels.
 * Recibe un apuntador a una cadena que es la etiqueta/label.
*/
void push_label(labels* ls, char *l){
    if(ls->count<1000){
        strcpy(ls->label[ls->count], l);
        ls->count++;
    }
}

/*
 * Obtiene sin eliminar el ´último label agregado.
 * Recibe la lista de labels
 * Regresa una cadena que es el label.
*/
char *get_top_label(labels* ls){
    return ls->label[ls->count-1];
}

/*
 * Obtiene el penúltimo label.
 * Recibe la lista de labels.
 * Regresa una cadena que es la penúltima agregada.
*/
char *get_top_label_previous(labels* ls){
    return ls->label[ls->count-2];
}

/*
 * Inicializa nuestra estructura labels.
*/
void create_labels(labels* ls){
    ls->count=0;
}

/*
 * Imprime los labels como stack.
 * Recibe un apuntador a labels.
*/
void print_stack_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=ls->count-1; i >-1; i--){
        printf("%s\n", ls->label[i]);
    }
}

/* Imprime los labels como lista. 
 * Recibe un apuntador a los labels.
*/
void print_list_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=0;i<ls->count; i++){
        printf("%s\n", ls->label[i]);
    }
}