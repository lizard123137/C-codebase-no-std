#include "hashtable.h"

Hashtable *hashtable_alloc(u32 size) {
  Hashtable *hash =
      heap_alloc(sizeof(Hashtable) + sizeof(Hashtable_Data) * size);
  hash->size = size;

  return hash;
}

void hashtable_free(Hashtable *table) { heap_free(table); }

u32 hashtable_hash(Hashtable *table, u8 *name) {
  u32 len = strnlen(name, MAX_NAME);
  u32 sum = 0;

  for (u32 i = 0; i < len; ++i) {
    sum += name[i];
    sum *= name[i];
  }

  return hash(sum) % table->size;
}

i32 hashtable_insert(Hashtable *table, Hashtable_Data *ptr) {
  if (ptr == NULL)
    return -1;
  int index = hashtable_hash(table, ptr->name);
  if (table->data[index] != NULL) {
    return -1;
  }

  table->data[index] = ptr;
  return index;
}

Hashtable_Data *hashtable_delete(Hashtable *table, u8 *name) {
  int index = hashtable_hash(table, name);
  if (table->data[index] != NULL) {
    Hashtable_Data *temp = table->data[index];
    table->data[index] = NULL;
    return temp;
  }
  return NULL;
}

Hashtable_Data *hashtable_peek(Hashtable *table, u8 *name) {
  Hashtable_Data *res = table->data[hashtable_hash(table, name)];
  if (res == NULL)
    return NULL;
  return res;
}

void hashtable_print(Hashtable *table) {
  printf("Hashtable (%u):\n", table->size);
  for (u32 i = 0; i < table->size; ++i) {
    if (table->data[i] != NULL)
      printf("%u\t%s\t", i, table->data[i]->name);
    else
      printf("%u\t---\n", i);
  }
}