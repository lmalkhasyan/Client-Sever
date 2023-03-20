#include "server.h"


struct List sock_list = {.head = NULL, .size = 0, .socket_listen = -1};

int main()
{
    signal(SIGINT, handle_sigint);
    printf("Configuring local address...\n");
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo *bind_address;
    int s = getaddrinfo(0, SERVER_PORT, &hints, &bind_address);
    if (s != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    printf("Creating socket...\n");
    int socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    
    if (socket_listen == -1)
    {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(EXIT_FAILURE);
    }
    sock_list.socket_listen = socket_listen;

    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) 
    {
        freeaddrinfo(bind_address);
        fprintf(stderr, "bind() failed. (%d)\n", errno);
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if (listen(socket_listen, 5) < 0) 
    {
        fprintf(stderr, "listen() failed. (%d)\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connection...\n");
    int socket_client;
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

    while(1)
    {
        socket_client = accept(socket_listen, (struct sockaddr*)&client_address, &client_len);
        if (socket_client == -1)
        {
            fprintf(stderr, "accept() failed. (%d)\n", errno);
            exit(EXIT_FAILURE);
        }
        push_front(&sock_list, socket_client);
        struct Client_socket current = {.sock_node = sock_list.head, .list = &sock_list};
        
        printf("Client is connected... \n");
        pthread_t client;
        pthread_create(&client, NULL, client_thread, &current);
        pthread_detach(client);
    }

    printf("Closing listening socket...\n");
    close(socket_listen);
}


