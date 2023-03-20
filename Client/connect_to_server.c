#include "client.h"

int socket_server = -1;

int connect_to_server(char *ip, char *port)
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

    socket_server = socket(peer_address->ai_family,
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
    char *message;
    char *start_point = NULL;
    while ((message = readline("Client>> ")) != NULL)
    {
        add_history(message);
        
        int status = check_packet(message, &start_point, socket_server);
        if (status == 1)
            continue;
        else if (status == -1)
            break;

        status = sender(socket_server, start_point, strlen(start_point));
        if (status < 0)
        {
            free(message);
            continue;
        }
        else if (status == 1)
        {
            break;
        }

        char *buffer = NULL;
        status = receiver(socket_server, &buffer);
        if (status != 0)
        {
            close(socket_server);
            if (buffer)
            {
                free(message);
                free(buffer);
                buffer = NULL;
            }
            if (status == 1)
            {
                close(socket_server);
                return -1;
            }
            free(message);
            continue;
        }
        free(message);
        free(buffer);
        buffer = NULL;
    }
    free(message);
    clear_history();        
    return -1;
}