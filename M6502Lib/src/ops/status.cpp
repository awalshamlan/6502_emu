#include "M6502/cpu.h"

void CPU::CLC() {
  SetFlag(CARRY_FLAG, false);
  Cycles--;
}

void CPU::CLD() {
  SetFlag(DECIMAL_FLAG, false);
  Cycles--;
}

void CPU::CLI() {
  SetFlag(INTERRUPT_FLAG, false);
  Cycles--;
}

void CPU::CLV() {
  SetFlag(OVERFLOW_FLAG, false);
  Cycles--;
}
