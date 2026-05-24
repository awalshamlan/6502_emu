#include "M6502/cpu.h"

void CPU::DEC(Word address) {
  Byte value = ReadByte(address);
  value--;
  Cycles--;
  WriteByte(address, value);
  SetZN(value);
}

void CPU::INC(Word address) {
  Byte value = ReadByte(address);
  value++;
  Cycles--;
  WriteByte(address, value);
  SetZN(value);
}

void CPU::DEC_ZP() { DEC(FetchByte()); }

void CPU::DEC_ZPX() {
  Byte address = FetchByte() + X;
  Cycles--;
  DEC(address);
}

void CPU::DEC_ABS() { DEC(FetchWord()); }

void CPU::DEC_ABSX() {
  Word address = FetchWord() + X;
  Cycles--;
  DEC(address);
}

void CPU::DEX() {
  X--;
  Cycles--;
  SetZN(X);
}

void CPU::DEY() {
  Y--;
  Cycles--;
  SetZN(Y);
}

void CPU::INC_ZP() { INC(FetchByte()); }

void CPU::INC_ZPX() {
  Byte address = FetchByte() + X;
  Cycles--;
  INC(address);
}

void CPU::INC_ABS() { INC(FetchWord()); }

void CPU::INC_ABSX() {
  Word address = FetchWord() + X;
  Cycles--;
  INC(address);
}

void CPU::INX() {
  X++;
  Cycles--;
  SetZN(X);
}

void CPU::INY() {
  Y++;
  Cycles--;
  SetZN(Y);
}