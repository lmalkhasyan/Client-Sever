#include "client.h"

extern int socket_server;

void handle_sigint(int sig)
{
    (void)sig;
    if(socket_server > 0)
        close(socket_server);
    rl_clear_history();
    rl_callback_handler_remove();
    exit(0);
}