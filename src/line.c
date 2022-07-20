#include <string.h>
#include <stdlib.h>

#include "line.h"
#include "memory.h"

void initLineArray(LineArray *array) {
  array->capacity = 0;
  array-> count = 0;
  array->lines = NULL;
}

void writeLineArray(LineArray *array, int line) {
  if (line <= 0) exit(1);
  while (array->capacity < line) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->lines = GROW_ARRAY(int,
			      array->lines,
			      oldCapacity,
			      array->capacity);
    memset(&array->lines[oldCapacity], 0, sizeof(int) * (array->capacity - oldCapacity));
  }
  line--;
  array->lines[line]++;
  if (array->count < line + 1) {
    array->count = line + 1;
  }
}

void freeLineArray(LineArray *array) {
  FREE_ARRAY(int, array->lines, array->capacity);
  initLineArray(array);
}
