#include "M6502/cpu.h"

void CPU::ADC(Byte operand) {
  const Byte oldA = A;
  const Word result = A + GetFlag(CARRY_FLAG) + operand;
  A = (result & 0xFF);
  SetFlag(CARRY_FLAG, result > 0xFF);
  SetZN(A);
  SetFlag(OVERFLOW_FLAG, (~(oldA ^ operand) & (oldA ^ A) & NEGATIVE_FLAG) != 0);
}

void CPU::SBC(Byte operand){
  ADC(~operand);
}


void CPU::CMP(Byte reg, Byte operand) {
  Byte result = reg - operand;

  SetFlag(CARRY_FLAG, reg >= operand);
  SetFlag(ZERO_FLAG, reg == operand);
  SetFlag(NEGATIVE_FLAG, (result & NEGATIVE_FLAG) != 0);
}

// ADC Start
void CPU::ADC_IM() { ADC(FetchByte()); }
void CPU::ADC_ZP() { ADC(ReadZeroPageOperand()); }
void CPU::ADC_ZPX() { ADC(ReadZeroPageXOperand()); }
void CPU::ADC_ABS() { ADC(ReadAbsoluteOperand()); }
void CPU::ADC_ABSX() { ADC(ReadAbsoluteXOperand()); }
void CPU::ADC_ABSY() { ADC(ReadAbsoluteYOperand()); }
void CPU::ADC_INDX() { ADC(ReadIndexedIndirectOperand()); }
void CPU::ADC_INDY() { ADC(ReadIndirectIndexedOperand()); }

// SBC Start
void CPU::SBC_IM() { SBC(FetchByte()); }
void CPU::SBC_ZP() { SBC(ReadZeroPageOperand()); }
void CPU::SBC_ZPX() { SBC(ReadZeroPageXOperand()); }
void CPU::SBC_ABS() { SBC(ReadAbsoluteOperand()); }
void CPU::SBC_ABSX() { SBC(ReadAbsoluteXOperand()); }
void CPU::SBC_ABSY() { SBC(ReadAbsoluteYOperand()); }
void CPU::SBC_INDX() { SBC(ReadIndexedIndirectOperand()); }
void CPU::SBC_INDY() { SBC(ReadIndirectIndexedOperand()); }


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