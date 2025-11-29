# **Mini Linux Networking Project**

This project provides minimal examples of TCP and UDP communication using the Linux socket API.
The code includes a TCP echo server, a TCP client, and a small UDP demonstration program.
Each component uses low-level system calls such as `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `read()`, `write()`, `sendto()`, and `recvfrom()`.

The goal of this project is to clearly illustrate how Linux manages sockets, how TCP and UDP differ, and how the OS handles ports, buffers, and connection metadata.

---

## **Project Components**

### **TCP Echo Server**

* Listens on port **5050**
* Accepts a single incoming TCP connection
* Reads up to 256 bytes from the client
* Prints the received data
* Echoes the same data back to the client
* Closes all sockets before exiting

### **TCP Client**

* Connects to `127.0.0.1:5050`
* Sends one line of text
* Receives the server’s response
* Prints the received message
* Closes the socket when finished

### **UDP Demonstration**

* Sends a single datagram (e.g., `"ping"`) to port **6060**
* Waits for a datagram reply using `recvfrom()`
* Demonstrates connectionless communication (no handshake)

---

## **Build and Execution**

Build all executables:

```bash
make
```

Run the TCP echo server:

```bash
./tcp_server
```

Run the TCP client:

```bash
./tcp_client
```

Run the UDP demo:

```bash
./udp_demo
```

---

## **Directory Structure**

| File                             | Purpose                                |
| -------------------------------- | -------------------------------------- |
| `tcp_server.c`                   | Minimal TCP echo server implementation |
| `tcp_client.c`                   | TCP client for server testing          |
| `udp_demo.c`                     | UDP sender/receiver example            |
| `writeup.md`                     | Notes explaining networking concepts   |
| `Makefile`                       | Build rules                            |
| `main_server.c`, `main_client.c` | Test drivers (unchanged)               |

---

## **Concepts Illustrated**

### **TCP vs UDP**

TCP provides a reliable, ordered byte stream with a connection-oriented handshake.
UDP transmits independent datagrams without establishing a connection, offering lower latency but no delivery guarantees.

### **Sockets as File Descriptors**

Sockets are represented internally by file descriptors, allowing them to use the standard Linux I/O API (`read`, `write`, `close`, etc.).
This unifies network I/O with other forms of input/output in the OS.

### **Socket Lifecycle**

Typical TCP sequence:

```
Server: socket → bind → listen → accept → read/write → close  
Client: socket → connect → read/write → close
```

Each step configures the socket for a different stage of communication.

### **OS Networking Abstractions**

The operating system uses internal buffers, port numbers, and connection metadata to track communication.
For TCP, each connection is identified by a 4-tuple:
`(local IP, local port, remote IP, remote port)`.

