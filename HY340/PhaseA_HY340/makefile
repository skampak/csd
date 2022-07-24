CC = gcc
OBJ = scanner

make:
	clear
	$(MAKE) $(OBJ)
	$(CC) -o scanner scanner.o

scanner: scanner.l
	flex --outfile=scanner.c $<
	$(CC) -c -o scanner.o scanner.c

.PHONY: clean

clean:
	rm scanner scanner.c *.o
