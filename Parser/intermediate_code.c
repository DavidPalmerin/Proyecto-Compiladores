/* 
 * File:   intermediate_code.h
 * Author: Adrian Ulises Mercado Martínez
 *
 * Created on 3 de diciembre de 2018, 20:19
 */
#include "intermediate_code.h"
#include <stdio.h>

void create_code(ic* code){
    code->count= 0;
}


int insert_cuad(ic* code, cuadrupla c){
    if(code->count<MAX_CODE){
        code->c[code->count++] = c;
        return code->count-1;
    }
    return -1;
}


void print_code(ic* code){
    FILE * CODIGO;
    CODIGO = fopen("codigo.ci", "w");
    int i;
    for(i=0; i < code->count; i++){
        cuadrupla temporal = code->c[i];
        switch(temporal.op){
            case GOTO:
                fprintf(CODIGO, "goto %s\n", temporal.res);
                //printf("goto %s\n", temporal.res);
                break;
            case IFF:
                fprintf(CODIGO, "if %s goto %s\n", temporal.op1, temporal.res);
                //printf("if %s goto %s\n", temporal.op1, temporal.res);
                break;
            case LT:
                fprintf(CODIGO, "%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GT:
                fprintf(CODIGO, "%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LE:
                fprintf(CODIGO, "%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GE:
                fprintf(CODIGO, "%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case EQ:
                fprintf(CODIGO, "%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case NE:
                fprintf(CODIGO, "%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MA:
                fprintf(CODIGO, "%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MEN:
                fprintf(CODIGO, "%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case ML:
                fprintf(CODIGO, "%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case DV:
                fprintf(CODIGO, "%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                //printf("%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LB:
                fprintf(CODIGO, "%s:", temporal.res);
                //printf("%s:", temporal.res);
                break;
            case AS:
                fprintf(CODIGO, "%s = %s\n", temporal.res, temporal.op1);
                //printf("%s = %s\n", temporal.res, temporal.op1);
                break;
            case CT:
                fprintf(CODIGO, "%s = %s %s\n",  temporal.res, temporal.op1,temporal.op2);
                //printf("%s = %s\n", temporal.res, temporal.op1);
                break;
        }        
    }
    fclose(CODIGO);
}


