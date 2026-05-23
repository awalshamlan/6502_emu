#include "M6502/cpu.h"

void CPU::LDA(Byte value) {
  A = value;
  LDASetFlags();
}

void CPU::LDASetFlags() {
  SetFlag(ZERO_FLAG, (A == 0));
  SetFlag(NEGATIVE_FLAG, (A & NEGATIVE_FLAG) > 0);
}

void CPU::LDA_IM() { LDA(FetchByte()); }

void CPU::LDA_ZP() { LDA(ReadZeroPageOperand()); }

void CPU::LDA_ZPX() { LDA(ReadZeroPageXOperand()); }

void CPU::LDA_ABS() { LDA(ReadAbsoluteOperand()); }

void CPU::LDA_ABSX() { LDA(ReadAbsoluteXOperand()); }

void CPU::LDA_ABSY() { LDA(ReadAbsoluteYOperand()); }

void CPU::LDA_INDX() { LDA(ReadIndexedIndirectOperand()); }

void CPU::LDA_INDY() { LDA(ReadIndirectIndexedOperand()); }
