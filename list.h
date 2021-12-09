#ifndef LIST_H
#define LIST_H

#include "point.h"

typedef point item_t;

typedef struct node
{
    item_t item;
    struct node* next;
    struct node* prev;
} node;

typedef struct
{
    node* head;
    node* tail;
} list;

void init_list(list* l);
void pop_back(list* l);
void pop_front(list* l);
item_t get_back(list* l);
item_t get_front(list* l);
void push_back(list* l, item_t i);
void push_front(list* l, item_t i);
void clear_list(list* l);

#endif // LIST_H
