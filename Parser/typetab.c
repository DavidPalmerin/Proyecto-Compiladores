/* 
 * File:   typetab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */
#include "typetab.h"
#include <stdio.h>
#include <string.h>

type new_type(){
    type t;
    t.type = -1;
    t.tam = -1;
    t.dim = -1;
    t.base = -1;
    return t;
}
type new_type2(int tipo,int tam,int dim,int base){
    type t;
    t.type = tipo;
    t.tam = tam;
    t.dim = dim;
    t.base = base;
    return t;
}   
type depth_search_type(typetab *tt, int pos)
{   typetab *parent = tt->parent;
    type exists = tt->types[pos]; 
    if (exists.type == 0 && parent != NULL)
        exists = parent->types[pos];
    printf("pos = %d,tipoooo-> %d\n",pos,exists.type );
    return exists;
    //return tt->types[pos];
}
int insert_type(typetab *tt, type t){
    if(t.base > tt->count)
        return -1;
    tt->types[tt->count] = t;
    tt->count++;  
    //printf("Se guardó tipo.\n");      
    return 1;
}
void print_table_types(typetab* tt){    
    int i;
    printf("POS\ttype\tTAM\tDIM\tT_BASE\n");    
    for(i=0; i < tt->count; i++){
        printf("%d\t%d\t%d\t%d\t%d\n", i, 
            tt->types[i].type, 
            tt->types[i].tam, 
            tt->types[i].dim,
            tt->types[i].base);          
    }
}
void fprint_table_types(typetab* tt, FILE *file){    
    int i;
    fprintf(file,"POS\ttype\tTAM\tDIM\tT_BASE\n");    
    for(i=0; i < tt->count; i++){
        fprintf(file, "%d\t%d\t%d\t%d\t%d\n", i, 
            tt->types[i].type, 
            tt->types[i].tam, 
            tt->types[i].dim,
            tt->types[i].base);          
    }
}
void print_type(type t){
   // if (tt->count < i)
    printf("TIPO: %d\t%d\t%d\t%d\n", 
        t.type, 
        t.tam, 
        t.dim,
        t.base);
   // else printf("Error: No existe tipo.\n");          
}
int get_type_(typetab* tt, int pos){
    type t = depth_search_type(tt, pos);
    return t.type;
}

int get_tam(typetab* tt, int pos){
    int tam = tt->types[pos].tam;
    if(tam == 0){
        typetab *parent = tt->parent;
        tam = parent->types[pos].tam;
    }
    return tam;
}

int get_dim(typetab* tt, int pos){
    int dim = tt->types[pos].dim;
    if(dim == 0){
        typetab *parent = tt->parent;
        dim = parent->types[pos].dim;
    }
    return dim;
}

int get_base(typetab* tt, int pos){
    int base = tt->types[pos].base;
    if(base == 0){
        typetab *parent = tt->parent;
        base = parent->types[pos].base;
    }
    return base;
}
void create_table_types(typetab *tt, void *parent){
    // Tipos base
    type void_type = new_type();
    void_type.type = 0;
    
    type char_type = new_type();
    char_type.type = 1;
    char_type.tam = 1;

    type int_type = new_type();
    int_type.type = 2;
    int_type.tam = 4;

    type float_type = new_type();
    float_type.type = 3;
    float_type.tam = 4;

    type double_type = new_type();
    double_type.type = 2;
    double_type.tam = 8;

    type struct_type = new_type();
    struct_type.type = 5;

    type string_type = new_type();
    string_type.type = 6;
    
    tt->parent = parent;
    tt->types[0] = void_type;
    tt->types[1] = char_type;
    tt->types[2] = int_type;
    tt->types[3] = float_type;
    tt->types[4] = double_type;
    tt->types[5] = struct_type;
    tt->types[6] = string_type;
    tt->count=7;
}


