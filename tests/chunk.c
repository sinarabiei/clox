#include "../src/chunk.h"

#include "common.h"

void test_chunk() {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  assert(chunk.code[0] == OP_CONSTANT);
  assert(chunk.code[2] == OP_RETURN);
  assert(IS_EQUAL(chunk.constants.values[0], 1.2));
  assert(getLine(&chunk, 0) == 123);
  assert(getLine(&chunk, 2) == 123);
  freeChunk(&chunk);
}
