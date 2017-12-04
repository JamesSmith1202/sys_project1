run: all
	./run

all: main.o functions.o
	gcc -o run main.o functions.o

main.o: main.c headers.h
	gcc -c main.c

functions.o: functions.c headers.h
	gcc -c functions.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf run