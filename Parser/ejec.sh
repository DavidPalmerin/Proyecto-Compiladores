#!/bin/bash
flex lexer.flex 
bison -d parser.y
gcc *.c -o gram
./gram test.txt
