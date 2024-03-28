#define ENABLE_ASSERT 1

#include "general/base.h"
#include "general/bits.h"
#include "general/io.h"
#include "general/memory.h"
#include "string/string.h"
#include "structures/hashtable.h"
#include "structures/linkedlist.h"
#include "structures/matrix.h"

// TODO: Add IO
//           - Fix putchar (not always reacting to \t \n etc.)
//           - Add support for other architectures
//           - Fix printf binary representation
//           - Add all types to printf
//           - Fix structPrint
// TODO: Add string operations
// TODO: Add more math functions
// TODO: Add more linkedlist functionality

// TODO: Fix hashtable collisions
// TODO: Fix Pow function

// TODO: Document library usage

// CHECK: Check memory fragmentation in alloc()

i32 main(void) {
  printf("numbers: %d, %d \n", 2, 5);
  printf("numbers:\t%f %lf %x", 2.0, 56.24, 0xffff);

  // heap_debug_dump();

  return 0;
}