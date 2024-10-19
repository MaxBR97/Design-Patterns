target: all

all: Observer.o Subscriber.o Resource.o main.o
	g++ -W -o exec main.o Observer.o Subscriber.o Resource.o

main.o: main.cpp
	g++ -W -c -o main.o main.cpp

Subscriber.o: Subscriber.cpp
	g++ -W -c -o Subscriber.o Subscriber.cpp

Resource.o: Resource.cpp
	g++ -W -c -o Resource.o Resource.cpp

Observer.o: Observer.cpp
	g++ -W -c -o Observer.o Observer.cpp

clean:
	rm -f *.o exec

# compile and run
run:
	make && echo "STARTING\n" && ./exec