#include "chunk.h"
#include <criterion/criterion.h>


Test(test_chunk, init_chunk) {
  Chunk chunk;
  initChunk(&chunk);

  cr_assert_eq(chunk.count, 0, "Expected count to be 0, but got %td", chunk.count);
  cr_assert_eq(chunk.capacity, 0, "Expected capacity to be 0, but got %td", chunk.capacity);
  cr_assert_null(chunk.code, "Expected code to be NULL, but got %p", (void *)chunk.code);
  cr_assert_null(chunk.lines, "Expected lines to be NULL, but got %p", (void *)chunk.lines);
  cr_assert_eq(chunk.constants.count, 0, "Expected constants count to be 0, but got %td", chunk.constants.count);
  cr_assert_eq(chunk.constants.capacity, 0, "Expected constants capacity to be 0, but got %td", chunk.constants.capacity);
  cr_assert_null(chunk.constants.values, "Expected constants values to be NULL, but got %p", (void *)chunk.constants.values);
}
