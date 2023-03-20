#include "server.h"

void *client_thread(void *arg)
{
    struct Client_socket client = *(struct Client_socket *)arg;

    while (1)
    {
        char *buffer = NULL;
        int status = receiver(client.sock_node->data, &buffer);
        if (status != 0)
        {
            if (buffer)
            {
                free(buffer);
                buffer = NULL;
            }
            if (status == -1)
            {
                delete_Node(client.list, client.sock_node);
                return NULL;
            }
            continue;
        }

        fprintf(stderr, "Client>> \"%s\n\"", buffer);
        char *output = execute(buffer);

        if (output == NULL)
        {
            fprintf(stderr, "Server>> Error in execution of command\n");
            free(buffer);
            buffer = NULL;
            continue;
        }
        printf("Server >> my output: %s\n", output);
        sender(&client, output, strlen(output));
        free(buffer);
        free(output);
    }
    return NULL;
}