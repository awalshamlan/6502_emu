#include "M6502/cpu.h"

void CPU::ADC(Byte value) {
  const Byte oldA = A;
  const Word result = A + GetFlag(CARRY_FLAG) + value;
  A = (result & 0xFF);
  ADCSetFlags(oldA, value, result);
}

void CPU::ADCSetFlags(Byte oldA, Byte operand, Word result) {
  SetFlag(CARRY_FLAG, result > 0xFF);
  SetFlag(ZERO_FLAG, A == 0);
  SetFlag(NEGATIVE_FLAG, (A & NEGATIVE_FLAG) != 0);
  SetFlag(OVERFLOW_FLAG, (~(oldA ^ operand) & (oldA ^ A) & NEGATIVE_FLAG) != 0);
}

void CPU::ADC_IM() { ADC(FetchByte()); }

void CPU::ADC_ZP() { ADC(ReadZeroPageOperand()); }

void CPU::ADC_ZPX() { ADC(ReadZeroPageXOperand()); }

void CPU::ADC_ABS() { ADC(ReadAbsoluteOperand()); }

void CPU::ADC_ABSX() { ADC(ReadAbsoluteXOperand()); }

void CPU::ADC_ABSY() { ADC(ReadAbsoluteYOperand()); }

void CPU::ADC_INDX() { ADC(ReadIndexedIndirectOperand()); }

void CPU::ADC_INDY() { ADC(ReadIndirectIndexedOperand()); }
