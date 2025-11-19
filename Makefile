CC = gcc
CFLAGS = -Wall -Wextra -g

all: tcp_server tcp_client udp_demo

tcp_server: tcp_server.c
	$(CC) $(CFLAGS) -o tcp_server tcp_server.c

tcp_client: tcp_client.c
	$(CC) $(CFLAGS) -o tcp_client tcp_client.c

udp_demo: udp_demo.c
	$(CC) $(CFLAGS) -o udp_demo udp_demo.c

clean:
	rm -f tcp_server tcp_client udp_demo

test: all
	bash test.sh
