#include <stdio.h>
#include "defs.h"
#include "tests.h"


int main() {
  int count = 0;
  printf("\nrunning tests\n");
  TEST(test_initLineArray);
  TEST(test_writeLineArray);
  TEST(test_chunk);
  printf("\ntest result: \033[0;32mok\033[0m. %d passed;\n\n", count);
  return 0;
}
