#include "server.h"

int sender(int socket, char *packet, size_t length)
{
    u_int32_t prefix = htonl(length);
    if (send(socket, &prefix, sizeof(prefix), 0) < 0)
    {
        perror("Error sending message length: [try again]");
        return -1;
    }
    if (send(socket, packet, length, 0) < 0)
    {
        perror("Error sending message [try again]");
        return -1;
    }
    return 0;
}