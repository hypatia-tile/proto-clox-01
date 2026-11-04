#ifndef clox_debug_h
#define clox_debug_h

#include "common.h"
#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name);
clox_count_t disassembleInstruction(Chunk *chunk, clox_count_t offset);

#endif // clox_debug_h

