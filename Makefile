system: clean buscador.o
	gcc buscador.o -lm -o buscador
	@echo " "
	@echo " ----------- "
	@echo "Follow instruction"
	@echo "Use in terminal:"
	@echo " $ ./buscador /path/to/want word_to_search max_number_lines"
	@echo " "
	@echo " "
	@echo "Example"
	@echo " ./buscador dir/show/ test 3"
	@echo " "
	@echo " "
	rm -rf *.o
buscador.o: main.c
	gcc -c main.c -o buscador.o -lm
clean:
	rm -rf *.o
