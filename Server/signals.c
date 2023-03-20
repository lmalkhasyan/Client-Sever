#include "server.h"

extern struct List sock_list;

void handle_sigint(int sig)
{
    (void)sig;
    clear_list(&sock_list);
    if(sock_list.socket_listen > 0)
    {
        fprintf(stderr, "Closing listening socket=[%d]\n", sock_list.socket_listen);
        close(sock_list.socket_listen);
    }
    exit(0);
}