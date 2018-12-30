/* 
 * File:   typetab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */
#include <stdio.h>

#include "stack.h"

#ifndef TYPETAB_H
#define TYPETAB_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _type{
        int type;
        int tam;
        int dim;
        int base;
    } type;

    typedef struct _typetab{
        type types[1000];
        int count;
        int last_dir;
        void *parent;
    } typetab;

    type new_type(void);
    type new_type2(int tipo,int tam,int dim,int base);
    type depth_search_type(typetab *st, int pos);
    int insert_type(typetab*, type );
    void print_table_types(typetab*);
    void fprint_table_types(typetab* st, FILE *file);
    void create_table_types(typetab *st,void *parent);
    int get_tam(typetab *tt, int pos);
    int get_type_(typetab* tt, int pos);
    int get_tam(typetab* tt, int pos);
    int get_dim(typetab* tt, int pos);
    int get_base(typetab* tt, int pos);
    void print_type(type t);
    
#ifdef __cplusplus
}
#endif

#endif /* TYPETAB_H */

