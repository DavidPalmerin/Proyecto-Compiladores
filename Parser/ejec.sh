#!/bin/bash
#gcc ./data_structures/list.c -o list
#gcc ./data_structures/stack.c -o stack
flex lexer.flex 
/usr/local/opt/bison@3.2/bin/bison -d parser.y
gcc *.c -o gram
./gram test2.txt
#cat codigo.ci
