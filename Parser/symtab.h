/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */

#include "attributes.h"
#include "stack.h"

#ifndef SYMTAB_H
#define SYMTAB_H

#ifdef __cplusplus
extern "C" {
#endif

    struct _symbol{
        char id[32];
        type type;
        int dir;
    };
    
    typedef struct _symbol sym;
    
    typedef struct _symtab{
        sym symbols[1000];
        int count;
        int last_dir;
    } symtab;
    
    typedef struct _env
    {
        symtab symbols;
        stack exprs;
    } env;

    int search(symtab *, char*);
    int insert(symtab*, sym );
    void print_table(symtab*);
    int get_dir(symtab*, char*);
    type get_type(symtab*, char *);
    void create_table(symtab *st);
    


#ifdef __cplusplus
}
#endif

#endif /* SYMTAB_H */

