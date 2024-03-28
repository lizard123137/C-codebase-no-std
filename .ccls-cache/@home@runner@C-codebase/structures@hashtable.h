#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../general/base.h"
#include "../general/io.h"
#include "../general/memory.h"
#include "../string/string.h"

#define MAX_NAME 64

typedef struct {
  u8 name[MAX_NAME];
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
} Hashtable_Data;

typedef struct {
  u32 size;
  Hashtable_Data *data[];
} Hashtable;

Hashtable *hashtable_alloc(u32 size);
void hashtable_free(Hashtable *table);

u32 hashtable_hash(Hashtable *table, u8 *name);
i32 hashtable_insert(Hashtable *table, Hashtable_Data *ptr);
Hashtable_Data *hashtable_delete(Hashtable *table, u8 *name);
Hashtable_Data *hashtable_peek(Hashtable *table, u8 *name);
void hashtable_print(Hashtable *table);

#ifdef __cplusplus
}
#endif

#endif // HASHTABLE_H