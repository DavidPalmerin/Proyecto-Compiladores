/* 
 * File:   typetab.h
 * Author: Mendez Servin Melissa.
 *
 * Created on 25 de diciembre de 2018, 19:36
 */
#include <stdio.h>

#include "stack.h"

#ifndef TYPETAB_H
#define TYPETAB_H

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Definición de un tipo, (uso principal para el 
     * manejo de arreglos).
     * Autora : Mendez Servin Melissa.
     */
    typedef struct _type{
        // Tipo al que representa, si es un tipo base
        // tendrá asignado un número entre el 0 y el 6,
        // mientras que si es un arreglo será mayor a éstos.
        int type;
        // Tamaño del tipo al que representa (en bytes).
        int tam;
        // Dimensión definida del arreglo.
        int dim;
        // Tipo base al que hace referencia el arreglo.
        int base;
    } type;

    /* Tabla para almacenar tipos, los cuales se identi-
     * can por su índice dentro de la tabla.
     * Autora : Mendez Servin Melissa.
     */
    typedef struct _typetab{
        type types[1000];
        int count;
        int last_dir;
        void *parent;
    } typetab;

    /*
     * Auxiliar para el manejo de las dimensiones de un a-
     * rreglo, el cual tiene capacidad de a lo más 10 di-
     * mensiones.
     * Autora: Mendez Servin Melissa.
     */
    typedef struct _arreglo
    {
        int array_dim[10];
        int count;
    }arreglo;
    
    type new_type(void);
    int insert_type(typetab*, type );
    void print_table_types(typetab*);
    void fprint_table_types(typetab* st, FILE *file);
    void create_table_types(typetab *st,void *parent);
    int get_tam(typetab *tt, int pos);
    int get_dim(typetab* tt, int pos);
    int get_base(typetab* tt, int pos);
    void print_type(type t);
    void insert_dim(arreglo*,int d);
    arreglo create_arreglo();
    
#ifdef __cplusplus
}
#endif

#endif /* TYPETAB_H */

