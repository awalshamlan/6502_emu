#include "M6502/cpu.h"

void CPU::JMP(Word address) { ProgramCounter = address; }

void CPU::JMP_ABS() { JMP(FetchWord()); }
void CPU::JMP_IND() { JMP(ReadWord(FetchWord())); }

void CPU::JSR_ABS() {
  Word subroutineAddress = FetchWord();
  PushWord(ProgramCounter - 1);
  JMP(subroutineAddress);
  Cycles--;
}