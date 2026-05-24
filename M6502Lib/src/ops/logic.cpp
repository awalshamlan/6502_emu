#include "M6502/cpu.h"

void CPU::AND(Byte operand) {
  A &= operand;
  SetZN(A);
}

void CPU::EOR(Byte operand) {
  A ^= operand;
  SetZN(A);
}

void CPU::BIT(Byte operand) {
  Byte result = A & operand;
  SetFlag(ZERO_FLAG, (result == 0));
  SetFlag(OVERFLOW_FLAG, (operand & OVERFLOW_FLAG) != 0);
  SetFlag(NEGATIVE_FLAG, (operand & NEGATIVE_FLAG) != 0);
}

void CPU::ORA(Byte operand) {
  A |= operand;
  SetZN(A);
}

// AND Handlers
void CPU::AND_IM() { AND(FetchByte()); }
void CPU::AND_ZP() { AND(ReadZeroPageOperand()); }
void CPU::AND_ZPX() { AND(ReadZeroPageXOperand()); }
void CPU::AND_ABS() { AND(ReadAbsoluteOperand()); }
void CPU::AND_ABSX() { AND(ReadAbsoluteXOperand()); }
void CPU::AND_ABSY() { AND(ReadAbsoluteYOperand()); }
void CPU::AND_INDX() { AND(ReadIndexedIndirectOperand()); }
void CPU::AND_INDY() { AND(ReadIndirectIndexedOperand()); }

// EOR Handlers
void CPU::EOR_IM() { EOR(FetchByte()); }
void CPU::EOR_ZP() { EOR(ReadZeroPageOperand()); }
void CPU::EOR_ZPX() { EOR(ReadZeroPageXOperand()); }
void CPU::EOR_ABS() { EOR(ReadAbsoluteOperand()); }
void CPU::EOR_ABSX() { EOR(ReadAbsoluteXOperand()); }
void CPU::EOR_ABSY() { EOR(ReadAbsoluteYOperand()); }
void CPU::EOR_INDX() { EOR(ReadIndexedIndirectOperand()); }
void CPU::EOR_INDY() { EOR(ReadIndirectIndexedOperand()); }

// BIT Handlers
void CPU::BIT_ZP() { BIT(ReadZeroPageOperand()); }
void CPU::BIT_ABS() { BIT(ReadAbsoluteOperand()); }

// ORA Handlers
void CPU::ORA_IM() { ORA(FetchByte()); }
void CPU::ORA_ZP() { ORA(ReadZeroPageOperand()); }
void CPU::ORA_ZPX() { ORA(ReadZeroPageXOperand()); }
void CPU::ORA_ABS() { ORA(ReadAbsoluteOperand()); }
void CPU::ORA_ABSX() { ORA(ReadAbsoluteXOperand()); }
void CPU::ORA_ABSY() { ORA(ReadAbsoluteYOperand()); }
void CPU::ORA_INDX() { ORA(ReadIndexedIndirectOperand()); }
void CPU::ORA_INDY() { ORA(ReadIndirectIndexedOperand()); }
