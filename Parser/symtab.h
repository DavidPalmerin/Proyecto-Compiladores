/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
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
    };
    
    typedef struct _symbol sym;
    
    typedef struct _symtab{
        sym symbols[1000];
        int count;
        int last_dir;
        void *parent;
    } symtab;

    int search(symtab *, char*);
    int depth_search(symtab *st, char *id);
    int insert(symtab*, sym );
    void print_table(symtab*);
    void fprint_table(symtab* st, FILE *file);
    int get_dir(symtab*, char*);
    void create_table(symtab *st, void *parent);
    int get_type(symtab*, char *);

    


#ifdef __cplusplus
}
#endif

#endif /* SYMTAB_H */

