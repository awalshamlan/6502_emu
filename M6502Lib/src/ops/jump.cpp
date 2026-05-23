#include "M6502/cpu.h"

void CPU::JSR() {
  Word subroutineAddress = FetchWord();
  PushWord(ProgramCounter - 1);
  ProgramCounter = subroutineAddress;
  Cycles--;
}