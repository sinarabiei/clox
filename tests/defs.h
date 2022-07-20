#ifndef tests_defs_h
#define tests_defs_h

#define TEST(test) \
  count++; \
  printf("test "#test" ... "); \
  (test)(); \
  printf("\033[0;32mok\033[0m\n")

#endif
