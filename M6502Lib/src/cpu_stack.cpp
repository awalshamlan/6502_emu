#include "M6502/cpu.h"

void CPU::PushByte(Byte value) {
  (*Memory)[STACK_BASE + StackPointer] = value;
  StackPointer--;
  Cycles--;
}

void CPU::PushWord(Word value) {
  PushByte(((value >> 8) & 0xFF));
  PushByte((value & 0xFF));
}

Byte CPU::PullByte(){
  StackPointer++;
  Byte value = (*Memory)[STACK_BASE + StackPointer];
  Cycles--;
  return value;
}