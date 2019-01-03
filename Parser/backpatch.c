/* 
 * File:   backpath.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 20:35
 * No se realizan modificaciones al archivo proporcionado por el profesor.
 */
#include "backpatch.h"
#include "intermediate_code.h"
#include <stdio.h>
#include <string.h>


/*
 * Crea una nueva lista de labels.
 * Recibe un apuntador a una cadena que será
 * el primer label en almacenar.
 * Reegresa una lista labels inicializada con l como
 * primer elemento.
*/
labels create_list(char* l){
    labels ls;
    create_labels(&ls);
    strcpy(ls.label[ls.count], l);
    ls.count++;
    return ls;
}

/*
 * Crea una lista de labels vacía.
*/
labels create_empty_list(){
    labels ls;
    create_labels(&ls);    
    return ls;
}


/*
 * Une dos structs labels en uno solo.
 * Los elementos de ls1 se agregarán primero a la nueva mezcla.
 * Recibe ls1 que es una lista de labels
 * Recibe ls2 que es una lista de labels.
 * Regresa la structura con la mezcla de ambas.
*/
labels merge(labels* ls1, labels* ls2){
    labels ls;
    create_labels(&ls);
    int i;
    for(i =0; i< ls1->count;i++){
        strcpy(ls.label[ls.count++], ls1->label[i]);
    }
    for(i =0; i< ls2->count;i++){
        strcpy(ls.label[ls.count++], ls2->label[i]);
    }
    return ls;
}

/*
 * Realiza la sustitución de todas las labels por la cadena l
 * Esta sustitución se realiza en la estructura ic.
 * Todas las cadenas en ic* que estén en labels se sustituirán por l.
 * Recibe labels que queremos sustituir.
 * La nueva cadena que será el remplazo.
 * El codigo intermedio donde reemplazaremos.
*/
int backpatch(labels* ls, char* l, ic* code){
    int i, j;
    for(i=0; i < ls->count; i++){
        for(j=0; j<code->count; j++){
            if(strcmp(code->c[j].res, ls->label[i])==0){
                strcpy(code->c[j].res, l);
            }
        }
    }
}

/*
 * Obtiene la primer etiqueta agregada.
*/
char *get_first(labels* ls){
    return ls->label[0];
}
