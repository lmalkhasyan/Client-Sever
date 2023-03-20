#include "server.h"

void push_front(struct List *list, int data)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = NULL;
    
    fprintf(stderr, "I am adding socket fd=[%d] to list\n", new_node->data);
    if (list->head == NULL)
    {
        new_node->next = NULL;
        list->head = new_node;
    }
    else
    {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
}

void clear_list(struct List *list)
{
    struct Node *current = list->head;
    while (current != NULL)
    {
        struct Node *temp = current;
        current = current->next;
        fprintf(stderr, "I am deleting socket fd=[%d] from list\n", temp->data);
        // shutdown(temp->data, SHUT_RDWR);
        close(temp->data);
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}


void delete_Node(struct List *list, struct Node *nodeToDelete)
{
    if (list->head == NULL || nodeToDelete == NULL)
        return;

    fprintf(stderr, "I am deleting socket fd=[%d] from list\n", nodeToDelete->data);
    if (list->head == nodeToDelete)
    {
        list->head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL)
    {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    if (nodeToDelete->prev != NULL)
    {
        nodeToDelete->prev->next = nodeToDelete->next;
    }
    list->size--;
    close(nodeToDelete->data);
    free(nodeToDelete);
}
