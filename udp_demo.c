#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define PORT 6060

int main(void)
{
    // 1. Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("Socket failed");
        return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    const char *msg = "ping";
    ssize_t sentMsg = sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (sentMsg == -1)
    {
        perror("sendto failed");
        close(sockfd);
        return 1;
    }

    printf("Sent: %s\n", msg);

    // Set timeout
    struct timeval timevalue;
    timevalue.tv_sec = 2;
    timevalue.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timevalue, sizeof(timevalue)) == -1)
    {
        perror("setsockopt failed");
        close(sockfd);
        return 1;
    }

    // Receive one datagram with recvfrom()
    struct sockaddr_in from_addr;
    socklen_t addrlen = sizeof(from_addr);
    char buf[256];
    ssize_t r = recvfrom(sockfd, buf, 255, 0, (struct sockaddr *)&from_addr, &addrlen);
    if (r == -1)
    {
        perror("recvfrom failed or timeout");
        printf("No reply received within 2 seconds.\n");
    }
    else
    {
        buf[r] = '\0';
        printf("Received: %s\n", buf);
    }

    // 6. Close socket
    close(sockfd);

    return 0;
}
