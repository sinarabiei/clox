#include "../src/chunk.h"

#include "common.h"

void test_chunk() {
  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 256; i++) {
    writeConstant(&chunk, 1.2, 123);
  }
  writeConstant(&chunk, 2.4, 124);
  writeChunk(&chunk, OP_RETURN, 124);  
  assert(chunk.code[0] == OP_CONSTANT);
  assert(chunk.code[2] == OP_CONSTANT);
  assert(chunk.code[510] == OP_CONSTANT);
  assert(chunk.code[512] == OP_CONSTANT_LONG);
  assert(chunk.code[516] == OP_RETURN);
  assert(IS_EQUAL(chunk.constants.values[0], 1.2));
  assert(IS_EQUAL(chunk.constants.values[2], 1.2));
  assert(IS_EQUAL(chunk.constants.values[255], 1.2));
  assert(IS_EQUAL(chunk.constants.values[256], 2.4));
  assert(getLine(&chunk, 0) == 123);
  assert(getLine(&chunk, 2) == 123);
  assert(getLine(&chunk, 510) == 123);
  assert(getLine(&chunk, 512) == 124);
  assert(getLine(&chunk, 516) == 124);
  freeChunk(&chunk);
}
