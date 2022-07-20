#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initLineArray(&chunk->lines);
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeLineArray(&chunk->lines);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t,
			     chunk->code,
			     oldCapacity,
			     chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  writeLineArray(&chunk->lines, line);
  chunk->count++;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int constant = addConstant(chunk, value);
  if (constant < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constant , line);
  } else {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, (constant >> 16)  & 255, line);
    writeChunk(chunk, (constant >> 8) & 255, line);
    writeChunk(chunk, constant & 255, line);
  }
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int offset) {
  int total = 0;
  for (int i = 0; i < chunk->lines.count; i++) {
    total += chunk->lines.lines[i];
    if (offset < total) return i + 1;
  }
  exit(1);
}
