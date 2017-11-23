run: all
	./run

all: main.o
	gcc -o run main.o 

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf run