CC = gcc
CFLAGS = -g -pedantic -Wall -std=c99 -Werror -Wextra
LMFLAG = -lm
OBJ = lexer.o parser.o stack.o tree.o tree_transform.o main.o
PROG = lab24

all: lexer.o parser.o stack.o tree.o tree_transform.o main.o
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LMFLAG)

lexer.o: lexer.c
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c  tree.c

tree_transform.o.o: tree_transform.o.c
	$(CC) $(CFLAGS) -c tree_transform.o.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ)

cleanall:
	rm -f $(PROG)  $(OBJ)