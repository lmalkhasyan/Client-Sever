#include "client.h"

int connect_to_server(char *ip, char *port, char *message)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    struct addrinfo *peer_address;
    if (getaddrinfo(ip, port, &hints, &peer_address))
    {
        fprintf(stderr, "getaddrinfo() failed. (%s)\n", strerror(errno));
        return -1;
    }

    int socket_server = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);
    if (socket_server < 0)
    {
        fprintf(stderr, "socket() failed. (%s)\n", strerror(errno));
        return -1;
    }

    if (connect(socket_server, peer_address->ai_addr, peer_address->ai_addrlen))
    {
        fprintf(stderr, "connect() failed. (%s)\n", strerror(errno));
        close(socket_server);
        return -1;
    }
    freeaddrinfo(peer_address);
    printf("Client>> Connected!\n");

    while (1)
    {
        printf("Client>> ");
        fgets(message, MAX_MSG_LEN, stdin);

        char *start_point = NULL;
        int status = check_packet(message, &start_point, socket_server);
        if (status == 1)
            continue;
        else if (status == -1)
            break;

        if (sender(socket_server, start_point, strlen(start_point)) < 0)
        {
            continue;
        }

        char *buffer = NULL;
        status = receiver(socket_server, &buffer);
        if (status != 0)
        {
            close(socket_server);
            if (buffer)
            {
                free(buffer);
                buffer = NULL;
            }
            if(status == -1)
                return -1;
            continue;
        }

        free(buffer);
        buffer = NULL;
    }
    return -1;
}