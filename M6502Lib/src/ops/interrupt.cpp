#include "M6502/cpu.h"

void CPU::BRK() {
  FetchByte(); // Padding
  PushWord(ProgramCounter);
  PushByte(Status | UNUSED_FLAG | BREAK_FLAG);
  SetFlag(INTERRUPT_FLAG, true);
  ProgramCounter = ReadWord(INTERRUPT_VECTOR);
}