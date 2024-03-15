all: graph.o main.o
	gcc graph.o main.o -o final -std=c99 -Wall

graph.o:
	gcc -c graph.c -o graph.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o final

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./final

run:
	./final
