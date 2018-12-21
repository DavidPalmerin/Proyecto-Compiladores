/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */
#include "symtab.h"
#include <stdio.h>
#include <string.h>


int search(symtab *st, char*id){
    int i;
    for(i=0; i <st->count; i++){
        if(strcmp(st->symbols[i].id, id)==0)
            return i;
    }
    return -1;
}

int insert(symtab *st, sym s){
    if(search(st, s.id)==-1 && st->count<1000){
        st->symbols[st->count] = s;
        st->count++;        
        return 1;
    }
    return -1;
}

void print_table(symtab* st){    
    int i;
    printf("POS\tID\tTIPO\tDIR\n");    
    for(i=0; i < st->count; i++){
        printf("%d\t%s\t%d\t%d\n", i, st->symbols[i].id, st->symbols[i].type, st->symbols[i].dir);        
    }
}


int get_dir(symtab *st, char* id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].dir;
    }
}

int get_type(symtab* st, char *id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].type;
    }
}

void create_table(symtab *st){
    st->count=0;
}