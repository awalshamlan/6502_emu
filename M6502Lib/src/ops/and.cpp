#include "M6502/cpu.h"
#include "M6502/types.h"

void CPU::ANDSetFlags() {
  SetFlag(ZERO_FLAG, A == 0);
  SetFlag(NEGATIVE_FLAG, (A & NEGATIVE_FLAG) > 0);
}

void CPU::AND(Byte value) {
  A &= value;
  ANDSetFlags();
}

void CPU::AND_IM() { AND(FetchByte()); }

void CPU::AND_ZP() { AND(ReadZeroPageOperand()); }

void CPU::AND_ZPX() { AND(ReadZeroPageXOperand()); }

void CPU::AND_ABS() { AND(ReadAbsoluteOperand()); }

void CPU::AND_ABSX() { AND(ReadAbsoluteXOperand()); }

void CPU::AND_ABSY() { AND(ReadAbsoluteYOperand()); }

void CPU::AND_INDX() { AND(ReadIndexedIndirectOperand()); }

void CPU::AND_INDY() { AND(ReadIndirectIndexedOperand()); }
