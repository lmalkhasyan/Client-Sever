#ifndef SERVER_H
#define SERVER_H

#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define SERVER_PORT "8080"

void *client_thread(void *arg);
int receiver(int socket, char **buffer);
int sender(int socket, char *packet, size_t length);
char *execute(const char *cmd);

#endif