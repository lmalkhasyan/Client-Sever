#include "client.h"

int main()
{
    signal(SIGINT, handle_sigint);
    char *token = NULL;
    char *buffer = NULL;
    rl_bind_key('\t', rl_complete);
    add_history("connect 127.0.0.1 8080");
    while ((buffer = readline("Client>> ")) != NULL)
    {
        if (!*buffer)
            continue;
        add_history(buffer);

        token = strtok(buffer, " ");
        if (!strcmp(token, "quit"))
        {
            printf("Client>> Programm Termination!\n");
            clear_history();
            free(buffer);
            return 0;
        }
        else if (!strcmp(token, "connect"))
        {
            char *ip = strtok(NULL, " ");
            char *port = strtok(NULL, " ");
            if (strtok(NULL, " ") != NULL || !ip || !port)
            {
                printf("Client> Empty IP/Port or extra symbols!\n");
            }
            else if (is_valid_ip(ip) && is_valid_port(port))
            {
                printf("Client>> connection to [%s:%s]\n", ip, port);
                if (connect_to_server(ip, port) < 0)
                {
                    printf("Client>> You can connect again!\n");
                }
            }
        }
        else
        {
            printf("Client>> You Must Connect!\n"
                    "Client>> [connect <IP_ADDRESS> <PORT>]\n"
                    "         ['dissconect' to exit]\n"
                    "         [shell \"command\"]\n"
                    "         ['quit' to close the client programm]\n");
        }
        free(buffer);
    }
    return 0;
}
