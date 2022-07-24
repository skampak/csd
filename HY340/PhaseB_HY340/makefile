CC = gcc
OBJ = symtable.o parser.o scanner.o

make:
	clear
	@echo "--------MAKE ALPHA---------"
	$(MAKE) $(OBJ)
	$(CC) -o alpha scanner.o parser.o symtable.o
	@echo "----MAKE WAS SUCCESSFUL----"
	
parser.o: parser.y
	bison -v --yacc --defines --output=parser.c $<
	$(CC) -c -o $@ parser.c
	
scanner.o: scanner.l
	flex --outfile=scanner.c $<
	$(CC) -c -o $@ scanner.c
	
symtable.o: symtable.c symtable.h
	$(CC) -c -o $@ $<
	
.PHONY: clean

clean:
	rm alpha scanner.c parser.c parser.h parser.output *.o
