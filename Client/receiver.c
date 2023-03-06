#include "client.h"

int receiver(int socket, char **buffer)
{
    uint32_t prefix;
    ssize_t n = recv(socket, &prefix, sizeof(prefix), 0);
    if (n < 0)
    {
        perror("Error receiving length from Server:");
        return -1;
    }
    else if (n == 0)
    {
        fprintf(stderr, "Server disconnected\n");
        return 1;
    }

    uint32_t length = ntohl(prefix);
    *buffer = malloc(length + 1);
    if (!(*buffer))
    {
        fprintf(stderr, "Malloc allocation error (%s)", strerror(errno));
        return -1;
    }
    n = recv(socket, *buffer, length, 0);
    if (n < 0)
    {
        perror("Error receiving message:");
        return -1;
    }
    else if (n == 0)
    {
        fprintf(stderr, "Server disconnected\n");
        return 1;
    }
    (*buffer)[length] = '\0';
    printf("Server>>\n%s", *buffer);
    return 0;
}