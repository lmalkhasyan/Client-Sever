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


struct Node
{
	int         data;
	struct Node	*next;
	struct Node *prev;
};

struct List
{
	struct Node	*head;
	int 		socket_listen;
	int		    size;
};

struct Client_socket
{
	struct Node *sock_node;
	struct List *list;	
};

#ifndef Glob
#define Glov
// struct List sock_list = {.head = NULL, .size = 0};
#endif

void *client_thread(void *arg);
int receiver(int socket, char **buffer);
int sender(struct Client_socket *client, char *packet, size_t length);
char *execute(const char *cmd);

void push_front(struct List *lst, int data);
void clear_list(struct List *lst);
int is_empty(struct List *lst);
void delete_Node(struct List *list, struct Node *nodeToDelete);

void handle_sigint(int sig);

#endif