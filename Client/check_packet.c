#include "client.h"

int check_packet(char *str, char **startpoint, int socket_server)
{
    char *token = NULL;

    str[strlen(str) - 1] = '\0';
    token = strtok(str, " ");
    if (!token || *token == '\n')
        return 1;
    if (!strcmp(token, "disconnect") && strtok(NULL, " ") == NULL)
    {
        printf("Client>> dissconecting...\n");
        close(socket_server);
        return -1;
    }
    else if (!strcmp(token, "connect"))
    {
        printf("Client>> You are already connected!\n");
        return 1;
    }
    else if (!strcmp(token, "quit"))
    {
        close(socket_server);
        printf("Client>>  Program termination!\n");;
        exit(EXIT_SUCCESS);
    }
    else if (!strcmp(token, "shell"))
    {
        char *command = strtok(NULL, "\"");
        
        if (command == NULL || strtok(NULL, "\"") != NULL)
        {
            fprintf(stderr, "Client>> [Bad Command usage shell \"command\"] \n");
            return 1;
        }
        *startpoint = command;
        return 0;
    }
    else
    {
        printf("Client>> [connect <IP_ADDRESS> <PORT>] ['dissconect' to exit]\n"
        "         [shell \"command\"] ['quit' to close the client programm]\n");
        return 1;
    }
}