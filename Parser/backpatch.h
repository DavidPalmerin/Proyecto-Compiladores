/* 
 * File:   backpath.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 20:35
 * No se realizan modificaciones al archivo proporcionado por el profesor.
 */

#ifndef BACKPATH_H
#define BACKPATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "attributes.h"
#include "intermediate_code.h"
    
    labels create_list(char*);
    labels create_empty_list();
    labels merge(labels*, labels*);
    int backpatch(labels*, char*, ic*);
    char *get_first(labels*);


#ifdef __cplusplus
}
#endif

#endif /* BACKPATH_H */

