
target: all

all: main.o network_ops.o ssl_protocol.o
	g++ -g -W -o exec main.o network_ops.o ssl_protocol.o

main.o: main.cpp
	g++ -g -W -c -o main.o main.cpp

network_ops.o: network_ops.cpp
	g++ -g -W -c -o network_ops.o network_ops.cpp

ssl_protocol.o: ssl_protocol.cpp
	g++ -g -W -c -o ssl_protocol.o ssl_protocol.cpp

clean:
	rm *.o exec

run:
	make all && ./exec