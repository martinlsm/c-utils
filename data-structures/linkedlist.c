#include "linkedlist.h"

#include <errno.h>

typedef struct SinglyLinkedListNode SinglyLinkedListNode;

struct SinglyLinkedList {
  SinglyLinkedListNode *first;
  size_t len;
};

struct SinglyLinkedListNode {
  SinglyLinkedListNode *next;
  void *data;
};


int singly_linked_list_create(SinglyLinkedList **list) {
  if (list == NULL) {
    return EINVAL;
  }

  *list = malloc(sizeof(SinglyLinkedList));
  if (*list == NULL) {
    return ENOMEM;
  }

  (*list)->first = NULL;
  (*list)->len = 0;

  return 0;
}

int singly_linked_list_destroy(SinglyLinkedList **list) {
  if (list == NULL) {
    return EINVAL;
  }

  SinglyLinkedListNode *node = (*list)->first;
  while (node != NULL) {
    SinglyLinkedListNode *next = node->next;
    free(node);
    node = next;
  }

  free(*list);
  *list = NULL;

  return 0;
}

int singly_linked_list_push_back(SinglyLinkedList *list, void *data) {
  if (list == NULL) {
    return EINVAL;
  }

  SinglyLinkedListNode *new_node = malloc(sizeof(SinglyLinkedList));
  if (new_node == NULL) {
    return ENOMEM;
  }
  new_node->next = NULL;
  new_node->data = data;

  if (list->len == 0) {
    list->first = new_node;
  } else {
    // Find the currently last node.
    SinglyLinkedListNode *curr_last = list->first;
    while (curr_last->next != NULL) {
      curr_last = curr_last->next;
    }

    curr_last->next = new_node;
  }

  list->len += 1;

  return 0;
}

int singly_linked_list_remove_last(SinglyLinkedList *list) {
  if (list == NULL || list->len == 0) {
    return EINVAL;
  }

  if (list->len == 1) {
    free(list->first);
    list->first = NULL;
    list->len = 0;
    return 0;
  }

  // Find the currently second last node.
  SinglyLinkedListNode *second_last = list->first;
  while (second_last->next->next != NULL) {
    second_last = second_last->next;
  }

  free(second_last->next);
  second_last->next = NULL;

  list->len -= 1;

  return 0;
}

int singly_linked_list_push_front(SinglyLinkedList *list, void *data) {
  if (list == NULL) {
    return EINVAL;
  }

  SinglyLinkedListNode *new_first = malloc(sizeof(SinglyLinkedListNode));
  if (new_first == NULL) {
    return ENOMEM;
  }

  new_first->next = list->first;
  list->first = new_first;
  list->len += 1;

  return 0;
}

int singly_linked_list_len(SinglyLinkedList *list, size_t *len) {
  if (list == NULL || len == NULL) {
    return EINVAL;
  }

  *len = list->len;

  return 0;
}

int singly_linked_list_get_first(SinglyLinkedList *list, void **data) {
  if (list == NULL || list->len == 0 || data == NULL) {
    return EINVAL;
  }

  *data = list->first->data;

  return 0;
}

int singly_linked_list_get_last(SinglyLinkedList *list, void **data) {
  if (list == NULL || list->len == 0 || data == NULL) {
    return EINVAL;
  }

  SinglyLinkedListNode *last = list->first;
  while (last->next != NULL) {
    last = last->next;
  }

  *data = last->data;

  return 0;
}

int singly_linked_list_get(SinglyLinkedList *list, size_t index, void **data) {
  if (list == NULL || index >= list->len || data == NULL) {
    return EINVAL;
  }

  // Find the corresponding node.
  SinglyLinkedListNode *node = list->first;
  for (size_t i = 0; i < index; ++i) {
    node = node->next;
  }

  *data = node->data;

  return 0;
}

int singly_linked_list_index_of(SinglyLinkedList *list, void *data, size_t *index) {
  if (list == NULL || index == NULL) {
    return EINVAL;
  }

  SinglyLinkedListNode *node = list->first;
  size_t i = 0;
  while (node != NULL && node->data != data) {
    node = node->next;
    i += 1;
  }

  if (node == NULL) {
    return ENODATA;
  }

  *index = i;

  return 0;
}
