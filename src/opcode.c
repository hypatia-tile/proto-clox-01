#include "opcode.h"
#include "check.h"

const char *opcodeName(Opcode instruction) {
  switch (instruction) {
  case OP_CONSTANT:
    return "OP_CONSTANT";
  case OP_RETURN:
    return "OP_RETURN";
  }
  ABORT();
}
