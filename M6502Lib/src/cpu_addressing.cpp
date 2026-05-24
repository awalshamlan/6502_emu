#include "M6502/cpu.h"

Byte CPU::ReadZeroPageOperand() {
  Byte zeroPageAddress = FetchByte();
  return ReadByte(zeroPageAddress);
}

Byte CPU::ReadZeroPageXOperand() {
  Byte zeroPageAddress = FetchByte();
  zeroPageAddress += X;
  Cycles--;
  return ReadByte(zeroPageAddress);
}

Byte CPU::ReadZeroPageYOperand() {
  Byte zeroPageAddress = FetchByte();
  zeroPageAddress += Y;
  Cycles--;
  return ReadByte(zeroPageAddress);
}

Byte CPU::ReadAbsoluteOperand() {
  Word absoluteAddress = FetchWord();
  return ReadByte(absoluteAddress);
}

Byte CPU::ReadAbsoluteXOperand(bool pageCrossPenalty) {
  Word absoluteAddress = FetchWord();
  Word effectiveAddress = absoluteAddress + X;
  if (pageCrossPenalty && (absoluteAddress >> 8 != effectiveAddress >> 8))
    Cycles--;
  return ReadByte(effectiveAddress);
}

Byte CPU::ReadAbsoluteYOperand(bool pageCrossPenalty) {
  Word absoluteAddress = FetchWord();
  Word effectiveAddress = absoluteAddress + Y;
  if (pageCrossPenalty && (absoluteAddress >> 8 != effectiveAddress >> 8))
    Cycles--;
  return ReadByte(effectiveAddress);
}

// Uses X register
Byte CPU::ReadIndexedIndirectOperand() {
  Byte operand = FetchByte();
  Byte pointerLocation = operand + X;
  Cycles--;
  Word effectiveAddress = ReadWordFromZeroPage(pointerLocation);
  return ReadByte(effectiveAddress);
}

Byte CPU::ReadIndirectIndexedOperand(bool pageCrossPenalty) {
  Byte pointerLocation = FetchByte();
  Word pointer = ReadWordFromZeroPage(pointerLocation);
  Word effectiveAddress = pointer + Y;
  if (pageCrossPenalty && (pointer >> 8 != effectiveAddress >> 8))
    Cycles--;
  return ReadByte(effectiveAddress);
}