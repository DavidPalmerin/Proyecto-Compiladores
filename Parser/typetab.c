/* 
 * File:   typetab.h
 * Author: Melissa Mendez Servin
 *
 * Created on 25 de diciembre de 2018,
 */
#include "typetab.h"
#include <stdio.h>
#include <string.h>

/*
 * Devuelve un tipo nuevo, inicializando todos sus
 * valores en -1.
 * Autora : Mendez Servin Melissa.
 */
type new_type(){
    type t;
    t.type = -1;
    t.tam = -1;
    t.dim = -1;
    t.base = -1;
    return t;
}
/*
 * Agrega al tipo t dentro de la tabla dada, si
 * se trata de la tabla global, agrega en su  
 * siguiente contador, en otro caso, agrega a 
 * partir del último tipo agregado en su tabla
 * padre (si se trata del primero), en otro caso
 * agrega a partir del último de la tabla actal,
 * es decir, de su contador.
 * Autora : Mendez Servin Melissa.
 */
int insert_type(typetab *tt, type t){
    if(tt->parent == NULL){
        if(t.base > tt->count)
            return -1;
        tt->types[tt->count] = t;
        tt->count++;  
        return 1;
    }
    else
    {
        typetab *parent = tt->parent;
        int new_count = parent->count + 1;
        if(tt->count >= new_count){
            tt->types[tt->count] = t;
            tt->count++;
        }
        else
        {
            tt->types[new_count] = t;
            tt->count = new_count + 1; 
        }
        return 1;
    }    
}
/*
 * Imprime en consola la tabla tipos dada.
 * Autora : Mendez Servin Melissa.
 */
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
/*
 * Escribe en el archivo dado la tabla de tipos
 * recibida.
 * Autora : Mendez Servin Melissa.
 */
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
/*
 * Imprime en consola al tipo dado (auxiliar para
 * depurar código).
 * Autora : Mendez Servin Melissa.
 */
void print_type(type t){
    printf("TIPO: %d\t%d\t%d\t%d\n", 
        t.type, 
        t.tam, 
        t.dim,
        t.base);         
}
/*
 * Devuelve el tamalo del tipo en la posisción dada 
 * dentro de la tabla de típos actual, en otro caso
 * busca dentro de la tabla de tipos padre.
 * Autora : Mendez Servin Melissa.
 */
int get_tam(typetab* tt, int pos){
    int tam = tt->types[pos].tam;
    if(tam == 0){
        typetab *parent = tt->parent;
        tam = parent->types[pos].tam;
    }
    return tam;
}
/*
 * Devuelve la dimensión del tipo en la posisción dada 
 * dentro de la tabla de típos actual, en otro caso
 * busca dentro de la tabla de tipos padre.
 * Autora : Mendez Servin Melissa.
 */
int get_dim(typetab* tt, int pos){
    int dim = tt->types[pos].dim;
    if(dim == 0){
        typetab *parent = tt->parent;
        dim = parent->types[pos].dim;
    }
    return dim;
}
/*
 * Devuelve la base del tipo en la posisción dada 
 * dentro de la tabla de típos actual, en otro caso
 * busca dentro de la tabla de tipos padre.
 * Autora : Mendez Servin Melissa.
 */
int get_base(typetab* tt, int pos){
    int base = tt->types[pos].base;
    if(base == 0){
        typetab *parent = tt->parent;
        base = parent->types[pos].base;
    }
    return base;
}
/*
 * Crea una tabla de tipos, e incializa su contador y 
 * los tipos predefinidos o base (void,char,int,float,
 * double,struc y cadena).
 * Autora : Mendez Servin Melissa.
 */
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


