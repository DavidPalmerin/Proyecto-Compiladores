#!/bin/bash
flex lexer.flex 
gcc lex.yy.c -o ./t
