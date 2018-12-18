#!/bin/bash
flex lexer.flex 
bison -d parser.y
gcc lex.yy.c parser.tab.c -o gram
./gram test.txt
