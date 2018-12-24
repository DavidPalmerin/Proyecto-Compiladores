/* 
 * File:   attributes.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 19:59
 */

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _type{
        int type;
        int dim;
    } type;

    typedef struct _exp{
        char dir[32];
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


    // typedef struct _bools{
    //     labels trues;
    //     labels falses;
    // } bools;

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


