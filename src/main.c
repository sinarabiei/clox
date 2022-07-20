#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  for (int i = 0; i < 256; i++) {
    writeConstant(&chunk, 1.2, 123);
  }
  writeConstant(&chunk, 2.4, 124);
  writeChunk(&chunk, OP_RETURN, 124);
  disassembleChunk(&chunk, "test chunk");  
  freeChunk(&chunk);
  return 0;
}
