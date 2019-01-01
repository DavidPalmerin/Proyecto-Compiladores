/* 
 * File:   intermediate_code.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 20:19
 */

#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define GOTO 1
#define IFF 2
#define LT 3
#define GT 4
#define LE 5
#define GE 6
#define EQ 7
#define NE 8
#define MA 9
#define MEN 10
#define ML 11
#define DV 12
#define MD 13
#define LB 14
#define AS 15
#define CT 16
#define PARAM 17
#define CALL 18
#define AS_ARR 19
#define ASS 20
#define RET 21

#define MAX_CODE 1000

    typedef struct _cuadrupla{
        int op;
        char op1[32];
        char op2[32];
        char res[32];
        char * string_op;
    } cuadrupla;
    
     
    typedef struct _intremediate_code{
       cuadrupla c[MAX_CODE];
       int count;
    } ic;
    
    void create_code(ic*);
    int insert_cuad(ic*, cuadrupla);      
    void print_code(ic*);

#ifdef __cplusplus
}
#endif

#endif /* INTERMEDIATE_CODE_H */

