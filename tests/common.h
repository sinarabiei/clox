#ifndef tests_common_h
#define tests_common_h

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define EPSILON 0.00001

#define IS_EQUAL(lhs, rhs) \
  abs((lhs) - (rhs)) < EPSILON

#endif
