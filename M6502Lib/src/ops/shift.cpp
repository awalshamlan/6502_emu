#include "M6502/cpu.h"

void CPU::ASL(Word address)
{
  Byte operand = ReadByte(address);
  SetFlag(CARRY_FLAG, (operand & CARRY_FLAG) != 0);
  operand *= 2;
  Cycles--;
  WriteByte(address, operand);
  SetZN(operand);
}

void CPU::LSR(Word address)
{
  Byte operand = ReadByte(address);
  SetFlag(CARRY_FLAG, (operand & CARRY_FLAG) != 0);
  operand >>= 1;
  Cycles--;
  WriteByte(address, operand);
  SetZN(operand);
}

// ASL Start

// LSR Start
void CPU::LSR_AC()
{
  SetFlag(CARRY_FLAG, (A & 0x01) != 0);
  A >>= 1;
  Cycles--;
  SetZN(A);
}
void CPU::LSR_ZP() { LSR(FetchByte()); }
void CPU::LSR_ZPX() { LSR(ResolveZeroPageXAddress()); }
void CPU::LSR_ABS() { LSR(FetchWord()); }
void CPU::LSR_ABSX() { LSR(ResolveAbsoluteXAddress()); }