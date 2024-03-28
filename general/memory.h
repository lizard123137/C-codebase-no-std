#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "io.h"

#define HEAP_CAP 640000
#define CHUNK_LIST_CAP 1024

typedef struct {
  u8 *start;
  u32 size;
} Heap_Chunk;

typedef struct {
  u32 count;
  Heap_Chunk chunks[CHUNK_LIST_CAP];
} Heap_Chunk_List;

i32 chunk_list_find(const Heap_Chunk_List *list, void *ptr);
void chunk_list_insert(Heap_Chunk_List *list, void *ptr, u32 size);
void chunk_list_remove(Heap_Chunk_List *list, u32 index);
void chunk_list_dump(Heap_Chunk_List *list);

void *heap_alloc(u32 size);
void heap_free(void *ptr);
void heap_collect(void);
void *heap_memset(void *dest, u32 val, u32 len);

void heap_debug_dump(void);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H