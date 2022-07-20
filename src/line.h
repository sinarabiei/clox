#ifndef clox_line_h
#define clox_line_h

typedef struct {
  int capacity;
  int count;
  int *lines;
} LineArray;

void initLineArray(LineArray *array);
void writeLineArray(LineArray *array, int line);
void freeLineArray(LineArray *array);

#endif
