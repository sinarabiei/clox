#ifndef clox_emulate_h
#define clox_emulate_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk *chunk;
  uint8_t *ip; // instruction pointer (program counter)
  Value stack[STACK_MAX];
  Value *stackTop;
} Emulator;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initEmulator();
void freeEmulator();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
