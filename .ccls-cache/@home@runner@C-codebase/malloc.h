#ifndef MALLOC_H
#define MALLOC_H

#include "base.h"
#define HEAP_CAPACITY 640000

function void *heap_alloc(u32 size);
function void heap_free(void *ptr);
function void heap_collect();

#endif // MALLOC_H