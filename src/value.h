#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

/**
 * @brief Constants pool.
 */
typedef struct {
  clox_count_t capacity;
  clox_count_t count;
  Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

#endif // clox_value_h
