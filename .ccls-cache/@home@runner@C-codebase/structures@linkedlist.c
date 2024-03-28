#include "linkedlist.h"

LinkedListNode linkedlist_node_create(LinkedListData data) {
  return (LinkedListNode){.data = data, .next = NULL};
}

LinkedList linkedlist_create(LinkedListNode *head) {
  return (LinkedList){.head = head};
}

LinkedListNode *linkedlist_get_tail(LinkedList *list) {
  LinkedListNode *cur = list->head;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  return cur;
}

void linkedlist_add(LinkedList *list, LinkedListNode *node) {
  linkedlist_get_tail(list)->next = node;
}

void linkedlist_print(LinkedList *list) {
  LinkedListNode *cur = list->head;
  while (cur->next != NULL) {
    printf("%d\n", cur->data.i32_val);
    cur = cur->next;
  }
  printf("%d\n", cur->data.i32_val);
}