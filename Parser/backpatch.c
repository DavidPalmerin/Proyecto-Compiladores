/* 
 * File:   backpath.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 20:35
 */
#include "backpatch.h"
#include "intermediate_code.h"
#include <stdio.h>
#include <string.h>

labels create_list(char* l){
    labels ls;
    create_labels(&ls);
    strcpy(ls.label[ls.count], l);
    ls.count++;
    return ls;
}


labels create_empty_list(){
    labels ls;
    create_labels(&ls);    
    return ls;
}


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


char *get_first(labels* ls){
    return ls->label[0];
}
