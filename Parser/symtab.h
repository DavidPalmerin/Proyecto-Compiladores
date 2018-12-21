/* 
 * File:   symtab.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:36
 */

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
    } symtab;
    
    int search(symtab *, char*);
    int insert(symtab*, sym );
    void print_table(symtab*);
    int get_dir(symtab*, char*);
    int get_type(symtab*, char *);
    void create_table(symtab *st);
    


#ifdef __cplusplus
}
#endif

#endif /* SYMTAB_H */

