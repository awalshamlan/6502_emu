#include "M6502/cpu.h"
#include "M6502/types.h"

void CPU::BIT_ZP() {
  Byte testTarget = ReadZeroPageOperand();
  Byte result = A & testTarget;
  SetFlag(ZERO_FLAG, (result == 0));
  SetFlag(OVERFLOW_FLAG, (testTarget & OVERFLOW_FLAG) == 1);
  SetFlag(NEGATIVE_FLAG, (testTarget & NEGATIVE_FLAG) == 1);
}

void CPU::BIT_ABS() {
  Byte testTarget = ReadAbsoluteOperand();
  Byte result = A & testTarget;
  SetFlag(ZERO_FLAG, (result == 0));
  SetFlag(OVERFLOW_FLAG, (testTarget & OVERFLOW_FLAG) == 1);
  SetFlag(NEGATIVE_FLAG, (testTarget & NEGATIVE_FLAG) == 1);
}