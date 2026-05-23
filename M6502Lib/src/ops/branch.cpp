#include "M6502/cpu.h"

void CPU::Branch(bool branchFlag) {
  SignedByte offset = FetchByte(); // Signed because we can go backwards
  Word originalProgramCounter = ProgramCounter;
  if (branchFlag) {
    ProgramCounter += offset;
    Cycles--;
    if (ProgramCounter >> 8 != originalProgramCounter >> 8)
      Cycles--;
  }
}

void CPU::BCC() { Branch(!GetFlag(CARRY_FLAG)); }

void CPU::BCS() { Branch(GetFlag(CARRY_FLAG)); }

void CPU::BVC() { Branch(!GetFlag(OVERFLOW_FLAG)); }

void CPU::BVS() { Branch(GetFlag(OVERFLOW_FLAG)); }

void CPU::BEQ() { Branch(GetFlag(ZERO_FLAG)); }

void CPU::BNE() { Branch(!GetFlag(ZERO_FLAG)); }

void CPU::BMI() { Branch(GetFlag(NEGATIVE_FLAG)); }

void CPU::BPL() { Branch(!GetFlag(NEGATIVE_FLAG)); }
