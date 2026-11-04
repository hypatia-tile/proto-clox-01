#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

/**
 * @brief A sequence of bytecode virtual machine can execute.
 *
 * A Chunk has a dynamic array @ref code that holds the bytecode instructions
 * for the virtual machine. It can grow in size as needed to accommodate more
 * instructions.
 */
typedef struct {
  clox_count_t count;    ///< Count of bytes in the dynamic array @ref code.
  clox_count_t capacity; ///< Allocated size of dynamic array.
  uint8_t *code;         ///< Dynamic array of instructions
  int *lines; ///< Dynamic array of line numbers corresponding to each
              ///< instruction in @ref code.
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void freeChunk(Chunk *chunk);

#endif // clox_chunk_h
