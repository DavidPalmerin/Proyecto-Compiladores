/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */
#include "symtab.h"
#include <stdio.h>
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

int depth_search(symtab *st, char *id)
{      
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL)
        return search(parent, id);
    
    return exists;
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
    printf("POS\tID\tTIPO\tDIR\tDIM\n");    
    for(i=0; i < st->count; i++){
        printf("%d\t%s\t%d\t%d\t%d\n", i,
        st->symbols[i].id,
        st->symbols[i].type.type,
        st->symbols[i].dir,
        st->symbols[i].type.dim);        
    }
}

void fprint_table(symtab* st, FILE *file){    
    int i;
    fprintf(file,"POS\tID\tTIPO\tDIR\tDIM\n");    
    for(i=0; i < st->count; i++){
        fprintf(file, "%d\t%s\t%d\t%d\t%d\n", i, 
            st->symbols[i].id, 
            st->symbols[i].type.type, 
            st->symbols[i].dir,
            st->symbols[i].type.dim);          
    }
}


int get_dir(symtab *st, char* id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].dir;
    }
}

type get_type(symtab* st, char *id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].type;
    }
}

void create_table(symtab *st, void *parent){
    st->count=0;
    st->parent = parent;
}


