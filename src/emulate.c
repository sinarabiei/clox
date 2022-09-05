#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "emulate.h"

Emulator emulator;

static void resetStack() {
  emulator.stackTop = emulator.stack;
}

void initEmulator() {
  resetStack();
}

void freeEmulator() {}

void push(Value value) {
  *emulator.stackTop = value;
  emulator.stackTop++;
}

Value pop() {
  emulator.stackTop--;
  return *emulator.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*emulator.ip++)
#define READ_CONSTANT() (emulator.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
  do { \
    double b = pop(); \
    double a = pop(); \
    push(a op b); \
  } while (false)
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = emulator.stack; slot < emulator.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(emulator.chunk,
			   (int)(emulator.ip - emulator.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction  = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_ADD: BINARY_OP(+); break;
    case OP_SUBTRACT: BINARY_OP(-); break;
    case OP_MULTIPLY: BINARY_OP(*); break;
    case OP_DIVIDE: BINARY_OP(/); break;
    case OP_NEGATE: push(-pop()); break;
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char *source) {
  compile(source);
  return INTERPRET_OK;
}
