#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct SinglyLinkedList SinglyLinkedList;

int singly_linked_list_create(SinglyLinkedList **list);
int singly_linked_list_destroy(SinglyLinkedList **list);
int singly_linked_list_push_back(SinglyLinkedList *list, void *data);
int singly_linked_list_remove_last(SinglyLinkedList *list);
int singly_linked_list_push_front(SinglyLinkedList *list, void *data);
int singly_linked_list_len(SinglyLinkedList *list, size_t *len);
int singly_linked_list_get_first(SinglyLinkedList *list, void **data);
int singly_linked_list_get_last(SinglyLinkedList *list, void **data);
int singly_linked_list_get(SinglyLinkedList *list, size_t index, void **data);
int singly_linked_list_index_of(SinglyLinkedList *list, void *data, size_t *index);

#endif
