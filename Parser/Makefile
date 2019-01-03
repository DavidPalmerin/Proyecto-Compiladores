# Makefile
# Autores: Mendez Servin Melissa & Palmerin Morales David Gabriel.
# Proyecto final compiladores.
.PHONY : instructions clean ejec ejec show_ci show_contexts show_producciones show_err show_errlex show_tokens show_comm
instructions:
	@echo "make ejec"
	@echo "		Ejecuta el compilador con un archivo de prueba."	
	@echo "make run"
	@echo "		Compila el compilador. Seguido es neceserario"
	@echo "		Ejecutar ./gram test.txt, donde test será su "
	@echo "		archivo a compilar. "
	@echo "make clean"
	@echo "		Borra los archivos generados por el proyecto."
	@echo "make show_ci"
	@echo "		Muestra en consola el código intermedio (en el" 
	@echo "		caso de existir)."
	@echo "make show_contexts"
	@echo "		Muestra en consola los contextos generados por" 
	@echo "		el código (en el caso de existir)."
	@echo "make show_producciones"
	@echo "		Muestra en consola las producciones generadas" 
	@echo "		por el código dada nuestra gramática (en el caso" 
	@echo "		de existir)."
	@echo "make show_err"
	@echo "		Muestra en consola los errores generados por el" 
	@echo "		código (en el caso de existir)."
	@echo "make show_errlex"
	@echo "		Muestra en consola los errores léxicos generados" 
	@echo "		por el código (en el caso de existir)."
	@echo "make show_comm"
	@echo "		Muestra en consola los comentarios del código" 
	@echo "		dado (en el caso de existir)."
	@echo "make show_tokens"
	@echo "		Muestra en consola los tokens del código dado" 
	@echo "		(en el caso de existir)."	
ejec :	
	@flex lexer.flex 
	@bison -d parser.y
	@$(CC) *.c -o gram -w
	@./gram test.txt

#ejec especial para Palmi
ejec2:
	@flex lexer.flex 
	@/usr/local/opt/bison@3.2/bin/bison -d parser.y
	@$(CC) *.c -o gram -w
	@./gram test.txt

run :	
	@flex lexer.flex 
	@bison -d parser.y
	@$(CC) *.c -o gram -w

clean:
	@rm -f lex.yy.c
	@rm -rf parser.tab.c parser.tab.h
	@rm -f gram
	@rm -f *~
	@rm -rf comentarios.txt tokens_output.txt
	@rm -rf errores_lexicos.txt codigo.ci
	@rm -rf contexts.txt errores.txt producciones.txt
	@echo Se borraron los archivos generados.

show_ci:
	@cat codigo.ci 
show_contexts:
	@cat contexts.txt
show_producciones:
	@cat producciones.txt
show_err:
	@cat errores.txt
show_tokens:
	@cat tokens_output.txt
show_errlex:
	@cat errores_lexicos.txt
show_comm:
	@cat comentarios.txt