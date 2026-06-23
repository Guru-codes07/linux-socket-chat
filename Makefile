CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: server client

server: server.c
$(CC) $(CFLAGS) server.c -o server

client: client.c
$(CC) $(CFLAGS) client.c -o client

clean:
rm -f server client

run-server: server
./server

run-client: client
./client

.PHONY: all clean run-server run-client

