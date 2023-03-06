#include "server.h"

void *client_thread(void *arg)
{
    int client_fd = *(int *)arg;

    while (1)
    {
        char *buffer = NULL;
        int status = receiver(client_fd, &buffer);
        if (status != 0)
        {
            close(client_fd);
            if (buffer)
            {
                free(buffer);
                buffer = NULL;
            }
            if (status == -1)
                return NULL;
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
        sender(client_fd, output, strlen(output));
        free(buffer);
        free(output);
    }
    return NULL;
}