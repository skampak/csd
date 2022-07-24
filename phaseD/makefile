CC = gcc
OBJ = symtable.o parser.o scanner.o intermediate.o target.o
CFLAGS = -Wall

make:
	clear
	@echo "--------MAKE ALPHA---------"
	$(MAKE) $(OBJ)
	$(CC) -o alpha scanner.o parser.o symtable.o intermediate.o target.o $(CFLAGS)
	@echo "----MAKE WAS SUCCESSFUL----"
	
parser.o: parser.y
	bison -v --yacc --defines --output=parser.c $<
	$(CC) -c -o $@ parser.c $(CFLAGS)
	
scanner.o: scanner.l
	flex -oscanner.c $<
	$(CC) -c -o $@ scanner.c
	
symtable.o: symtable.c symtable.h
	$(CC) -c -o $@ $< $(CFLAGS)

intermediate.o: intermediate.c intermediate.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
target.o: target.c target.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
.PHONY: clean

clean:
	rm alpha scanner.c parser.c parser.h parser.output *.o
