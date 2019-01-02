/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 * Modificado el 1 de Enero de 2019
 * Se agregan nuevas funciones y definiciones.
 */
#include <stdio.h>
#include "stack.h"

#ifndef SYMTAB_H
#define SYMTAB_H

#ifdef __cplusplus
extern "C" {
#endif

    struct _symbol{
        char id[32];
        int type;
        int dir;
        void *struct_content;
    };
    
    typedef struct _symbol sym;
    
    typedef struct _symtab{
        sym symbols[1000];
        int count;
        int last_dir;
        void *parent;
    } symtab;


    /* Tabla para almacenar contextos de funciones.
     * Se eligió crear una tabla aparte para facilitar su uso.
     * Una alternativa era un apuntador en symtab a otra tabla de símbolos.
    */
    typedef struct _funrec{
        char id[32];
        symtab *context;
        
        /* Los primeros 'params' elementos en context
        son los argumentos esperados en la función.*/
        int params;

        /*Ayuda a verificar tipos de los argumentos.*/
        int counter;
    } funrec;

    typedef struct _funtab{
        funrec funs[1000];
        int count;
    } funtab;


    int search(symtab *, char*);
    int depth_search(symtab *st, char *id);
    int insert(symtab*, sym );
    void print_table(symtab*);
    void fprint_table(symtab* st, FILE *file);
    int get_dir(symtab*, char*);
    void create_table(symtab *st, void *parent);
    int get_type(symtab*, char *);
    symtab* get_struct_content(symtab *st, char *);

    /* Funciones análogas a las definidas anteirormente.*/
    void create_funtab(funtab *tab);
    int insert_fun(funtab *tab, funrec rec);
    void print_funtable(funtab* st);
    int is_function(funtab *tab, char id[32]);
    funrec* get_rec(funtab *tab, char id[32]);



#ifdef __cplusplus
}
#endif

#endif /* SYMTAB_H */
