#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5050

int main(void)
{
    // 1. Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket failed");
        return 1;
    }

    // Allow immediate reuse of the port
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt failed");
        return 1;
    }

    // 2. Bind to port 5050 on localhost.
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Bind failed");
        return 1;
    }

    // 3. Call listen() with a backlog of 5
    if (listen(sockfd, 5) == -1)
    {
        perror("Listen failed");
        return 1;
    }

    // printf("Server listening on port %d...\n", PORT);

    // 4. Accept exactly one connection using accept().
    int client = accept(sockfd, NULL, NULL);
    if (client == -1)
    {
        perror("Accept failed");
        return 1;
    }

    // printf("Client connected!\n");

    // 5. Read up to 256 bytes.
    char buf[256];
    ssize_t r = read(client, buf, 255);
    if (r == -1)
    {
        perror("Read failed");
        close(client);
        close(sockfd);
        return 1;
    }

    buf[r] = '\0';

    // 6. Print the received message.
    printf("%s", buf);

    // 7. Echo the same message back to the client using write()
    ssize_t w = write(client, buf, r);
    if (w == -1)
    {
        perror("Write failed");
        close(client);
        close(sockfd);
        return 1;
    }

    // 8. Close both sockets before exiting.
    close(client);
    close(sockfd);

    // printf("Server closing.!\n");

    return 0;
}