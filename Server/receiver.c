#include "server.h"

int receiver(int socket, char **buffer)
{
    uint32_t prefix;
    ssize_t recv_status = recv(socket, &prefix, sizeof(prefix), 0);
    if (recv_status < 0)
    {
        perror("Error receiving length from Client:");
        return 1;
    }
    else if (recv_status == 0)
    {
        fprintf(stderr, "Client disconnected\n");
        return -1;
    }
    
    uint32_t length = ntohl(prefix);
    fprintf(stderr, "Client message Length in bytes %d\n", length);
    *buffer = malloc(length + 1 + 5);
    if (!(*buffer))
    {
        fprintf(stderr, "Malloc allocation error (%s)", strerror(errno));
        return -1;
    }
    recv_status = recv(socket, *buffer, length, 0);
    if (recv_status < 0)
    {
        perror("Error receiving message");
        return 1;
    }
    else if (recv_status == 0)
    {
        fprintf(stderr, "Client disconnected\n");
        return -1;
    }
    (*buffer)[length] = '\0';
    strcat(*buffer, " 2>&1");
    return 0;
}