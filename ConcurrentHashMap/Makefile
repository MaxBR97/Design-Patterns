
all: main

main: main.o concurrentHashMap.o
	gcc -o main main.o concurrentHashMap.o

main.o: main.c
	gcc -c -o main.o main.c

concurrentHashMap.o: concurrentHashMap.c
	gcc -c -o concurrentHashMap.o concurrentHashMap.c

clean:
	rm -f main main.o concurrentHashMap.o