#!/bin/bash
flex lexer.flex 
/usr/local/opt/bison@3.2/bin/bison -d parser.y
gcc *.c -o gram
./gram test2.txt
cat codigo.ci
