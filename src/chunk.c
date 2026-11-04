#include "chunk.h"
#include "check.h"
#include "memory.h"
#include "src/common.h"
#include "src/value.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    clox_count_t oldCount = chunk->capacity;
    if (grow_capacity(&chunk->capacity, chunk->capacity)) {
      ABORT();
    }
    clox_count_t newCount = chunk->capacity;
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCount, newCount);
    chunk->lines = GROW_ARRAY(int, chunk->lines, oldCount, newCount);
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  initChunk(chunk);
  freeValueArray(&chunk->constants);
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
