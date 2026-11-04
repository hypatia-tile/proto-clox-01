#include "chunk.h"
#include "common.h"
#include "opcode.h"
#include "debug.h"
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  printf("hello, clox\n");
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, 4.2);
  writeChunk(&chunk, OP_CONSTANT, 126);
  writeChunk(&chunk, constant, 126);
  constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 127);
  writeChunk(&chunk, constant, 127);
  writeChunk(&chunk, OP_RETURN, 127);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
