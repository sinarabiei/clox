#include "../src/line.h"

#include "common.h"

void test_initLineArray() {
  LineArray array;
  initLineArray(&array);
  assert(array.count == 0);
  assert(array.capacity == 0);
  assert(array.lines == NULL);
}

void test_writeLineArray() {
  LineArray array;
  initLineArray(&array);

  writeLineArray(&array, 1);
  assert(array.count == 1);
  assert(array.capacity == 8);
  assert(array.lines[0] == 1);

  writeLineArray(&array, 8);
  assert(array.count == 8);
  assert(array.capacity == 8);
  assert(array.lines[7] == 1);

  writeLineArray(&array, 9);
  assert(array.count == 9);
  assert(array.capacity == 16);
  assert(array.lines[8] == 1);

  writeLineArray(&array, 1);
  assert(array.count == 9);
  assert(array.capacity == 16);
  assert(array.lines[0] == 2);

  freeLineArray(&array);
}
