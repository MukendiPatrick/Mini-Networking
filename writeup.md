# Networking Writeup

## 1. TCP vs UDP
### TCP
| Feature            | TCP                 | UDP          |
|-------------------|-----------------------------------------------------|--------------------------------------|
| **Connection**      | Connection-oriented (3-way handshake) | Connectionless, no handshake |
| **Reliability**     | Reliable, ordered, byte-stream | Unreliable, unordered datagrams |
| **Speed / Overhead**| Slower, Uses congestion control & acknowledgments | Lower latency, minimal overhead |
| **Example Use**     | Good for Web, SHH, email | Good for DNS, VoIP, gaming |

## 2. Sockets as File Descriptors
(Explain what it means that sockets are FDs and why it's useful.)

In unix systems, a socket is represented internally as a file descriptor. This means when we call socket()
function, the OS returns an integer (fd) and this integer can used for all I/O operations.
It's usefull, since eveything is a file descriptor, programs interact with sockets using the sam system calls,
read(), write(), close(), dup2(), select(),etc.


## 3. Socket Lifecycle
bind: Assign an IP address and port number to the socket so that the server can be reachable.
listen: Listen makes the socket available to receive client incoming connection requests.
accept: Accepts a client connection request and returns a new socket for that particular client.
connect: A TCP connection request from the client side to the server.

(Describe bind, listen, accept, connect.)

## 4. OS Networking Abstractions

- Ports: The numbers are stored as unsigned 16-bit integers and they are used to route the packet to a specfic application on the same system. For example multiple web browsers (email client, a video-conferencing client) may be running on the same system. When computer recives a TCP packet or UDP datagram, the OS system looks at the destination port number in that packet. That port number is used to look up which application should handle it.

- buffers, queues, retransmissions hidden under API. When a socket is called the kernel creates two buffers (receive and send buffer) which is stored inside the OS kernel.  "Receive buffer" stores incoming data untill the application calls read() or recv() to prevent data loss. and the "send buffer" stores outgoing data until the OS can send it over the network.

- TCP 4-tuple: The OS tracks socket identity using a 4-tuple (local IP, local port, remote IP, remote port) for TCP connections, this allows many client to connect to the same server port at the same time. The server distingushes them by their source IP address and port number.

(Ports, buffers, the TCP 4-tuple, etc.)
