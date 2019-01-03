/* 
 * File:   attributes.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:59
 * Modified on 1 de Enero de 2018
 * Se agregan definiciones de env, switches.
 * Agregado por: Palmerin Morales David Gabriel.
 */
#include "symtab.h"
#include "typetab.h"

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct _exp{
        char dir[32];
        char arr[32];
        char * cadena;
        int type;
    } exp;
    
    typedef struct _numero{
        int type;
        char val[32];
    } numero;

    typedef struct _labels{
        char label[1000][32];
        int count;
    } labels;

    typedef struct _bools{
        labels trues;
        labels falses;
    } bools;

    /* Se crea una pila de env que son los contextos en los que estamos. 
     * Autor: Melissa Mendez Servín.
              Palmerin Morales David Gabriel.
    */ 
    typedef struct _env
    {
        symtab symbols;
        typetab types;
    } env;

    /* Se usa para atributo de switch.
     * Autor: Palmerin Morales David Gabriel.
    */
    typedef struct _switches
    {
        char label[32];
        char caso[32];
        int  link;
    } switches;

    char *pop_label(labels*);
    void push_label(labels*, char *l);
    
    char *get_top_label(labels*);    
    char *get_top_label_previous(labels*);
    void create_labels(labels*);
    void print_stack_labels(labels*);
    void print_list_labels(labels*);
    



#ifdef __cplusplus
}
#endif

#endif /* ATTRIBUTES_H */


