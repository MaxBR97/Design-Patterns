CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g   # Added -g for debugging symbols

all: main 

main: main.o circle.o rectangle.o shape.o square.o
	$(CC) $(CFLAGS) -o main main.o circle.o rectangle.o shape.o square.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

circle.o: circle.c
	$(CC) $(CFLAGS) -c circle.c

rectangle.o: rectangle.c
	$(CC) $(CFLAGS) -c rectangle.c

shape.o: shape.c
	$(CC) $(CFLAGS) -c shape.c

square.o: square.c
	$(CC) $(CFLAGS) -c square.c

clean:
	rm -f main main.o circle.o rectangle.o shape.o square.o