#include "M6502/cpu.h"

void CPU::CMP(Byte reg, Byte operand) {
  Byte result = reg - operand;

  SetFlag(CARRY_FLAG, reg >= operand);
  SetFlag(ZERO_FLAG, reg == operand);
  SetFlag(NEGATIVE_FLAG, (result & NEGATIVE_FLAG) != 0);
}

// CMP Start
void CPU::CMP_IM() { CMP(A, FetchByte()); }

void CPU::CMP_ZP() { CMP(A, ReadZeroPageOperand()); }

void CPU::CMP_ZPX() { CMP(A, ReadZeroPageXOperand()); }

void CPU::CMP_ABS() { CMP(A, ReadAbsoluteOperand()); }

void CPU::CMP_ABSX() { CMP(A, ReadAbsoluteXOperand()); }

void CPU::CMP_ABSY() { CMP(A, ReadAbsoluteYOperand()); }

void CPU::CMP_INDX() { CMP(A, ReadIndexedIndirectOperand()); }

void CPU::CMP_INDY() { CMP(A, ReadIndirectIndexedOperand()); }

// CPX Start
void CPU::CPX_IM() { CMP(X, FetchByte()); }

void CPU::CPX_ZP() { CMP(X, ReadZeroPageOperand()); }

void CPU::CPX_ABS() { CMP(X, ReadAbsoluteOperand()); }

// CPY Start
void CPU::CPY_IM() { CMP(Y, FetchByte()); }

void CPU::CPY_ZP() { CMP(Y, ReadZeroPageOperand()); }

void CPU::CPY_ABS() { CMP(Y, ReadAbsoluteOperand()); }