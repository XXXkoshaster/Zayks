prog: deck.o main.o
	g++ deck.o main.o
deck.o: deck.h deck.c
	g++ -c deck.c
main.o: deck.h main.c
	g++ -c main.c
