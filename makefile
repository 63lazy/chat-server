CC = g++
CFLAGS = -Wall -g -pthread -std=c++20

all: bin/server bin/client

bin/server: obj/server.o | bin
	$(CC) $(CFLAGS) $^ -o $@

bin/client: obj/client.o | bin
	$(CC) $(CFLAGS) $^ -o $@

obj/server.o: src/server.cpp src/protocol.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/client.o: src/client.cpp src/protocol.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	rm -rf obj bin

.PHONY: all clean
