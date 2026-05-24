#include "M6502/cpu.h"

void CPU::LSR(Word address) {
  Byte operand = ReadByte(address);
  SetFlag(CARRY_FLAG,
          (operand & CARRY_FLAG) != 0); // cursed but technically correct
  operand >>= 1;
  Cycles--;
  WriteByte(address, operand);
  SetZN(operand);
}

// LSR Handlers
void CPU::LSR_AC() {
  SetFlag(CARRY_FLAG, (A & 0x01) != 0);
  A >>= 1;
  Cycles--;
  SetZN(A);
}
void CPU::LSR_ZP() { LSR(FetchByte()); }

void CPU::LSR_ZPX() {
  Byte zeroPageAddress = FetchByte();
  zeroPageAddress += X;
  Cycles--;
  LSR(zeroPageAddress);
}

void CPU::LSR_ABS() { LSR(FetchWord()); }

void CPU::LSR_ABSX() {
  Word absoluteAddress = FetchWord();
  absoluteAddress += X;
  Cycles--;
  LSR(absoluteAddress);
}