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

char *pop_label(labels* ls){
    char *t= (char*) malloc(32*sizeof(char));
    if(ls->count>-1){        
        strcpy(t,ls->label[ls->count-1]);
        ls->count--;        
    }
    return t;
}

void push_label(labels* ls, char *l){
    if(ls->count<1000){
        strcpy(ls->label[ls->count], l);
        ls->count++;
    }
}

char *get_top_label(labels* ls){
    return ls->label[ls->count-1];
}

char *get_top_label_previous(labels* ls){
    return ls->label[ls->count-2];
}

void create_labels(labels* ls){
    ls->count=0;
}


void print_stack_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=ls->count-1; i >-1; i--){
        printf("%s\n", ls->label[i]);
    }
}


void print_list_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=0;i<ls->count; i++){
        printf("%s\n", ls->label[i]);
    }
}