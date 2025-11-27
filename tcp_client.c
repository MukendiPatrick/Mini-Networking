#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5050

int main(void)
{
    // 1. Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Client Socket failed");
        return 1;
    }

    // 2. Connects to 127.0.0.1:5050 using connect().
    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("Client Connect failed");
        return 1;
    }

    // printf("Connected to server!\n");

    // 3. Sends one line of text via write()

    char buf[256];

    // Read from stdin
    if (fgets(buf, sizeof(buf), stdin) == NULL)
    {
        perror("fgets failed");
        return 1;
    }

    // char *msg = "Hello!\n";
    ssize_t w = write(sockfd, buf, strlen(buf));
    if (w == -1)
    {
        perror("Client write failed");
        close(sockfd);
        return 1;
    }

    // 4. Reads the server’s response.
    // char buf[256];
    ssize_t r = read(sockfd, buf, sizeof(buf) - 1);
    if (r == -1)
    {
        perror("Client Read failed");
        close(sockfd);
        return 1;
    }

    buf[r] = '\0';

    // 5.  Prints msg from server
    printf("Received: %s", buf);

    // 6. Close socket
    close(sockfd);

    return 0;
}
