target: all

all: Main.o Peculiar.o 
	g++ -W -o exec Main.o Peculiar.o 

Main.o: Main.cpp
	g++ -W -c -g -o Main.o Main.cpp

Peculiar.o: Peculiar.cpp
	g++ -W -c  -g -o Peculiar.o Peculiar.cpp

clean:
	rm -f *.o exec

# compile and run
run:
	make && echo "STARTING\n" && ./exec