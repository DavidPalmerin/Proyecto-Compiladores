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
    printf("POS\tID\tTIPO\tDIR\n");    
    for(i=0; i < st->count; i++){
        printf("%d\t%s\t%d\t%d\n", i,
        st->symbols[i].id,
        st->symbols[i].type,
        st->symbols[i].dir);        
    }
}

void fprint_table(symtab* st, FILE *file){    
    int i;
    fprintf(file,"POS\tID\tTIPO\tDIR\n");    
    for(i=0; i < st->count; i++){
        fprintf(file, "%d\t%s\t%d\t%d\n", i,
        st->symbols[i].id, 
        st->symbols[i].type, 
        st->symbols[i].dir);        
    }
}

int get_dir(symtab *st, char* id){
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL){
        exists = search(parent, id);
        return parent->symbols[exists].dir;
    }
    return st->symbols[exists].dir;
}

int get_type(symtab* st, char *id){
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL){
        exists = search(parent, id);
        return parent->symbols[exists].type;
    }
    return st->symbols[exists].type;
}

void create_table(symtab *st, void *parent){
    st->count=0;
    st->parent = parent;
}

void create_funtab(funtab *tab){
    tab->count = 0;
}

int insert_fun(funtab *tab, funrec rec){
    if (tab->count >= 1000)
        return -1;

    tab->funs[tab->count] = rec;
    tab->count += 1;
    return 1;
}

void print_funtable(funtab* st){    
    int i;
    printf("ID\tPARAMS\t COUNTER\n");    
    for(i=0; i < st->count; i++){
        printf("%s\t%d\t%d\n", st->funs[i].id,
        st->funs[i].params, st->funs[i].counter);        
    }

}

int is_function(funtab *tab, char id[32])
{
    int i;
    for (i = 0; i < tab->count; i++)
        if (strcmp(tab->funs[i].id, id) == 0)
            return 1;
    return 0;
}

funrec* get_rec(funtab *tab, char id[32])
{
    int i;
    for (i = 0; i < tab->count; i++)
        if (strcmp(tab->funs[i].id, id) == 0)
            return &tab->funs[i];
}


