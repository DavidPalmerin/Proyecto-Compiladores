/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 * Modificaciones: Palmerin Morales David Gabriel. 
 */
#include "symtab.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>


/*
 * Busca en la tabla de símbolos un símbolo con el mismo
 * id al recibido.
 * Recibe st, la tabla de símbolos.
 * Recibe id, un apuntador a una cadena.
 * Regresa -1 si no existe un símbolo con tal id.
 * En otro caso, regresa el índice donde se encontró.
*/
int search(symtab *st, char*id){
    int i;
    for(i=0; i <st->count; i++){
        if(strcmp(st->symbols[i].id, id)==0)
            return i;
    }
    return -1;
}

/*
 * Realiza la búsqueda como en la función search().
 * Sin embaro, también busca en parent, que es un apuntador
 * a otra tabla de símbolos.
 * Regresa -1 si no existe.
 * Regres el índice donde se encontró, en otro caso.
*/
int depth_search(symtab *st, char *id)
{      
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL)
        return search(parent, id);
    
    return exists;
}

/*
 * Agrega un nuevo símbolo a la tabla de símbolos.
 * No puede existir otro símbolo en st con el mismo id
 *  que el sym s.
 * Recibe un apuntador a una tabla de símbolos st.
 * Recibe un símbolo s.
 * Regresa -1 si no es posible insertarlo.
 * Regresa 1 si lo insertó.
*/
int insert(symtab *st, sym s){
    if(search(st, s.id)==-1 && st->count<1000){
        st->symbols[st->count] = s;
        st->count++;        
        return 1;
    }
    return -1;
}

/* 
 * Imprime la tabla de símbolos recibida.
 * Recibe un apuntador a tal tabla.
*/
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

/*
 * Imprime en un archivo la tabla de símbolos.
 * Recibe un apuntador a una tabla de símbolos.
 * Recibe un apuntador a un archivo donde se escribirá la
 * respresentación del symtab.
*/
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

/*
 * Obtiene la dirección correspondiente el símbolo con el id recibido.
 * Recibe un apuntador a la tabla de símbolos.
 * Recibe un apuntador a una cadena del que queremos su dirección.
 * Si no existe tal símbolo entonces regresa -1.
*/
int get_dir(symtab *st, char* id){
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL){
        exists = search(parent, id);
        return parent->symbols[exists].dir;
    }
    return st->symbols[exists].dir;
}

/*
 * Obtiene el topo correspondiente al símbolo con el id recibido.
 * Recibe una tabla de símbolos st.
 * Recibe una cadena del símbolo qu queremos.
 * Regresa -1 si no existe tal simbolo con id.
*/
int get_type(symtab* st, char *id){
    symtab *parent = st->parent;
    int exists = search(st, id); 
    if (exists == -1 && parent != NULL){
        exists = search(parent, id);
        return parent->symbols[exists].type;
    }
    return st->symbols[exists].type;
}

/*
 * Inicializa la estructura symtab.
 * Recibe un apuntador al symtab que queremos.
 * Recibe un apuntador al padre que le queremos asignar.
*/
void create_table(symtab *st, void *parent){
    st->count=0;
    st->parent = parent;
}

/*
 * Inicializa la tabla de funciones.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
void create_funtab(funtab *tab){
    tab->count = 0;
}

/*
 * Inserta un registro en la tabla.
 * Recibe la tabla de funciones tab.
 * Recibe el registro rec a agregar.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
int insert_fun(funtab *tab, funrec rec){
    if (tab->count >= 1000)
        return -1;

    tab->funs[tab->count] = rec;
    tab->count += 1;
    return 1;
}

/*
 * Imprime la tabla de funciones recibida st.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
void print_funtable(funtab* st){    
    int i;
    printf("ID\tPARAMS\t COUNTER\n");    
    for(i=0; i < st->count; i++){
        printf("%s\t%d\t%d\n", st->funs[i].id,
        st->funs[i].params, st->funs[i].counter);        
    }

}

/*
 * Verifica si un id es una función en la tabla recibida.
 * Será función si existe un registro con un id igual al recibido.
 * Recibe tab la tabla de funciones.
 * Recibe id a buscar.
 * Regresa 1 si existe, en otro caso 0.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
int is_function(funtab *tab, char id[32])
{
    int i;
    for (i = 0; i < tab->count; i++)
        if (strcmp(tab->funs[i].id, id) == 0)
            return 1;
    return 0;
}

/*
 * Obtiene uno de los registro suqe almacena la tabla.
 * Recibe tab la tabla de registros de funciones funrec.
 * Recibe id que identifica a tal registro.
 * Regresa el registro funrec, si existe.
 * En otro caso, regresa NULL.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
funrec* get_rec(funtab *tab, char id[32])
{
    int i;
    for (i = 0; i < tab->count; i++)
        if (strcmp(tab->funs[i].id, id) == 0){
            return &tab->funs[i];
        }
    return NULL;
}

/*
 * Obtiene el atributo struct_content de un registro funrec.
 * Recibe la tabla st compuesta de registros funrec.
 * Recibe id que identifica al struct_content que buscamos.
 * Regresa -1 si no existe tal identificador en la tabla.
 *
 * Autor: Palmerin Morales David Gabriel.
*/
symtab* get_struct_content(symtab *st, char *id)
{
    symtab *parent = st->parent;
    int exists = search(st, id);
    if (exists == -1 && parent != NULL){
        exists = search(parent, id);
        return parent->symbols[exists].struct_content;
    }
    if (exists) 
        return st->symbols[exists].struct_content;
    return -1;
}


