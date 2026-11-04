#include "value.h"
#include "common.h"
#include "memory.h"
#include "src/check.h"

void initValueArray(ValueArray *array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    clox_count_t oldCount = array->capacity;
    if (grow_capacity(&array->capacity, oldCount)) {
      ABORT();
    }
    clox_count_t newCount = array->capacity;
    array->values = GROW_ARRAY(Value, array->values, oldCount, newCount);
  }
  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray *array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void printValue(Value value) {
  printf("%g", value);
}
