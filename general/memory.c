#include "memory.h"

u8 heap[HEAP_CAP] = {0};

Heap_Chunk_List alloced_chunks = {0};
Heap_Chunk_List freed_chunks = {
    .count = 1, .chunks = {[0] = {.start = heap, .size = sizeof(heap)}}};

i32 chunk_list_find(const Heap_Chunk_List *list, void *ptr) {
  for (u32 i = 0; i < list->count; ++i) {
    if (list->chunks[i].start == ptr)
      return i;
  }
  return -1;
}

void chunk_list_insert(Heap_Chunk_List *list, void *ptr, u32 size) {
  Assert(list->count < CHUNK_LIST_CAP);
  list->chunks[list->count].start = ptr;
  list->chunks[list->count].size = size;

  for (u32 i = list->count;
       i > 0 && list->chunks[i].start < list->chunks[i - 1].start; --i) {
    const Heap_Chunk t = list->chunks[i];
    list->chunks[i] = list->chunks[i - 1];
    list->chunks[i - 1] = t;
  }

  list->count += 1;
}

void chunk_list_remove(Heap_Chunk_List *list, u32 index) {
  Assert(index < list->count);
  for (u32 i = index; i < list->count - 1; ++i) {
    list->chunks[i] = list->chunks[i + 1];
  }
  list->count -= 1;
}

void chunk_list_dump(Heap_Chunk_List *list) {
  printf("Chunks (%u):\n", list->count);
  for (u32 i = 0; i < list->count; ++i) {
    printf("start: %p, size: %u\n", list->chunks[i].start,
           list->chunks[i].size);
  }
}

void *heap_alloc(u32 size) {
  if (size == 0)
    return NULL;

  for (u32 i = 0; i < freed_chunks.count; ++i) {
    const Heap_Chunk chunk = freed_chunks.chunks[i];
    if (chunk.size >= size) {

      chunk_list_remove(&freed_chunks, i);

      const u32 tail_size = chunk.size - size;
      chunk_list_insert(&alloced_chunks, chunk.start, size);

      if (tail_size > 0) {
        chunk_list_insert(&freed_chunks, chunk.start + size, tail_size);
      }

      return chunk.start;
    }
  }

  return NULL;
}

void heap_free(void *ptr) {
  const i32 index = chunk_list_find(&alloced_chunks, ptr);
  Assert(index >= 0);
  chunk_list_insert(&freed_chunks, alloced_chunks.chunks[index].start,
                    alloced_chunks.chunks[index].size);
  chunk_list_remove(&alloced_chunks, (u32)index);
  heap_collect();
}

void heap_collect(void) {
  if (freed_chunks.count <= 1)
    return;

  for (u32 i = 0; i < freed_chunks.count - 1; ++i) {
    Heap_Chunk cur = freed_chunks.chunks[i];
    Heap_Chunk next = freed_chunks.chunks[i + 1];

    if (cur.start + cur.size == next.start) {
      u8 *start = cur.start;
      u32 size = cur.size + next.size;

      chunk_list_remove(&freed_chunks,
                        chunk_list_find(&freed_chunks, next.start));
      chunk_list_remove(&freed_chunks,
                        chunk_list_find(&freed_chunks, cur.start));
      chunk_list_insert(&freed_chunks, start, size);
    }
  }
}

void *heap_memset(void *dest, u32 val, u32 len) {
  u8 *ptr = (u8 *)dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void heap_debug_dump(void) {
  chunk_list_dump(&alloced_chunks);
  chunk_list_dump(&freed_chunks);
}