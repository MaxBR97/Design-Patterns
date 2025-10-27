
all: main

main: main.o concurrentHashMap.o
	gcc -lpthread -o main main.o concurrentHashMap.o

main.o: main.c
	gcc -g -c -o main.o main.c

concurrentHashMap.o: concurrentHashMap.c
	gcc -g -c -o concurrentHashMap.o concurrentHashMap.c

clean:
	rm -f main main.o concurrentHashMap.o