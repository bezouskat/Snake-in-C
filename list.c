#include "list.h"

#include <stddef.h>
#include <stdlib.h>

void init_list(list* l)
{
    l->head = NULL;
    l->tail = NULL;
}

void pop_back(list* l)
{
    if (l->tail == NULL)
        return;

    node* to_delete = l->tail;

    l->tail = l->tail->prev;
    free(to_delete);

    if (l->tail)
        l->tail->next = NULL;
    else
        l->head = NULL;
}

void pop_front(list* l)
{
    if (l->head == NULL)
        return;

    node* to_delete = l->head;

    l->head = l->head->next;
    free(to_delete);

    if (l->head)
        l->head->prev = NULL;
    else
        l->tail = NULL;
}

item_t get_back(list* l)
{
    return l->tail->item;
}

item_t get_front(list* l)
{
    return l->head->item;
}

void push_back(list* l, item_t i)
{
    node* new_node = malloc(sizeof(node));

    new_node->item = i;
    new_node->next = NULL;
    new_node->prev = l->tail;

    if (l->tail)
        l->tail->next = new_node;
    else
        l->head = new_node;

    l->tail = new_node;
}

void push_front(list* l, item_t i)
{
    node* new_node = malloc(sizeof(node));

    new_node->item = i;
    new_node->next = l->head;
    new_node->prev = NULL;

    if (l->head)
        l->head->prev = new_node;
    else
        l->tail = new_node;

    l->head = new_node;
}

void clear_list(list* l)
{
    node* to_delete;

    while (l->head != NULL)
    {
        to_delete = l->head;
        l->head = l->head->next;
        free(to_delete);
    }

    l->tail = NULL;
}
