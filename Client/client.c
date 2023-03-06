#include "client.h"

int main()
{
    char buffer[MAX_MSG_LEN];
    char *token = NULL;
    while (1)
    {
        printf("Client>> ");
        if(!fgets(buffer, sizeof(buffer), stdin))
            continue;
        if (*buffer == '\n')
            continue;

        buffer[strlen(buffer) - 1] = '\0';
        token = strtok(buffer, " ");
        if(token == NULL)
            continue;
        if (!strcmp(token, "quit"))
        {
            printf("Client>> Programm Termination!\n");
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
                if (connect_to_server(ip, port, buffer) < 0)
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
    }
    return 0;
}
