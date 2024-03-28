#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../general/base.h"
#include "../general/io.h"

typedef struct {
  union {
    u8 u8_val;
    u16 u16_val;
    u32 u32_val;
    u64 u64_val;

    i8 i8_val;
    i16 i16_val;
    i32 i32_val;
    i64 i64_val;

    f32 f32_val;
    f64 f64_val;

    void *any;
  };
} LinkedListData;

typedef struct _LinkedListNode {
  LinkedListData data;
  struct _LinkedListNode *next;
} LinkedListNode;

typedef struct {
  LinkedListNode *head;
} LinkedList;

LinkedListNode linkedlist_node_create(LinkedListData data);

LinkedList linkedlist_create(LinkedListNode *head);
LinkedListNode *linkedlist_get_tail(LinkedList *list);
void linkedlist_add(LinkedList *list, LinkedListNode *node);
void linkedlist_print(LinkedList *list);

#endif // LINKEDLIST_H