# ICA13-NetworkBasics

In this assignment, you’ll build small tools that expose how Linux creates and manages network connections: a TCP echo server, a TCP client, a tiny UDP sender/receiver, and a short written component explaining how sockets operate inside the OS. You will complete this work in a Linux environment (lab VM, WSL2, or Docker) so that the correct system calls and behavior are available.

You’ll be given simple drivers and tests. Your job is to implement the required C programs so the tests pass and you learn how networking abstractions interact with the OS.

## Linux Environment

You must run this assignment on Linux:

### Windows + WSL2

1. Install WSL and Ubuntu from Microsoft Store.
2. In Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential
```

### macOS/Chromebook + Docker

1. Install Docker Desktop.
2. Start a container and install tools:

```bash
docker run -it --name minishell -v "$PWD":/hw -w /hw ubuntu bash
apt update && apt install -y build-essential bash
```

To double check your installation is correct, `gcc --version` prints a version number.

## To Do

You will implement three small deliverables:

- **tcp_server.c**: create a simple TCP echo server using ``socket()``, ``bind()``, ``listen()``, and ``accept()``.
- **tcp_client.c**: create a client that connects with ``connect()``, writes a message, and reads the server’s reply.
- **udp_demo.c**: send and receive a single datagram using UDP sockets.
- **writeup.md**: short written answers about TCP vs UDP, sockets as file descriptors, and the OS abstractions used in networking.

## Networking Concepts

A **socket** is an endpoint for communication represented internally as a **file descriptor**, just like regular files or pipes. Programs interact with sockets using the same system calls: ``read()``, ``write()``, ``close()``, ``dup2()``, ``select()``, etc.

TCP creates a reliable byte stream through a connection-oriented handshake. UDP sends independent, unreliable datagrams without establishing a connection. The OS tracks socket identity using a 4-tuple ``(local IP, local port, remote IP, remote port)`` for TCP connections, while UDP simply delivers datagrams to any process bound to the destination port.

The socket lifecycle for TCP is:

```perl
server: socket → bind → listen → accept → read/write → close
client: socket → connect → read/write → close
```

Your code will demonstrate these system calls and how the OS uses them to deliver data across the network.

## Example

If the server receives:

```bash
hello world
```

Your server should print the line and send the exact same message back to the client. The client prints what it receives:

```bash
Received: hello world
```

For UDP, your program will send a datagram and print the response (if any). No connection or handshake is required.

## Implementation

### tcp_server.c

In ``tcp_server.c``, you will implement a minimal TCP echo server.

Your server must:

1. Create a socket with

    ```c
    socket(AF_INET, SOCK_STREAM, 0);
    ```

2. Bind to port 5050 on localhost.
3. Call ``listen()`` with a backlog of 5.
4. Accept exactly **one** connection using ``accept()``.
5. Read up to 256 bytes.
6. Print the received message.
7. Echo the same message back to the client using ``write()``.
8. Close both sockets before exiting.

Use these headers:
``<sys/socket.h>``, ``<netinet/in.h>``, ``<arpa/inet.h>``, ``<unistd.h>``.

Return 0 on success and nonzero on error. Use ``perror()`` for error messages.

### tcp_client.c

In ``tcp_client.c``, write a simple TCP client that:

1. Creates a socket with ``socket()``.
2. Connects to ``127.0.0.1:5050`` using ``connect()``.
3. Sends one line of text via ``write()``.
4. Reads the server’s response.
5. Prints:

    ```bash
    Received: <message>
    ```

6. Closes the socket.

On any error, print with ``perror()`` and return nonzero.

### udp_demo.c

In ``udp_demo.c``, implement a small UDP sender/receiver.

Your program should:

1. Create a UDP socket using ``SOCK_DGRAM``.
2. Send a datagram (e.g., ``"ping"``) to localhost on port 6060.
3. Attempt to receive one datagram with ``recvfrom()``.
4. Print the reply or a message if timeout occurs.

You do not call ``listen()``, ``accept()``, or perform a handshake—UDP is connectionless.

### writeup.md

In ``writeup.md``, answer the following concisely:

1. **TCP vs UDP**: three differences and one example use for each.
2. **Sockets as file descriptors**: what this means and why it’s useful.
3. **Socket lifecycle**: describe the purpose of ``bind``, ``listen``, ``accept``, and ``connect``.
4. **OS abstractions**: explain buffers, ports, and the TCP 4-tuple.

One paragraph per item is sufficient.

## Files

Your repository will contain:

- ``tcp_server.c`` – Implement the echo server.
- ``tcp_client.c`` – Implement the TCP client.
- ``udp_demo.c`` – Minimal UDP example.
- ``writeup.md`` – Short written responses.
- ``main_server.c`` – Driver for testing (don’t modify).
- ``main_client.c`` – Driver for testing (don’t modify).
- ``Makefile`` – Build rules for server, client, udp, and all.
- ``test.sh`` – Full functional test suite.
- ``README.md`` – This file.

## Testing

Your implementation will be run against test.sh. To complete this assignment, you must pass:

Section 1: TCP server socket creation + lifecycle

Section 2: Client connect + message exchange

Section 3: Echo functionality

Section 4: UDP send/receive

Section 5: Contents of writeup.md

To compile:

```shell
make
```

To run tests:

```shell
make test
```

To run manually:

```shell
./tcp_server       # start the server
./tcp_client       # send a message
./udp_demo         # run the UDP example
```

## Hints

- Work incrementally. Test each part before running the full suite.
- Useful C headers:
``<stdio.h>``, ``<stdlib.h>``, ``<string.h>``, ``<unistd.h>``, ``<sys/socket.h>``, ``<netinet/in.h>``, ``<arpa/inet.h>``, ``<errno.h>``

**For TCP**:

- Remember to zero your sockaddr_in.
- Use htons() to convert the port to network order.
- Use inet_addr("127.0.0.1") or inet_pton().

**For UDP**:

- Use sendto() and recvfrom() instead of write()/read().
- Always close sockets with close().
